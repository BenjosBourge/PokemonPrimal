/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
*/

#include <GUI/Game.hpp>
#include <string>
#include <filesystem>

int main(int argc, char** argv)
{
    //not currently used
    std::string executablePath = std::filesystem::canonical(argv[0]).parent_path().string();
    std::cout << "Executable path: " << executablePath << std::endl;
    Game game(executablePath);

    game.run();
    return 0;
}

