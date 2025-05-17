#ifndef LIBRARYMODEL_H
#define LIBRARYMODEL_H

#include <QAbstractListModel>
#include <QSqlDatabase>
#include <QList>

#include "libraryitem.h"

class LibraryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LibraryItemRoles {
        LibraryArtistRole   = Qt::UserRole + 1,
        LibraryTitleRole    = Qt::UserRole + 2,
        LibraryCueStartRole = Qt::UserRole + 3,
        LibraryCueIntroRole = Qt::UserRole + 4,
        LibraryCueMixRole   = Qt::UserRole + 5,
        LibraryCueEndRole   = Qt::UserRole + 6,
        LibraryDurationRole = Qt::UserRole + 7,
        LibraryFileNameRole = Qt::UserRole + 8,
        LibraryColorRole    = Qt::UserRole + 9
    };

     LibraryModel(const QString &sqlitePath = QString(), QObject *parent = nullptr);
    ~LibraryModel() override;

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE QObject* randomItem();
    Q_INVOKABLE QObject* getItem(int index) const;

signals:

private:
    QString m_sqlitePath;
    QList<QSharedPointer<LibraryItem>> m_libraryItems;

    QSqlDatabase openDb(const QString &path, const char *connectionName) const;
    void initModel();

};

#endif // LIBRARYMODEL_H
