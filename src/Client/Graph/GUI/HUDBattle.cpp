/*
** Pokemon Primal
** File description:
** AnimatedSprite
*/

#include <Graph/GUI/HUDBattle.hpp>
#include <NetworkClient.hpp>

void buttonAttack1(NetworkClient &networkClient)
{
    std::cout << "Attack 1 clicked!" << std::endl;
}

void buttonAttack2(NetworkClient &networkClient)
{
    std::cout << "Attack 2 clicked!" << std::endl;
}

void buttonAttack3(NetworkClient &networkClient)
{
    std::cout << "Attack 3 clicked!" << std::endl;
}

void buttonAttack4(NetworkClient &networkClient)
{
    std::cout << "Attack 4 clicked!" << std::endl;
}


HUDBattle::HUDBattle()
{
    std::shared_ptr<Button> button1 = std::make_shared<Button>(sf::Vector2f(700, 500), sf::Vector2f(220, 120), "Attack 01");
    button1->onClick = buttonAttack1;
    std::shared_ptr<Button> button2 = std::make_shared<Button>(sf::Vector2f(940, 500), sf::Vector2f(220, 120), "Attack 02");
    button2->onClick = buttonAttack2;
    std::shared_ptr<Button> button3 = std::make_shared<Button>(sf::Vector2f(700, 660), sf::Vector2f(220, 120), "Attack 03");
    button3->onClick = buttonAttack3;
    std::shared_ptr<Button> button4 = std::make_shared<Button>(sf::Vector2f(940, 660), sf::Vector2f(220, 120), "Attack 04");
    button4->onClick = buttonAttack4;
    _components.push_back(button1);
    _components.push_back(button2);
    _components.push_back(button3);
    _components.push_back(button4);
};


void HUDBattle::draw(sf::RenderWindow &window)
{
    for (auto &component : _components) {
        component->draw(window);
    }
};


void HUDBattle::buttonClicked(sf::RenderWindow *window, NetworkClient &networkClient)
{
    for (auto &component : _components) {
        if (std::dynamic_pointer_cast<Button>(component)) {
            std::shared_ptr<Button> button = std::dynamic_pointer_cast<Button>(component);

            if (button->isMouseOver(*window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    button->onClick(networkClient);
                }
            }
        }
    }
}