#include "playlistitem.h"

#include <QDebug>

PlaylistItem::PlaylistItem(QObject *parent)
    : QObject(parent),
      m_artist(""),
      m_title(""),
      m_cueStart(0.0),
      m_cueIntro(0.0),
      m_cueMix(0.0),
      m_cueEnd(0.0),
      m_duration(0.0),
      m_progress(0.0),
      m_fileName(""),
      m_color(Qt::red)
{
    qDebug() << "PlaylistItem::PlaylistItem(" << m_artist << m_title << m_cueStart << m_cueIntro <<
        m_cueMix << m_cueEnd << m_duration << m_color << ")";
}

PlaylistItem::PlaylistItem(const QString &artist, const QString &title, double cueStart, double cueIntro,
                           double cueMix, double cueEnd, double duration, const QColor &color, QObject *parent)
{
    m_artist = artist;
    m_title = title;
    m_cueStart = cueStart;
    m_cueIntro = cueIntro;
    m_cueMix = cueMix;
    m_cueEnd = cueEnd;
    m_duration = duration;
    m_progress = 0.0;
    m_fileName = "";
    m_color = color;
    qDebug() << "PlaylistItem::PlaylistItem(" << m_artist << m_title << m_cueStart << m_cueIntro <<
        m_cueMix << m_cueEnd << m_duration << m_color << ")";
}

PlaylistItem::~PlaylistItem()
{
    qDebug() << "~PlaylistItem::PlaylistItem(" << m_artist << m_title << m_cueStart << m_cueIntro <<
        m_cueMix << m_cueEnd << m_duration << m_color << ")";
}

QString PlaylistItem::artist() const
{
    return m_artist;
}

void PlaylistItem::setArtist(const QString &newArtist)
{
    if (m_artist != newArtist) {
        m_artist = newArtist;
        emit artistChanged();
    }
}

QString PlaylistItem::title() const
{
    return m_title;
}

void PlaylistItem::setTitle(const QString &newTitle)
{
    if (m_title != newTitle) {
        m_title = newTitle;
        emit titleChanged();
    }
}

double PlaylistItem::cueStart() const
{
    return m_cueStart;
}

void PlaylistItem::setCueStart(double newCueStart)
{
    if (m_cueStart != newCueStart) {
        m_cueStart = newCueStart;
        emit cueStartChanged();
    }
}

double PlaylistItem::cueIntro() const
{
    return m_cueIntro;
}

void PlaylistItem::setCueIntro(double newCueIntro)
{
    if (m_cueIntro != newCueIntro) {
        m_cueIntro = newCueIntro;
        emit cueIntroChanged();
    }
}

double PlaylistItem::cueMix() const
{
    return m_cueMix;
}

void PlaylistItem::setCueMix(double newCueMix)
{
    if (m_cueMix != newCueMix) {
        m_cueMix = newCueMix;
        emit cueMixChanged();
    }
}

double PlaylistItem::cueEnd() const
{
    return m_cueEnd;
}

void PlaylistItem::setCueEnd(double newCueEnd)
{
    if (m_cueEnd != newCueEnd) {
        m_cueEnd = newCueEnd;
        emit cueEndChanged();
    }
}

double PlaylistItem::duration() const
{
    return m_duration;
}

void PlaylistItem::setDuration(double newDuration)
{
    if (m_duration != newDuration) {
        m_duration = newDuration;
        emit durationChanged();
    }
}

double PlaylistItem::progress() const
{
    return m_progress;
}

void PlaylistItem::setProgress(double newProgress)
{
    if (m_progress != newProgress) {
        m_progress = newProgress;
        emit progressChanged();
    }
}

QString PlaylistItem::fileName() const
{
    return m_fileName;
}

void PlaylistItem::setFileName(const QString &newFileName)
{
    if (m_fileName != newFileName) {
        m_fileName = newFileName;
        emit fileNameChanged();
    }
}

QColor PlaylistItem::color() const
{
    return m_color;
}

void PlaylistItem::setColor(const QColor &newColor)
{
    if (m_color != newColor) {
        m_color = newColor;
        emit colorChanged();
    }
}

void PlaylistItem::debug(QString message)
{
    qDebug() << "PlaylistItem::debug()" << message << m_artist << m_title << m_cueStart << m_cueIntro <<
        m_cueMix << m_cueEnd << m_duration << m_progress << m_fileName << m_color;
}
