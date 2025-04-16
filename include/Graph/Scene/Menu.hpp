/*
** Pokemon Primal
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#pragma once

#include <Graph/Scene/IScene.hpp>

class Menu : public IScene {
public:
    Menu() = default;
    ~Menu() = default;
    void draw();
    //add information from the server into the function
    void update();
    void handleEvent();

protected:
private:
    
};

#endif /* !MENU_HPP_ */
