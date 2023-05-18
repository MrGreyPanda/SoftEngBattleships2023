#include "connection_panel.h"

std::string ConnectionPanel::server_address_input_;
std::string ConnectionPanel::server_address_;
uint16_t ConnectionPanel::server_port_ = 0;

GameState* ConnectionPanel::game_state_ = nullptr;

void ConnectionPanel::init() {
    SDLGui::SDLGuiContext* connection_panel_context =
        new SDLGui::SDLGuiContext("connection_panel_context");

    SDLGui::TextWidget* connect_to_server_text = new SDLGui::TextWidget(
        "connect_to_server_text", "Connect to Server", .06f, .1f, .4f, .09f, 0.,
        SDLGui::TextFlagsExt_CenterTextVertical |
            SDLGui::TextFlagsExt_NoBackground);
    connection_panel_context->addWidget(connect_to_server_text);

    SDLGui::TextWidget* server_address_text = new SDLGui::TextWidget(
        "server_address_text", "Server Address", .1f, .4f, .3f, .06f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground);
    connection_panel_context->addWidget(server_address_text);

    SDLGui::TextInputWidget* server_address_text_input =
        new SDLGui::TextInputWidget(
            server_address_input_, "server_address_input", 32, .55f, .4f, .4f,
            .06f, 0., SDLGui::TextInputFlagsExt_CenterText);
    connection_panel_context->addWidget(server_address_text_input);

    SDLGui::TextWidget* server_message_text = new SDLGui::TextWidget(
        "server_message_text", "", .0f, .7f, .3f, .04f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    connection_panel_context->addWidget(server_message_text);

    SDLGui::TextButtonWidget* connection_button = new SDLGui::TextButtonWidget(
        "server_connection_button", "Connect", 0.f, .8f, .3f, .08f, 0.,
        SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    connection_panel_context->addWidget(connection_button);

    SDLGui::SDLGuiEnvironment::pushContext(connection_panel_context);
}

void ConnectionPanel::render() {
    SDLGui::begin("connection_panel_context");

    if (SDLGui::TextButton("server_connection_button")) {
        if (check_server_address()) {
            if (!ClientNetworkManager::connect(server_address_,
                                               server_port_))
                SDLGui::Text("server_message_text")
                    .updateText(64, "Failed to connect to %s:%hu",
                                server_address_.c_str(), server_port_);
            else {
                SDLGui::Text("server_message_text")
                    .updateText(64, "Connecting to %s:%hu...",
                                server_address_.c_str(), server_port_);
                SDLGui::TextButton("server_connection_button").disable();
                SDLGui::TextInput("server_address_input").disable();
                //ClientNetworkManager::send_request(JoinRequest());
            }
        }
        else
            SDLGui::Text("server_message_text").updateText(64, "Invalid address %s", server_address_input_.c_str());
    }

    if (ClientNetworkManager::get_connection_status() ==
        ClientNetworkConnectionStatus::CONNECTED) {
        SDLGui::Text("server_message_text")
            .updateText(64, "Connected to %s:%hu", server_address_.c_str(),
                        server_port_);
        game_state_->set_phase(Lobby);
        
    }

    SDLGui::end();
}

bool ConnectionPanel::check_server_address() {
    std::regex ipv4_regex("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\:[0-9]+");
    std::smatch ipv4_regex_match;
    if (std::regex_match(server_address_input_, ipv4_regex_match, ipv4_regex)) {
        /* REGEX_MATCH SHOULD BE ABLE TO SPLIT THE STRING INTO COMPONENTS (to be replaced if someone know how to make it work) */
        /*printf("%llu\n", ipv4_regex_match.size());
        for (uint32_t i = 0; i < ipv4_regex_match.size(); ++i) {
            printf("%s\n", ipv4_regex_match[i].str().c_str());
        }*/
        std::string::size_type n = server_address_input_.find(':');
        server_address_ = server_address_input_.substr(0, n);
        std::string port_substring = server_address_input_.substr(n + 1, server_address_input_.size() - n - 1);
        server_port_ = (uint16_t)std::stoi(port_substring);
        return true;
    }

    return false;
}
