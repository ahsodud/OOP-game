#include "Command.hpp"

Command::Command(std::vector<std::string>& input) {
        if (!input.empty()) {
            type_ = CommandType::INVALID;
            std::string commandTypeStr = input[0];
            for (char& c : commandTypeStr) 
            {
              c = std::tolower(c);
            }
            if (commandTypeStr == "place") 
            {
              type_ = CommandType::PLACE;
            } 
            else if (commandTypeStr == "pass") 
            {
              type_ = CommandType::PASS;
            } 
            else if (commandTypeStr == "move") 
            {
              type_ = CommandType::MOVE;
            } 
            else if (commandTypeStr == "map") 
            {
              type_ = CommandType::MAP;
            } 
            else if (commandTypeStr == "info") 
            {
              type_ = CommandType::INFO;
            } 
            else if (commandTypeStr == "quit") 
            {
              type_ = CommandType::QUIT;
            }
            if (type_ != CommandType::INVALID) 
            {
              parameters_.insert(parameters_.end(), input.begin() + 1, input.end());
            }
        }
    }

Command::Command(CommandType type) : type_(type) {}

Command::~Command() {}

Command::Command(const Command& other) : type_(other.type_), parameters_(other.parameters_) {}

bool Command::isQuit() {
    return type_ == CommandType::QUIT;
}

CommandType Command::getType() {
    return type_;
}

std::vector<std::string>& Command::getParameters() {
    return parameters_;
}

void Command::setType(CommandType type) {
    type_ = type;
}
