#include"Box.h"
#include<SFML/Graphics.hpp>
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
using json = nlohmann::json;
Box::Box() {
	
}
Box::~Box() {

}
void Box::init(sf::Vector2f leftop, sf::Vector2f size) {
	box.setSize(size);
	box.setPosition(leftop);
	//i dont really know if the position is leftop
}
sf::RectangleShape Box::getBox() {
	return box;
}
void Box::setPos(sf::Vector2f pos) {
	box.setPosition(pos);
}