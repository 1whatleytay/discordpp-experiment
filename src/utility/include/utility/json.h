#pragma once

#include <utility/parser.h>
#include <utility/optional.h>

#include <vector>
#include <unordered_map>

namespace utility {
    class Json {
        bool booleanValue = false;
        double numberValue = 0;
        std::string stringValue;
        std::vector<Json> arrayValue;
        std::unordered_map<std::string, Json> objectValue;

    public:
        enum class Type {
            Boolean,
            Number,
            String,
            Array,
            Object,
            Null,
            Empty,
        };

        Type type = Type::Object;

        Optional<bool> boolean() const;
        Optional<double> number() const;
        Optional<std::string> string() const;
        Json at(size_t index) const;
        Json at(const std::string &key) const;

//        template <typename T>
//        Optional<T> asNumber() const {
//            Optional<double> optional = number();
//            if (optional.empty())
//                return Optional<T>();
//
//            return Optional<T>(optional.get());
//        }
//
//        template <typename T>
//        Optional<T> asString() const {
//            Optional<std::string> optional = string();
//            if (optional.empty())
//                return Optional<T>();
//
//            return Optional<T>(optional.get());
//        }

        bool empty() const;
        bool has(size_t index) const;
        bool has(const std::string &key) const;
        size_t getSize() const;

        Json operator[](size_t index) const;
        Json operator[](const std::string &key) const;

        Json clear();
        Json parse(utility::Parser &parser);

        Json() = default;
        explicit Json(const std::string &text);
    };
}