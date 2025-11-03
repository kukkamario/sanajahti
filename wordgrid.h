#ifndef WORDGRID_H
#define WORDGRID_H
#include <QString>
#include <string>

class WordGrid
{
public:
    WordGrid();
    bool loadFromText(const QString& text);

    QChar cell(int x, int y);

    alignas(16) char grid[4][4];
};

#endif // WORDGRID_H
