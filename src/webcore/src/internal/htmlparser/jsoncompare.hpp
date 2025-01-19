#ifndef HTMLPARSER_SRC_JSON_COMPARE_H
#define HTMLPARSER_SRC_JSON_COMPARE_H

#include <sstream>

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

#define WARNING_QUOTE(data) '`' << data << '`'

#define WARNING_HEAD(data)  \
    if constexpr (true) {   \
        m_warnings << data; \
        m_warnings << '\n'; \
    }

#define WARNING_CONTENT(data) WARNING_HEAD("  " << data)

class JSONCompare {
public:
    JSONCompare(const nlohmann::ordered_json& source, const nlohmann::ordered_json& expected) {
        m_ok = compare(source, expected);
    }

    bool ok() { return m_ok; }

    std::string warnings() { return m_warnings.str(); }

private:
    bool compare_array(const nlohmann::ordered_json& source,
                       const nlohmann::ordered_json& expected) {
        bool is_same = true;

        // compare all fields in expected to source
        auto len = std::min(expected.size(), source.size());
        for (int i = 0; i < len; ++i) {
            auto source_item = source[i];
            auto expected_item = expected[i];

            if (source_item.is_array() || source_item.is_object() || expected_item.is_object() ||
                expected_item.is_array()) {
                m_path.push_back(std::to_string(i));
                is_same = is_same && compare(source_item, expected_item);
                m_path.pop_back();
            } else if (source_item != expected_item) {
                is_same = false;
            }
        }

        // all items left in source are invalid
        if (source.size() > len) {
            WARNING_HEAD("Unexpected array values");
            for (int i = len; i < source.size(); ++i) {
                is_same = false;
                m_path.push_back(std::to_string(i));
                WARNING_CONTENT("found " << WARNING_QUOTE(truncate(source[i].dump())))
                WARNING_CONTENT("  at " << path_string());
                m_path.pop_back();
            }
        }

        return is_same;
    }

    bool compare(const nlohmann::ordered_json& source, const nlohmann::ordered_json& expected) {
        bool is_same = true;

        // compare all fields in expected to source
        for (auto& it : expected.items()) {
            auto result = source.find(it.key());

            if (result == source.end()) {
                is_same = false;
                WARNING_HEAD("Missing field");
                WARNING_CONTENT("field " << WARNING_QUOTE(it.key()))
                WARNING_CONTENT("at " << path_string());
            } else if (result->is_object() && it.value().is_object()) {
                m_path.push_back(it.key());
                is_same = is_same && compare(*result, it.value());
                m_path.pop_back();
            } else if (result->is_array() && it.value().is_array()) {
                m_path.push_back(it.key());
                is_same = is_same && compare_array(*result, it.value());
                m_path.pop_back();
            } else if ((result->type() != it.value().type()) || (*result != it.value())) {
                is_same = false;
                WARNING_HEAD("Unexpected value");
                WARNING_CONTENT("field " << WARNING_QUOTE(it.key()))
                WARNING_CONTENT("expected " << WARNING_QUOTE(truncate(it.value().dump())))
                WARNING_CONTENT("found " << WARNING_QUOTE(truncate(result.value().dump())))
                WARNING_CONTENT("at " << path_string());
            }
        }

        // all fields in source which are not in expected are invalid
        for (auto& it : source.items()) {
            auto result = expected.find(it.key());
            if (result != expected.end()) continue;

            is_same = false;
            WARNING_HEAD("Unexpected field");
            WARNING_CONTENT("field " << WARNING_QUOTE(it.key()))
            WARNING_CONTENT("expected " << WARNING_QUOTE(truncate(it.value().dump())))
            WARNING_CONTENT("found " << WARNING_QUOTE(truncate(it.value().dump())))
            WARNING_CONTENT("at " << path_string());
        }

        return is_same;
    }

    std::string truncate(const std::string& str) {
        const size_t max = 50;
        if (str.length() > max) return str.substr(0, max - 3) + "...";
        return str;
    }

    std::string path_string() {
        std::string str;
        str.push_back('\'');
        if (m_path.empty()) {
            str.push_back('.');
        } else {
            for (auto s : m_path) {
                str += '.' + s;
            }
        }
        str.push_back('\'');

        return str;
    }

private:
    bool m_ok;
    std::vector<std::string> m_path;
    std::stringstream m_warnings;
};

#endif  // !HTMLPARSER_SRC_JSON_COMPARE_H
