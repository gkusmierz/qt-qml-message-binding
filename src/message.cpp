#include "message.h"

Message::Message(QObject *parent)
    : QObject(parent),
      m_author(""),
      m_text("")
{}

Message::Message(const QString &author, const QString &text, QObject *parent)
    : QObject(parent),
      m_author(author),
      m_text(text)
{}

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
