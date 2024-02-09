#include <iostream>
#include <map>

std::map<uint8_t, std::pair<std::string, uint8_t>> weather_codes{
    {0,  {"Clear",                         0}},
    {1,  {"Mainly clear",                  0}},
    {2,  {"Partly cloudy",                 1}},
    {3,  {"Overcast",                      2}},
    {45, {"Fog",                           3}},
    {48, {"Fog",                           3}},
    {51, {"Light drizzle",                 4}},
    {53, {"Moderate drizzle",              4}},
    {55, {"Dense drizzle",                 4}},
    {56, {"Moderate drizzle",              4}},
    {57, {"Dense drizzle",                 4}},
    {61, {"Slight rain",                   5}},
    {63, {"Moderate rain",                 6}},
    {65, {"Heavy rain",                    6}},
    {66, {"Light freezy rain",             7}},
    {67, {"Heavy freezy rain",             7}},
    {71, {"Slight snow fall",              9}},
    {73, {"Medium snow fall",              8}},
    {75, {"Heavy snow fall",               8}},
    {77, {"Snow grains",                   9}},
    {80, {"Slight rain show…",             10}},
    {81, {"Medium rain show…",             11}},
    {82, {"Violent rain sho…",             11}},
    {85, {"Slight snow show…",             12}},
    {86, {"Heavy snow shower",             13}},
    {95, {"Thunderstorm",                  14}},
    {96, {"T/s + slight hail",             15}},
    {99, {"T/s + heavy hail",              15}}
};

