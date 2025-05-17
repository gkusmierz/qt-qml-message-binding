#include "librarymodel.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QColor>
#include <QQmlEngine>

LibraryModel::LibraryModel(const QString &sqlitePath, QObject *parent)
    : QAbstractListModel(parent),
      m_sqlitePath(sqlitePath)
{
    initModel();

    // Random seed initialization
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    qDebug() << "LibraryModel::LibraryModel(" << m_sqlitePath << ")";
}

LibraryModel::~LibraryModel()
{
    qDebug() << "~LibraryModel::LibraryModel()";
}

int LibraryModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_libraryItems.count();
}

QVariant LibraryModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() > m_libraryItems.count())
        return QVariant();

    QSharedPointer<LibraryItem> item = m_libraryItems[index.row()];

    QString debugMsg = QString("%1/%2").arg(index.row()).arg(role);
    item->debug(debugMsg);

    switch (role) {
    case LibraryArtistRole:
        return item->artist();
    case LibraryTitleRole:
        return item->title();
    case LibraryCueStartRole:
        return item->cueStart();
    case LibraryCueIntroRole:
        return item->cueIntro();
    case LibraryCueMixRole:
        return item->cueMix();
    case LibraryCueEndRole:
        return item->cueEnd();
    case LibraryDurationRole:
        return item->duration();
    case LibraryFileNameRole:
        return item->fileName();
    case LibraryColorRole:
        return item->color();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> LibraryModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[LibraryArtistRole] = "artist";
    roles[LibraryTitleRole] = "title";
    roles[LibraryCueStartRole] = "cueStart";
    roles[LibraryCueIntroRole] = "cueIntro";
    roles[LibraryCueMixRole] = "cueMix";
    roles[LibraryCueEndRole] = "cueEnd";
    roles[LibraryDurationRole] = "duration";
    roles[LibraryFileNameRole] = "fileName";
    roles[LibraryColorRole] = "color";
    return roles;
}

QObject *LibraryModel::randomItem()
{
    if (m_libraryItems.isEmpty()) {
        qWarning().noquote() << "Library items are empty!";
        return nullptr;
    }

    // Get a random valid index
    int randomIndex = rand() % m_libraryItems.size();

    if (randomIndex >= 0 && randomIndex < m_libraryItems.size()) {
        // Get the item from the library
        QSharedPointer<LibraryItem> item = m_libraryItems[randomIndex];

        qDebug() << "LibraryModel::randomItem returning" << item->artist()
                 << item->title();

        // Return raw pointer, but it's kept alive by item in m_recentlyAccessedItems
        return item.data();
    }

    return nullptr;
}

QObject *LibraryModel::getItem(int index) const {
    // Safety check for index bounds
    if (index < 0 || index >= m_libraryItems.size()) {
        qWarning().noquote() << "Library item index out of bounds:" << index;
        return nullptr;
    }

    // Get the item from the library
    QSharedPointer<LibraryItem> item = m_libraryItems[index];

    qDebug() << "LibraryModel::getItem returning" << item->artist()
             << item->title();

    // Return raw pointer, but it's kept alive by item in m_recentlyAccessedItems
    return item.data();
}

QSqlDatabase LibraryModel::openDb(const QString &path, const char *connectionName) const
{
    QSqlDatabase db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"),
                                                QString::fromLatin1(connectionName));
    db.setDatabaseName(path);
    if (!db.open()) {
        qWarning().noquote() << "SQLite open failed:" << db.lastError().text();
    }
    return db;
}

void LibraryModel::initModel()
{
    QSqlDatabase db = openDb(m_sqlitePath, "LibraryModel");

    if (!db.isOpen()) {
        qWarning().noquote() << "Database is not open!";
        return;
    }

    QSqlQuery countQuery(db);
    if (!countQuery.exec("select count(*) as cnt from items")) {
        qWarning().noquote() << "Failed to execute query:" << countQuery.lastError().text();
        return;
    }

    if (!countQuery.next()) {
        qWarning().noquote() << "Failed to fetch count:" << countQuery.lastError().text();
        return;
    }

    int count = countQuery.value("cnt").toInt();

    QSqlQuery query(db);
    if (!query.exec("select artist, title, duration from items order by artist, title, duration")) {
        qWarning().noquote() << "Failed to execute query:" << query.lastError().text();
        return;
    }

    beginInsertRows(QModelIndex(), count, count);
    while (query.next()) {
        QString artist = query.value("artist").toString();
        QString title = query.value("title").toString();
        double duration = query.value("duration").toDouble();

        auto item = new LibraryItem{artist, title, 0.0, 0.0, 0.0, 0.0, duration, "red"};
        m_libraryItems.append(QSharedPointer<LibraryItem>(item));
    }
    endInsertRows();

    db.close();

}
