#include "Field.hpp"

Field::Field(Player* player, int chips, bool is_water) 
    : player_(player), chips_(chips), is_water_(is_water) {}

Field::~Field() {}

Player* Field::getPlayer() const {
    return player_;
}

void Field::setPlayer(Player* player) {
    player_ = player;
}

int Field::getChips() const {
    return chips_;
}

void Field::setChips(int chips){
  chips_ = chips;
}

void Field::addChips(int chips) {
    chips_ = chips_ + chips;
}

bool Field::getIsWater() const {
    return is_water_;
}

void Field::setIsWater(bool is_water) {
    is_water_ = is_water;
}
