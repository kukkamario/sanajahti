#ifndef WORDDB_H
#define WORDDB_H
#include <string>
#include <vector>
#include <array>
#include <QString>

class WordDb
{
public:
    struct Word {
        Word(const Word&) noexcept = default;
        Word(Word&&) noexcept = default;
        Word() noexcept = default;
        Word& operator=(const Word&) noexcept = default;
        Word& operator=(Word&&) noexcept = default;

        void swap(Word& b) noexcept {
            chars.swap(b.chars);
        }

        std::array<char, 16> chars;

        bool operator==(const Word& b) const noexcept {
            return chars == b.chars;
        }
        bool operator<(const Word& b) const noexcept {
            return chars < b.chars;
        }

        unsigned len() const noexcept {
            unsigned i = 0;
            for (; i < 16; ++i) {
                if (chars[i] == '\0') break;
            }

            return i;
        }

        QString toQString() const;
    };

    using it_t = std::vector<Word>::const_iterator;

    WordDb();

    bool load(const std::string& file);

    std::pair<it_t, it_t> prefixRange(const Word& w) const;
    std::pair<it_t, it_t> prefixRange(const Word& w, const it_t& begin, const it_t& end) const;

    std::vector<Word> sortedWords;
};

#endif // WORDDB_H
