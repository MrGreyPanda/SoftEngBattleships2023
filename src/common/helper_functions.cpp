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
    return {ShipData{ShipCategory::Destroyer, true, 6, 7},
            ShipData{ShipCategory::Submarine, true, 2, 7},
            ShipData{ShipCategory::Cruiser, true, 4, 5},
            ShipData{ShipCategory::Battleship, false, 7, 2},
            ShipData{ShipCategory::Carrier, true, 3, 6}};
}