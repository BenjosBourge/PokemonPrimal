/*
** Pokemon Primal
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

class IScene {
public:
    IScene() = default;
    ~IScene() = default;
    virtual void draw(sf::RenderWindow &window) = 0;
protected:
private:
    
};

#endif /* !ISCENE_HPP_ */
