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
int Map::tileReturnId(sf::Vector2f pos) {//the feet tile of the player
	int xid = static_cast<int>(floor(pos.x))/200+1;
	//in traditional c, it cuts off toward zero.
	int yid = static_cast<int>(floor(pos.y))/200+1;
	//if you are (100,100) then its tile(1,1)
	//and (250,250) in tile(2,2);
	return yid * 10000 + xid;
}
///returns an id,each unique:0001 0001~9999 9999,first four digits in Y.
///each 200*200px
///0-199,200-399...

sf::Vector2f Map::tileReturnPos(int posId) {
	//the left-low corner of the tile.
	int yid = posId / 10000;
	int xid = posId % 10000;
	sf::Vector2f pos;
	pos.x = (xid - 1) * 200;
	pos.y = (yid - 1) * 200;
	return pos;
}
sf::Texture Map::getTexture(int typeId) {
	sf::Texture texture;
	std::string path = "assets/pics/tile.png";
///this needs to be reimplemented as check whether already loaded the type of texture.
///will arrange some uniform file path mentioning typeId. 
	if (!texture.loadFromFile(path)) {
		std::cout << "cannot load tile texture,typeId is " << typeId << "\n";
	    //Geex says that I can load an emergency texture.perhaps later.
		//the nickname really suits!
	}
	return texture;
}

void Map::tileRender(int posId, int typeId, sf::RenderWindow& window) {
///need another json for all the assets-pics ?
///prototype stage: direct path torward assets.
	sf::Sprite sprite;
	sf::Texture texture=getTexture(typeId);
	sprite.setTexture(texture);
	sf::Vector2f posRender = tileReturnPos(posId);
	posRender.y = 830.0f - posRender.y;
	sprite.setPosition(posRender);
	window.draw(sprite);
}

