#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
const short int SIZE=2;
class Ray : public sf::Drawable{
    public:
        Ray(sf::Vector2f pos, float angle);
        Ray(sf::Vector2f pos1,sf::Vector2f pos2);
        sf::Vector2f& operator[](int index);
        void update(sf::Time dT);
    private:
       virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::Vertex points[SIZE]; 
        float m_angle;

};

