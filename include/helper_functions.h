#pragma once

#include <ctime>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "ship.h"

using json = nlohmann::json;

namespace HelperFunctions {
std::string create_random_id();

json load_json_from_file(std::string path_from_executable);

std::array<ShipData, 5> get_funny_ship_configuration();

}  // namespace HelperFunctions
