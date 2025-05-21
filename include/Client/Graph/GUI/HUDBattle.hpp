/*
** Pokemon Primal
** File description:
** HUDMapEditor
*/

#pragma once

#include <Graph/GUI/IHUD.hpp>
#include <Graph/GUI/HUDComponents/TextBox.hpp>
#include <Graph/GUI/HUDComponents/Button.hpp>
#include <Objects/Map.hpp>
#include <string>
#include <cmath>

class NetworkClient;

class HUDBattle : public IHUD {
public:
    HUDBattle();
    ~HUDBattle() = default;


    void draw(sf::RenderWindow &window) override;
    void buttonClicked(sf::RenderWindow *window, NetworkClient &networkClient);

    void setText(int id, const std::string &text, bool visible);
    void setAttack(int id, const std::string &text, bool visible);
protected:

private:
    std::vector<std::shared_ptr<IComponent>> _components;
    std::vector<std::shared_ptr<IComponent>> _textsHp;
};