#include "App.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <random>

static std::mt19937 rndEngine(static_cast<unsigned long>(std::time(nullptr)));
static inline float value(float begin, float end, std::mt19937 &engine = rndEngine)
{
    std::uniform_real_distribution<float> dist(begin, end);
    return dist(engine);
}
const sf::Time App::timePerFrame = sf::seconds(1.f / 60.f);
bool lineIntersect(const sf::Vector2f &A1, const sf::Vector2f &A2, const sf::Vector2f &B1, const sf::Vector2f &B2, sf::Vector2f &intersection);
App::App()
    : mWindow(sf::VideoMode(800, 600), "Raycast", sf::Style::Default, sf::ContextSettings(0, 0, 8)),
      player(5)
{
    player.setPosition(300, 300);
    player.setFillColor(sf::Color::White);
    player.setOrigin(5, 5);

    const float step = 1.f / 1000;
    for (int i = 0; i < 360 * 60; i += 1)
    {
        rays.push_back(Ray(player.getPosition(), i));
    }

    for (int i = 0; i < 5; i++)
    {
        int x1 = value(0, 800);
        int y1 = value(0, 600);

        int x2 = value(0, 800);
        int y2 = value(0, 600);

        walls.push_back(Wall(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2)));
    }
}

void App::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += timePerFrame;
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            handleEvents();
            update(timePerFrame);
        }
        render();
    }
}

void App::update(sf::Time dT)
{
    for (auto &ray : rays)
    {
        ray[0] = player.getPosition();
        ray.update(dT);
        sf::Vector2f closest;
        float max = std::numeric_limits<float>::max();
        for (auto &wall : walls)
        {
            sf::Vector2f iPoint;
            if (lineIntersect(ray[0], ray[1], wall[0], wall[1], iPoint))
            {

                double dx = (ray[0].x - iPoint.x);
                double dy = (ray[0].y - iPoint.y);
                float distance = dx * dx + dy * dy;
                if (distance < max)
                {
                    max = distance;
                    closest = iPoint;
                }
            }
        }
        if (closest.x != 0){
            ray[1] = closest;
        }
    }
}
void App::handleEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
        if (event.type == sf::Event::MouseMoved /*&& event.key.code == sf::Mouse::Button::Left*/)
        {
            sf::Vector2f mousePos{static_cast<sf::Vector2f>(sf::Mouse::getPosition(mWindow))};
            player.setPosition(mousePos);
        }
    }
}
void App::render()
{
    mWindow.clear();
    for (auto &ray : rays)
    {
        mWindow.draw(ray);
    }
    mWindow.draw(player);
    for (auto &wall : walls)
    {
        mWindow.draw(wall);
    }
    mWindow.display();
}
float PerpDot(const sf::Vector2f &a, const sf::Vector2f &b) { return (a.y * b.x) - (a.x * b.y); }

bool lineIntersect(const sf::Vector2f &A1, const sf::Vector2f &A2, const sf::Vector2f &B1, const sf::Vector2f &B2, sf::Vector2f &intersection)
{
    sf::Vector2f a(A2 - A1);
    sf::Vector2f b(B2 - B1);
    sf::Vector2f c(B2 - A2);

    float f = PerpDot(a, b);

    // lines are parallel
    if (!f)
    {
        return false;
    }

    float aa = PerpDot(a, c);
    float bb = PerpDot(b, c);

    if (f < 0)
    {
        if (aa > 0)
            return false;
        if (bb > 0)
            return false;
        if (aa < f)
            return false;
        if (bb < f)
            return false;
    }
    else
    {
        if (aa < 0)
            return false;
        if (bb < 0)
            return false;
        if (aa > f)
            return false;
        if (bb > f)
            return false;
    }

    intersection = b * (1.0f - (aa / f)) + B1; // assigns the point of intersection

    return true;
}