#ifndef PLAYLISTITEM_H
#define PLAYLISTITEM_H

#include <QObject>
#include <QColor>

class PlaylistItem : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString artist READ artist WRITE setArtist NOTIFY artistChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(double cueStart READ cueStart WRITE setCueStart NOTIFY cueStartChanged)
    Q_PROPERTY(double cueIntro READ cueIntro WRITE setCueIntro NOTIFY cueIntroChanged)
    Q_PROPERTY(double cueMix READ cueMix WRITE setCueMix NOTIFY cueMixChanged)
    Q_PROPERTY(double cueEnd READ cueEnd WRITE setCueEnd NOTIFY cueEndChanged)
    Q_PROPERTY(double duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(double progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
public:
    PlaylistItem(QObject *parent = nullptr);
    ~PlaylistItem() override;

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

    double progress() const;
    void setProgress(double newProgress);

    QString fileName() const;
    void setFileName(const QString &newFileName);

    QColor color() const;
    void setColor(const QColor &newColor);

signals:
    void artistChanged();
    void titleChanged();
    void cueStartChanged();
    void cueIntroChanged();
    void cueMixChanged();
    void cueEndChanged();
    void durationChanged();
    void progressChanged();
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
    double m_progress;
    QString m_fileName;
    QColor m_color;
};

#endif // PLAYLISTITEM_H
