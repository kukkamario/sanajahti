#include "wordgrid.h"
#include <QList>
#include <map>

WordGrid::WordGrid()
{
    std::memset(grid, 0, sizeof(grid));
}


bool WordGrid::loadFromText(const QString &text)
{
    std::map<QChar, char> mapping;
    for (char c = 'a'; c <= 'z'; ++c) {
        mapping[QChar(c)] = c;
    }
    mapping[QChar(0xE4u)] = '1';
    mapping[QChar(0xF6u)] = '2';
    mapping[QChar(0xE5u)] = '3';

    QList<QString> lines = text.split(QChar('\n'));
    if (lines.size() < 4) {
        QString combinedLines = text;
        combinedLines.remove('\n');
        combinedLines.remove(' ');
        combinedLines.remove('\t');

        if (combinedLines.size() == 16){
            lines = {
                combinedLines.sliced(0, 4),
                combinedLines.sliced(4, 4),
                combinedLines.sliced(8, 4),
                combinedLines.sliced(12, 4),
            };
        }
    }

    int row = 0;
    for (QString line : lines) {
        line = line.trimmed();
        if (line.isEmpty()) continue;

        if (row == 4) {
            return false;
        }

        if (line.length() != 4) {
            return false;
        }

        line = line.toLower();

        for (int i = 0; i < 4; ++i) {
            auto it = mapping.find(line[i]);
            if (it == mapping.end()) {
                return false;
            }
            grid[row][i] = it->second;
        }
        ++row;
    }

    return row == 4;
}

QChar WordGrid::cell(int x, int y)
{
    char c = grid[y][x];

    if (c == '\0') return QChar(' ');
    if (c == '1') return QChar(0xE4u);
    if (c == '2') return QChar(0xF6u);
    if (c == '3') return QChar(0xE5u);

    return QChar(c);
}
