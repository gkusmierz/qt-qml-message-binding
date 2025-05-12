#ifndef PLAYLISTDAO_H
#define PLAYLISTDAO_H

#include <QObject>
#include <QSqlDatabase>
#include <QSharedPointer>
#include <QList>

#include "playlistitem.h"

class PlaylistDao : public QObject
{
    Q_OBJECT
public:
     PlaylistDao(const QString &sqlitePath = QString(), QObject *parent = nullptr);
    ~PlaylistDao() override;

    Q_INVOKABLE PlaylistItem* randomItem();

signals:

private:
    QString m_sqlitePath;
    QList<QSharedPointer<PlaylistItem>> m_playlistItems;

    QSqlDatabase openDb(const QString &path, const char *connectionName) const;
    void fillPlaylistItems();

};

#endif // PLAYLISTDAO_H
