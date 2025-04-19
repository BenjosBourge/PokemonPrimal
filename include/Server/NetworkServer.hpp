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

    sf::TcpSocket _tcpSocket;
    sf::IpAddress _ip;
    unsigned short _port;
    bool _isConnected;
};

class NetworkServer {
public:
    NetworkServer();
    ~NetworkServer();

    void host(int port);
    void receivePacket();

    void sendTcpPacketToAllClients(const std::string &data);
    void sendUdpPacketToAllClients(const std::string &data);

    void sendTcpPacket(const std::string &data, int clientId);
    void sendUdpPacket(const std::string &data, int clientId);

    sf::TcpSocket _socket;
    bool _isConnected;
    sf::SocketSelector _selector;
    sf::TcpListener _listener;
    sf::UdpSocket _udpSocket;
    ClientConnection _clients[4];
};