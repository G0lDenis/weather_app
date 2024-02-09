#ifndef WEATHER_APP_AGGREGATION_H
#define WEATHER_APP_AGGREGATION_H

#include <nlohmann/json.hpp>

using nlohmann::json;

struct ExactMeteoData {
    float temp;
    uint16_t wind_speed;
    uint16_t wind_direction;
    uint8_t weather_code;
};

struct MeteoData {
    float min_temp;
    float max_temp;
    float precipitation;
    uint16_t min_wind_speed;
    uint16_t max_wind_speed;
    uint16_t wind_direction;
    uint8_t weather_code;
    uint8_t humidity;
    uint8_t visibility;
};

struct Day {
    std::string date;
    MeteoData meteo[4]{};
};

struct City {
    std::string name;
    std::string country;
    std::pair<float, float> coordinates;
    ExactMeteoData current_meteo;
    std::vector<Day> days;
};

template<typename T>
T MaxJsonElement(json& js, const std::string& key, uint16_t start_index, uint16_t end_index) noexcept {
    auto first = js[key].begin() + start_index;
    const auto last = js[key].begin() + end_index;
    T value = first->get<T>();
    for (; first != last; first++) {
        value = std::max(value, first->get<T>());
    }

    return value;
}

template<typename T>
T MinJsonElement(json& js, const std::string& key, uint16_t start_index, uint16_t end_index) noexcept {
    auto first = js[key].begin() + start_index;
    const auto last = js[key].begin() + end_index;
    T value = first->get<T>();
    for (; first != last; first++) {
        value = std::min(value, first->get<T>());
    }

    return value;
}

template<typename T>
float MeanJsonElement(json& js, const std::string& key, uint16_t start_index, uint16_t end_index) noexcept {
    float value{};
    auto first = js[key].begin() + start_index;
    const auto last = js[key].begin() + end_index;
    for (; first != last; first++) {
        value += first->get<T>();
    }

    return value / (float) (end_index - start_index);
}

void AggregateDayInfo(MeteoData& meteo, json& js, uint16_t start_index, uint16_t end_index) noexcept;

void SaveInfo(City& city, json& js, uint8_t shown_days) noexcept;

#endif //WEATHER_APP_AGGREGATION_H
