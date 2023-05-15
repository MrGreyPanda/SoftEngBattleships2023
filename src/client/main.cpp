
#include <cstdint>
#include <cstdio>

#include "GameController.h"
#include "client_network_manager.h"

int main(int argc, const char** argv) {
    GameController::init();
    GameController::run();
    return 0;
}