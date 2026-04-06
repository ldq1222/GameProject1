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
            ////INPUT////
            if (event.type == sf::Keyboard::A) {
                player.walk(-1);
            }
            if (event.type == sf::Keyboard::D) {

                player.walk(1);
            }
            if (event.type == sf::Keyboard::Backspace) {
                player.jump();
            }
        }
        window.clear();
        window.draw(player.getsprite());
    }
    
	return 0;
}//why are there no changes

