#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "menu.h"
#include <cstdlib>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
enum DIRECTION
{
    UP=0,
    UP_RIGHT=45,
    RIGHT=90,
    DOWN_RIGHT=135,
    DOWN=180,
    DOWN_LEFT=225,
    LEFT=270,
    UP_LEFT=315

};
DIRECTION Dir=UP_RIGHT;
const float BALL_SPEED=3,SHAPE_DISTANCE=50;
float ball_move_direction=Dir,widok=0;
int iSNull=0,isWinner=27;
bool isWin=false;
sf::Vector2f ball_position(1000,600);
void paddleMove();
void ballMove();
void collision_detect();
sf::RenderWindow window(sf::VideoMode(1240, 768), "Arkanoid!");//tworzenie okna
sf::Sprite paddle,shape[30],null;
sf::Sprite test;

sf::CircleShape ball;

static sf::View GameView(sf::Vector2f(0,0),sf::Vector2f(1240,768)),MenuView(sf::Vector2f(0,0),sf::Vector2f(1240,768)),EndView(sf::Vector2f(0,0),sf::Vector2f(1240,768));
static Menu menu(1240,768);

void shapeCollision();
void loadAndDrawShape();
void paddle_collision();
void drawEndView();
int main()
{
    srand( time( NULL ) );
    float x=rand()%1000+1;
    ball.setPosition(x,600);
    ball_position.x=x;
    test.setPosition(ball_position.x,ball_position.y);
    sf::Texture tek;

    tek.loadFromFile("graphics/test.png");
    test.setTexture(tek);
    test.setScale(0.01,0.01);
    sf::Image icon;
    icon.loadFromFile("graphics/icon.png");

window.setIcon(32,32,icon.getPixelsPtr());
    window.setFramerateLimit(144);
    sf::Texture textureToPaddle,textureToBall;
    textureToPaddle.loadFromFile("graphics/paddle.png");
    textureToBall.loadFromFile("graphics/ball1.png");

    paddle.setTexture(textureToPaddle);
    paddle.setPosition(556,650);
    ball.setRadius(15);
    ball.setOutlineColor(sf::Color::Red);
    ball.setOutlineThickness(6);
    ball.setFillColor(sf::Color::Green);
    window.setMouseCursorVisible(false);
    MenuView=window.getDefaultView();
    GameView=window.getDefaultView();
    EndView=window.getDefaultView();
    window.setView(MenuView);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))//dopóki istnieja eventy
        {
            // sprawdzenie typu eventów
            switch (event.type)
            {
            // zamkniêcie okna
            case sf::Event::Closed:
            {

                window.close();
            }
            break;

            // wciœniêcie klawisza (dowolnego)
            case sf::Event::KeyPressed:
            {
                if(event.key.code==sf::Keyboard::Up&&widok==0)
                {
                    menu.MoveUp();
                }
                if(event.key.code==sf::Keyboard::Down&&widok==0)
                {
                    menu.MoveDown();
                }
                if(event.key.code==sf::Keyboard::Return&&widok==0)
                {
                    switch(menu.GetPressedItem())
                    {
                    case 0:
                    {
                        widok=1;

                    }
                    break;
                    case 1:
                    {
                        window.close();

                    }
                    break;
                    }

                }
                if(event.key.code==sf::Keyboard::Return&&widok==2)
                {
                    window.close();
                }
            }
            break;
            default:// inne eventy s¹ pomijane
                break;
            }
        }
        window.clear(sf::Color::Cyan);//czyszczenie i ustawienie koloru
        if(widok==0)
        {
            menu.Draw(window);
        }
        if(widok==1)
        {
            loadAndDrawShape();
            paddleMove();
            ballMove();
            shapeCollision();
            test.setPosition(ball_position.x+8,ball_position.y+15);
            paddle_collision();
            collision_detect();
            window.draw(test);
            if(isWinner<=0)
            {
                isWin=true;
                widok=2;
            }
        }
           if(widok==2)
        {
            drawEndView();
        }
        window.display();

    }
    return 0;
}
void loadAndDrawShape()
{
    sf::Vector2f position(30,SHAPE_DISTANCE);
    sf::Texture tekstura;
    tekstura.loadFromFile("graphics/shape1.png");
    for(int i=0; i<10; i++)
    {
        if(iSNull==0)
        {
            shape[i].setTexture(tekstura);
        }
        shape[i].setPosition(position.x,position.y);
        position.x+=135;
        window.draw(shape[i]);
    }

    sf::Vector2f position1(30,SHAPE_DISTANCE*2);

    tekstura.loadFromFile("graphics/shape2.png");
    for(int i=10; i<20; i++)
    {
        if(iSNull==0)
        {
            shape[i].setTexture(tekstura);
        }
        shape[i].setPosition(position1.x,position1.y);
        position1.x+=135;
        window.draw(shape[i]);
    }


    sf::Vector2f position2(30,SHAPE_DISTANCE*3);

    tekstura.loadFromFile("graphics/shape3.png");
    for(int i=20; i<30; i++)
    {

        if(iSNull==0)
        {
            shape[i].setTexture(tekstura);
        }
        shape[i].setPosition(position2.x,position2.y);
        position2.x+=135;
        window.draw(shape[i]);
    }//od 0 do 29
    iSNull=1;
}

