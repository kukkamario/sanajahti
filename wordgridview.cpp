#include "wordgridview.h"
#include <QPainter>
#include <QPaintEvent>

WordGridView::WordGridView(QWidget *parent) : QWidget(parent)
{

}

void WordGridView::setGrid(const WordGrid &grid)
{
    this->grid = grid;
    repaint();
}

void WordGridView::setResolution(const Resolution &r)
{
    resolution = r;
    repaint();
}

void WordGridView::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.setFont(QFont("monospace", 40));

    int spacingW = width() / 5;
    int spacingH = height() / 5;
    int paddingW = width() / 10;
    int paddingH = height() / 10;

    QPoint p1;
    p.setPen(QPen(QBrush(QColor(255, 0, 0)), 5.0));

    float mult = 0;
    float factor = 1.0 / (resolution.points.size() - 1);
    for (const std::pair<char, char>& charP : resolution.points) {
        QPoint p2(spacingW + spacingW * charP.first, spacingH + spacingH * charP.second);

        if (p1 != QPoint()) {
            p.setPen(QPen(QBrush(QColor(255 - int(mult * 100), 0, 0)), 8.0 - mult * 4));
            p.drawLine(p1, p2);
        }
        else {
            p.setPen(QPen(QBrush(QColor(255 - int(mult * 100), 0, 0)), 3.0));
            p.drawEllipse(p2, spacingW / 2, spacingH / 2);
        }
        p1 = p2;
        mult += factor;
    }

    p.setPen(QPen(QBrush(QColor(0,0,0)), 1));
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            QChar c = grid.cell(x, y);
            c = c.toUpper();

            QRect r(paddingW + spacingW * x, paddingH + spacingH * y, spacingW, spacingH);
            p.drawText(r, Qt::AlignCenter, c);
        }
    }
}
