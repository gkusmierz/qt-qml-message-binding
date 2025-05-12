#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QObject>
#include <QColor>

class LibraryItem : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(double cueStart READ cueStart WRITE setCueStart NOTIFY cueStartChanged)
    Q_PROPERTY(double cueIntro READ cueIntro WRITE setCueIntro NOTIFY cueIntroChanged)
    Q_PROPERTY(double cueMix READ cueMix WRITE setCueMix NOTIFY cueMixChanged)
    Q_PROPERTY(double cueEnd READ cueEnd WRITE setCueEnd NOTIFY cueEndChanged)
    Q_PROPERTY(double duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    LibraryItem(QObject *parent = nullptr);
    LibraryItem(const LibraryItem &other);
    LibraryItem(const QString &artist, const QString &title, const double &cueStart,
                const double &cueIntro, const double &cueMix, const double &cueEnd,
                const double &duration, const QColor &color, QObject *parent = nullptr);

    ~LibraryItem() override;

    LibraryItem &operator=(const LibraryItem &other);

    QString artist() const;
    void setArtist(const QString &newArtist);

    QString title() const;
    void setTitle(const QString &newTitle);

    double cueStart() const;
    void setCueStart(double newCueStart);

    double cueIntro() const;
    void setCueIntro(double newCueIntro);

    double cueMix() const;
    void setCueMix(double newCueMix);

    double cueEnd() const;
    void setCueEnd(double newCueEnd);

    double duration() const;
    void setDuration(double newDuration);

    QString fileName() const;
    void setFileName(const QString &newFileName);

    QColor color() const;
    void setColor(const QColor &newColor);

    Q_INVOKABLE void debug(QString message);

signals:
    void artistChanged();
    void titleChanged();
    void cueStartChanged();
    void cueIntroChanged();
    void cueMixChanged();
    void cueEndChanged();
    void durationChanged();
    void fileNameChanged();
    void colorChanged();

private:
    QString m_artist;
    QString m_title;
    double m_cueStart;
    double m_cueIntro;
    double m_cueMix;
    double m_cueEnd;
    double m_duration;
    QString m_fileName;
    QColor m_color;
};

#endif // LIBRARYITEM_H
