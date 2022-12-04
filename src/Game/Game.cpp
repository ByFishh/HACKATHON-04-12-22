#include "./Game.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

Game::Game()
{
    this->snowballTexture.loadFromFile("./res/snowball.png");

    this->backgroundTexture.loadFromFile("./res/background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition({0, 0});

    this->pointerTexture.loadFromFile("./res/papanowel.png");
    pointerSprite.setTexture(pointerTexture);
    pointerSprite.setPosition({0, 0});
}

Game::~Game()
{
}

void Game::Loop()
{
    sf::Clock spawnClock;
    sf::Clock moveClock;
    sf::Time elapsedSpawnTime;
    sf::Time elapsedMoveTime;
    sf::RenderWindow window(sf::VideoMode(1080, 720), "NoelX");

    int speed = 100;

    while (window.isOpen())
    {
        if (this->score % 50 == 0 && speed > 50)
        {
            speed -= 5;
        }

        if (this->life <= 0)
        {
            std::cout << "Vous avez perdu avec un score de " << this->score << std::endl;
            return;
        }
        sf::Event event;
        elapsedSpawnTime = spawnClock.getElapsedTime();
        if (elapsedSpawnTime.asSeconds() >= 2)
        {
            this->ThrowRandomSnowBall();
            spawnClock.restart();
        }

        elapsedMoveTime = moveClock.getElapsedTime();
        if (elapsedMoveTime.asMilliseconds() >= speed)
        {
            for (std::list<sf::Sprite>::iterator i = this->snowballList.begin(); i != this->snowballList.end(); i++)
            {
                sf::Vector2f pos = (*i).getPosition();
                pos.x = pos.x - 20;

                if (pos.x <= -100)
                {
                    std::list<sf::Sprite>::iterator newIt = i;
                    newIt++;
                    this->snowballList.erase(i);
                    i = newIt;
                    this->score += 10;
                }
                else
                {
                    (*i).setPosition(pos);
                }
            }
            moveClock.restart();
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                sf::IntRect papanowelRect = {pos.x,
                                             pos.y,
                                             100,
                                             118};
                this->pointerSprite.setPosition(pos.x - 50, pos.y - 57);

                for (std::list<sf::Sprite>::iterator i = this->snowballList.begin(); i != this->snowballList.end(); i++)
                {
                    sf::Vector2f spritePos = (*i).getPosition();
                    sf::IntRect spriteRect = {(int)spritePos.x,
                                              (int)spritePos.y,
                                              100,
                                              100};

                    if (spriteRect.intersects(papanowelRect))
                    {
                        this->life -= 1;
                        std::list<sf::Sprite>::iterator newIt = i;
                        newIt++;
                        this->snowballList.erase(i);
                        i = newIt;
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        this->Display(window);
        window.display();
    }
    return;
}

void Game::Display(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("./res/font.ttf");

    sf::Text scoreText;
    sf::Text lifeText;

    scoreText.setFont(font);
    lifeText.setFont(font);

    scoreText.setString("Score:" + std::to_string(this->score));
    lifeText.setString("Life:" + std::to_string(this->life));

    scoreText.setCharacterSize(70);
    lifeText.setCharacterSize(70);

    scoreText.setPosition({0, 0});
    lifeText.setPosition({200, 0});

    scoreText.setColor(sf::Color::Black);
    lifeText.setColor(sf::Color::Black);

    window.draw(this->backgroundSprite);
    window.draw(this->pointerSprite);

    for (sf::Sprite sprite : this->snowballList)
    {
        window.draw(sprite);
    }

    window.draw(lifeText);
    window.draw(scoreText);
}

void Game::ThrowRandomSnowBall()
{
    int random = rand() % 4;

    sf::Sprite tmp;

    tmp.setTexture(this->snowballTexture);
    tmp.setPosition({1000, 720 / 4 * random + (float)50});

    this->snowballList.push_front(tmp);
}