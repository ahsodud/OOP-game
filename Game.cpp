// Game.cpp

#include "Game.hpp"
#include "Utils.hpp"
//#include "Command.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

Game::Game(int maximum_rounds, char* config_path)
    : map_(nullptr), player_a_(nullptr), player_b_(nullptr), current_round_(0),
      max_rounds_(maximum_rounds), phase_(Phase::PLACEMENT), active_player_(nullptr) {
    // Initialize the game components
    player_a_ = new Player('A');
    player_b_ = new Player('B');
    map_ = new Map(config_path, player_a_, player_b_);
}

Game::~Game() {
    delete map_;
    delete player_a_;
    delete player_b_;
}

int Game::getRoundNumber(char* string) {
    int number_rounds;
    if(Utils::decimalStringToInt(string,number_rounds))
    {
      return number_rounds;
    }
    else return -1;
}

bool Game::isValidRoundNumber(int rounds) {
    if(rounds >= 1)
    {
      return true;
    }
    else
    {
      return false;
    }
}

bool Game::isValidConfig(char* config_path) {
  std::string filename{config_path};
  std::ifstream file{filename};
  if(!file.is_open())
  {
    return false;
  }
  std::string firstLine;
  if (std::getline(file, firstLine))
  {
    if (firstLine != "OOP") 
    {
      return false;
    }
  } 
  else
  {
    return false;
  }
  return true;
}

void Game::start() {
    current_round_ = 1;
    phase_ = Phase::PLACEMENT;
    active_player_ = player_a_;
    std::cout << "Welcome to OOPtimal Tactics!" << std::endl;
    std::cout << "Playing maximum of " << max_rounds_ << " round(s)!" << std::endl;
    std::cout << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "Round " << current_round_ << "/" << max_rounds_ << " starts!" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "\n" << "------------------" << std::endl;
    std::cout << "Placement Phase" << std::endl;
    std::cout << "------------------" << std::endl;
    //player_a_->addChips(std::max(1, static_cast<int>(ceil(static_cast<float>(player_a_->getFieldsOwned()) / 3.0))));
    //player_b_->addChips(std::max(1, static_cast<int>(ceil(static_cast<float>(player_a_->getFieldsOwned()) / 3.0))));
    map_->printMap();
    std::cout << std::endl;
}

