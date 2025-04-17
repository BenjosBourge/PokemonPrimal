/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
*/

#include <NetworkClient.hpp>

NetworkClient::NetworkClient() : _ip(sf::IpAddress::Any) {
    _isConnected = false;
    _port = 0;
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::connect(std::string ip, unsigned int port)
{
    _ip = sf::IpAddress::resolve(ip).value();
    _port = port;
    sf::Socket::Status status = _socket.connect(_ip, port);
    if (status != sf::Socket::Status::Done) {
        std::cout << "Cannot connect to the server" << std::endl;
        return;
    } else
        std::cout << "Connected to the server" << std::endl;
    _isConnected = true;
}

void NetworkClient::sendPacket(std::string data)
{
     if (_isConnected) {
        sf::Packet packet;
         packet << data;
         std::cout << "Sending packet: " << packet.getData() << std::endl;
        if (_socket.send(packet) != sf::Socket::Status::Done)
            std::cout << "Error: Cannot send packet" << std::endl;
    } else
        std::cout << "Not connected to the server" << std::endl;
}