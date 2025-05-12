#include "librarymodel.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QColor>

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
    if (!index.isValid() || index.row() < 0 || index.row() >= m_libraryItems.size())
        return QVariant();

    const QSharedPointer<LibraryItem> &msgPtr = m_libraryItems[index.row()];

    QString debugMsg = QString("%1/%2").arg(index.row()).arg(role);
    msgPtr->debug(debugMsg);

    if (!msgPtr)
        return QVariant();

    switch (role) {
    case LibraryArtistRole:
        return msgPtr->artist();
    case LibraryTitleRole:
        return msgPtr->title();
    case LibraryCueStartRole:
        return msgPtr->cueStart();
    case LibraryCueIntroRole:
        return msgPtr->cueIntro();
    case LibraryCueMixRole:
        return msgPtr->cueMix();
    case LibraryCueEndRole:
        return msgPtr->cueEnd();
    case LibraryDurationRole:
        return msgPtr->duration();
    case LibraryFileNameRole:
        return msgPtr->fileName();
    case LibraryColorRole:
        return msgPtr->color();
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

    int randomIndex = rand() % m_libraryItems.size();
    return getItem(randomIndex);
}

QObject *LibraryModel::getItem(int index) const {
    if (index >= 0 && index < m_libraryItems.size())
        return m_libraryItems[index].data(); // return raw QObject* for QML
    return nullptr;
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

    beginInsertRows(QModelIndex(), 0, count);
    while (query.next()) {
        QString artist = query.value("artist").toString();
        QString title = query.value("title").toString();
        double duration = query.value("duration").toDouble();

        auto item = QSharedPointer<LibraryItem>::create(artist, title, 0.0, 0.0, 0.0, 0.0, duration, "red");
        m_libraryItems.append(item);
    }
    endInsertRows();

    db.close();

}
