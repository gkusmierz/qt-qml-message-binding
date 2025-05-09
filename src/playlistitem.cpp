#include "playlistitem.h"

#include <QDebug>

PlaylistItem::PlaylistItem(QObject *parent)
    : QObject(parent),
      m_author(""),
      m_text(""),
      m_color(Qt::black),
      m_progress(0.0)
{
    qDebug() << "PlaylistItem created()";
}

PlaylistItem::PlaylistItem(const QString &author, const QString &text, const QColor &color, const qreal &progress, QObject *parent)
    : QObject(parent),
      m_author(author),
      m_text(text),
      m_color(color),
      m_progress(progress)
{
    qDebug() << "PlaylistItem created(" << m_author << m_text << m_color << m_progress << ")";;
}

PlaylistItem::~PlaylistItem()
{
    qDebug() << "PlaylistItem destroyed (" << m_author << m_text << m_color << m_progress << ")";
}

QString PlaylistItem::author() const {
    return m_author;
}

QString PlaylistItem::text() const {
    return m_text;
}

void PlaylistItem::setAuthor(const QString &newAuthor)
{
    if (m_author == newAuthor)
        return;

    m_author = newAuthor;
    emit authorChanged();
}

void PlaylistItem::setText(const QString &newText)
{
    if (m_text == newText)
        return;

    m_text = newText;
    emit textChanged();
}

QColor PlaylistItem::color() const {
    return m_color;
}

void PlaylistItem::setColor(const QColor &newColor)
{
    if (m_color == newColor)
        return;

    m_color = newColor;
    emit colorChanged();
}

qreal PlaylistItem::progress() const {
    return m_progress;
}

void PlaylistItem::setProgress(qreal newProgress)
{
    if (m_progress == newProgress)
        return;

    m_progress = newProgress;
    emit progressChanged();
}
