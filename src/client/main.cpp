
#include <cstdint>
#include <cstdio>

#include "client_network_manager.h"
#include "game_controller.h"

int main(int argc, const char** argv) {
    GameController::init();
    GameController::run();
    return 0;
}