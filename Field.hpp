#ifndef FIELD_HPP
#define FIELD_HPP
#include "Player.hpp"
#include <iostream>

class Field {
private:
  Player* player_;
  int chips_;
  bool is_water_;
public:
  Field(Player* player, int chips, bool is_water);

  Field(const Field&) = delete;

  ~Field();

  int getChips()const;

  bool getIsWater()const;

  Player* getPlayer()const;

  void addChips(int chips);
  
  void setChips(int chips);

  void setIsWater(bool is_water);

  void setPlayer(Player* player );

};

#endif