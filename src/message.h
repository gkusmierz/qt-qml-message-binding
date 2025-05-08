#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QColor>

class Message : public QObject {

    Q_OBJECT

    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(qreal progress READ progress WRITE setProgress NOTIFY progressChanged)
public:
    Message(QObject *parent = nullptr);
    Message(const QString &author, const QString &text, const QColor &color, const qreal &progress, QObject *parent = nullptr);

    ~Message() override;

    QString author() const;
    void setAuthor(const QString &newAuthor);

    QString text() const;
    void setText(const QString &newText);

    QColor color() const;
    void setColor(const QColor &newColor);

    qreal progress() const;
    void setProgress(qreal newProgress);

signals:
    void authorChanged();
    void textChanged();
    void colorChanged();
    void progressChanged();

private:
    QString m_author;
    QString m_text;
    QColor m_color;
    qreal m_progress;
};

#endif // MESSAGE_H
