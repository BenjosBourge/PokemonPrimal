/*
** Pokemon Primal
** File description:
** AnimatedSprite
*/

#include <Graph/GUI/HUDBattle.hpp>
#include <NetworkClient.hpp>

void buttonAttack1(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At1");
}

void buttonAttack2(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At2");
}

void buttonAttack3(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At3");
}

void buttonAttack4(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    networkClient.sendPacket("Btn_At4");
}

void buttonBag(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    //show bag items
}

void buttonSwitch(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    //show the other pokemons
}

void buttonRun(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    networkClient.sendPacket("BRn");
}

void buttonFight(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    std::cout << "Fight button clicked" << std::endl;

    auto BattleScene = std::dynamic_pointer_cast<HUDBattle>(hud);
    if (BattleScene) {
        BattleScene->_isMoveButtonsVisible = !BattleScene->_isMoveButtonsVisible;

        BattleScene->showMoveButtons(BattleScene->_isMoveButtonsVisible);
    }
}

void buttonMove(std::shared_ptr<IHUD> hud, NetworkClient &networkClient)
{
    networkClient.sendPacket("BMv");
}

HUDBattle::HUDBattle()
{
    //move buttons
    std::shared_ptr<Button> button1 = std::make_shared<Button>(sf::Vector2f(700, 400), sf::Vector2f(220, 120), "Attack 01");
    button1->onClick = buttonAttack1;
    std::shared_ptr<Button> button2 = std::make_shared<Button>(sf::Vector2f(940, 400), sf::Vector2f(220, 120), "Attack 02");
    button2->onClick = buttonAttack2;
    std::shared_ptr<Button> button3 = std::make_shared<Button>(sf::Vector2f(700, 560), sf::Vector2f(220, 120), "Attack 03");
    button3->onClick = buttonAttack3;
    std::shared_ptr<Button> button4 = std::make_shared<Button>(sf::Vector2f(940, 560), sf::Vector2f(220, 120), "Attack 04");
    button4->onClick = buttonAttack4;
    _moveButton.push_back(button1);
    _moveButton.push_back(button2);
    _moveButton.push_back(button3);
    _moveButton.push_back(button4);

    //menu buttons
    std::shared_ptr<Button> menuButton1 = std::make_shared<Button>(sf::Vector2f(180, 800), sf::Vector2f(300, 150), "Bag");
    menuButton1->onClick = buttonBag;
    std::shared_ptr<Button> menuButton2 = std::make_shared<Button>(sf::Vector2f(490, 800), sf::Vector2f(300, 150), "Pokemon");
    menuButton2->onClick = buttonSwitch;
    std::shared_ptr<Button> menuButton3 = std::make_shared<Button>(sf::Vector2f(800, 800), sf::Vector2f(300, 150), "Run");
    menuButton3->onClick = buttonRun;
    std::shared_ptr<Button> menuButton4 = std::make_shared<Button>(sf::Vector2f(1110, 800), sf::Vector2f(300, 150), "Fight");
    menuButton4->onClick = buttonFight;
    std::shared_ptr<Button> menuButton5 = std::make_shared<Button>(sf::Vector2f(1420, 800), sf::Vector2f(300, 150), "Move");
    menuButton5->onClick = buttonMove;

    _menuButton.push_back(menuButton1);
    _menuButton.push_back(menuButton2);
    _menuButton.push_back(menuButton3);
    _menuButton.push_back(menuButton4);
    _menuButton.push_back(menuButton5);

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

    showMoveButtons(false);
};


void HUDBattle::draw(sf::RenderWindow &window)
{
    for (auto &component : _moveButton) {
        component->draw(window);
    }
    for (auto &component : _textsHp) {
        component->draw(window);
    }
    for (auto &component : _menuButton) {
        component->draw(window);
    }
};


bool HUDBattle::buttonClicked(sf::RenderWindow *window, NetworkClient &networkClient)
{
    bool click = false;
    for (auto &component : _moveButton) {
        if (std::dynamic_pointer_cast<Button>(component)) {
            std::shared_ptr<Button> button = std::dynamic_pointer_cast<Button>(component);

            if (button->isMouseOver(*window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    auto scene = std::make_shared<HUDBattle>(*this);
                    button->onClick(scene, networkClient);
                    click = true;
                }
            }
        }
    }
    for (auto &component : _menuButton) {
        if (std::dynamic_pointer_cast<Button>(component)) {
            std::shared_ptr<Button> button = std::dynamic_pointer_cast<Button>(component);

            if (button->isMouseOver(*window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    auto scene = std::make_shared<HUDBattle>(*this);
                    button->onClick(scene, networkClient);
                    click = true;
                }
            }
        }
    }
    return click;
}

void HUDBattle::showMoveButtons(bool visible)
{
    for (auto &button : _moveButton) {
        auto moveButton = std::dynamic_pointer_cast<Button>(button);
        if (moveButton)
            moveButton->_visible = visible;
    }
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
    if (id < 0 || id >= _moveButton.size())
        return;
    auto button = std::dynamic_pointer_cast<Button>(_moveButton[id]);
    if (button) {
        button->_text.setString(text);
        button->_visible = visible;
    }
}