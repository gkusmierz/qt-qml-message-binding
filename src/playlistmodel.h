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
        ArtistRole = Qt::UserRole + 1,
        TitleRole,
        CueStartRole,
        CueIntroRole,
        CueMixRole,
        CueEndRole,
        DurationRole,
        ProgressRole,
        FileNameRole,
        ColorRole
    };

    explicit PlaylistModel(QObject *parent = nullptr);

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addPlaylistItem(const QString &artist, const QString &title,
                                     double cueStart, double cueIntro, double cueMix,
                                     double cueEnd, double duration, const QColor &color);
    Q_INVOKABLE void random(int index);
    Q_INVOKABLE void randomProgress();
    Q_INVOKABLE void randomColor();

private:
    QList<QSharedPointer<PlaylistItem>> m_playlistItems;;
};

#endif // PLAYLISTMODEL_H
