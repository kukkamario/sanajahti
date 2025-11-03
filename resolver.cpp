#include "resolver.h"
//#include <QDebug>

Resolver::Resolver(const WordDb &db, const WordGrid& grid) : db(db), grid(grid) {

}

void Resolver::resolveFromCell(int x, int y)
{
    reset();
    continueResolving(x, y, db.sortedWords.begin(), db.sortedWords.end());
}

void Resolver::reset()
{
    word.chars.fill('\0');
    used = 0;
    foundWords.clear();
    wordLen = 0;
}

void Resolver::continueResolving(int x, int y, WordDb::it_t begin, WordDb::it_t end)
{
    uint32_t prevUsed = used;
    char c = getC(x, y);
    mark(x, y);
    word.chars[wordLen] = c;
    points.push_back({x, y});
    wordLen += 1;

    auto range = db.prefixRange(word, begin, end);

    if (range.first != range.second) {

        //qDebug() << "Comparing " << range.first->toQString() << " and " << word.toQString();
        if (*range.first == word) {
            foundWords.push_back(
                        Resolution{
                            word.toQString(),
                            points
                        });
            ++range.first;
        }

        if (canContinueTo(x - 1, y - 1)) {
            continueResolving(x - 1, y - 1, range.first, range.second);
        }
        if (canContinueTo(x - 1, y)) {
            continueResolving(x - 1, y, range.first, range.second);
        }
        if (canContinueTo(x - 1, y + 1)) {
            continueResolving(x - 1, y + 1, range.first, range.second);
        }
        if (canContinueTo(x, y - 1)) {
            continueResolving(x, y - 1, range.first, range.second);
        }
        if (canContinueTo(x, y + 1)) {
            continueResolving(x, y + 1, range.first, range.second);
        }
        if (canContinueTo(x + 1, y - 1)) {
            continueResolving(x + 1, y - 1, range.first, range.second);
        }
        if (canContinueTo(x + 1, y)) {
            continueResolving(x + 1, y, range.first, range.second);
        }
        if (canContinueTo(x + 1, y + 1)) {
            continueResolving(x + 1, y + 1, range.first, range.second);
        }
    }

    used = prevUsed;
    wordLen -= 1;
    word.chars[wordLen] = '\0';
    points.resize(points.size() - 1);
}
