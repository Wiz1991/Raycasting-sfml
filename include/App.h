#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Line.h"
#include <vector>
class App
{
public:
    typedef Ray Wall;
    App();
    void run();
    void update(sf::Time dT);
    void render();
    void handleEvents();
private:
    void genWalls();
    
private:
    sf::RenderWindow mWindow;
    sf::CircleShape player;
    std::vector<Ray> rays;
    std::vector<Wall> walls;
    static const sf::Time timePerFrame;
};
