#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Player.h"
#include "Map.h"
using json = nlohmann::json;
//finally!!!!!for some reason it automatically repaired itself when I re-updated it 
//with /showInclude.（because it probably regenerated）
sf::Sprite s;
sf::Texture t;
const int HEIGHT = 1080, WIDTH = 1920;
Map map;
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
    player.update(deltatime, Gravity,s);
    //I realized that the collide should be put in the upd()
    //also the collide() doesnt need pass-bys,because later it is caled by the position.
    std::cout << "isJump = " << player.isJump << "\n";
    return;
}


void render(sf::RenderWindow& window) {
    //needs an upside down globally.
    //current is in player.
    window.clear(sf::Color(0, 150, 150, 150));
    //this TRGB is a sort of deep duckweed-blue
    //to prevent my eyes from dying
///upd26.8.19: duckweed-blue is now a sign of unsuccessful tile-loading. 
    
    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) {
            //for some reason I mixed Tile with Map...
            //reimplement is for later[yawn]
            map.tileRender(i * 10000 + j, 1, window);
        }//tttt praying.
    }

    player.render(window);
    window.draw(s);
    //you can refer to a referance after all

    window.display();
    return;
}

int main() {
    map.init(1,"src/map.json");
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
    //emergency!!!
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

