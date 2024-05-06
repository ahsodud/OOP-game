#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player
{
private:
  char id_;
  int chips_;
  bool has_passed_;
  int fields_owned_;
public:
  Player(char id): id_(id), chips_(1), has_passed_(false){}

  ~Player() {}

  Player(const Player&) = delete;

  int getFieldsOwned() const;

  char getId() const;

  int getChips() const;

  bool hasPassed() const;

  void setChips(int chips);

  void addChips(int chips);

  void setHasPassed(bool has_passed);
  
  void setFieldsOwned(int fields_owned);

  void increaseFieldsOwned();
};

#endif