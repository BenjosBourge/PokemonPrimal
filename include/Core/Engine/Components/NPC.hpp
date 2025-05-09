/*
** Pokemon Primal
** File description:
** Input
*/

#pragma once
#include <Engine/Components/IComponent.hpp>
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <memory>

class IPattern {
public:
    virtual ~IPattern() = default;
    virtual sf::Vector2i move(sf::Vector2i pos) = 0;
};

class StaticPattern : public IPattern {
public:
    StaticPattern() = default;
    ~StaticPattern() = default;

    sf::Vector2i move(sf::Vector2i pos) override;
};

class LinePattern : public IPattern {
public:
    LinePattern(sf::Vector2i a, sf::Vector2i b) : a(a), b(b), index(0) {}
    ~LinePattern() = default;

    sf::Vector2i move(sf::Vector2i pos) override;

    sf::Vector2i a;
    sf::Vector2i b;
    int index;
};

class SquarePattern : public IPattern {
public:
    SquarePattern(sf::Vector2i a, sf::Vector2i b, sf::Vector2i c, sf::Vector2i d) : a(a), b(b), c(c), d(d) {}
    ~SquarePattern() = default;
    sf::Vector2i move(sf::Vector2i pos) override;

    sf::Vector2i a;
    sf::Vector2i b;
    sf::Vector2i c;
    sf::Vector2i d;
    int index = 0;
};

class RoamingPattern : public IPattern {
public:
    RoamingPattern(sf::Vector2i a, sf::Vector2i b) : a(a), b(b) {}
    ~RoamingPattern() = default;
    sf::Vector2i move(sf::Vector2i pos) override;

    sf::Vector2i a;
    sf::Vector2i b;

    sf::Vector2i target;
};


class NPC : virtual public IComponent {
public:
    NPC() {
        name = "NPC";
        pattern = std::make_shared<StaticPattern>();
    }

    NPC(std::string name, std::shared_ptr<IPattern> pattern) {
        this->name = name;
        this->pattern = pattern;
    }
    ~NPC() = default;

    std::string name;
    std::shared_ptr<IPattern> pattern;
};
