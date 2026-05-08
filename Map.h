#pragma once
#include<SFML/Graphics.hpp>
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
using json = nlohmann::json;
class Map
{
private:
	int mapId;
	json mapData;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	Map(const std::string& textureName);
	~Map();
	void init(int id, const std::string& jsonName);
	int getCurTile(sf::Vector2f pos);
	sf::RectangleShape getTileBounds(int tileId);
};



