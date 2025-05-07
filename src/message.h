#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(qreal progress READ progress WRITE setProgress NOTIFY progressChanged)
public:
    Message(QObject *parent = nullptr);
    Message(const QString &author, const QString &text, const qreal &progress, QObject *parent = nullptr);

    ~Message() override;

    QString author() const;
    void setAuthor(const QString &newAuthor);

    QString text() const;
    void setText(const QString &newText);

    qreal progress() const;
    void setProgress(qreal newProgress);

signals:
    void authorChanged();
    void textChanged();
    void progressChanged();

private:
    QString m_author;
    QString m_text;
    qreal m_progress;
};

#endif // MESSAGE_H
