#include <SFML/Graphics.hpp>
#include <list>

class Game
{
private:
    int life = 3;
    int score = 0;

    sf::Texture backgroundTexture;
    sf::Texture pointerTexture;
    sf::Texture snowballTexture;

    sf::Sprite backgroundSprite;
    sf::Sprite pointerSprite;

    std::list<sf::Sprite> snowballList;

public:
    Game();
    ~Game();

    void Loop();
    void Display(sf::RenderWindow &window);
    void ThrowRandomSnowBall();
};