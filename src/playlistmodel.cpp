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

    const QSharedPointer<PlaylistItem> item = m_playlistItems[index.row()];

    QString debugMsg = QString("%1/%2").arg(index.row()).arg(role);
    item->debug(debugMsg);

    switch (role) {
    case PlaylistArtistRole:

        return item->artist();
    case PlaylistTitleRole:
        return item->title();
    case PlaylistCueStartRole:
        return item->cueStart();
    case PlaylistCueIntroRole:
        return item->cueIntro();
    case PlaylistCueMixRole:
        return item->cueMix();
    case PlaylistCueEndRole:
        return item->cueEnd();
    case PlaylistDurationRole:
        return item->duration();
    case PlaylistProgressRole:
        return item->progress();
    case PlaylistFileNameRole:
        return item->fileName();
    case PlaylistColorRole:
        return item->color();
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

void PlaylistModel::addPlaylistItem(const QString &artist, const QString &title,
                                    const double &cueStart, const double &cueIntro,
                                    const double &cueMix, const double &cueEnd,
                                    const double &duration, const QColor &color)
{
    // Validate inputs before creating a new item
    if (artist.isEmpty() && title.isEmpty()) {
        qWarning() << "PlaylistModel::addPlaylistItem - Empty artist and title";
        return;
    }

    const int row = m_playlistItems.count();
    beginInsertRows(QModelIndex(), row, row);
    auto newItem = QSharedPointer<PlaylistItem>::create(
        artist, title, cueStart, cueIntro, cueMix, cueEnd, duration, color);
    m_playlistItems.append(newItem);
    endInsertRows();

    qDebug() << "PlaylistModel::addPlaylistItem - Added new item:" << artist
             << title << duration;
}

void PlaylistModel::random(int index)
{
    // Check if index is valid before accessing the shared pointer
    if (index < 0 || index >= m_playlistItems.size()) {
        qWarning() << "PlaylistModel::random - Invalid index:" << index;
        return;
    }

    QSharedPointer<PlaylistItem> item = m_playlistItems[index];

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

    const QSharedPointer<PlaylistItem> item = m_playlistItems[index];

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

    QSharedPointer<PlaylistItem> item = m_playlistItems[index];

    // set random color
    QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
    item->setColor(randomColor);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { PlaylistColorRole });
}
