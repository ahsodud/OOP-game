#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "Field.hpp" 
#include "Player.hpp" 

class Map {
private:
    int columns_;
    int rows_;
    std::vector<std::vector<Field*>> fields_;
    bool output_active_;

public:
    Map(char* config_path, Player* player_a, Player* player_b);
    ~Map(); 
    Map(const Map&) = delete; 
    int getColumns() const;
    void setColumns(int columns);
    void setRows(int rows);
    int getRows() const;
    const std::vector<std::vector<Field*>>& getFields() const;
    bool isOutputActive() const;
    void setOutputActive(bool output_active);
    void printMap() const;

private:
    void loadConfig(char* config_path, Player* player_a, Player* player_b);
};

#endif
