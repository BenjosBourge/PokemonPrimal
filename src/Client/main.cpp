/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
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

