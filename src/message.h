#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    Message(QObject *parent = nullptr);
    Message(const QString &author, const QString &text, QObject *parent = nullptr);

    ~Message() override = default;

    QString author() const;
    void setAuthor(const QString &newAuthor);

    QString text() const;
    void setText(const QString &newText);

signals:
    void authorChanged();
    void textChanged();

private:
    QString m_author;
    QString m_text;
};

#endif // MESSAGE_H
