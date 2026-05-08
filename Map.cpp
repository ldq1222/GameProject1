#include"Map.h"
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
using json = nlohmann::json;
const int TileSize = 64;
Map::Map(const std::string& textureName) {
	mapId = 0;
	texture.loadFromFile(textureName);
	sprite.setTexture(texture);
	//i figured out that it would save time by loading it only once 
	//instead of stuffing it in init()
}
Map::~Map() {
	
}
void Map::init(int id,const std::string& jsonName) {
	mapId = id;
	std::ifstream mapFile(jsonName, std::ios::binary);
	if (!mapFile.is_open()) {
		std::cout << "failed to open mapfile\n";
	}
	mapFile >> mapData;

}
//void Map::saveData() {
//
//}
int Map::getCurTile(sf::Vector2f pos) {
	int tilex = (int)(pos.x) / TileSize;
	int tiley = (int)(pos.y) / TileSize;
	return (tiley << 15) + tilex;
	//i guess it wouldnt be bigger than 2^15,right
	
}
sf::RectangleShape getTileBounds(int tileId) {

}
