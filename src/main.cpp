#include <SFML/Graphics.hpp>
#include <cmath>
#include <SFML/Audio.hpp>
using namespace sf;


#include <MainMenu.hpp>
#include <Car.hpp>
#include <SoundManager.hpp>

int main()
{

  float windowHeight = 1024;
  float windowWidth = 768;

  RenderWindow MENU(VideoMode(1280, 720), "Main Menu", Style::Default);
  MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);


  //Photo to the Game + additional features
  Texture t1,t2;
  t1.loadFromFile("images/background.png");
  t2.loadFromFile("images/car.png");
  t1.setSmooth(true);
  t2.setSmooth(true);
  Sprite sBackground(t1), sCar(t2);
  //scales the background sprite to twice its original size.
  sBackground.scale(2,2);
  // sets the origin
  sCar.setOrigin(22, 22);
  float R=22;
  //amount of cars
  const int N=5;
  Car car[N];
  for(int i=0;i<N;i++)
  {
    car[i].x=300+i*50;
    car[i].y=1700+i*80;
    car[i].speed=7+i;
  }

  //Parameters
  float speed=0,angle=0;
  float maxSpeed=12.0;
  float acc=0.2, dec=0.3;
  float turnSpeed=0.08;
  int offsetX=0,offsetY=0;


  //Photo to the MENU
  Texture t3;
  t3.loadFromFile("images/hotline_miami.png");
  t3.setSmooth(true);
  Sprite MenuBackground(t3);

  // run the program as long as the window is open
  while (MENU.isOpen()){

      // check all the window's events that were triggered since the last iteration of the loop
      Event e;
      while (MENU.pollEvent(e))
      {
             // "close requested" event: we close the window
            if (e.type == Event::Closed)
            {
                MENU.close();
            }

            if (e.type == Event::KeyReleased)
            {
                if (e.key.code == Keyboard::Up)
                {
                  mainMenu.MoveUp();
                  break;
                }
                if (e.key.code == Keyboard::Down)
                {
                  mainMenu.MoveDown();
                  break;
                }
                if (e.key.code == Keyboard::Return) {

                  RenderWindow Play(VideoMode(windowHeight, windowWidth), "Car Racing Game!");
                  Play.setFramerateLimit(60);
                  RenderWindow OPTIONS(VideoMode(windowHeight, windowWidth), "OPTIONS");
                  RenderWindow ABOUT(VideoMode(windowHeight, windowWidth), "ABOUT");

                  int x = mainMenu.MainMenuPressed();
                  if (x == 0)
                  {
                    SoundManager::playMusic("sounds/Hotline Miami Soundtrack ~ Hydrogen [TubeRipper.cc].ogg"); 
                    while (Play.isOpen())
                    {
                      Event aevent;
                      while (Play.pollEvent(aevent)) {
                        if (aevent.type == Event::Closed)
                        {
                        Play.close();
                        }
                        if (aevent.type == Event::KeyPressed)
                        {
                          if (aevent.key.code == Keyboard::Escape)
                          {
                            Play.close();
                          }
                        
                        }
                      }
                      
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

                      if (Right && speed!=0)  angle += turnSpeed * speed/maxSpeed;
                      if (Left && speed!=0)   angle -= turnSpeed * speed/maxSpeed;

                      car[0].speed = speed;
                      car[0].angle = angle;

                      for(int i=0;i<N;i++) car[i].move();
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


                      Play.clear(Color::White);

                      if (car[0].x>320) offsetX = car[0].x-320;
                      if (car[0].y>240) offsetY = car[0].y-240;

                      sBackground.setPosition(-offsetX,-offsetY);
                      Play.draw(sBackground);

                      Color colors[10] = {Color::Red, Color::Green, Color::Magenta, Color::Blue, Color::White};

                      for(int i=0;i<N;i++)
                      {
                        sCar.setPosition(car[i].x-offsetX,car[i].y-offsetY);
                        sCar.setRotation(car[i].angle*180/3.141593);
                        sCar.setColor(colors[i]);
                        Play.draw(sCar);
                      }
                      MENU.close();
                      Play.display();
                      OPTIONS.close();
                      ABOUT.close();
                      Play.clear();
                      Play.draw(sBackground);

                    }
                    
                  }
                  if (x == 1)
                  {
                    SoundManager::stopMusic();
                    while (OPTIONS.isOpen())
                    {
                      Event aevent;
                      while (OPTIONS.pollEvent(aevent)){
                        if (aevent.type == Event::Closed)
                        {
                          OPTIONS.close();
                        }
                        if (aevent.type == Event::KeyPressed)
                        {
                          if (aevent.key.code == Keyboard::Escape)
                          {
                            OPTIONS.close();
                          }
                        
                        }
                      }
                      MENU.close();
                      Play.close();
                      OPTIONS.clear();
                      ABOUT.close();
                      OPTIONS.display();
                    }
                  }
                  if (x == 2)
                  {
                    SoundManager::stopMusic();
                    while (ABOUT.isOpen())
                    {
                      Event aevent;
                      while (ABOUT.pollEvent(aevent))
                      {
                        if (aevent.type == Event::Closed)
                        {
                          ABOUT.close();
                        }
                        if (aevent.type == Event::KeyPressed)
                        {
                          if (aevent.key.code == Keyboard::Escape)
                          {
                            ABOUT.close();
                          }
                        
                        }
 
                      }
                      MENU.close();
                      Play.close();
                      OPTIONS.close();
                      ABOUT.clear();
                      ABOUT.display();
                    }
                  }
                  if (x == 3)
                    SoundManager::stopMusic();
                    MENU.close();
                  break;
                }
            }
    }
    MENU.clear();
    MENU.draw(MenuBackground);
    mainMenu.draw(MENU);
    MENU.display();
  }
  return 0;
}
