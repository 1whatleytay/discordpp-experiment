#include <utility/parser.h>

#include <algorithm>

const char symbols[] = {
    ':',
    ';',
    ',',
    '.',
    '{',
    '}',
    '+',
    '-',
    '=',
    '/',
    '\\',
    '@',
    '#',
    '$',
    '%',
    '^',
    '&',
    '|',
    '*',
    '(',
    ')',
    '!',
    '?',
    '<',
    '>',
    '~',
    '[',
    ']',
    '\"',
    '\'',
};

bool isStrongChar(char ch) {
    if (std::isspace(ch)) return true;
    for (char c : symbols) {
        if (c == ch) return true;
    }
    return false;
}

namespace utility {
    bool Parser::end(int offset) {
        return index + offset >= text.length();
    }

    bool Parser::reachedEnd(int offset) {
        pushIndex();
        return end(offset);
    }

    void Parser::pushIndex() {
        if (mode != Original) while (!end() && std::isspace(text[index])) { index++; }
    }

    void Parser::rollback() {
        index = rollbackIndex;
    }

    void Parser::select() {
        selectIndex = index;
    }

    std::string Parser::clip() {
        return text.substr((unsigned long) selectIndex, (unsigned long) index - (unsigned long) selectIndex);
    }

    void Parser::back() {
        index = selectIndex;
    }

    std::string Parser::last() {
        int temp = index;

        while (index > 0 && std::isspace(text[index])) { index--; }
        if (mode != Original) while (index > 0 && !isStrongChar(text[index])) { index--; }

        std::string word = next();
        rollback();

        rollbackIndex = temp;

        return word;
    }

    std::string Parser::until(const std::vector<std::string> &tests) {
        rollbackIndex = index;
        pushIndex();

        int length = 0;
        while (!reachedEnd(length)) {
            bool match = false;
            for (const std::string &test : tests) {
                if (text.substr(index + length, test.size()) == test) {
                    match = true;
                    break;
                }
            }

            if (match)
                break;

            length++;
        }

        std::string result;
        if (!reachedEnd())
            result = text.substr((unsigned long) index, (unsigned long) length);

        index += length;

        return result;
    }

    std::string Parser::next() {
        rollbackIndex = index;
        pushIndex();

        int length = 1;

        if (!reachedEnd(length) && !isStrongChar(text[index]))
            while (!reachedEnd(length) && !isStrongChar(text[index + length])) { length++; }

        std::string result = reachedEnd() ? "" : text.substr((unsigned long) index, (unsigned long) length);
        index += length;

        return result;
    }

    std::string Parser::peek() {
        int temp = rollbackIndex;

        std::string word = next();

        index = rollbackIndex;
        rollbackIndex = temp;

        return word;
    }

    Parser::Parser(std::string nText) : text(move(nText)) {}
}
