#include <functional>
#include <shared_mutex>
#include <unordered_map>
#include <string>

#include "client_request.h"
#include "server_response.h"
#include "sockpp/tcp_acceptor.h"
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_connector.h"



class ResponseListenerThread {

public:

    ResponseListenerThread(sockpp::tcp_connector* connection);
    ~ResponseListenerThread();

protected:
    virtual ExitCode Entry();


private:
    void outputError(std::string title, std::string message);

    sockpp::tcp_connector* connection_;



};