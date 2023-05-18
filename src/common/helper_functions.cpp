#include "helper_functions.h"

std::string HelperFunctions::create_random_id() {
    auto t = std::time(nullptr);
    return std::to_string(std::hash<std::string>{}(std::to_string(t)));
}

json HelperFunctions::load_json_from_file(std::string path_from_executable) {
    // load json from file
    std::ifstream file(path_from_executable);

    return json::parse(file);
}
