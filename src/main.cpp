#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Player.h"
Player player;
void input(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::D) {
///            player.walk();
        }
    }
}
/// 
sf::Vector2f pos;
sf::Sprite sprite;
sf::Texture texture;
void update(double deltatime) {
    //    player.update(deltatime);
    ///  
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        pos.x += deltatime * 50;
        sprite.setPosition(pos);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        pos.x -= deltatime * 50;
        sprite.setPosition(pos);
    }
    ///
}
int main() {
    /// 

    texture.loadFromFile("assets/pics/square.png");
    sprite.setTexture(texture);
    pos.x = 10.0f;
    pos.y = 0;
    /// 

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
            input(event);
        }
        float elapsed = clock.restart().asSeconds();
        if (elapsed > 1.0f)elapsed = 1.0f;
        update(elapsed);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}