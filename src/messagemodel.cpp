#include "messagemodel.h"

MessageModel::MessageModel(QObject *parent)
    : QAbstractListModel(parent) {}

int MessageModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) return 0;
    return m_messages.count();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_messages.size())
        return QVariant();

    const QSharedPointer<Message> &msgPtr = m_messages[index.row()];

    if (!msgPtr)
        return QVariant();

    switch (role) {
        case AuthorRole:
            return msgPtr->author();
        case TextRole:
            return msgPtr->text();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> MessageModel::roleNames() const {
    return {
        { AuthorRole, "author" },
        { TextRole, "text" }
    };
}

void MessageModel::addMessage(const QString &author, const QString &text) {
    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(QSharedPointer<Message>::create(author, text, this));
    endInsertRows();
}