void paddleMove()
{
    sf::Vector2i mousePosition=sf::Mouse::getPosition(window);
    paddle.setPosition(mousePosition.x,650);
    window.draw(paddle);
}
void ballMove()
{

    if(ball_move_direction==DOWN)//w dól
    {
        ball_position.y+=BALL_SPEED;
    }
    else if(ball_move_direction==UP)//w góre
    {
        ball_position.y-=BALL_SPEED;
    }
    else if(ball_move_direction==RIGHT)//w lewo
    {
        ball_position.x+=BALL_SPEED;
    }
    else if(ball_move_direction==LEFT)//w prawo
    {
        ball_position.x-=BALL_SPEED;
    }
    else if(ball_move_direction==DOWN_LEFT)//w lewo w dół
    {
        ball_position.x-=BALL_SPEED;
        ball_position.y+=BALL_SPEED;

    }
    else if(ball_move_direction==DOWN_RIGHT)//w prawo w dół
    {
        ball_position.x+=BALL_SPEED;
        ball_position.y+=BALL_SPEED;

    }
    else if(ball_move_direction==UP_LEFT)//w prawo w dół
    {
        ball_position.y-=BALL_SPEED;
        ball_position.x-=BALL_SPEED;

    }
    else if(ball_move_direction==UP_RIGHT)
    {
        ball_position.y-=BALL_SPEED;
        ball_position.x+=BALL_SPEED;
    }
    ball.setPosition(ball_position.x,ball_position.y);
    window.draw(ball);

}
void paddle_collision()
{
    sf::FloatRect otherBox =test.getGlobalBounds();
    sf::FloatRect otherBox1 =paddle.getGlobalBounds();

    if (otherBox1.intersects(otherBox))
    {
        if(ball_move_direction==DOWN_LEFT)
            ball_move_direction=UP_LEFT;
        if(ball_move_direction==DOWN_RIGHT)
            ball_move_direction=UP_RIGHT;
        if(ball_move_direction==DOWN)
            ball_move_direction=UP;
        ball_position.x+=3;

    }
}

void collision_detect()
{

    if(ball_position.y>670)
    {
        isWin=false;
        widok=2;

    }
//---------------------------------------------
//PRAWY BOK
    if(ball_position.x>1200)
    {
        if(ball_move_direction==DOWN_RIGHT)
        {

            ball_move_direction=DOWN_LEFT;

        }
        else if(ball_move_direction==UP_RIGHT)
        {

            ball_move_direction=UP_LEFT;

        }
        else if(ball_move_direction==RIGHT)
        {

            ball_move_direction=LEFT;

        }
    }
    //---------------------------------------------
//LEWY BOK
    if(ball_position.x<5)
    {
        if(ball_move_direction==DOWN_LEFT)
        {

            ball_move_direction=DOWN_RIGHT;

        }
        else if(ball_move_direction==UP_LEFT)
        {

            ball_move_direction=UP_RIGHT;

        }
        else if(ball_move_direction==LEFT)
        {

            ball_move_direction=RIGHT;

        }
    }
    //---------------------------------------------
//SUFIT
    if(ball_position.y<0)
    {
        if(ball_move_direction==UP)
        {

            ball_move_direction=DOWN;

        }
        else if(ball_move_direction==UP_LEFT)
        {

            ball_move_direction=DOWN_LEFT;

        }
        else if(ball_move_direction==UP_RIGHT)
        {

            ball_move_direction=DOWN_RIGHT;

        }
    }

}
void shapeCollision()
{
    for(size_t i=0; i<30; i++)
    {
        sf::FloatRect rect1;
        rect1.top = ball_position.y;
        rect1.left = ball_position.x;
        rect1.height = 35.0;
        rect1.width = 35.0;
        sf::FloatRect boundingBoxSprite1;
        boundingBoxSprite1=shape[i].getGlobalBounds();
        if(boundingBoxSprite1.intersects(rect1))
        {

            shape[i]=null;
            isWinner--;
            std::cout<<isWinner<<std::endl;
            if(ball_move_direction==UP)
            {

                ball_move_direction=DOWN;

            }
            else if(ball_move_direction==UP_LEFT)
            {

                ball_move_direction=DOWN_LEFT;

            }
            else if(ball_move_direction==UP_RIGHT)
            {
                //3 upy

                ball_move_direction=DOWN_RIGHT;

            }
            else if(ball_move_direction==DOWN_RIGHT)
            {

                ball_move_direction=UP_RIGHT;

            }
            else if(ball_move_direction==LEFT)
            {

                ball_move_direction=RIGHT;

            }
            else if(ball_move_direction==DOWN_LEFT)
            {

                ball_move_direction=UP_LEFT;

            }
            else if(ball_move_direction==RIGHT)
            {

                ball_move_direction=LEFT;

            }
            else if(ball_move_direction==DOWN)
            {

                ball_move_direction=UP;

            }
        }
    }
}
void drawEndView()
{
    sf::Text tekst;
    sf::Font font;
    font.loadFromFile("fonts/Caladea-Bold.ttf");
    tekst.setCharacterSize(100);
    tekst.setFont(font);
    tekst.setFillColor(sf::Color::Red);

    if(isWin==true)
    {
        tekst.setString("WINNER");
        tekst.setPosition(sf::Vector2f(1240/2-(tekst.getLocalBounds().width/2),200));
        window.draw(tekst);
    }
    if(isWin==false)
    {
        tekst.setString("GAME OVER");
        tekst.setPosition(sf::Vector2f(1240/2-(tekst.getLocalBounds().width/2),200));
        window.draw(tekst);
    }
}
