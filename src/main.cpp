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
    float ax = a.left + a.width / 2;
    float ay = a.top - a.height / 2;
    float ssx = ss.left + ss.width / 2;
    float ssy = ss.top -= ss.height / 2;

    float dx = fabs(ax - ssx);
    float dy = fabs(ay - ssy);
    float ox = a.width / 2 + ss.width / 2;
    float oy = a.height / 2 + ss.height / 2;
    float lapX = ox - dx;
    float lapY = oy - dy;
    sf::Vector2f v = player.getVelocity();
    if (!(lapX < Deviation && lapY < Deviation)) {
        if (fabs(lapX - lapY) < Deviation) {
            if (v.x > v.y) {
                //deal with x
                if (ax <= ssx) {
                    ax -= lapX+Deviation;
                    //it wont effect the players touch ,right? 
                }
                else if (ax > ssx) {
                    ax += lapX + Deviation;
                }
                v.x = 0;
            }
            else {
                if (ay <= ssy) {
                    ay -= lapY + Deviation;
                }
                else if (ay > ssy) {
                    ay += lapY + Deviation;
                }
                v.y = 0;//?
            }
        }
        else if (lapY <= lapX) {
            if (ay <= ssy) {
                ay -= lapY + Deviation;
            }
            else if (ay > ssy) {
                ay += lapY + Deviation;
            }
            v.y = 0;//?
        }
        else if (lapX > lapY) {
            if (ax <= ssx) {
                ax -= lapX + Deviation;
            }
            else if (ax > ssx) {
                ax += lapX + Deviation;
            }
            v.x = 0;
        }
        player.setVelocity(v);
        player.setPosition({ ax - a.width / 2,ay + a.height / 2 });
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

