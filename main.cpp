///////////////////////////////////////////////////////////////////
// Source for Pong Collision Test example                        //
// http://trederia.blogspot.com/2016/02/2d-physics-101-pong.html //
// Released into the public domain                               //
// Example 2                                                     //
///////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

#include <vector>

//------vector maths------//
float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
    return lv.x * rv.x + lv.y * rv.y;
}

sf::Vector2f normalise(sf::Vector2f source)
{
    float length = std::sqrt(dot(source, source));
    if (length != 0) source /= length;
    return source;
}

sf::Vector2f reflect(const sf::Vector2f& velocity, const sf::Vector2f& normal)
{
    return -2.f * dot(velocity, normal) * normal + velocity;
}

float lengthSquared(const sf::Vector2f& source)
{
    return dot(source, source);
}


//------ball class-----//
class Ball final : public sf::Drawable, public sf::Transformable
{
public:
    explicit Ball(const std::vector<sf::RectangleShape>& solidObjects, const std::vector<sf::CircleShape>& circleObjects)
        : m_solidObjects    (solidObjects),
        m_circleObjects     (circleObjects),
        m_velocity          (1.2f, 0.75f) //insert random values here :)
    {
        m_shape.setRadius(10.f);
        setOrigin(10.f, 10.f);

        m_velocity = normalise(m_velocity);
    }

    ~Ball() = default;

    void update(float dt)
    {
        //move the ball
        move(m_velocity * m_speed * dt);

        //check each object for collision
        sf::FloatRect overlap; //holds overlap data, if any
        sf::FloatRect ballBounds = getTransform().transformRect(m_shape.getLocalBounds()); //mutliply the shape bounds by our transform
        for (const auto& o : m_solidObjects)
        {
            if (o.getGlobalBounds().intersects(ballBounds, overlap))
            {
                auto collisionNormal = o.getPosition() - getPosition();
                auto manifold = getManifold(overlap, collisionNormal);
                resolve(manifold);
                break; //skip the rest of the objects
            }
        }

        //check circle shapes
        for (const auto& o : m_circleObjects)
        {
            auto collisionNormal = o.getPosition() - getPosition();
            if (lengthSquared(collisionNormal) < ((o.getRadius() * o.getRadius()) + (m_shape.getRadius() * m_shape.getRadius())))
            {
                //we have a collision
                auto manifold = getManifold(o.getRadius() + m_shape.getRadius(), collisionNormal);
                resolve(manifold);
                break;
            }
        }
    }

private:

    const std::vector<sf::RectangleShape>& m_solidObjects;
    const std::vector<sf::CircleShape>& m_circleObjects;

    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
    const float m_speed = 10000.f;

    sf::Vector3f getManifold(const sf::FloatRect& overlap, const sf::Vector2f& collisionNormal)
    {
        //the collision normal is stored in x and y, with the penetration in z
        sf::Vector3f manifold;

        if (overlap.width < overlap.height)
        {
            manifold.x = (collisionNormal.x < 0) ? 1.f : -1.f;
            manifold.z = overlap.width;
        }
        else
        {
            manifold.y = (collisionNormal.y < 0) ? 1.f : -1.f;
            manifold.z = overlap.height;
        }
        
        return manifold;
    }

    sf::Vector3f getManifold(float summedDistance, const sf::Vector2f& collisionNormal)
    {
        auto collisionDistance = std::sqrt(lengthSquared(collisionNormal));
        auto normal = normalise(collisionNormal);
        sf::Vector3f manifold;
        manifold.x = normal.x;
        manifold.y = normal.y;
        manifold.z = collisionDistance - summedDistance;
        return manifold;
    }

    void resolve(const sf::Vector3f& manifold)
    {
        //move the ball out of the solid object by the penetration amount
        sf::Vector2f normal(manifold.x, manifold.y);
        move(normal * manifold.z);

        //reflect the current velocity to make the ball bounce
        m_velocity = reflect(m_velocity, normal);
    }

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        rt.draw(m_shape, states);
    }
};

//-------builds scene-----//
void createSolidObjects(std::vector<sf::RectangleShape>& shapes)
{
    //we set the shape origins to the centre of the object
    //so that comparing the position with the ball's position
    //gives us a good idea of the direction the ball is moving

    shapes.emplace_back(sf::Vector2f(600.f, 20.f)); //top
    shapes.back().setOrigin(shapes.back().getSize() / 2.f);
    shapes.back().setPosition(300.f, 10.f);

    shapes.emplace_back(sf::Vector2f(20.f, 760.f)); //left
    shapes.back().setOrigin(shapes.back().getSize() / 2.f);
    shapes.back().setPosition(10.f, 400.f);

    shapes.emplace_back(sf::Vector2f(20.f, 760.f)); //right
    shapes.back().setOrigin(shapes.back().getSize() / 2.f);
    shapes.back().setPosition(590.f, 400.f);

    shapes.emplace_back(sf::Vector2f(600.f, 20.f)); //bottom
    shapes.back().setOrigin(shapes.back().getSize() / 2.f);
    shapes.back().setPosition(300.f, 790.f);

    //make the paddle last so we can easily grab a reference to it
    shapes.emplace_back(sf::Vector2f(100.f, 20.f));
    shapes.back().setOrigin(shapes.back().getSize() / 2.f);
    shapes.back().setPosition(300.f, 700.f);
}

void createCircleObjects(std::vector<sf::CircleShape>& shapes)
{
    shapes.emplace_back(30.f);
    shapes.back().setPosition(420.f, 80.f);
    shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

    shapes.emplace_back(60.f);
    shapes.back().setPosition(220.f, 180.f);
    shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

    shapes.emplace_back(20.f);
    shapes.back().setPosition(400.f, 580.f);
    shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

    shapes.emplace_back(45.f);
    shapes.back().setPosition(120.f, 340.f);
    shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());

    shapes.emplace_back(50.f);
    shapes.back().setPosition(320.f, 410.f);
    shapes.back().setOrigin(shapes.back().getRadius(), shapes.back().getRadius());
}

//-------main function------//
int main()
{
    //render target
    sf::RenderWindow window(sf::VideoMode(600, 800), "Pong Collision");

    //delta time clock
    sf::Clock frameClock;

    //vector of static objects
    std::vector<sf::RectangleShape> solidObjects;
    createSolidObjects(solidObjects);

    //get a ref to the paddle shape
    sf::RectangleShape& paddle = solidObjects.back();

    //vector of static circular objects
    std::vector<sf::CircleShape> circleObjects;
    createCircleObjects(circleObjects);

    //the dynamic object
    Ball ball(solidObjects, circleObjects);
    ball.setPosition(300.f, 400.f);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
       {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            //update the paddle position
            else if (event.type == sf::Event::MouseMoved)
            {
                auto x = std::max(0, std::min(600, event.mouseMove.x));
                auto position = paddle.getPosition();
                position.x = static_cast<float>(x);
                paddle.setPosition(position);
            }
        }
        //update the dynamic object
        ball.update(frameClock.restart().asSeconds());

        //draw everything
        window.clear();
        window.draw(ball);
        for (const auto& o : solidObjects)
        {
            window.draw(o);
        }
        for (const auto& o : circleObjects)
        {
            window.draw(o);
        }
        window.display();
    }

    return 0;
}