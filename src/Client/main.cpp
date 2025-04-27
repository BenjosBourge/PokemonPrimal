/*
** Pokemon Primal
** File description:
** main Client
*/

#include <filesystem>
#include <Game.hpp>
#include <SFML/Network.hpp>
#include <NetworkClient.hpp>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    Game game;

    game.run();
    return 0;
}

