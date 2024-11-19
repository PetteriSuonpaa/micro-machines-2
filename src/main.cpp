#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
int main()
{
    //creating world box2d (version 3.x)
    b2Vec2 gravity = {0.0f, -10.0f};
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = gravity;
    b2WorldId worldId = b2CreateWorld(&worldDef);

    //creating a body
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){0.0f, 4.0f};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    //Creating a shape
    b2Polygon box = b2MakeBox(1.0f, 1.0f);

    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    
    b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &box);

    b2DestroyBody(bodyId);
    bodyId = b2_nullBodyId;

    //testing SFML (version 2.6)
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}