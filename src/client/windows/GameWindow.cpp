#include "GameWindow.h"

char ConnectionWindow::m_server_address_input[33];
char ConnectionWindow::m_server_address[33];
uint16_t ConnectionWindow::m_server_port = 0;

void ConnectionWindow::init()
{
    memset(m_server_address_input, '\0', 33 * sizeof(char));
    memset(m_server_address, '\0', 33 * sizeof(char));
    SDLGui::SDLGuiContext* connectionWindowContext = 
        new SDLGui::SDLGuiContext("connectionWindow");

    SDLGui::TextWidget* connectToServerText = 
        new SDLGui::TextWidget("connectToServerText", "Connect to Server", 
            .06f, .1f, .4f, .09f, 0., SDLGui::TextFlagsExt_CenterTextVertical | SDLGui::TextFlagsExt_NoBackground);
    connectionWindowContext->addWidget(connectToServerText);

    SDLGui::TextWidget* serverAddressText = 
        new SDLGui::TextWidget("serverAddressText", "Server Address", 
            .1f, .4f, .3f, .06f, 0., SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground);
    connectionWindowContext->addWidget(serverAddressText);

    SDLGui::TextInputWidget* serverAddressTextInput = 
        new SDLGui::TextInputWidget("serverAddressInput", m_server_address_input, 32,
            .55f, .4f, .4f, .06f, 0., SDLGui::TextInputFlagsExt_CenterText);
    connectionWindowContext->addWidget(serverAddressTextInput);

    SDLGui::TextWidget* serverMessageText = 
        new SDLGui::TextWidget("serverMessageText", "", 
            .0f, .7f, .3f, .04f, 0., SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground | SDLGui::TextFlagsExt_CenterHorizontal);
    connectionWindowContext->addWidget(serverMessageText);

    SDLGui::TextButtonWidget* connectionButton = 
        new SDLGui::TextButtonWidget("serverConnectionButton", "Connect",
            0.f, .8f, .3f, .08f, 0., SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    connectionWindowContext->addWidget(connectionButton);

    SDLGui::SDLGuiEnvironment::pushContext(connectionWindowContext);
}

void ConnectionWindow::render()
{
    SDLGui::begin("connectionWindow");

    if (SDLGui::TextButton("serverConnectionButton")) {
        if (check_server_address()) {
            if (!ClientNetworkManager::connect(m_server_address, m_server_port))
                SDLGui::Text("serverMessageText").updateText(64, "Failed to connect to %s:%hu", m_server_address, m_server_port);
            else {
                SDLGui::Text("serverMessageText").updateText(64, "Connecting to %s:%hu...", m_server_address, m_server_port);
                SDLGui::TextButton("serverConnectionButton").disable();
                SDLGui::TextInput("serverAddressInput").disable();
                ClientNetworkManager::send_request(ClientRequest(ClientRequestType::Join));
            }
        }
    }

    if (ClientNetworkManager::get_connection_status() == ClientNetworkConnectionStatus::CONNECTED)
        SDLGui::Text("serverMessageText").updateText(64, "Connected to %s:%hu", m_server_address, m_server_port);

    SDLGui::end();
}

bool ConnectionWindow::check_server_address()
{
    size_t address_size = strlen(m_server_address_input);
    uint32_t dots_found = 0;
    char buffer[16];
    uint32_t buffer_index = 0;
    size_t i = 0;
    for (i = 0; i < address_size; ++i) {
        if (m_server_address_input[i] == ':') break;
        m_server_address[i] = m_server_address_input[i];
        if (m_server_address_input[i] == '.') {
            dots_found++;
            continue;
        }
        if (m_server_address_input[i] < '0' || m_server_address_input[i] > '9') return false;
    }
    if (i == address_size - 1) return false;    //No ':' found
    i++;
    for (; i < address_size; ++i) {
        buffer[buffer_index++] = m_server_address_input[i];
    }
    m_server_port = (uint16_t)atoi(buffer);

    return true;
}
