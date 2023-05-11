#include "GameWindow.h"

char ConnectionWindow::m_serverAddress[20];
uint16_t ConnectionWindow::m_serverPort = 0;

void ConnectionWindow::init()
{
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
        new SDLGui::TextInputWidget("serverAddressInput", m_serverAddress, 20,
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
        SDLGui::Text("serverMessageText").updateText(32, "Connecting...");
        // Try to connect to the server
    }

    SDLGui::end();
}