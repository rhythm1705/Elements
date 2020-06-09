#include "elmtpch.h"

#include "Message.h"

namespace Elements {
    Message::Message(System* sender, std::any data) : sender(sender), data(data) {
        Message::type = MessageType::None;
    }
    Message::Message(System* sender, MessageType type, std::any data) : sender(sender), type(type), data(data) {
    }
    Message::~Message() {}

}