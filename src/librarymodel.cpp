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
    if (!index.isValid() || index.row() < 0 || index.row() >= m_libraryItems.size())
        return QVariant();

    const QSharedPointer<LibraryItem> &msgPtr = m_libraryItems[index.row()];

    // QString debugMsg = QString("%1/%2").arg(index.row()).arg(role);
    // msgPtr->debug(debugMsg);

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

    // Get a random valid index
    int randomIndex = rand() % m_libraryItems.size();
    
    if (randomIndex >= 0 && randomIndex < m_libraryItems.size()) {
        // Get the item from the library
        QSharedPointer<LibraryItem> item = m_libraryItems[randomIndex];
        
        // Validate the pointer
        if (!item) {
            qWarning().noquote() << "Null library item at index" << randomIndex;
            return nullptr;
        }
        
        // Add to the recently accessed items queue to keep it alive
        // This is a critical step to ensure the object doesn't get destroyed
        // while QML is still using it
        m_recentlyAccessedItems.append(item);

        // Tell QML that C++ still owns the object
        QQmlEngine::setObjectOwnership(item.data(), QQmlEngine::CppOwnership);
        
        // Keep the queue at a reasonable size
        while (m_recentlyAccessedItems.size() > MAX_RECENT_ITEMS) {
            // Remove the oldest item from the queue
            m_recentlyAccessedItems.removeFirst();
        }
        
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
    
    // Validate the pointer
    if (!item) {
        qWarning().noquote() << "Null library item at index" << index;
        return nullptr;
    }
    
    // Cast away constness to update the recently accessed items
    LibraryModel* self = const_cast<LibraryModel*>(this);
    
    // Add to the recently accessed items queue to keep it alive
    self->m_recentlyAccessedItems.append(item);

    // Tell QML that C++ still owns the object
    QQmlEngine::setObjectOwnership(item.data(), QQmlEngine::CppOwnership);
    
    // Keep the queue at a reasonable size
    while (self->m_recentlyAccessedItems.size() > MAX_RECENT_ITEMS) {
        // Remove the oldest item from the queue
        self->m_recentlyAccessedItems.removeFirst();
    }
    
    qDebug() << "LibraryModel::getItem returning" << item->artist()
             << item->title();
             
    // Return raw pointer, but it's kept alive by item in m_recentlyAccessedItems
    return item.data();
}

void LibraryModel::releaseQmlReferences()
{
    // Log what we're releasing
    if (!m_recentlyAccessedItems.isEmpty()) {
        QStringList names;
        for (const QSharedPointer<LibraryItem> &item : m_recentlyAccessedItems) {
            if (!item.isNull()) {
                names << QString("%1 - %2").arg(item->artist(), item->title());
            }
        }
        
        if (!names.isEmpty()) {
            qDebug() << "LibraryModel::releaseQmlReferences - clearing" << names.size()
                     << "items:" << names.join(", ");
        }
    }
    
    // Clear all recently accessed items
    m_recentlyAccessedItems.clear();
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
