#pragma once

#include <string>
#include <vector>

namespace utility {
    class Parser {
        int rollbackIndex = 0;
        int index = 0;
        std::string text;

        int selectIndex = 0;

        bool end(int offset = 0);

        void pushIndex();

    public:
        enum Mode {
            Generic,
            Original,
        };

        Mode mode = Generic;

        bool reachedEnd(int offset = 0);

        void rollback();

        void select();

        std::string clip();

        void back();

        std::string last();

        std::string next();

        std::string peek();

        std::string until(const std::vector<std::string> &tests);

        explicit Parser(std::string nText);
    };
}
