#pragma once

#include <string>

std::string create_random_id() {
    return std::to_string(std::hash<std::string>{}(std::to_string(rand())));
}