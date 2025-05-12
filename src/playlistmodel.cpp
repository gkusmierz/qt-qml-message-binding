#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent) {}

int PlaylistModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_playlistItems.count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_playlistItems.size())
        return QVariant();

    const QSharedPointer<PlaylistItem> &msgPtr = m_playlistItems[index.row()];

    QString debugMsg = QString("%1/%2").arg(index.row()).arg(role);
    msgPtr->debug(debugMsg);

    if (!msgPtr)
        return QVariant();

    switch (role) {
        case ArtistRole:
            return msgPtr->artist();
        case TitleRole:
            return msgPtr->title();
        case CueStartRole:
            return msgPtr->cueStart();
        case CueIntroRole:
            return msgPtr->cueIntro();
        case CueMixRole:
            return msgPtr->cueMix();
        case CueEndRole:
            return msgPtr->cueEnd();
        case DurationRole:
            return msgPtr->duration();
        case ProgressRole:
            return msgPtr->progress();
        case FileNameRole:
            return msgPtr->fileName();
        case ColorRole:
            return msgPtr->color();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    return {
        { ArtistRole, "artist" },
        { TitleRole, "title" },
        { CueStartRole, "cueStart" },
        { CueIntroRole, "cueIntro" },
        { CueMixRole, "cueMix" },
        { CueEndRole, "cueEnd" },
        { DurationRole, "duration" },
        { ProgressRole, "progress" },
        { FileNameRole, "fileName" },
        { ColorRole, "color" }
    };
}

void PlaylistModel::addPlaylistItem(const QString &artist, const QString &title,
                                    double cueStart, double cueIntro, double cueMix,
                                    double cueEnd, double duration, const QColor &color)
{
    beginInsertRows(QModelIndex(), m_playlistItems.size(), m_playlistItems.size());

    m_playlistItems.append(QSharedPointer<PlaylistItem>::create(
        artist, title, cueStart, cueIntro, cueMix, cueEnd, duration, "red"));

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
    emit dataChanged(modelIndex, modelIndex, { ColorRole, ProgressRole });
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
    emit dataChanged(modelIndex, modelIndex, { ProgressRole });
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
    emit dataChanged(modelIndex, modelIndex, { ColorRole });
}
