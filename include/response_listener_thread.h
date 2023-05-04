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
    /**
     * @brief  threaded loop which deals with incoming server responses
     */
    //virtual ExitCode entry(); //from wxwidgets?


private:
    /**
     * @brief communicates error to the user
     * @param title
     * @param message
     */
    void output_error_(std::string title, std::string message);

    /**
     * @brief a tcp connector on which the listener listens for incoming responses
     */
    sockpp::tcp_connector* connection_;



};