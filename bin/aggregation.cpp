#include "aggregation.h"


uint8_t TotalWeatherCode(json& js, uint16_t start_index, uint16_t end_index) noexcept {
    std::map<uint8_t, uint8_t> freq_map;
    auto first = js["weathercode"].begin() + start_index;
    const auto last = js["weathercode"].begin() + end_index;
    for (; first != last; first++) {
        freq_map[first->get<uint8_t>()]++;
    }

    return std::max_element(freq_map.begin(), freq_map.end(),
                            [](const std::pair<uint8_t, uint8_t>& p1,
                               const std::pair<uint8_t, uint8_t>& p2)
                            {return p1.second < p2.second; })->first;
}

void AggregateDayInfo(MeteoData& meteo, json& js, uint16_t start_index, uint16_t end_index) noexcept {
    meteo.min_temp = MinJsonElement<float>(js, "temperature_2m", start_index, end_index);
    meteo.max_temp = MaxJsonElement<float>(js, "temperature_2m", start_index, end_index);
    meteo.precipitation = std::round(MeanJsonElement<float>(js, "precipitation", start_index, end_index) * 10) / 10;
    meteo.min_wind_speed = MinJsonElement<uint16_t>(js, "windspeed_10m", start_index, end_index);
    meteo.max_wind_speed = MaxJsonElement<uint16_t>(js, "windspeed_10m", start_index, end_index);
    meteo.wind_direction = static_cast<uint16_t>(std::round(MeanJsonElement<float>(js, "winddirection_10m", start_index, end_index)));
    meteo.humidity = static_cast<uint8_t>(std::round(MeanJsonElement<float>(js, "relativehumidity_2m", start_index, end_index)));
    meteo.visibility = static_cast<uint8_t>(std::round(MeanJsonElement<float>(js, "visibility", start_index, end_index) / 1000));
    meteo.weather_code = TotalWeatherCode(js, start_index, end_index);
}

void SaveInfo(City& city, json& js, uint8_t shown_days) noexcept {
    city.current_meteo.temp = js["current_weather"]["temperature"].get<float>();
    city.current_meteo.wind_speed = js["current_weather"]["windspeed"].get<uint16_t>();
    city.current_meteo.wind_direction = js["current_weather"]["winddirection"].get<uint16_t>();
    city.current_meteo.weather_code = js["current_weather"]["weathercode"].get<uint8_t>();
    city.days.clear();
    city.days.resize(shown_days);
    for (auto day = 0; day < shown_days; day++) {
        city.days[day].date = js["hourly"]["time"][24 * day].get<std::string>().substr(0, 10);
        AggregateDayInfo(city.days[day].meteo[0], js["hourly"], 24 * day, 24 * day + 9);
        AggregateDayInfo(city.days[day].meteo[1], js["hourly"], 24 * day + 9, 24 * day + 14);
        AggregateDayInfo(city.days[day].meteo[2], js["hourly"], 24 * day + 14, 24 * day + 21);
        AggregateDayInfo(city.days[day].meteo[3], js["hourly"], 24 * day + 21, 24 * day + 24);
    }
}
