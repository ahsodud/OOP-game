#ifndef GAME_HPP
#define GAME_HPP

#include "Map.hpp"
#include "Player.hpp"
#include "Command.hpp"
#include <fstream>
#include <string>
#include <algorithm>

enum class Phase {
    PLACEMENT,
    MOVEMENT,
    END
};

class Game {
private:
    Map* map_;
    Player* player_a_;
    Player* player_b_;
    int current_round_;
    int max_rounds_;
    Phase phase_;
    Player* active_player_;

public:
    Game(int maximum_rounds, char* config_path);
    
    ~Game();

    Game(const Game& other) = delete;

    // Methods
    static int getRoundNumber(char* string);
    static bool isValidRoundNumber(int rounds);
    static bool isValidConfig(char* config_path);
    void start();
    void execute(Command command);
    bool isRunning();

    // Getters
    Map* getMap() const;
    Player* getPlayerA() const;
    Player* getPlayerB() const;
    int getCurrentRound() const;
    int getMaxRounds() const;
    Phase getPhase() const;
    Player* getActivePlayer() const;

    // Setters
    void setMaxRounds(int max_rounds);
    void setPhase(Phase phase);
    void setActivePlayer(Player* active_player);
};

#endif