std::string pictures[][5] = {
    {"\033[38;5;226m    \\   /    \033[0m",
    "\033[38;5;226m     .-.     \033[0m",
    "\033[38;5;226m  ‒ (   ) ‒  \033[0m",
    "\033[38;5;226m     `-᾿     \033[0m",
    "\033[38;5;226m    /   \\    \033[0m"},
    {"\033[38;5;226m   \\  /\033[0m      ",
    "\033[38;5;226m _ /\"\"\033[38;5;250m.-.    \033[0m",
    "\033[38;5;226m   \\_\033[38;5;250m(   ).  \033[0m",
    "\033[38;5;226m   /\033[38;5;250m(___(__) \033[0m",
        "             "},
    {"             ",
    "\033[38;5;250m     .--.    \033[0m",
    "\033[38;5;250m  .-(    ).  \033[0m",
    "\033[38;5;250m (___.__)__) \033[0m",
    "             "},
    {"             ",
    "\033[38;5;251m _ - _ - _ - \033[0m",
    "\033[38;5;251m  _ - _ - _  \033[0m",
    "\033[38;5;251m _ - _ - _ - \033[0m",
    "             "},
    {"\033[38;5;250m     .-.     \033[0m",
    "\033[38;5;250m    (   ).   \033[0m",
    "\033[38;5;250m   (___(__)  \033[0m",
    "\033[38;5;111m    ʻ \033[38;5;255m*\033[38;5;111m ʻ \033[38;5;255m*  \033[0m",
    "\033[38;5;255m   *\033[38;5;111m ʻ \033[38;5;255m*\033[38;5;111m ʻ   \033[0m"},
    {"\033[38;5;250m     .-.     \033[0m",
    "\033[38;5;250m    (   ).   \033[0m",
    "\033[38;5;250m   (___(__)  \033[0m",
    "\033[38;5;111m    ʻ ʻ ʻ ʻ  \033[0m",
    "\033[38;5;111m   ʻ ʻ ʻ ʻ   \033[0m"},
    {"\033[38;5;240;1m     .-.     \033[0m",
    "\033[38;5;240;1m    (   ).   \033[0m",
    "\033[38;5;240;1m   (___(__)  \033[0m",
    "\033[38;5;21;1m  ‚ʻ‚ʻ‚ʻ‚ʻ   \033[0m",
    "\033[38;5;21;1m  ‚ʻ‚ʻ‚ʻ‚ʻ   \033[0m"},
    {"\033[38;5;226m _`/\"\"\033[38;5;250m.-.    \033[0m",
    "\033[38;5;226m  ,\\_\033[38;5;250m(   ).  \033[0m",
    "\033[38;5;226m   /\033[38;5;250m(___(__) \033[0m",
    "\033[38;5;111m     ʻ \033[38;5;255m*\033[38;5;111m ʻ \033[38;5;255m* \033[0m",
    "\033[38;5;255m    *\033[38;5;111m ʻ \033[38;5;255m*\033[38;5;111m ʻ  \033[0m"},
    {"\033[38;5;250m     .-.     \033[0m",
    "\033[38;5;250m    (   ).   \033[0m",
    "\033[38;5;250m   (___(__)  \033[0m",
    "\033[38;5;255m   * * * *   \033[0m",
    "\033[38;5;255m  * * * *    \033[0m"},
    {"\033[38;5;250m     .-.     \033[0m",
    "\033[38;5;250m    (   ).   \033[0m",
    "\033[38;5;250m   (___(__)  \033[0m",
    "\033[38;5;255m    *  *  *  \033[0m",
    "\033[38;5;255m   *  *  *   \033[0m"},
    {"\033[38;5;226m _`/\"\"\033[38;5;250m.-.    \033[0m",
    "\033[38;5;226m  ,\\_\033[38;5;250m(   ).  \033[0m",
    "\033[38;5;226m   /\033[38;5;250m(___(__) \033[0m",
    "\033[38;5;111m     ʻ ʻ ʻ ʻ \033[0m",
    "\033[38;5;111m    ʻ ʻ ʻ ʻ  \033[0m"},
    {"\033[38;5;226m _`/\"\"\033[38;5;240;1m.-.    \033[0m",
    "\033[38;5;226m  ,\\_\033[38;5;240;1m(   ).  \033[0m",
    "\033[38;5;226m   /\033[38;5;240;1m(___(__) \033[0m",
    "\033[38;5;21;1m   ‚ʻ‚ʻ‚ʻ‚ʻ  \033[0m",
    "\033[38;5;21;1m   ‚ʻ‚ʻ‚ʻ‚ʻ  \033[0m"},
    {"\033[38;5;226m _`/\"\"\033[38;5;250m.-.    \033[0m",
    "\033[38;5;226m  ,\\_\033[38;5;250m(   ).  \033[0m",
    "\033[38;5;226m   /\033[38;5;250m(___(__) \033[0m",
    "\033[38;5;255m     *  *  * \033[0m",
    "\033[38;5;255m    *  *  *  \033[0m"},
    {"\033[38;5;226m _`/\"\"\033[38;5;240;1m.-.    \033[0m",
    "\033[38;5;226m  ,\\_\033[38;5;240;1m(   ).  \033[0m",
    "\033[38;5;226m   /\033[38;5;240;1m(___(__) \033[0m",
    "\033[38;5;255;1m    * * * *  \033[0m",
    "\033[38;5;255;1m   * * * *   \033[0m"},
    {"\033[38;5;240;1m     .-.     \033[0m",
    "\033[38;5;240;1m    (   ).   \033[0m",
    "\033[38;5;240;1m   (___(__)  \033[0m",
    "\033[38;5;21;1m  ‚ʻ\033[38;5;228;5m⚡\033[38;5;21;25mʻ‚\033[38;5;228;5m⚡\033[38;5;21;25m‚ʻ \033[0m",
    "\033[38;5;21;1m  ‚ʻ‚ʻ\033[38;5;228;5m⚡\033[38;5;21;25mʻ‚ʻ  \033[0m"},
    {"\033[38;5;226m _`/\"\"\033[38;5;250m.-.    \033[0m",
    "\033[38;5;226m  ,\\_\033[38;5;250m(   ).  \033[0m",
    "\033[38;5;226m   /\033[38;5;250m(___(__) \033[0m",
    "\033[38;5;228;5m  ⚡\033[38;5;111;25mʻ ʻ\033[38;5;228;5m⚡\033[38;5;111;25mʻ ʻ \033[0m",
    "\033[38;5;111m    ʻ ʻ ʻ ʻ  \033[0m"}
};

