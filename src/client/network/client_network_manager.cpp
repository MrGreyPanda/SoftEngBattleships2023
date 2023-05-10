

#include "client_network_manager.h"

#include <nlohmann/json.hpp>
#include <thread>

#include "helper_functions.h"
#include "player.h"
#include "server_response.h"
#include <sockpp/exception.h>



using json = nlohmann::json;

//initialise static members
sockpp::tcp_connector* ClientNetworkManager::connection_ = nullptr;

bool ClientNetworkManager::connection_success_ = false;
bool ClientNetworkManager::failed_to_connect_ = false;

void::ClientNetworkManager::init(const std::string& host, const uint16_t port){
    //initialise sockpp framework
    //sockpp::socket_initializer sock_init;

    //reset connection status
    ClientNetworkManager::connection_success_ = false;
    ClientNetworkManager::failed_to_connect_ = false;

    //delete exiting connection and create new one
    if(ClientNetworkManager::connection_!= nullptr){
        ClientNetworkManager::connection_->shutdown();
        delete ClientNetworkManager::connection_;
    }
    ClientNetworkManager::connection_ = new sockpp::tcp_connector();

    //try connecting to server
    if(ClientNetworkManager::connect_(host, port)){
        //GameController::showStatus("Connected
        //TODO: tell GameController that you're connected to host on port
        ClientNetworkManager::connection_success_=true;

        //start network thread
        ResponseListenerThread* response_listener_thread= new ResponseListenerThread(ClientNetworkManager::connection_);

        //TODO: check if no error, showError if there is an error
        //if(response_listener_thread->Run() != )
    }   else    {
        ClientNetworkManager::failed_to_connect_ = true;
        //TODO:
        //GameController::showStatus("Not connected");
    }
}


bool ClientNetworkManager::connect_(const std::string &host, const uint16_t port) {
    //create sockpp address and catch any errors
    sockpp::inet_address address;
    try {
        //TODO: inet_address(host, port);
        //address = sockpp::inet_address(host,port);
    }   catch (const sockpp::getaddrinfo_error& e) {
        //TODO:
        //GameController::showError("Connection error",
        return false;
    }

    //establish connection to given address
    if (!ClientNetworkManager::connection_->connect(address)){
        //TODO:
        //GameController::showError
        return false;
    }
    return true; //connect worked
}


void ClientNetworkManager::send_request(const ClientRequest &request) {
    //wait until network connected (max. 5 sec)
    int connection_check_counter = 0;
    while(!ClientNetworkManager::connection_success_
        && !ClientNetworkManager::failed_to_connect_
        && connection_success_ < 200){
        //TODO: do 25 Millisleep and increase counter
        //wxMilliSleep(25);
        //connection_check_counter++; //increase the counter
    }

    //don't continue if failed to connect to server
    if(ClientNetworkManager::failed_to_connect_){
        return;
    }

    if(ClientNetworkManager::connection_success_ && ClientNetworkManager::connection_->is_connected()){

        //serialise request into JSON string
        //TODO:

        //turn message into stream and prepend message length

        //output message for debugging purposes
        //#ifdef PRINT_NETWORK_MESSAGES
        //std::cout << "Sending request : " << message << std::endl;
        //#endif

        //send message to server
        ssize_t bytesSent = ClientNetworkManager::connection_->write(message);

        //if number of bytes sent doesn't match length of message, something probably went wrong
        if (bytesSent != ssize_t(message.length())){
            //TODO:
            //GameController::showError...
        }

    } else {
        //TODO:
        //GameController::showError...
    }
}





