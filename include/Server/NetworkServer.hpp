/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** Server.hpp
*/

#pragma once

#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class ClientConnection {
public:
    ClientConnection();
    ~ClientConnection();

    sf::TcpSocket _socket;
    std::string _ip;
    unsigned short _port;
    bool _isConnected;
};

class NetworkServer {
public:
    NetworkServer();
    ~NetworkServer();

    void host(int port);
    void receivePacket();

    sf::TcpSocket _socket;
    bool _isConnected;
    sf::SocketSelector _selector;
    sf::TcpListener _listener;
    ClientConnection _clients[4];
};