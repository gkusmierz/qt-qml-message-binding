#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QList>

#include "message.h"

class MessageModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum MessageRoles {
        AuthorRole = Qt::UserRole + 1,
        TextRole
    };

    explicit MessageModel(QObject *parent = nullptr);

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addMessage(const QString &author, const QString &text);

private:
    QList<QSharedPointer<Message>> m_messages;
};

#endif // MESSAGEMODEL_H
