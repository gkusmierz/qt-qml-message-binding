#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent) {}

int PlaylistModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_messages.count();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_messages.size())
        return QVariant();

    const QSharedPointer<PlaylistItem> &msgPtr = m_messages[index.row()];

    if (!msgPtr)
        return QVariant();

    switch (role) {
        case AuthorRole:
            return msgPtr->author();
        case TextRole:
            return msgPtr->text();
        case ColorRole:
            return msgPtr->color();
        case ProgressRole:
            return msgPtr->progress();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> PlaylistModel::roleNames() const {
    return {
        { AuthorRole, "author" },
        { TextRole, "text" },
        { ColorRole, "color" },
        { ProgressRole, "progress" }
    };
}

void PlaylistModel::addMessage(const QString &author, const QString &text) {
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(QSharedPointer<PlaylistItem>::create(author, text, "red", 0.0, this));
    endInsertRows();
}

void PlaylistModel::random(int index)
{
    // set random progress between 0.0 and 1.0
    m_messages[index]->setProgress(static_cast<qreal>(rand()) / RAND_MAX);

    // set random color
    QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
    m_messages[index]->setColor(randomColor);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { ColorRole, ProgressRole });
}

void PlaylistModel::randomProgress()
{
    // select randomly on of items from m_messages
    if (m_messages.isEmpty()) return;
    int index = rand() % m_messages.size();

    // set random progress between 0.0 and 1.0
    m_messages[index]->setProgress(static_cast<qreal>(rand()) / RAND_MAX);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { ProgressRole });
}

void PlaylistModel::randomColor()
{
    // select randomly on of items from m_messages
    if (m_messages.isEmpty()) return;
    int index = rand() % m_messages.size();

    // set random color
    QColor randomColor(rand() % 256, rand() % 256, rand() % 256);
    m_messages[index]->setColor(randomColor);

    // emit dataChanged signal to notify the view
    QModelIndex modelIndex = this->index(index);
    emit dataChanged(modelIndex, modelIndex, { ColorRole });
}
