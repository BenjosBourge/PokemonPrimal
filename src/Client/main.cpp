/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
*/

#include <filesystem>
#include <Graph/Game.hpp>
#include <SFML/Network.hpp>
#include <NetworkClient.hpp>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    //not currently used
    std::string executablePath = std::filesystem::canonical(argv[0]).parent_path().string();
    std::cout << "Executable path: " << executablePath << std::endl;
    Game game(executablePath);

    game.run();
    return 0;
}

