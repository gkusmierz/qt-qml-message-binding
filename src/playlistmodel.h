#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QList>

#include "playlistitem.h"

class PlaylistModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum PlaylstItemRoles {
        AuthorRole = Qt::UserRole + 1,
        TextRole,
        ColorRole,
        ProgressRole
    };

    explicit PlaylistModel(QObject *parent = nullptr);

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addMessage(const QString &author, const QString &text);
    Q_INVOKABLE void random(int index);
    Q_INVOKABLE void randomProgress();
    Q_INVOKABLE void randomColor();

private:
    QList<QSharedPointer<PlaylistItem>> m_messages;
};

#endif // PLAYLISTMODEL_H
