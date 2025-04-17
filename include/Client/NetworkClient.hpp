/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
*/

#pragma once
#include <string>
#include <SFML/Network.hpp>
#include <iostream>

class NetworkClient {
public:
    NetworkClient();
    ~NetworkClient();

    void connect(std::string ip, unsigned int port);
    void sendPacket(std::string data);

    bool _isConnected;
    sf::TcpSocket _socket;
    sf::IpAddress _ip;
    unsigned short _port;
};
