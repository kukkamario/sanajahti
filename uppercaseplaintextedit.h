#ifndef UPPERCASEPLAINTEXTEDIT_H
#define UPPERCASEPLAINTEXTEDIT_H

#include <QPlainTextEdit>

class UpperCasePlainTextEdit : public QPlainTextEdit
{
public:
    explicit UpperCasePlainTextEdit(QWidget *parent = nullptr);

    virtual bool eventFilter (QObject *obj, QEvent *event) override;
};

#endif // UPPERCASEPLAINTEXTEDIT_H


