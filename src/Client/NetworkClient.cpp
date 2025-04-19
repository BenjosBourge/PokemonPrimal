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
    if (_udpSocket.bind(54000) != sf::Socket::Status::Done) {
        std::cout << "Cannot bind UDP socket" << std::endl;
        return;
    }
    _udpSocket.setBlocking(false);
    sf::Socket::Status status = _tcpSocket.connect(_ip, port);
    _tcpSocket.setBlocking(false);
    if (status != sf::Socket::Status::Done) {
        std::cout << "Cannot connect to the server" << std::endl;
        return;
    } else
        std::cout << "Connected to the server" << std::endl;
    _isConnected = true;
    _selector.add(_tcpSocket);
    _selector.add(_udpSocket);
}

void NetworkClient::sendPacket(std::string data)
{
     if (_isConnected) {
        sf::Packet packet;
         packet << data;
         std::cout << "Sending packet: " << packet.getData() << std::endl;
        if (_tcpSocket.send(packet) != sf::Socket::Status::Done)
            std::cout << "Error: Cannot send packet" << std::endl;
    } else
        std::cout << "Not connected to the server" << std::endl;
}

void NetworkClient::receivePacket() {
    if (!_isConnected) {
        //std::cerr << "Error: Not connected" << std::endl;
        return;
    }

    if (_selector.wait(sf::milliseconds(1))) {
        if (_selector.isReady(_tcpSocket)) {
            sf::Packet receivedData;
            sf::Socket::Status status;

            std::cout << "Packet get" << std::endl;
            do {
                status = _tcpSocket.receive(receivedData);
            } while (status == sf::Socket::Status::Partial);

            if (status == sf::Socket::Status::Done) {
                std::string data;
                receivedData >> data;
                std::cout << "Received TCP: " << data << std::endl;
            } else if (status == sf::Socket::Status::Disconnected) {
                std::cout << "Server Disconnected" << std::endl;
                _isConnected = false;
            }
        }

        if (_selector.isReady(_udpSocket)) {
            sf::Packet receivedData;
            std::optional<sf::IpAddress> sender;
            unsigned short port;

            if (_udpSocket.receive(receivedData, sender, port) == sf::Socket::Status::Done) {
                std::string data;
                receivedData >> data;
                std::cout << "Received UDP: " << data << std::endl;
            }
        }
    }
}