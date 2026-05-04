#include"Map.h"
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
using json = nlohmann::json;
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