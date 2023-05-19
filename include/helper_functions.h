#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <ctime>

using json = nlohmann::json;

namespace HelperFunctions {
std::string create_random_id();

json load_json_from_file(std::string path_from_executable);
}  // namespace HelperFunctions
