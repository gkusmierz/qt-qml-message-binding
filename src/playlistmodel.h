#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "playlistitem.h"

class PlaylistModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum PlaylstItemRoles {
        PlaylistArtistRole   = Qt::UserRole + 1,
        PlaylistTitleRole    = Qt::UserRole + 2,
        PlaylistCueStartRole = Qt::UserRole + 3,
        PlaylistCueIntroRole = Qt::UserRole + 4,
        PlaylistCueMixRole   = Qt::UserRole + 5,
        PlaylistCueEndRole   = Qt::UserRole + 6,
        PlaylistDurationRole = Qt::UserRole + 7,
        PlaylistProgressRole = Qt::UserRole + 8,
        PlaylistFileNameRole = Qt::UserRole + 9,
        PlaylistColorRole    = Qt::UserRole + 10
    };

    PlaylistModel(QObject *parent = nullptr);
    ~PlaylistModel() override;

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addPlaylistItem(const QString &artist, const QString &title,
                                     const double &cueStart, const double &cueIntro,
                                     const double &cueMix, const double &cueEnd,
                                     const double &duration, const QColor &color);
    Q_INVOKABLE void random(int index);
    Q_INVOKABLE void randomProgress();
    Q_INVOKABLE void randomColor();

private:
    QList<QSharedPointer<PlaylistItem>> m_playlistItems;
};

#endif // PLAYLISTMODEL_H
