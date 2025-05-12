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

    PlaylistItem *msgPtr = m_playlistItems[index.row()];

    //QString debugMsg = QString("%1/%2").arg(index.row()).arg(role);
    //msgPtr->debug(debugMsg);

    if (msgPtr == nullptr)
        return QVariant();

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

void PlaylistModel::addPlaylistItem(const QString &artist, const QString &title,
                                    double cueStart, double cueIntro, double cueMix,
                                    double cueEnd, double duration, const QColor &color)
{
    beginInsertRows(QModelIndex(), m_playlistItems.size(), m_playlistItems.size());

    // Create a new PlaylistItem and add it to the list
    PlaylistItem *item = new PlaylistItem(artist, title, cueStart, cueIntro, cueMix, cueEnd, duration, color);
    m_playlistItems.append(item);

    endInsertRows();
}

void PlaylistModel::random(int index)
{
    // set random progress between 0.0 and 1.0
    m_playlistItems[index]->setProgress(static_cast<qreal>(rand()) / RAND_MAX);

    // set random color
    QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
    m_playlistItems[index]->setColor(randomColor);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { PlaylistColorRole, PlaylistProgressRole });
}

void PlaylistModel::randomProgress()
{
    // select randomly on of items from m_messages
    if (m_playlistItems.isEmpty()) return;
    int index = rand() % m_playlistItems.size();

    // set random progress between 0.0 and 1.0
    m_playlistItems[index]->setProgress(static_cast<qreal>(rand()) / RAND_MAX);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { PlaylistProgressRole });
}

void PlaylistModel::randomColor()
{
    // select randomly on of items from m_messages
    if (m_playlistItems.isEmpty()) return;
    int index = rand() % m_playlistItems.size();

    // set random color
    QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
    m_playlistItems[index]->setColor(randomColor);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { PlaylistColorRole });
}
