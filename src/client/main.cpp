#include <cstdint>
#include <cstdio>

#include "GameController.h"

int main(int argc, const char** argv) {
    //printf("Hello World from Client!\n");
    GameController::init();
    GameController::run();
    return 0;
}