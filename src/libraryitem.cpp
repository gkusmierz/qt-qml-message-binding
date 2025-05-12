#include "libraryitem.h"

#include <QDebug>

LibraryItem::LibraryItem(QObject *parent)
    : QObject(parent),
      m_artist(""),
      m_title(""),
      m_cueStart(0.0),
      m_cueIntro(0.0),
      m_cueMix(0.0),
      m_cueEnd(0.0),
      m_duration(0.0),
      m_fileName(""),
      m_color(Qt::red)
{
    qDebug() << "LibraryItem::LibraryItem(" << m_artist << m_title << m_cueStart << m_cueIntro <<
        m_cueMix << m_cueEnd << m_duration << m_color << ")";
}

LibraryItem::LibraryItem(const LibraryItem &other)
{
    m_artist = other.m_artist;
    m_title = other.m_title;
    m_cueStart = other.m_cueStart;
    m_cueIntro = other.m_cueIntro;
    m_cueMix = other.m_cueMix;
    m_cueEnd = other.m_cueEnd;
    m_duration = other.m_duration;
    m_fileName = other.m_fileName;
    m_color = other.m_color;

    setParent(other.parent());
}

LibraryItem::LibraryItem(const QString &artist, const QString &title, const double &cueStart,
                         const double &cueIntro, const double &cueMix, const double &cueEnd,
                         const double &duration, const QColor &color, QObject *parent)
{
    m_artist = artist;
    m_title = title;
    m_cueStart = cueStart;
    m_cueIntro = cueIntro;
    m_cueMix = cueMix;
    m_cueEnd = cueEnd;
    m_duration = duration;
    m_fileName = "";
    m_color = color;

    setParent(parent);

    qDebug() << "LibraryItem::LibraryItem(" << m_artist << m_title << m_cueStart << m_cueIntro <<
        m_cueMix << m_cueEnd << m_duration << m_color << ")";
}

LibraryItem::~LibraryItem()
{
    qDebug() << "~LibraryItem::LibraryItem(" << m_artist << m_title << m_cueStart << m_cueIntro <<
        m_cueMix << m_cueEnd << m_duration << m_color << ")";
}

LibraryItem &LibraryItem::operator=(const LibraryItem &other)
{
    if (this != &other) {
        m_artist = other.m_artist;
        m_title = other.m_title;
        m_cueStart = other.m_cueStart;
        m_cueIntro = other.m_cueIntro;
        m_cueMix = other.m_cueMix;
        m_cueEnd = other.m_cueEnd;
        m_duration = other.m_duration;
        m_fileName = other.m_fileName;
        m_color = other.m_color;
    }
    return *this;
}

QString LibraryItem::artist() const
{
    return m_artist;
}

void LibraryItem::setArtist(const QString &newArtist)
{
    if (m_artist != newArtist) {
        m_artist = newArtist;
        emit artistChanged();
    }
}

QString LibraryItem::title() const
{
    return m_title;
}

void LibraryItem::setTitle(const QString &newTitle)
{
    if (m_title != newTitle) {
        m_title = newTitle;
        emit titleChanged();
    }
}

double LibraryItem::cueStart() const
{
    return m_cueStart;
}

void LibraryItem::setCueStart(double newCueStart)
{
    if (m_cueStart != newCueStart) {
        m_cueStart = newCueStart;
        emit cueStartChanged();
    }
}

double LibraryItem::cueIntro() const
{
    return m_cueIntro;
}

void LibraryItem::setCueIntro(double newCueIntro)
{
    if (m_cueIntro != newCueIntro) {
        m_cueIntro = newCueIntro;
        emit cueIntroChanged();
    }
}

double LibraryItem::cueMix() const
{
    return m_cueMix;
}

void LibraryItem::setCueMix(double newCueMix)
{
    if (m_cueMix != newCueMix) {
        m_cueMix = newCueMix;
        emit cueMixChanged();
    }
}

double LibraryItem::cueEnd() const
{
    return m_cueEnd;
}

void LibraryItem::setCueEnd(double newCueEnd)
{
    if (m_cueEnd != newCueEnd) {
        m_cueEnd = newCueEnd;
        emit cueEndChanged();
    }
}

double LibraryItem::duration() const
{
    return m_duration;
}

void LibraryItem::setDuration(double newDuration)
{
    if (m_duration != newDuration) {
        m_duration = newDuration;
        emit durationChanged();
    }
}

QString LibraryItem::fileName() const
{
    return m_fileName;
}

void LibraryItem::setFileName(const QString &newFileName)
{
    if (m_fileName != newFileName) {
        m_fileName = newFileName;
        emit fileNameChanged();
    }
}

QColor LibraryItem::color() const
{
    return m_color;
}

void LibraryItem::setColor(const QColor &newColor)
{
    if (m_color != newColor) {
        m_color = newColor;
        emit colorChanged();
    }
}

void LibraryItem::debug(QString message)
{
    qDebug() << "LibraryItem::debug()" << message << m_artist << m_title << m_cueStart <<
        m_cueIntro << m_cueMix << m_cueEnd << m_duration << m_fileName << m_color;
}
