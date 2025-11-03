#ifndef WORDGRIDVIEW_H
#define WORDGRIDVIEW_H

#include <QWidget>
#include "wordgrid.h"
#include "resolver.h"

class WordGridView : public QWidget
{
    Q_OBJECT
public:
    explicit WordGridView(QWidget *parent = nullptr);

    void setGrid(const WordGrid& grid);
    void setResolution(const Resolution& r);
signals:

private:
    void paintEvent(QPaintEvent* e) override;

    WordGrid grid;
    Resolution resolution;
};

#endif // WORDGRIDVIEW_H
