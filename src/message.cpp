#include "message.h"

#include <QDebug>

Message::Message(QObject *parent)
    : QObject(parent),
      m_author(""),
      m_text(""),
      m_progress(0.0)
{
    qDebug() << "Message created()";
}

Message::Message(const QString &author, const QString &text, const qreal &progress, QObject *parent)
    : QObject(parent),
      m_author(author),
      m_text(text),
      m_progress(progress)
{
    qDebug() << "Message created(" << author << text << progress << ")";;
}

Message::~Message()
{
    qDebug() << "Message destroyed (" << m_author << m_text << m_progress << ")";
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
