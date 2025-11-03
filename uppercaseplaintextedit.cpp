#include "uppercaseplaintextedit.h"


UpperCasePlainTextEdit::UpperCasePlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    installEventFilter(this);
}

bool UpperCasePlainTextEdit::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        if (auto *e = dynamic_cast<QKeyEvent *>(event)) {

            /*
               * If QKeyEvent::text() returns an empty QString then let normal
               * processing proceed as it may be a control (e.g. cursor movement)
               * key.  Otherwise convert the text to upper case and insert it at
               * the current cursor position.
               */
            auto text = e->text();
            if (!text.isEmpty() && text != '\x08') {
                insertPlainText(text.toUpper());
                return true;
            }
        }
    }
    return QPlainTextEdit::eventFilter(obj, event);
}
