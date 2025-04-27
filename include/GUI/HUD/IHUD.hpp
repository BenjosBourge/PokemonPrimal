/*
** Pokemon Primal
** File description:
** IHUD
*/

#ifndef IHUD_HPP_
#define IHUD_HPP_

#pragma once

#include <array>
#include <memory>
#include <SFML/Graphics.hpp>
#include <string>

class IHUD {
    public:
        IHUD() = default;
        virtual ~IHUD() = default;

        virtual void draw(sf::RenderWindow &window) = 0;

    protected:
        std::string assets;

    private:
};


#endif /* !IHUD_HPP_ */
