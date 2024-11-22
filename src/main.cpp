#include <SFML/Graphics.hpp>
#include <cmath>
#include <Car.cpp>
#include <SoundManager.cpp>
#include <SFML/Audio.hpp>
using namespace sf;

int main()
{
    float windowHeight = 1024;
    float windowWidth = 768;

    RenderWindow app(VideoMode(windowHeight, windowWidth), "Car Racing Game!");
    //ensures the game runs at 60 frames per second
    app.setFramerateLimit(60);

    Texture t1,t2,t3;
    //load the map images
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/car.png");
    t1.setSmooth(true);
    t2.setSmooth(true);
    
    // play music 
    SoundManager::playMusic("sounds/Hotline Miami Soundtrack ~ Hydrogen [TubeRipper.cc].ogg");

    Sprite sBackground(t1), sCar(t2);
    //scales the background sprite to twice its original size.
    sBackground.scale(2,2);
    // sets the origin
    sCar.setOrigin(22, 22);
    float R=22;

    // number of cars in the game
    const int N=5;
    Car car[N];
    //initializes postion and speed for each car
    for(int i=0;i<N;i++)
    {
      // x and y coordinate of each car
      car[i].x=300+i*50;
      car[i].y=1700+i*80;
      // increase speed for each car
      car[i].speed=7+i;
    }

    // Car Movement Parameters
   float speed=0,angle=0;
   float maxSpeed=12.0;
   float acc=0.2, dec=0.3;
   float turnSpeed=0.08;

    //  These are used to adjust the background based on the car's position, effectively creating a scrolling effect as the car moves.
   int offsetX=0,offsetY=0;

    // run the program as long as the window is open
    while (app.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event e;
        while (app.pollEvent(e))
        {
             // "close requested" event: we close the window
            if (e.type == Event::Closed)
                app.close();
        }

    // Handling User Input
    bool Up=0,Right=0,Down=0,Left=0;
    if (Keyboard::isKeyPressed(Keyboard::Up)) Up=1;
    if (Keyboard::isKeyPressed(Keyboard::Right)) Right=1;
    if (Keyboard::isKeyPressed(Keyboard::Down)) Down=1;
    if (Keyboard::isKeyPressed(Keyboard::Left)) Left=1;

    //car movement
    if (Up && speed<maxSpeed)
        if (speed < 0)  speed += dec;
        else  speed += acc;

    if (Down && speed>-maxSpeed)
        if (speed > 0) speed -= dec;
        else  speed -= acc;

    if (!Up && !Down)
        if (speed - dec > 0) speed -= dec;
        else if (speed + dec < 0) speed += dec;
        else speed = 0;
    
    //Turning the Car
    if (Right && speed!=0)  angle += turnSpeed * speed/maxSpeed;
    if (Left && speed!=0)   angle -= turnSpeed * speed/maxSpeed;

    car[0].speed = speed;
    car[0].angle = angle;
    // update positions (move) 
    for(int i=0;i<N;i++) car[i].move();
    // this is for the bots movement
    for(int i=1;i<N;i++) car[i].findTarget();

    //collision
    for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
    {      
        int dx=0, dy=0;
        while (dx*dx+dy*dy<4*R*R)
         {
           car[i].x+=dx/10.0;
           car[i].x+=dy/10.0;
           car[j].x-=dx/10.0;
           car[j].y-=dy/10.0;
           dx = car[i].x-car[j].x;
           dy = car[i].y-car[j].y;
           if (!dx && !dy) break;
         }
    }

    //Background and Car Rendering
    app.clear(Color::White);

    if (car[0].x>320) offsetX = car[0].x-320;
    if (car[0].y>240) offsetY = car[0].y-240;

    sBackground.setPosition(-offsetX,-offsetY);
    app.draw(sBackground);
    
    // Drawing Cars
    Color colors[10] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White};

    for(int i=0;i<N;i++)
    {
      sCar.setPosition(car[i].x-offsetX,car[i].y-offsetY);
      sCar.setRotation(car[i].angle*180/3.141593);
      sCar.setColor(colors[i]);
      app.draw(sCar);
    }
    //
    app.display();
    }

    return 0;
}
