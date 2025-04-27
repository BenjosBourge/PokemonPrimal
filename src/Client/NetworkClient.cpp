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

    int availablePort = port;
    while (availablePort < 65535) {
        if (_tcpSocket.connect(_ip, availablePort) == sf::Socket::Status::Done)
            break;
        availablePort++;
    }
    _tcpSocket.setBlocking(false);
    _isConnected = true;
    _selector.add(_tcpSocket);

    int portUdp = availablePort + 1;
    while (portUdp < 65535) {
        if (_udpSocket.bind(portUdp) == sf::Socket::Status::Done)
            break;
        portUdp++;
    }
    _udpSocket.setBlocking(false);
    _selector.add(_udpSocket);

    std::cout << "Connected to server." << std::endl;
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

std::string NetworkClient::receivePacket() {
    if (!_isConnected)
        return {};

    std::string inputs = "";

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
                inputs += data + ":";
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
                inputs += data + ":";
            }
        }
    }
    return inputs;
}