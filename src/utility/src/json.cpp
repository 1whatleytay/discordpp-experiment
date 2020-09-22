#include <utility/json.h>

#include <utility/parser.h>

#include <sstream>

namespace utility {
    std::string parseString(Parser &parser) {
        if (parser.next() != "\"")
            throw std::runtime_error("Expected string but got.");

        parser.mode = Parser::Mode::Original;

        std::stringstream stream;

        while (!parser.reachedEnd()) {
            stream << parser.until({"\\", "\""});
            std::string following = parser.next();

            if (following == "\"")
                break;

            if (following == "\\") {
                std::string escape = parser.next();
                if (escape == "\\")
                    stream << "\\";
                else if (escape == "\"")
                    stream << "\"";
                else
                    throw std::runtime_error("Unknown escape character in json.");
            }
        }

        parser.mode = Parser::Mode::Generic;

        return stream.str();
    }

    Optional<bool> Json::boolean() const {
        if (type == Type::Empty || type == Type::Null)
            return Optional<bool>();

        if (type != Type::Boolean)
            throw std::runtime_error("Mismatched json type.");

        return booleanValue;
    }

    Optional<double> Json::number() const {
        if (type == Type::Empty || type == Type::Null)
            return Optional<double>();

        if (type != Type::Number)
            throw std::runtime_error("Mismatched json type.");

        return numberValue;
    }

    Optional<std::string> Json::string() const {
        if (type == Type::Empty || type == Type::Null)
            return Optional<std::string>();

        if (type != Type::String)
            throw std::runtime_error("Mismatched json type.");

        return stringValue;
    }

    Json Json::at(size_t index) const {
        if (type != Type::Array)
            throw std::runtime_error("Mismachted json type.");

        if (index >= arrayValue.size()) {
            Json child;
            child.type = Type::Empty;
            return child;
        }

        return arrayValue[index];
    }

    Json Json::at(const std::string &key) const {
        if (type != Type::Object)
            throw std::runtime_error("Mismachted json type.");

        if (objectValue.find(key) == objectValue.end()) {
            Json child;
            child.type = Type::Empty;
            return child;
        }

        return objectValue.at(key);
    }

    size_t Json::getSize() const {
        if (type == Type::Empty)
            return 0;

        if (type == Type::Array)
            return arrayValue.size();

        if (type == Type::Object)
            return objectValue.size();

        throw std::runtime_error("Mismatched json type.");
    }

    bool Json::empty() const {
        return type == Type::Empty || type == Type::Null;
    }

    bool Json::has(size_t index) const {
        return index >= arrayValue.size();
    }

    bool Json::has(const std::string &key) const {
        return objectValue.find(key) != objectValue.end();
    }

    Json Json::operator[](size_t index) const {
        return at(index);
    }

    Json Json::operator[](const std::string &key) const {
        return at(key);
    }

    Json Json::clear() {
        booleanValue = false;
        numberValue = 0;
        stringValue.clear();
        arrayValue.clear();
        objectValue.clear();

        return *this;
    }

    Json Json::parse(utility::Parser &parser) {
        clear();

        std::string next = parser.next();

        if (next.empty())
            throw std::runtime_error("Could not parse json.");

        if (next == "true" || next == "false") {
            type = Type::Boolean;
            booleanValue = next == "true";
        } else if (std::isdigit(next[0]) || next == "-") {
            type = Type::Number;
            std::string temp = next;
            if (next == "-")
                temp += parser.next(); // xyz after -

            if (parser.peek() == ".")
                temp += parser.next() + parser.next(); // .xyz

            numberValue = std::stod(temp);
        } else if (next == "\"") {
            type = Type::String;
            parser.rollback();
            stringValue = parseString(parser);
        } else if (next == "[") {
            type = Type::Array;

            while (!parser.reachedEnd()) {
                if (parser.peek() == "]") {
                    parser.next();
                    break;
                }

                arrayValue.push_back(Json().parse(parser));

                if (parser.peek() == ",") {
                    parser.next();
                }
            }
        } else if (next == "{") {
            type = Type::Object;

            while (!parser.reachedEnd()) {
                if (parser.peek() == "}") {
                    parser.next();
                    break;
                }

                std::string name = parseString(parser);

                if (parser.next() != ":")
                    throw std::runtime_error("Expected : after object name.");

                objectValue[name].parse(parser);

                if (parser.peek() == ",") {
                    parser.next();
                }
            }
        } else if (next == "null") {
            type = Type::Null;
        } else {
            throw std::runtime_error("Unknown object in json.");
        }

        return *this;
    }

    Json::Json(const std::string &text) {
        Parser parser(text);

        parse(parser);
    }
}