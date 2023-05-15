
#include <thread>

#include "server_network_manager.h"

int main(int argc, const char** argv) {
    std::thread server_thread(ServerNetworkManager::start, 1337);
    // server_thread.detach();

    server_thread.join();

    return 0;
}
