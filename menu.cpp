#include "menu.h"
#include <SFML/Graphics.hpp>



Menu::Menu(float width,float height)
{
    if(!font.loadFromFile("fonts/Caladea-Bold.ttf"))
    {
        //nie znaleziono czcionki
    }

    menu[0].setFont(font);
menu[0].setCharacterSize(130);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(1240/2-(menu[0].getLocalBounds().width/2),height/2*0.5));

    menu[1].setFont(font);
menu[1].setCharacterSize(130);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(1240/2-(menu[1].getLocalBounds().width/2),height/2*0.9));
        author.setFont(font);
author.setCharacterSize(20);
    author.setFillColor(sf::Color::Black);
    author.setString("Autor:£ukasz Synowiec");
    author.setPosition(sf::Vector2f(1000,650));
    selectedItemIndex=0;
}
Menu::~Menu()
{
 std::cout<<"x";
}
void Menu::Draw(sf::RenderWindow &window)
{
    for(int i=0;i<MAX_NUMBER_OF_ITEMS;i++)
    {
        window.draw(menu[i]);
        window.draw(author);
    }
}

void Menu::MoveUp()
{
    if(selectedItemIndex-1>=0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);

    }
}
void Menu::MoveDown()
{
    if(selectedItemIndex+1<MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);

    }
}


