#include <fstream>
#include "Map.hpp"

Map::Map(char* config_path, Player* player_a, Player* player_b)
    : columns_(0), rows_(0), output_active_(true) {
    loadConfig(config_path, player_a, player_b);
}

Map::~Map() {
    for (auto& row : fields_) {
        for (auto field : row) {
            delete field;
        }
    }
}

int Map::getColumns() const {
    return columns_;
}

int Map::getRows() const {
    return rows_;
}

const std::vector<std::vector<Field*>>& Map::getFields() const {
    return fields_;
}

bool Map::isOutputActive() const {
    return output_active_;
}
void Map::setColumns(int columns){
    columns_ = columns;
};

void Map::setRows(int rows){
    rows_ = rows;
};

void Map::setOutputActive(bool output_active) {
    output_active_ = output_active;
}

void Map::printMap() const {
    std::cout << "  "; // print (0,0) as empty
    for (int col = 1; col <= columns_; ++col) // Print the column numbers
    {
      std::cout << "| " << col << " ";
    }
    std::cout << std::endl;
    for (int row = 0; row < rows_; ++row) { // Print the rows
        std::cout << row + 1 << " "; // Print the row number
        for (int col = 0; col < columns_; ++col) {  // Print each field of the map
            Player* player_here = fields_[row][col]->getPlayer();
            bool is_water = fields_[row][col]->getIsWater();
            int chips_here = fields_[row][col]->getChips();
            if (is_water) 
            {
              std::cout << "| " << "~" << " "; // Water cell
            } 
            else if (player_here != nullptr) 
            {
              std::cout << "|" << player_here->getId() << " " << chips_here ; // Cell occupied by a player
            } 
            else 
            {   
                std::cout << "|   "; // Empty cell
            }
        }
        std::cout << std::endl;
    }
}


void Map::loadConfig(char* config_path, Player* player_a, Player* player_b) {
    std::string filename{config_path};
    std::ifstream file{filename};
    if (!file.is_open()) 
    {
      return;
    }
    std::string magic_number;
    std::getline(file, magic_number);
    std::string dimensions;
    std::getline(file, dimensions); // Reading second line, where dimensions stored
    columns_ = dimensions.at(0) - '0'; // Convert char to int
    rows_ = dimensions.at(2) - '0';
    fields_.resize(rows_);
    for (int i = 0; i < rows_; ++i) // Map resize
    {  
        fields_[i].resize(columns_);
    }
    for (int i = 0; i < rows_; ++i) 
    {
      std::string row;
      std::getline(file, row);
      for (int j = 0; j < columns_; ++j) 
      {
        char field_type = row[j];
        int chips = 0;
        bool is_water = false;
        Player* owner = nullptr;
        if (field_type == 'a') 
        {
          owner = player_a;
          player_a->increaseFieldsOwned();
          chips = 1;
        } 
        else if (field_type == 'b') 
        {
          owner = player_b;
          player_b->increaseFieldsOwned();
          chips = 1; 
        } 
        else if (field_type == '0')
        {
          chips = 0;
        } 
        else 
        {
          is_water = true;
        } 
        fields_[i][j] = new Field(owner, chips, is_water);
      }
    }
    file.close();
}
