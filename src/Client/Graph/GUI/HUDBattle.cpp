/*
** Pokemon Primal
** File description:
** AnimatedSprite
*/

#include <Graph/GUI/HUDBattle.hpp>
#include <NetworkClient.hpp>

void buttonAttack1(NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At1");
}

void buttonAttack2(NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At2");
}

void buttonAttack3(NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At3");
}

void buttonAttack4(NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At4");
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

    //hp texts
    std::shared_ptr<TextBox> text1 = std::make_shared<TextBox>(sf::Vector2f(100, 600), 20, "HP: 0/0");
    std::shared_ptr<TextBox> text2 = std::make_shared<TextBox>(sf::Vector2f(200, 600), 20, "HP: 0/0");
    std::shared_ptr<TextBox> text3 = std::make_shared<TextBox>(sf::Vector2f(300, 600), 20, "HP: 0/0");
    std::shared_ptr<TextBox> text4 = std::make_shared<TextBox>(sf::Vector2f(400, 600), 20, "HP: 0/0");
    std::shared_ptr<TextBox> text5 = std::make_shared<TextBox>(sf::Vector2f(800, 100), 20, "HP: 0/0");
    std::shared_ptr<TextBox> text6 = std::make_shared<TextBox>(sf::Vector2f(900, 100), 20, "HP: 0/0");
    std::shared_ptr<TextBox> text7 = std::make_shared<TextBox>(sf::Vector2f(1000, 100), 20, "HP: 0/0");
    std::shared_ptr<TextBox> text8 = std::make_shared<TextBox>(sf::Vector2f(1100, 100), 20, "HP: 0/0");
    _textsHp.push_back(text1);
    _textsHp.push_back(text2);
    _textsHp.push_back(text3);
    _textsHp.push_back(text4);
    _textsHp.push_back(text5);
    _textsHp.push_back(text6);
    _textsHp.push_back(text7);
    _textsHp.push_back(text8);
};


void HUDBattle::draw(sf::RenderWindow &window)
{
    for (auto &component : _components) {
        component->draw(window);
    }
    for (auto &component : _textsHp) {
        component->draw(window);
    }
};


bool HUDBattle::buttonClicked(sf::RenderWindow *window, NetworkClient &networkClient)
{
    bool click = false;
    for (auto &component : _components) {
        if (std::dynamic_pointer_cast<Button>(component)) {
            std::shared_ptr<Button> button = std::dynamic_pointer_cast<Button>(component);

            if (button->isMouseOver(*window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    button->onClick(networkClient);
                    click = true;
                }
            }
        }
    }
    return click;
}

void HUDBattle::setText(int id, const std::string &text, bool visible)
{
    if (id < 0 || id >= _textsHp.size())
        return;
    auto textBox = std::dynamic_pointer_cast<TextBox>(_textsHp[id]);
    if (textBox) {
        textBox->_text.setString(text);
        textBox->_visible = visible;
    }
}

void HUDBattle::setAttack(int id, const std::string &text, bool visible)
{
    if (id < 0 || id >= _components.size())
        return;
    auto button = std::dynamic_pointer_cast<Button>(_components[id]);
    if (button) {
        button->_text.setString(text);
        button->_visible = visible;
    }
}