#include "connection_panel.h"

std::string ConnectionPanel::server_address_input_;
std::string ConnectionPanel::server_address_;
uint16_t ConnectionPanel::server_port_ = 0;

GameState* ConnectionPanel::game_state_ = nullptr;

void ConnectionPanel::init() {
    SDLGui::SDLGuiContext* connection_panel_context =
        new SDLGui::SDLGuiContext("connection_panel_context");

    SDLGui::ImageWidget* background_image = new SDLGui::ImageWidget(
        "background_image", "../assets/background_img.bmp", -.1f, .0f, 1.3f,
        1.f, 0.,
        SDLGui::ImageFlagsExt_CenterImageVertical |
            SDLGui::ImageFlagsExt_CenterImageHorizontal |
            SDLGui::ImageFlagsExt_NoBackground);
    connection_panel_context->addWidget(background_image);

    SDLGui::TextWidget* connect_to_server_text =
        new SDLGui::TextWidget("connect_to_server_text", "Connect to Server",
                               0, .0f, .05f, .6f, .1f, 0.,
                               SDLGui::TextFlagsExt_CenterText |
                                   SDLGui::TextFlagsExt_CenterHorizontal);
    connection_panel_context->addWidget(connect_to_server_text);

    SDLGui::TextWidget* server_address_text = new SDLGui::TextWidget(
        "server_address_text", "Server Address", 0, .1f, .4f, .3f, .06f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_CenterVertical |
            SDLGui::TextFlagsExt_NoBackground);
    connection_panel_context->addWidget(server_address_text);

    SDLGui::TextInputWidget* server_address_text_input =
        new SDLGui::TextInputWidget(
            server_address_input_, "server_address_input", 32, 0, .55f, .4f,
            .4f, .06f, 0.,
            SDLGui::TextInputFlagsExt_CenterText |
                SDLGui::TextInputFlagsExt_CenterVertical);
    connection_panel_context->addWidget(server_address_text_input);

    SDLGui::TextWidget* server_message_text = new SDLGui::TextWidget(
        "server_message_text", "", 0, .0f, .7f, .3f, .04f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    connection_panel_context->addWidget(server_message_text);

    SDLGui::TextButtonWidget* connection_button = new SDLGui::TextButtonWidget(
        "server_connection_button", "Connect", 0.f, .88f, .4f, .08f, 0.f,
        SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    connection_panel_context->addWidget(connection_button);

    SDLGui::pushContext(connection_panel_context);
}

void ConnectionPanel::render() {
    SDLGui::begin("connection_panel_context");

    static bool send_join_request = true;

    if (SDLGui::TextButton("server_connection_button")) {
        if (is_valid_ip_address(server_address_input_)) {
            if (!ClientNetworkManager::connect(server_address_, server_port_))
                SDLGui::Text("server_message_text")
                    .updateText(64, 0, "Failed to connect to %s:%hu",
                                server_address_.c_str(), server_port_);
            else {
                SDLGui::Text("server_message_text")
                    .updateText(64, 0, "Connecting to %s:%hu...",
                                server_address_.c_str(), server_port_);
                SDLGui::TextButton("server_connection_button").disable();
                SDLGui::TextInput("server_address_input").disable();
            }
        } else
            SDLGui::Text("server_message_text")
                .updateText(64, 0, "Invalid IP address %s",
                            server_address_input_.c_str());
    }

    if (ClientNetworkManager::get_connection_status() ==
        ClientNetworkConnectionStatus::CONNECTED) {
        SDLGui::Text("server_message_text")
            .updateText(64, 0, "Connected to %s:%hu", server_address_.c_str(),
                        server_port_);
        if (send_join_request) {
            ClientNetworkManager::send_message(JoinRequest().to_string());
            send_join_request = false;
        }
        if (game_state_->get_players().size() != 0)
            game_state_->set_phase(Lobby);
    } else {
        SDLGui::TextButton("server_connection_button").enable();
        SDLGui::TextInput("server_address_input").enable();
        send_join_request = true;
    }

    if (ClientNetworkManager::get_connection_status() ==
        ClientNetworkConnectionStatus::NOT_CONNECTED) {
        SDLGui::Text("server_message_text").updateText(64, 0, "");
    }

    SDLGui::end();
}

bool ConnectionPanel::is_valid_ip_address(const std::string& ip_address) {
    std::regex ipv4_regex(
        "(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|"
        "[1-"
        "9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\:[0-9]+");
    std::smatch ipv4_regex_match;
    std::regex localhost_regex("localhost\\:[0-9]+");
    std::smatch localhost_regex_match;
    if (std::regex_match(ip_address, ipv4_regex_match, ipv4_regex)) {
        std::cout << "Ipv4 matched" << std::endl;
        /* REGEX_MATCH SHOULD BE ABLE TO SPLIT THE STRING INTO COMPONENTS
         * (to be replaced if someone know how to make it work) */
        /*printf("%llu\n", ipv4_regex_match.size());
        for (uint32_t i = 0; i < ipv4_regex_match.size(); ++i) {
            printf("%s\n", ipv4_regex_match[i].str().c_str());
        }*/
        std::string::size_type n = ip_address.find(':');
        server_address_          = ip_address.substr(0, n);
        std::string port_substring =
            ip_address.substr(n + 1, ip_address.size() - n - 1);
        server_port_ = (uint16_t)std::stoi(port_substring);
        return true;
    } else if (std::regex_match(ip_address, localhost_regex_match,
                                localhost_regex)) {
        std::cout << "Localhost matched" << std::endl;
        std::string::size_type n = ip_address.find(':');
        server_address_          = ip_address.substr(0, n);
        std::string port_substring =
            ip_address.substr(n + 1, ip_address.size() - n - 1);
        server_port_ = (uint16_t)std::stoi(port_substring);
        return true;
    }

    return false;
}
