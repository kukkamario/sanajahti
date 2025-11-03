#include "worddb.h"
#include <fstream>
#include <algorithm>
//#include <QDebug>

WordDb::WordDb()
{

}

bool isValidChar(char c) {
    return (c >= 'a' && c <= 'z') || c == '1' || c == '2' || c == '3';
}

bool WordDb::load(const std::string& file)
{
    std::ifstream f(file);
    std::string line;
    while(std::getline(f, line)) {
        Word w;

        bool validWord = true;
        int i = 0;
        for (char c : line) {
            if (isValidChar(c)) {
                if (i == 16) {
                    validWord = false;
                    break;
                }
                w.chars[i] = c;
                ++i;
            }
        }

        if (!validWord) continue;

        if (i <= 3) continue;

        for (; i < 16; ++i) {
            w.chars[i] = '\0';
        }

        sortedWords.push_back(w);
    }

    std::sort(sortedWords.begin(), sortedWords.end());
    return true;
}

std::pair<WordDb::it_t, WordDb::it_t> WordDb::prefixRange(const WordDb::Word &w) const
{
    return prefixRange(w, sortedWords.begin(), sortedWords.end());
}

std::pair<WordDb::it_t, WordDb::it_t> WordDb::prefixRange(const Word& w, const it_t& begin, const it_t& end) const
{
    unsigned wordLen = w.len();

    auto prefixSort = [wordLen](const Word& a, const Word& b) {
        for (unsigned i = 0; i < wordLen; ++i) {
            if (a.chars[i] < b.chars[i]) return true;
            if (a.chars[i] > b.chars[i]) return false;
        }

        return false;
    };
    auto lower = std::lower_bound(begin, end, w, prefixSort);
    auto upper = std::upper_bound(begin, end, w, prefixSort);
    return {lower, upper};
}


QString WordDb::Word::toQString() const
{
    QString s;
    s.reserve(16);

    for (char c : chars) {
        if (c == '\0') break;
        if (c == '1') {
            s.push_back(QChar(0xE4u));
        }
        else if (c == '2') {
            s.push_back(QChar(0xF6u));
        }
        else if (c == '3') {
            s.push_back(QChar(0xE5));
        }
        else {
            s.push_back(QChar::fromLatin1(c));
        }
    }
    return s;
}
