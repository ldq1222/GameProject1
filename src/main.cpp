#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Player.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json=nlohmann::json;
//finally!!!!!for some reason it automatically repaired itself when I re-updated it 
//with /showInclude.（because it probably regenerated）

Player player;
const float Gravity = 2000.0f;
//this affects the jump and so do not change easily
void inputEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            std::cout << "Jumped\n";
            player.jump(Gravity);
        }
    }
}

sf::Vector2f pos;

void inputRealTime() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.walk(1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.walk(-1);
    }
}

void update(double deltatime) {
    player.update(deltatime, Gravity);
    return;
}

void render(sf::RenderWindow& window) {
    window.clear(sf::Color(0,150,150,150));
    //this TRGB is a sort of deep duckweed-blue
    //to prevent my eyes from dying
    player.render(window);
    //you can refer to a referance after all
    window.display();
    return;
}

int main() {
    player.init("assets/pics/square.png",10.0f);
    sf::Clock clock;
    double deltatime = 0.0f;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "sth");
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
        if (elapsed > 1.0f) elapsed = 1.0f;
        update(elapsed);
        render(window);
    }
    return 0;
}