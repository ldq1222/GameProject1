#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Player.h"
Player player;
void update(double deltatime) {
    player.update(deltatime);
}
int main() {

    sf::Window window;
    sf::RenderWindow window(sf::VideoMode(640, 480), "sth");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
    }
    
	return 0;
}

