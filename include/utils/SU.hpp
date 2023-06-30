#include <vector>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

using jsonDictVector = std::vector<std::unordered_map<std::string, nlohmann::json>>;
template<typename T>
class SU {
private:
    T value;
    std::vector<std::string> keys;

public:
    SU(T val, std::initializer_list<std::string> keys) : value(val), keys(keys) {}

    void load(const nlohmann::json& json) {
        if constexpr (std::is_same_v<T, jsonDictVector>) {
            get_json_array(json, value, keys.begin(), keys.end());
        }
        else {
            get_json_value(json, value, keys.begin(), keys.end());
        }
    }

    void save(nlohmann::json& json) {
        if constexpr (std::is_same_v<T, jsonDictVector>) {
            nlohmann::json* jsonPtr = &json;
            for (const auto& key : keys) {
                jsonPtr = &((*jsonPtr)[key]);
            }
            *jsonPtr = loadToListJson(value);
        }
        else {
            nlohmann::json* jsonPtr = &json;
            for (const auto& key : keys) {
                jsonPtr = &((*jsonPtr)[key]);
            }
            *jsonPtr = value;
        }
    }

    auto begin() {
        return value.begin();
    }

    auto end() {
        return value.end();
    }

    bool operator==(const T& other) const {
        return value == other;
    }

    operator T() const {
        return value;
    }

    SU(const T& value) : value(value) {}

    auto& operator[](size_t index) {
        return value[index];
    }

    const auto& operator[](size_t index) const {
        return value[index];
    }

private:
    template<typename Iter>
    void get_json_value(const nlohmann::json& json, T& val, Iter it, Iter end) {
        if (it == end) {
            return;
        }

        const std::string& key = *it;
        if (json.find(key) != json.end()) {
            if (std::next(it) != end) {
                get_json_value(json.at(key), val, std::next(it), end);
            }
            else {
                const nlohmann::json& out = json.at(key);
                out.get_to(val);
            }
        }
    }

    template<typename Iter>
    void get_json_array(const nlohmann::json& json, jsonDictVector& val, Iter it, Iter end) {
        if (it == end) {
            return;
        }

        const std::string& key = *it;
        if (json.find(key) != json.end()) {
            if (std::next(it) != end) {
                get_json_array(json.at(key), val, std::next(it), end);
            }
            else {
                const nlohmann::json& out = json.at(key);
                if (!out.empty()) {
                    val.clear();
                    for (const auto& item : out) {
                        std::unordered_map<std::string, nlohmann::json> temp;
                        for (auto& element : item.items()) {
                            temp[element.key()] = element.value();
                        }
                        val.push_back(temp);
                    }
                }
            }
        }
    }

    nlohmann::json loadToListJson(const jsonDictVector& list) {
        nlohmann::json ListJson;
        for (const auto& item : list) {
            nlohmann::json itemJson = item;
            ListJson.push_back(itemJson);
        }
        return ListJson;
    }
};
