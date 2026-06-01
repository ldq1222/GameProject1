#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include "Player.h"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
//finally!!!!!for some reason it automatically repaired itself when I re-updated it 
//with /showInclude.（because it probably regenerated）
sf::Sprite s;
sf::Texture t;
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

void saveData() {
    player.saveData("src/player.json");
    return;
}
void update(double deltatime) {
    player.update(deltatime, Gravity);
    sf::FloatRect a=player.getSprite().getGlobalBounds();
    sf::FloatRect ss = s.getGlobalBounds();
    if (a.intersects(ss)){
        std::cout << "collided!\n";
        float lapL = a.left + a.width - ss.left;
        float lapR = ss.left + ss.width - a.left;
        float lapU = ss.top - (a.top - a.height);
        float lapD = a.top - (ss.top - ss.height);
        float lapMin = std::min(lapL,std::min(lapR,std::min(lapU,lapD)));
        //GeeX taught me this spagetti code
        //all faults on them
        sf::Vector2f pos;
        pos.x = a.left;
        pos.y = a.top;
        if (lapMin == lapL) {
            pos.x -= lapL;
        }
        if (lapMin == lapR) {
            pos.x += lapR;
        }
        if (lapMin == lapU) {
            pos.y += lapU;
        }
        if (lapMin == lapD) {
            pos.y -= lapD;
        }
        player.setPosition(pos);
    }
    return;
}

void render(sf::RenderWindow& window) {
    window.clear(sf::Color(0, 150, 150, 150));
    //this TRGB is a sort of deep duckweed-blue
    //to prevent my eyes from dying
    player.render(window);
    window.draw(s);
    //you can refer to a referance after all
    window.display();
    return;
}

int main() {
    player.init("assets/pics/square.png", 10.0f);
    
    sf::Clock clock;
    double deltatime = 0.0f;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "sth");
    // window.setKeyRepeatEnabled(false);
    //this makes sure the event only happens once when the key is pressed, not every frame when the key is held down
    window.setVerticalSyncEnabled(true);

    ///temporary
    
    t.loadFromFile("assets/pics/rectangle.png");
    s.setTexture(t);
    s.setPosition({ 200.0f,500.0f });
    ///
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                saveData();
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

