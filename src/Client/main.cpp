/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
*/

#include <Graph/Game.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    //not currently used
    std::string assetsPath = "./assets/";
    Game game(assetsPath);

    sf::TcpSocket socket;
    sf::IpAddress ip(127, 0, 0, 1);
    sf::Socket::Status status = socket.connect(ip, 53000);
    if (status != sf::Socket::Status::Done) {
        std::cout << "Cannot connect to the server" << std::endl;
        return 1;
    } else
        std::cout << "Connected to the server" << std::endl;

    game.run();

    return 0;
}

