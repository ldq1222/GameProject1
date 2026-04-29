#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Player.h"
Player player;
void inputEvent(const sf::Event& event) {
   
}
/// 
sf::Vector2f pos;
void inputRealTime() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        player.walk(1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.walk(-1);
    }
}
void update(double deltatime) {
     player.update(deltatime);
     return;
}
void render(sf::RenderWindow& window) {
    window.clear();
    player.render(window);
    //you can refer to a referance after all
    window.display();
    return;
}
int main() {
    player.init("assets/pics/square.png",{10.0f,0.0f},10.0f);
    sf::Clock clock;
    double deltatime = 0.0f;
    sf::RenderWindow window(sf::VideoMode(640, 480), "sth");
    // window.setKeyRepeatEnabled(false);
     //this makes sure the event only happens once when the key is pressed, not every frame when the key is held down
    window.setVerticalSyncEnabled(true);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            inputEvent(event);
        }
        inputRealTime();
        float elapsed = clock.restart().asSeconds();
        if (elapsed > 1.0f)elapsed = 1.0f;
        update(elapsed);
        render(window);
    }
    return 0;
}