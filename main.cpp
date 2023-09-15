#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const int WIDTH = 800, HEIGHT = 600;
    sf::Vector2f origin(WIDTH / 2.f, 100.f);
    float radius = 20.f;
    float length = 200.f;
    float angle = -M_PI / 8;
    float aVelocity = 0;
    float aAcceleration = 0;
    float bob_x = 0, bob_y = 0;
    float gravity = 0.5;
    float damping = 0.995;
    bool pause = false;
    bool color_invert = false;
    sf::Color background = sf::Color::Black;


    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pendulum", sf::Style::Titlebar);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    sf::CircleShape bob(radius);
    bob.setOrigin(radius, radius);
    bob.setPosition(sf::Vector2f(WIDTH/2.f, length));
    bob.setFillColor(sf::Color::Black);
    bob.setOutlineThickness(-2.f);
    bob.setOutlineColor(sf::Color::White);

    sf::CircleShape dot(4);
    dot.setFillColor(sf::Color::White);
    dot.setOrigin(4, 4);
    dot.setPosition(origin.x, origin.y);

    sf::Vertex line[2];
    line[0].position = sf::Vector2f(origin.x, origin.y);
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    angle += M_PI_2;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || 
                event.type == sf::Event::Closed)
                window.close();
        }


        aAcceleration = (-1 * gravity / length) * sin(angle);
        aVelocity += aAcceleration;
        angle += aVelocity;

        bob_x = origin.x + sin(angle) * length;
        bob_y = origin.y + cos(angle) * length;
        bob.setPosition(bob_x, bob_y);
        aVelocity *= damping;
        line[1].position = sf::Vector2f(bob_x, bob_y);

        
        // pause
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            pause = true;
        while (pause)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
            {
                pause = false;
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) ||
                event.type == sf::Event::Closed)
                window.close();
        }
        // color changing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        {
            background = sf::Color::White;
            bob.setFillColor(sf::Color::White);
            bob.setOutlineColor(sf::Color::Black);
            dot.setFillColor(sf::Color::Black);
            line[0].color = sf::Color::Black;
            line[1].color = sf::Color::Black;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
        {
            background = sf::Color::Black;
            bob.setFillColor(sf::Color::Black);
            bob.setOutlineColor(sf::Color::White);
            dot.setFillColor(sf::Color::White);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
        }

        window.clear(background);
        window.draw(line, 2, sf::Lines);
        window.draw(bob);
        window.draw(dot);

        window.display();
    }

    return 0;
}