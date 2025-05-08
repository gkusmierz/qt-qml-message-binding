#include "message.h"

#include <QDebug>

Message::Message(QObject *parent)
    : QObject(parent),
      m_author(""),
      m_text(""),
      m_color(Qt::black),
      m_progress(0.0)
{
    qDebug() << "Message created()";
}

Message::Message(const QString &author, const QString &text, const QColor &color, const qreal &progress, QObject *parent)
    : QObject(parent),
      m_author(author),
      m_text(text),
      m_color(color),
      m_progress(progress)
{
    qDebug() << "Message created(" << m_author << m_text << m_color << m_progress << ")";;
}

Message::~Message()
{
    qDebug() << "Message destroyed (" << m_author << m_text << m_color << m_progress << ")";
}

QString Message::author() const {
    return m_author;
}

QString Message::text() const {
    return m_text;
}

void Message::setAuthor(const QString &newAuthor)
{
    if (m_author == newAuthor)
        return;

    m_author = newAuthor;
    emit authorChanged();
}

void Message::setText(const QString &newText)
{
    if (m_text == newText)
        return;

    m_text = newText;
    emit textChanged();
}

QColor Message::color() const {
    return m_color;
}

void Message::setColor(const QColor &newColor)
{
    if (m_color == newColor)
        return;

    m_color = newColor;
    emit colorChanged();
}

qreal Message::progress() const {
    return m_progress;
}

void Message::setProgress(qreal newProgress)
{
    if (m_progress == newProgress)
        return;

    m_progress = newProgress;
    emit progressChanged();
}
