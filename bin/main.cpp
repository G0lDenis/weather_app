#include "aggregation.cpp"
#include "interface.cpp"

#include <cpr/cpr.h>

#include <unistd.h>
#include <termios.h>
#include <chrono>

using nlohmann::json;

std::vector<City> cities;
uint8_t shown_days;
uint32_t update_frequency;
uint8_t current_city = 0;

void ParseConfiguration() {
    std::ifstream cfg_str("config.json");
    if (!cfg_str.is_open()) {
        throw std::runtime_error("Error during opening config. Please check that config.json exists and is correct");
    }
    json cfg = json::parse(cfg_str);
    std::ifstream file_key("api-key.txt");
    if (!file_key.is_open()) {
        throw std::runtime_error(
            "Error during opening file with api key. Please check that api-key.txt exists and is correct");
    }
    std::string key;
    std::getline(file_key, key);
    if (!cfg.contains("cities")) {
        throw std::runtime_error("Key \"cities\" was not found in config file");
    }

    for (const auto& city: cfg["cities"]) {
        std::string city_str = city.get<std::string>();
        if (std::find_if(cities.begin(), cities.end(),
                         [&city_str](const City& city) {
                             return city.name == city_str;
                         }) == cities.end()) {
            cpr::Response response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city"},
                                              cpr::Header{{"X-Api-Key", key}},
                                              cpr::Parameters{{"name", city_str}});
            if (response.status_code != 200 || response.text == "[]") {
                throw std::runtime_error("Can't find city \"" + city_str + "\". "
                                             "Please check your internet connection or correctness of name of searched city");
            }
            json data = json::parse(response.text);
            auto country = data[0]["country"].get<std::string>();
            auto latitude = data[0]["latitude"].get<float>();
            auto longitude = data[0]["longitude"].get<float>();
            cities.emplace_back(City(city_str, country, {latitude, longitude}));
        }
    }
    if (!cfg.contains("days")) {
        throw std::runtime_error("Key \"days\" was not found in config file");
    }
    shown_days = cfg["days"].get<uint32_t>();
    if (shown_days == 0 || shown_days > 7) {
        throw std::logic_error("Key \"days\" must contain number more than 0 and less than 8");
    }
    if (!cfg.contains("update_frequency")) {
        throw std::runtime_error("Key \"update_frequency\" was not found in config file");
    }
    update_frequency = cfg["update_frequency"].get<uint32_t>();
}

void UpdateMeteo() noexcept {
    for (auto& city: cities) {
        cpr::Response response = cpr::Get(cpr::Url{"https://api.open-meteo.com/v1/forecast"},
                                          cpr::Parameters{
                                              {"latitude",        std::to_string(city.coordinates.first)},
                                              {"longitude",       std::to_string(city.coordinates.second)},
                                              {"hourly",          "temperature_2m,relativehumidity_2m,"
                                                                  "precipitation,weathercode,visibility,"
                                                                  "windspeed_10m,winddirection_10m"},
                                              {"current_weather", "true"},
                                              {"timezone",        "Europe/Moscow"},
                                              {"forecast_days",   std::to_string(shown_days)}
                                          });
        if (response.status_code == 200) {
            json data = json::parse(response.text);
            SaveInfo(city, data, shown_days);
        }
    }
}

bool ReactOnKeyboard(const char key) {
    switch (key) {
        case 'n':
            current_city = (current_city == cities.size() - 1 ? 0 : current_city + 1);
            PrintCity(cities[current_city]);
            break;
        case 'p':
            current_city = (current_city ? current_city - 1 : cities.size() - 1);
            PrintCity(cities[current_city]);
            break;
        case '+':
            if (shown_days < 7) {
                shown_days++;
                UpdateMeteo();
                PrintCity(cities[current_city]);
            }
            break;
        case '-':
            if (shown_days > 1) {
                shown_days--;
                for (auto& city: cities) {
                    city.days.pop_back();
                }
                PrintCity(cities[current_city]);
            }
            break;
        case 27:
            return false;
        default:
            break;
    }

    return true;
}

static struct termios stored_settings;

void SetTerminal() {
    termios new_settings{};

    tcgetattr(STDIN_FILENO, &stored_settings);

    new_settings = stored_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void ResetTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &stored_settings);
}

int kbhit()
{
    timeval tv{};
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

int main() {
    try {
        ParseConfiguration();
    }
    catch (std::exception& ex) {
        std::cerr << ex.what() << "\n";
        exit(0);
    }
    UpdateMeteo();
    PrintCity(cities[current_city]);

    SetTerminal();
    auto start_time = std::chrono::steady_clock::now();

    int i = 0;
    int read_c;
    while(!i) {
        usleep(1);
        i = kbhit();
        if (i) {
            read_c = fgetc(stdin);
            i = !ReactOnKeyboard(static_cast<char>(read_c));
        }
        if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() -
                                                             start_time).count() >= update_frequency) {
            start_time = std::chrono::steady_clock::now();
            UpdateMeteo();
            PrintCity(cities[current_city]);
        }
    }
    ClearConsole();
    ResetTerminal();

    return 0;
}
