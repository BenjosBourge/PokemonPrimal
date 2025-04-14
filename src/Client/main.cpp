/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
*/

#include <Graph/Game.hpp>

int main(int argc, char** argv)
{
    //not currently used
    std::string assetsPath = "./assets/";
    Game game(assetsPath);
    game.run();

    return 0;
}