void Game::execute(Command command) {
    switch (command.getType())
    {
      case CommandType::PLACE:
      {
        int amount;
        int x_axis;
        int y_axis;
        std::vector<std::string> parameters = command.getParameters();
        if(phase_ != Phase::PLACEMENT)
        {
         std::cout << "[ERROR] Entered command is not valid in this phase!\n";
        break; 
        }
        if(!Utils::decimalStringToInt(parameters.at(0), amount))
        {
          std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
          break;
        }
        if(!Utils::decimalStringToInt(parameters.at(1), x_axis))
        {
          std::cout << "[ERROR] Invalid field!\n";
          break;
        }
        if(!Utils::decimalStringToInt(parameters.at(2), y_axis))
        {
          std::cout << "[ERROR] Invalid field!\n";
          break;
        }
        if(amount > active_player_->getChips())
        {
          std::cout << "[ERROR] Invalid amount! Must be a number <= chips in player inventory!\n";
          break;
        }
        if(amount < 1)
        {
          std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
          break;
        }
        if((x_axis < 1 || x_axis > 9) ||(y_axis < 1 || y_axis > 9))
        {
          std::cout << "[ERROR] Invalid field!\n";
          break;
        }
        std::vector<std::vector<Field*>> fields = map_->getFields();
        if(fields[y_axis-1][x_axis-1]->getPlayer() == nullptr)
        {
          std::cout << "[ERROR] Invalid field!\n";
          break;
        }
        fields[y_axis-1][x_axis-1]->addChips(amount);
        fields[y_axis-1][x_axis-1]->setPlayer(active_player_);
        if(map_->isOutputActive())
        {
          map_->printMap();
          std::cout << std::endl;
        }
        active_player_->setHasPassed(true);
        active_player_ = (active_player_ == player_a_) ? player_b_ : player_a_;
        if(player_a_->hasPassed()&&player_b_->hasPassed())
        {
          std::cout << "------------------" << std::endl;
          std::cout << "Movement Phase" << std::endl;
          std::cout << "------------------" << std::endl;
          if(map_->isOutputActive())
          {
            map_->printMap();
            std::cout << std::endl;
          }
          phase_ = Phase::MOVEMENT;
          player_a_->setHasPassed(false);
          player_b_->setHasPassed(false);
          active_player_ = player_b_;
        }
        break;
      }
      case CommandType::MOVE:
      {
        if(phase_ != Phase::MOVEMENT)
        {
         std::cout << "[ERROR] Entered command is not valid in this phase!\n";
         break; 
        }
        std::vector<std::string> parameters = command.getParameters();
        int old_amount;
        int new_amount;
        int move_amount;
        int new_x_axis;
        int new_y_axis;
        int old_x_axis;
        int old_y_axis;
        if(!Utils::decimalStringToInt(parameters.at(0), move_amount))
        {
          std::cout << "[ERROR] Invalid amount! Must be a number > 0!\n";
          break;
        }
        if(!Utils::decimalStringToInt(parameters.at(1), old_x_axis))
        {
          std::cout << "[ERROR] Invalid origin!\n";
          break;
        }
        if(!Utils::decimalStringToInt(parameters.at(2), old_y_axis))
        {
          std::cout << "[ERROR] Invalid origin!\n";
          break;
        }
        if(!Utils::decimalStringToInt(parameters.at(3), new_x_axis))
        {
          std::cout << "[ERROR] Invalid destination!\n";
          break;
        }
        if(!Utils::decimalStringToInt(parameters.at(4), new_y_axis))
        {
          std::cout << "[ERROR] Invalid destination!\n";
          break;
        }
        std::vector<std::vector<Field*>> fields = map_->getFields();
        if(fields[new_y_axis-1][new_x_axis-1]->getIsWater())
        {
          std::cout << "[ERROR] Invalid destination!\n";
          break;
        }
        if((new_x_axis < 1 || new_x_axis > 9) ||(new_y_axis < 1 || new_y_axis > 9))
        {
          std::cout << "[ERROR] Invalid destination!\n";
          break;
        }
        if((old_x_axis < 1 || old_x_axis > 9) ||(old_y_axis < 1 || old_y_axis > 9)||(active_player_ != fields[old_y_axis-1][old_x_axis-1]->getPlayer()))
        {
          std::cout << "[ERROR] Invalid origin!\n";
          break;
        }
        if(abs(new_x_axis - old_x_axis)>1)
        {
          std::cout << "[ERROR] Invalid destination!\n";
          break;
        }
        if(abs(new_y_axis - old_y_axis)>1)
        {
          std::cout << "[ERROR] Invalid destination!\n";
          break;
        }
        if(fields[old_y_axis-1][old_x_axis-1]->getPlayer() == nullptr)
        {
          active_player_->increaseFieldsOwned();
        }

        old_amount = fields[old_y_axis-1][old_x_axis-1]->getChips();

        if(move_amount > old_amount)
        {
          std::cout << "[ERROR] Invalid amount! Must be a number <= chips on origin field!\n";
          break;
        }

        new_amount = old_amount - move_amount;

        if(new_amount == 0)
        {
          fields[old_y_axis-1][old_x_axis-1]->setChips(new_amount);
          fields[old_y_axis-1][old_x_axis-1]->setPlayer(nullptr);
          fields[new_y_axis-1][new_x_axis-1]->addChips(move_amount);
          fields[new_y_axis-1][new_x_axis-1]->setPlayer(active_player_);
        }
        else 
        {
          fields[old_y_axis-1][old_x_axis-1]->setChips(new_amount);
          fields[old_y_axis-1][old_x_axis-1]->setPlayer(active_player_);
          fields[new_y_axis-1][new_x_axis-1]->addChips(move_amount);
          fields[new_y_axis-1][new_x_axis-1]->setPlayer(active_player_);
        }

        if(map_->isOutputActive())
        {
          map_->printMap();
          std::cout << std::endl;
        }
        active_player_ = (active_player_ == player_a_) ? player_b_ : player_a_;
       break;
      }
      case CommandType::MAP:
      {
        map_->setOutputActive(!map_->isOutputActive());
        if(map_->isOutputActive())
        {
          map_->printMap();
          std::cout << std::endl;
        }
        break;
      }
      case CommandType::PASS:
      {
        active_player_->setHasPassed(true);
        active_player_ = (active_player_ == player_a_) ? player_b_ : player_a_;
        if(player_a_->hasPassed()&&player_b_->hasPassed())
        {
          if(phase_ == Phase::PLACEMENT)
          {
          std::cout << "------------------" << std::endl;
          std::cout << "Movement Phase" << std::endl;
          std::cout << "------------------" << std::endl;
          phase_ = Phase::MOVEMENT;
          if(map_->isOutputActive())
          {
            map_->printMap();
            std::cout << std::endl;
          }
          player_a_->setHasPassed(false);
          player_b_->setHasPassed(false);
          active_player_ = player_b_;
          }
          else if(phase_ == Phase::MOVEMENT)
          {
            std::cout << "------------------" << std::endl;
            std::cout << "GAME END!\n" << std::endl;
            std::cout << "Player " << player_a_->getId() << " claimed " << player_a_->getFieldsOwned() << " field(s)!" << std::endl;
            std::cout << "Player " << player_b_->getId() << " claimed " << player_b_->getFieldsOwned() << " field(s)!" << std::endl;
            phase_ = Phase::END;
            break;
          }
        }
        break;
      }
      case CommandType::INFO:
      {
        std::cout << "Player " << active_player_->getId() << ":" << std::endl;
        std::cout << "You have " << active_player_->getChips() << " chip(s) saved!" << std::endl;
        std::cout << "You own " << active_player_->getFieldsOwned() << " field(s)!" << std::endl;
        std::cout << std::endl;
        break;
      }
      case CommandType::INVALID: break;
      case CommandType::QUIT: break;
      case CommandType::WRONG_PARAM: break;
    }   
}

bool Game::isRunning() {
  if(phase_ == Phase::PLACEMENT)
  {
    std::cout << "Player " << active_player_->getId() << ", you have " << active_player_->getChips() << " chip(s) left, where and how do you want to place your chips?" << std::endl;
  }
  if(phase_ == Phase::MOVEMENT)
  {
    if(active_player_->hasPassed())
        {
         std::cout << "Player " << active_player_->getId() << ", what do you want to do?" << std::endl;
         return true;
        }
    std::cout << "Player " << active_player_->getId() << ", what do you want to do?" << std::endl;
  }
  return phase_ != Phase::END;
};

Map* Game::getMap() const {
    return map_;
}

Player* Game::getPlayerA() const {
    return player_a_;
}

Player* Game::getPlayerB() const {
    return player_b_;
}

int Game::getCurrentRound() const {
    return current_round_;
}

int Game::getMaxRounds() const {
    return max_rounds_;
}

Phase Game::getPhase() const {
    return phase_;
}

Player* Game::getActivePlayer() const {
    return active_player_;
}

void Game::setMaxRounds(int max_rounds) {
    max_rounds_ = max_rounds;
}

void Game::setPhase(Phase phase) {
    phase_ = phase;
}

void Game::setActivePlayer(Player* active_player) {
    active_player_ = active_player;
}
