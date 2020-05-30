#include "Line.h"
#include <math.h>
Ray::Ray(sf::Vector2f pos1,sf::Vector2f pos2)
{
    points[0] = sf::Vertex(pos1,sf::Color::Green);
    points[1] = sf::Vertex(pos2,sf::Color::Green);
}
Ray::Ray(sf::Vector2f pos,float angle)
{
    points[0] = sf::Vertex(pos,sf::Color(255, 255, 255, 10));

    sf::Vector2f dirPoint;
    m_angle= angle* (3.14/180);

    dirPoint.x = points[0].position.x + 5000 * std::cos(m_angle);
    dirPoint.y = points[0].position.y + 5000 * std::sin(m_angle);

    points[1] = sf::Vertex(dirPoint,sf::Color(255, 255, 255, 10));    
}
void Ray::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(points, 2, sf::Lines, states);
}
sf::Vector2f& Ray::operator[](int index){
    return points[index].position;

}
void Ray::update(sf::Time dT){
    sf::Vector2f dirPoint;
    dirPoint.x = points[0].position.x + 5000 * std::cos(m_angle);
    dirPoint.y = points[0].position.y + 5000 * std::sin(m_angle);

   points[1] = sf::Vertex(dirPoint,sf::Color(255, 255, 255, 10));    
}