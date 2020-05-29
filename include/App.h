#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Font.hpp>

class App
{
public:
    App();
    void run();
    void update(sf::Time dT);
    void render();
    void handleEvents();

private:
    sf::RenderWindow mWindow;
    static const sf::Time timePerFrame;
};
