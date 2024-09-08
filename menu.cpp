#include "menu.h"


Menu::Menu(float width, float height)
{

!font.loadFromFile("karmat.ttf");

    if (!font.loadFromFile("karmat.ttf")) 
    {
       // handle error
    }

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::Green);
    menu[1].setString("Save");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::Green);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_ITEMS + 1) * 3));

    selectedItemIndex = 0;
}


Menu::~Menu()
{    
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < MAX_NUMBER_ITEMS; i++)
    {
        window.draw(menu[i]);
    }

}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::Yellow);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}