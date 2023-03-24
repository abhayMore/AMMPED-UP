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
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(160, 160), "Framerate Independent Movement");

    // Define the rectangle to be moved
    sf::RectangleShape rectangle(sf::Vector2f(16.f, 16.f));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(16.0f, 16.0f);

    // Define the movement speed of the rectangle (pixels per second)
    float speed = 200.f;

    // Define the direction vector of the rectangle
    sf::Vector2f direction(0.f, 0.f);

    int collisionMap[10][10] = {
    {1, 0, 0, 1, 1, 1, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 1},
    {0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 1, 1, 1, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 1, 1, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 1, 0, 1, 0, 0, 0, 1, 1}
    }

    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    direction = sf::Vector2f(-1.f, 0.f);
                    break;

                case sf::Keyboard::Right:
                    direction = sf::Vector2f(1.f, 0.f);
                    break;

                case sf::Keyboard::Up:
                    direction = sf::Vector2f(0.f, -1.f);
                    break;

                case sf::Keyboard::Down:
                    direction = sf::Vector2f(0.f, 1.f);
                    break;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    if (direction.x < 0.f)
                    {
                        direction.x = 0.f;
                    }
                    break;

                case sf::Keyboard::Right:
                    if (direction.x > 0.f)
                    {
                        direction.x = 0.f;
                    }
                    break;

                case sf::Keyboard::Up:
                    if (direction.y < 0.f)
                    {
                        direction.y = 0.f;
                    }
                    break;

                case sf::Keyboard::Down:
                    if (direction.y > 0.f)
                    {
                        direction.y = 0.f;
                    }
                    break;
                }
            }
        }

        // Get the time elapsed since the last frame
        float deltaTime = sf::Clock::restart().asSeconds();

        // Calculate the movement distance for this frame based on the elapsed time and direction vector
        sf::Vector2f distance = speed * deltaTime * direction;

        // Update the position of the rectangle based on the distance moved
        rectangle.setPosition(rectangle.getPosition() + distance);

        // Clear the window
        window.clear();

        // Draw the rectangle
        window.draw(rectangle);

        // Display the window
        window.display();
    }

    return 0;
}
*/



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