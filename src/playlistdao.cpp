#include "playlistdao.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QColor>

PlaylistDao::PlaylistDao(const QString &sqlitePath, QObject *parent)
    : QObject(parent),
      m_sqlitePath(sqlitePath)
{
    qDebug() << "PlaylistDao::PlaylistDao(" << m_sqlitePath << ")";
    fillPlaylistItems();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

PlaylistDao::~PlaylistDao()
{
    qDebug() << "~PlaylistDao::PlaylistDao()";
}

PlaylistItem* PlaylistDao::randomItem()
{
    if (m_playlistItems.isEmpty()) {
        qWarning().noquote() << "Playlist items are empty!";
        return nullptr;
    }

    int randomIndex = rand() % m_playlistItems.size();
    auto item = m_playlistItems[randomIndex];
    qDebug().noquote() << "Random item:" << item->artist() << item->title();
    return item.get();
}

QSqlDatabase PlaylistDao::openDb(const QString &path, const char *connectionName) const
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"),
                                                QString::fromLatin1(connectionName));
    db.setDatabaseName(path);
    if (!db.open()) {
        qWarning().noquote() << "SQLite open failed:" << db.lastError().text();
    }
    return db;
}

void PlaylistDao::fillPlaylistItems()
{
    QSqlDatabase db = openDb(m_sqlitePath, "PlaylistDao");

    if (!db.isOpen()) {
        qWarning().noquote() << "Database is not open!";
        return;
    }

    QSqlQuery query(db);
    if (!query.exec("select artist, title, duration from items order by artist, title, duration")) {
        qWarning().noquote() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString artist = query.value("artist").toString();
        QString title = query.value("title").toString();
        double duration = query.value("duration").toDouble();

        auto item = QSharedPointer<PlaylistItem>::create(artist, title, 0.0, 0.0, 0.0, 0.0, duration, "red");
        m_playlistItems.append(item);
    }

    db.close();

}
