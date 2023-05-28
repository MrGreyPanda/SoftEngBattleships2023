#pragma once

#include "base_message.h"

/**
 * @brief A message sent from the client to the server when the player wants to
 * join a lobby
 */
class JoinRequest : public BaseMessage {
   public:
    JoinRequest();
};
