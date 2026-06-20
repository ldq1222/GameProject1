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
const int HEIGHT = 1080, WIDTH = 1920;
sf::Sprite s;
sf::Texture t;
//sf::Sprite sths;
//sf::Texture stht;
Player player;
const float Gravity = 2000.0f;
//this affects the jump and so do not change easily
const float Deviation = 0.00005;
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
    sf::FloatRect a = player.getSprite().getGlobalBounds();
    sf::FloatRect ss = s.getGlobalBounds();
    sf::Vector2f aa = player.getPosition();
    sf::Vector2f v = player.getVelocity();
    if (a.intersects(ss)) {
        float x1 = std::fabs(a.left + a.width - ss.left);
        float x2 = std::fabs(ss.left + ss.width - a.left);
        float y1 = std::fabs(a.top - (ss.top - ss.height));
        float y2 = std::fabs(ss.top - (a.top - a.height));
        float lapX = std::min(x1,x2);
        float lapY = std::min(y1,y2);
        //the advantages of not having <bits/stdc++.h>
        if (lapX > lapY) {
            if (lapY == y2) {
                //from top
                aa.y += lapY;
                player.isJump = 0;
                v.y = 0;
                // I DEFINATELY had written an onGround 
            }
            else if (lapY == y1) {
                aa.y -= lapY;
            }
        }
        else if (lapY >= lapX) {
            if (lapX == x1) {
                //from left
                aa.x -= lapX;
            }
            else if (lapX == x2) {
                aa.x += lapX;
            }
        }
        player.setPosition(aa);
        player.setVelocity(v);
    }
    std::cout << "isJump = " << player.isJump << "\n";
    return;
}

void render(sf::RenderWindow& window) {
    window.clear(sf::Color(0, 150, 150, 150));
    //this TRGB is a sort of deep duckweed-blue
    //to prevent my eyes from dying
    player.render(window);
    window.draw(s);
    //you can refer to a referance after all
    window.draw(sths);
    window.display();
    return;
}

int main() {
    player.init("assets/pics/square.png", 10.0f);
    
    sf::Clock clock;
    double deltatime = 0.0f;
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "sth");
    // window.setKeyRepeatEnabled(false);
    //this makes sure the event only happens once when the key is pressed, not every frame when the key is held down
    window.setVerticalSyncEnabled(true);

    ///temporary
    
    t.loadFromFile("assets/pics/rectangle.png");
    s.setTexture(t);
    s.setPosition({ 200.0f,500.0f });
    ///
//    stht.loadFromFile("assets/pics/person2.png");
//    sths.setTexture(stht);
//    sths.setPosition({ 800.0f,500.0f });
    //picture works very well
    //so one tile is 2000*200.
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

