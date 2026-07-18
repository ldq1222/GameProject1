#include"Map.h"
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
using json = nlohmann::json;

Map::Map() {
	mapId = 0;

}
Map::~Map() {

}
void Map::init(int id, const std::string& jsonName) {
	mapId = id;
	std::ifstream mapFile(jsonName, std::ios::binary);
	if (!mapFile.is_open()) {
		std::cout << "failed to open mapfile\n";
		return;
	}
	mapFile >> mapData;

}

