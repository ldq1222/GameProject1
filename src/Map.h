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
	Map( /*const std::string& textureName*/ );
//	//i figured out that it would save time by loading it only once 
//	//instead of stuffing it in init()
	~Map();
	void init(int id, const std::string& jsonName);
	int tileReturnId(sf::Vector2f pos);
	sf::Vector2f tileReturnPos(int posId);
	
	sf::Texture getTexture(int typeId);
	void tileRender(int posId, int typeId, sf::RenderWindow& window);
///every tile consists of :
///  posid xxxx xxxx
///  type id x x xx
///   the type includes properties such as render,collision...

};
