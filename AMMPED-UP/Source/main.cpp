#include "../Header Files/Game.h"
int main()
{
    Game game;
    game.run();
    return 0;
}

/*
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Rectangle Movement");

    sf::RectangleShape rect(sf::Vector2f(50.0f, 50.0f));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f(100.0f, 100.0f));

   // float velocity = 100.0f;
    sf::Clock clock;

    //window.setKeyRepeatEnabled(false); // disable key repeat
    float velocity = 100.f;
    sf::Vector2f direction = { 0.f, 0.f };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    direction.x = -1.f;
                else if (event.key.code == sf::Keyboard::Right)
                    direction.x = 1.f;
                else if (event.key.code == sf::Keyboard::Up)
                    direction.y = -1.f;
                else if (event.key.code == sf::Keyboard::Down)
                    direction.y = 1.f;
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Left && direction.x < 0.f)
                    direction.x = 0.f;
                else if (event.key.code == sf::Keyboard::Right && direction.x > 0.f)
                    direction.x = 0.f;
                else if (event.key.code == sf::Keyboard::Up && direction.y < 0.f)
                    direction.y = 0.f;
                else if (event.key.code == sf::Keyboard::Down && direction.y > 0.f)
                    direction.y = 0.f;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        sf::Vector2f movement = direction * velocity * deltaTime;
        rect.move(movement);

        if (rect.getPosition().x < 0.f)
            rect.setPosition(0.f, rect.getPosition().y);
        if (rect.getPosition().y < 0.f)
            rect.setPosition(rect.getPosition().x, 0.f);
        if (rect.getPosition().x + rect.getSize().x > window.getSize().x)
            rect.setPosition(window.getSize().x - rect.getSize().x, rect.getPosition().y);
        if (rect.getPosition().y + rect.getSize().y > window.getSize().y)
            rect.setPosition(rect.getPosition().x, window.getSize().y - rect.getSize().y);

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}
*/