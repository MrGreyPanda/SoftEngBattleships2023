#include "GameWindow.h"

char ConnectionWindow::m_serverAddress[20];
uint16_t ConnectionWindow::m_serverPort = 0;

void ConnectionWindow::init()
{
    SDLGui::SDLGuiContext* connectionWindowContext = 
        new SDLGui::SDLGuiContext("connectionWindow");

    SDLGui::TextInputWidget* serverAddressTextInput = 
        new SDLGui::TextInputWidget("serverAddressInput", m_serverAddress, 20,
            0.f, .4f, .4f, .1f, 0., SDLGui::TextInputFlagsExt_CenterHorizontal |
            SDLGui::TextInputFlagsExt_CenterText);
    connectionWindowContext->addWidget(serverAddressTextInput);

    SDLGui::TextButtonWidget* connectionButton = 
        new SDLGui::TextButtonWidget("serverConnectionButton", "Connect",
            0.f, .51f, .3f, .1f, 0., SDLGui::TextButtonFlagsExt_CenterHorizontal |
            SDLGui::TextButtonFlagsExt_CenterText);
    connectionWindowContext->addWidget(connectionButton);

    SDLGui::SDLGuiEnvironment::pushContext(connectionWindowContext);
}

void ConnectionWindow::render()
{
    SDLGui::begin("connectionWindow");

    if (SDLGui::TextButton("serverConnectionButton")) {
        printf("Trying to connect\n");
    }

    SDLGui::end();
}