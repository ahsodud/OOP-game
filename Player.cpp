#include "Player.hpp"

int Player::getFieldsOwned() const{
  return fields_owned_;
}
char Player::getId() const { //getter Player ID
  return id_;
}
int Player::getChips() const { //getter chips
  return chips_;
}
bool Player::hasPassed() const { //getter has_passed
  return has_passed_;
}
void Player::setChips(int chips){ //setter chips
  chips_ = chips;
}
void Player::addChips(int chips){ //setter chips
  chips_ = chips_ + chips;
}
void Player::setHasPassed(bool has_passed){ //setter has passed
  has_passed_ = has_passed;
}
void Player::setFieldsOwned(int fields_owned){
  fields_owned_ = fields_owned;
}
void Player::increaseFieldsOwned(){
  fields_owned_++;
} 