std::string FindRotation(uint16_t angle) {
    switch (angle) {
        case 0 ... 22:
        case 338 ... 360:
            return "↑";
        case 23 ... 67:
            return "↗";
        case 68 ... 112:
            return "→";
        case 113 ... 157:
            return "↘";
        case 158 ... 202:
            return "↓";
        case 203 ... 247:
            return "↙";
        case 248 ... 292:
            return "←";
        default:
            return "↖";
    }
}

void ClearConsole() {
    system("clear");
}

void PrintCurrentDayInfo(const ExactMeteoData& data) noexcept {
    std::string* picture = pictures[weather_codes[data.weather_code].second];
    std::cout << picture[0] << '\n';
    std::cout << picture[1] << weather_codes[data.weather_code].first << '\n';
    std::cout << picture[2] << std::fixed << std::setprecision(1) << (data.temp > 0 ? "+" : "") << data.temp << " °C\n";
    std::cout << picture[3] << FindRotation(data.wind_direction) << ' ' << data.wind_speed << " km/h\n";
    std::cout << picture[4] << '\n';
}

void PrintRow(std::string row_pics[4], std::pair<std::string, uint8_t> row_data[4]) noexcept {
    std::cout << "│";
    std::cout.setf(std::ios::left);
    for (auto col = 0; col < 4; col++) {
        std::cout << row_pics[col] << std::setw(17 + static_cast<int>(row_data[col].first.length() - row_data[col].second))
                  << row_data[col].first << "│";
    }
    std::cout << '\n';
}

void PrintTableDayInfo(const Day& day) noexcept {
    const MeteoData* data = day.meteo;
    std::cout << "                                                       ┌─────────────┐                                                       \n"
                 "┌──────────────────────────────┬───────────────────────┤ " << day.date << "  ├───────────────────────┬──────────────────────────────┐\n";
    std::cout << "│           Morning            │             Noon      └──────┬──────┘    Evening            │            Night             │\n"
                 "├──────────────────────────────┼──────────────────────────────┼──────────────────────────────┼──────────────────────────────┤\n";

    std::ios init(nullptr);
    init.copyfmt(std::cout);

    for (auto row = 0; row < 5; row++) {
        std::stringstream stream;
        std::string row_pics[4];
        std::pair<std::string, uint8_t> row_data[4];
        for (auto col = 0; col < 4; col++) {
            row_pics[col] = pictures[weather_codes[(data + col)->weather_code].second][row];
            switch (row) {
                case 0:
                    stream << weather_codes[(data + col)->weather_code].first;
                    break;
                case 1:
                    stream << std::fixed << std::setprecision(1)
                           << ((data + col)->max_temp > 0 ? "+" : "") << (data + col)->max_temp << '('
                           << ((data + col)->min_temp > 0 ? "+" : "") << (data + col)->min_temp << ") °C";
                    break;
                case 2:
                    stream << FindRotation((data + col)->wind_direction) << ' '
                           << (data + col)->min_wind_speed << '-' << (data + col)->max_wind_speed << " km/h";
                    break;
                case 3:
                    stream << static_cast<int>((data + col)->visibility) << " km";
                    break;
                default:
                    stream << static_cast<int>((data + col)->humidity) << "% | "
                           << std::fixed << std::setprecision(1)
                           << (data + col)->precipitation << " mm";
            }
            uint8_t length = stream.str().length();
            if (row == 1) length--;
            else if (row == 2) length -= 2;
            row_data[col] = {stream.str(), length};
            stream.str("");
        }

        PrintRow(row_pics, row_data);
        std::cout.copyfmt(init);
    }

    std::cout << "└──────────────────────────────┴──────────────────────────────┴──────────────────────────────┴──────────────────────────────┘\n";
}

void PrintCity(const City& city) noexcept {
    ClearConsole();
    std::cout << "Weather for city " << city.name << ", " << city.country << ":\n\n";
    PrintCurrentDayInfo(city.current_meteo);
    for (auto& day: city.days) {
        PrintTableDayInfo(day);
    }
}
