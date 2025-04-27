/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Game
*/

#include <SFML/Graphics.hpp>
#include <Game.hpp>

void Game::processToken(const std::string &token)
{
    std::string command = token.substr(0, token.find('_'));
    std::vector<std::string> args;

    // getting arguments to command
    std::string arg = token.substr(token.find('_') + 1);
    std::stringstream ss(arg);
    std::string tmp;
    while (std::getline(ss, tmp, '_'))
        args.push_back(tmp);

    std::cout << "Command: " << command << " Args: " << args.size() << std::endl;
}

void Game::parseClientInput(const std::string &input)
{
    if (input.empty())
        return;
    std::stringstream ss(input);
    std::string tmp;

    while (std::getline(ss, tmp, ':'))
        processToken(tmp);
}