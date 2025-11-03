#ifndef RESOLVER_H
#define RESOLVER_H
#include "worddb.h"
#include "wordgrid.h"
#include <string>
#include <vector>
#include <QPoint>



struct Resolution {
    QString word;
    std::vector<std::pair<char, char>> points;
};

class Resolver
{
public:
    Resolver(const WordDb &db, const WordGrid& grid);

    void resolveFromCell(int x, int y);

    const std::vector<Resolution>& getFoundWords() const { return foundWords; }
private:
    void reset();
    void continueResolving(int x, int y, WordDb::it_t begin, WordDb::it_t end);

    void mark(int x, int y) {
        int index = x + y * 4;
        used |= 1u << index;
    };

    bool canContinueTo(int x, int y) {
        if (x < 0 || x >= 4 || y < 0 || y >= 4) return false;
        int index = x + y * 4;
        return (used & (1u << index)) == 0;
    }

    char getC(int x, int y) const {
        return grid.grid[y][x];
    }

    const WordDb& db;
    const WordGrid& grid;
    WordDb::Word word;
    std::vector<Resolution> foundWords;
    std::vector<std::pair<char, char>> points;
    uint32_t used = 0;
    unsigned wordLen = 0;
};

#endif // RESOLVER_H
