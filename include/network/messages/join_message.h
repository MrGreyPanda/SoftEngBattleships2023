#pragma once

#include "message.h"

class JoinMessage : public Message {
   public:
    JoinMessage();
    JoinMessage(const json& data);
};
