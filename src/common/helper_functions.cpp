#include "helper_functions.h"

std::string HelperFunctions::create_random_id() {
    auto t =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    return std::to_string(std::hash<std::string>{}(std::to_string(t)));
}

json HelperFunctions::load_json_from_file(std::string path_from_executable) {
    // load json from file
    std::ifstream file(path_from_executable);

    return json::parse(file);
}

std::array<ShipData, 5> HelperFunctions::get_funny_ship_configuration() {
    return {ShipData{ShipCategory::Carrier, 0, 0, true},
            ShipData{ShipCategory::Battleship, 0, 1, true},
            ShipData{ShipCategory::Cruiser, 0, 2, true},
            ShipData{ShipCategory::Submarine, 0, 3, true},
            ShipData{ShipCategory::Destroyer, 0, 4, true}};
}