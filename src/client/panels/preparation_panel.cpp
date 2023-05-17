#include "preparation_panel.h"

GameState* PreparationPanel::game_state_ = nullptr;
unsigned short PreparationPanel::help_button_counter_ = 0;

void PreparationPanel::init()
{
    SDLGui::SDLGuiContext* preparation_panel_context = 
        new SDLGui::SDLGuiContext("preparationPanelContext");

    SDLGui::GridWidget* preparation_grid = 
        new SDLGui::GridWidget("preparationGrid", .05f, .05f, .4f, .8f,
        0., 10, 10, SDLGui::GridFlagsExt_CenterVertical | SDLGui::GridFlagsExt_Square);
    preparation_panel_context->addWidget(preparation_grid);

    SDLGui::TextWidget* preparation_phase_title = 
        new SDLGui::TextWidget("preparation_title", "Preparation Phase",
        .0f, .05f, .6f, .1f, 0., SDLGui::TextFlagsExt_CenterText | 
        SDLGui::TextFlagsExt_CenterHorizontal);
        preparation_panel_context->addWidget(preparation_phase_title);

    SDLGui::TextButtonWidget* ready_button = 
        new SDLGui::TextButtonWidget("readyButton", "Ready", .0f, .9f, .3f, .08f, 0.,
        SDLGui::TextButtonFlagsExt_CenterText | SDLGui::TextButtonFlagsExt_CenterHorizontal);
    preparation_panel_context->addWidget(ready_button);

    SDLGui::DraggableImageWidget* carrier_ship = 
        new SDLGui::DraggableImageWidget("carrier_ship", "../assets/carrier.bmp",
        .6f, .2f, .3f, .12f, 0., 5, 1, 
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(carrier_ship);
    
    SDLGui::DraggableImageWidget* battleship_ship = 
        new SDLGui::DraggableImageWidget("battleship_ship", "../assets/battleship.bmp",
        .6f, .35f, .3f, .12f, 0., 4, 1, SDLGui::DraggableImageFlagsExt_NoBackground |
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(battleship_ship);
    
    SDLGui::DraggableImageWidget* cruiser_ship = 
        new SDLGui::DraggableImageWidget("cruiser_ship", "../assets/cruiser.bmp",
        .6f, .5f, .3f, .12f, 0., 3, 1, SDLGui::DraggableImageFlagsExt_NoBackground |
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(cruiser_ship);
    
    SDLGui::DraggableImageWidget* submarine_ship = 
        new SDLGui::DraggableImageWidget("submarine_ship", "../assets/submarine.bmp",
        .6f, .65f, .3f, .12f, 0., 3, 1, SDLGui::DraggableImageFlagsExt_NoBackground |
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(submarine_ship);

    SDLGui::DraggableImageWidget* destroyer_ship = 
        new SDLGui::DraggableImageWidget("destroyer_ship", "../assets/destroyer.bmp",
        .6f, .8f, .3f, .12f, 0., 2, 1, SDLGui::DraggableImageFlagsExt_NoBackground |
        SDLGui::DraggableImageFlagsExt_CenterImage);
    preparation_panel_context->addWidget(destroyer_ship);

    SDLGui::TextButtonWidget* help_button = new SDLGui::TextButtonWidget(
        "helpButton", "?", 0.85f, .05f, .1f, .05f, 0.,
         SDLGui::TextButtonFlagsExt_CenterText);
    preparation_panel_context->addWidget(help_button);


    SDLGui::TextWidget* help_message_text = new SDLGui::TextWidget(
        "helpMessageText", "", .01f, .1f, .8f, .8f, 0.,
        SDLGui::TextFlagsExt_CenterText | SDLGui::TextFlagsExt_NoBackground |
            SDLGui::TextFlagsExt_CenterHorizontal);
    preparation_panel_context->addWidget(help_message_text);

    SDLGui::SDLGuiEnvironment::pushContext(preparation_panel_context);
}

void PreparationPanel::render()
{
    SDLGui::begin("preparationPanelContext");

    if (SDLGui::TextButton("readyButton"))
        game_state_->set_phase(Battle);

    if(SDLGui::TextButton("helpButton")){
        if(help_button_counter_ == 0){
            ++help_button_counter_;
            // Set the background
            SDLGui::Text("helpMessageText").updateText(512, "Press R while holding a ship to rotate it. Click on the help button to close this message.");
        }
        else{
            --help_button_counter_;
            // Set the background to nothing
            SDLGui::Text("helpMessageText").updateText(512, "");
        }
    }

    SDLGui::end();
}