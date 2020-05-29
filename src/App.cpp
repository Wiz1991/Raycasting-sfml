#include "App.h"
#include <SFML/Window/Event.hpp>

const sf::Time App::timePerFrame = sf::seconds(1.f / 60.f);

App::App()
: mWindow(sf::VideoMode(800,600),"Raycast")
{

}

void App::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen()){
        sf::Time dt = clock.restart();
        timeSinceLastUpdate+=timePerFrame;
        while(timeSinceLastUpdate > timePerFrame){
            timeSinceLastUpdate-=timePerFrame;
            handleEvents();
            update(timePerFrame);
        }
        render();

    }
}

void App::update(sf::Time dT){





}
void App::handleEvents(){
    sf::Event event;
    while(mWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            mWindow.close();
        }
    }
}
void App::render(){
    mWindow.clear();
    //draw

    mWindow.display();
}