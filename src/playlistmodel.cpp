#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent),
      m_playlistItems()
{
    // Random seed initialization
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    qDebug() << "PlaylistModel::PlaylistModel()";
}

PlaylistModel::~PlaylistModel()
{
    qDebug() << "~PlaylistModel::PlaylistModel()";
}

int PlaylistModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_playlistItems.count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() > m_playlistItems.count())
        return QVariant();

    const QSharedPointer<PlaylistItem> &msgPtr = m_playlistItems[index.row()];

    // Check for null pointer before accessing it
    if (!msgPtr) {
        qWarning() << "PlaylistModel::data - Null playlist item at index:" << index.row();
        return QVariant();
    }

    // QString debugMsg = QString("%1/%2").arg(index.row()).arg(role);
    // msgPtr->debug(debugMsg);

    switch (role) {
    case PlaylistArtistRole:

        return msgPtr->artist();
    case PlaylistTitleRole:
        return msgPtr->title();
    case PlaylistCueStartRole:
        return msgPtr->cueStart();
    case PlaylistCueIntroRole:
        return msgPtr->cueIntro();
    case PlaylistCueMixRole:
        return msgPtr->cueMix();
    case PlaylistCueEndRole:
        return msgPtr->cueEnd();
    case PlaylistDurationRole:
        return msgPtr->duration();
    case PlaylistProgressRole:
        return msgPtr->progress();
    case PlaylistFileNameRole:
        return msgPtr->fileName();
    case PlaylistColorRole:
        return msgPtr->color();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[PlaylistArtistRole] = "artist";
    roles[PlaylistTitleRole] = "title";
    roles[PlaylistCueStartRole] = "cueStart";
    roles[PlaylistCueIntroRole] = "cueIntro";
    roles[PlaylistCueMixRole] = "cueMix";
    roles[PlaylistCueEndRole] = "cueEnd";
    roles[PlaylistDurationRole] = "duration";
    roles[PlaylistProgressRole] = "progress";
    roles[PlaylistFileNameRole] = "fileName";
    roles[PlaylistColorRole] = "color";
    return roles;
}

void PlaylistModel::addPlaylistItem(const QString &artist,
                                    const QString &title,
                                    double cueStart,
                                    double cueIntro,
                                    double cueMix,
                                    double cueEnd,
                                    double duration,
                                    const QColor &color)
{
    // Validate inputs before creating a new item
    if (artist.isEmpty() && title.isEmpty()) {
        qWarning() << "PlaylistModel::addPlaylistItem - Empty artist and title";
        return;
    }

    try {
        // Create local copies of all values to ensure complete independence from source data
        QString artistCopy = QString(artist); // Force a deep copy
        QString titleCopy = QString(title);   // Force a deep copy

        // Color needs special handling to ensure it's a new instance
        QColor colorCopy(color.red(), color.green(), color.blue(), color.alpha());

        // Create a new shared pointer with proper exception handling
        // Use our copied values to ensure complete independence
        auto newItem = QSharedPointer<PlaylistItem>::create(
            artistCopy, titleCopy, cueStart, cueIntro, cueMix, cueEnd, duration, colorCopy);

        // Add only if the item was created successfully
        if (newItem) {
            // tell Qt we're about to add one row at the end:
            const int row = m_playlistItems.count();
            beginInsertRows(QModelIndex(), row, row);
            m_playlistItems.append(newItem);
            endInsertRows();

            qDebug() << "PlaylistModel::addPlaylistItem - Added new item:"
                     << artistCopy << titleCopy << duration;
        }
    } catch (const std::exception &e) {
        qWarning() << "PlaylistModel::addPlaylistItem - Exception creating item:" << e.what();
    }
}

void PlaylistModel::random(int index)
{
    // Check if index is valid before accessing the shared pointer
    if (index < 0 || index >= m_playlistItems.size()) {
        qWarning() << "PlaylistModel::random - Invalid index:" << index;
        return;
    }

    // Check if the shared pointer is valid
    const QSharedPointer<PlaylistItem> &item = m_playlistItems[index];
    if (!item) {
        qWarning() << "PlaylistModel::random - Null playlist item at index:" << index;
        return;
    }

    // set random progress between 0.0 and 1.0
    item->setProgress(static_cast<qreal>(rand()) / RAND_MAX);

    // set random color
    QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
    item->setColor(randomColor);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { PlaylistColorRole, PlaylistProgressRole });
}

void PlaylistModel::randomProgress()
{
    // Check if there are any items
    if (m_playlistItems.isEmpty()) return;

    // Select randomly one of items from m_playlistItems
    int index = rand() % m_playlistItems.size();

    // Check if the shared pointer is valid
    const QSharedPointer<PlaylistItem> &item = m_playlistItems[index];
    if (!item) {
        qWarning() << "PlaylistModel::randomProgress - Null playlist item at index:" << index;
        return;
    }

    // set random progress between 0.0 and 1.0
    item->setProgress(static_cast<qreal>(rand()) / RAND_MAX);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { PlaylistProgressRole });
}

void PlaylistModel::randomColor()
{
    // Check if there are any items
    if (m_playlistItems.isEmpty()) return;

    // Select randomly one of items from m_playlistItems
    int index = rand() % m_playlistItems.size();

    // Check if the shared pointer is valid
    const QSharedPointer<PlaylistItem> &item = m_playlistItems[index];
    if (!item) {
        qWarning() << "PlaylistModel::randomColor - Null playlist item at index:" << index;
        return;
    }

    // set random color
    QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
    item->setColor(randomColor);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { PlaylistColorRole });
}
