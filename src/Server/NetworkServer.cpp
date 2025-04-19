/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** main.cpp
*/

#include <Engine/Engine.hpp>
#include <Server.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Network.hpp>

ClientConnection::ClientConnection() : _ip(sf::IpAddress::Any)
{
    _isConnected = false;
}

ClientConnection::~ClientConnection()
{
    _tcpSocket.disconnect();
}

NetworkServer::NetworkServer()
{
    _isConnected = false;
}

NetworkServer::~NetworkServer()
{

}

void NetworkServer::host(int port)
{
    if (_listener.listen(port) != sf::Socket::Status::Done) {
        std::cerr << "Error: Cannot listen on port " << port << std::endl;
        return;
    }
    _selector.add(_listener);
    if (_udpSocket.bind(port) != sf::Socket::Status::Done) {
        std::cerr << "Error: Cannot bind UDP socket to port " << port + 1 << std::endl;
        return;
    }
    _udpSocket.setBlocking(false);
    //_selector.add(_udpSocket);
}


/* Receiving Packets */

void NetworkServer::receivePacket() {
    if (_selector.wait(sf::milliseconds(1))) {
        if (_selector.isReady(_listener)) {
            std::size_t n = 4;
            for (std::size_t i = 0; i < 4; ++i) {
                if (!_clients[i]._isConnected) {
                    n = i;
                    break;
                }
            }
            if (n >= 4)
                std::cerr << "Too many clients" << std::endl;
            else if (_listener.accept(_clients[n]._tcpSocket) == sf::Socket::Status::Done) {
                std::cout << "Client connected : " << _clients[n]._tcpSocket.getRemoteAddress()->toString()
                          << std::endl;
                _clients[n]._ip = _clients[n]._tcpSocket.getRemoteAddress().value();
                _clients[n]._port = _clients[n]._tcpSocket.getRemotePort();
                _clients[n]._isConnected = true;
                _selector.add(_clients[n]._tcpSocket);
            }
        }

        for (int i = 0; i < 4; i++) {
            if (_clients[i]._isConnected && _selector.isReady(_clients[i]._tcpSocket)) {
                sf::Packet receivedData;
                sf::Socket::Status status;

                do {
                    status = _clients[i]._tcpSocket.receive(receivedData);
                } while (status == sf::Socket::Status::Partial);

                if (status == sf::Socket::Status::Done) {
                    std::string data;
                    receivedData >> data;
                    std::cout << "Received data from client " << i << ": " << data << std::endl;
                } else if (status == sf::Socket::Status::Disconnected) {
                    std::cout << "Client " << i << " Disconnected : " << _clients[i]._ip << std::endl;
                    _clients[i]._isConnected = false;
                    _selector.remove(_clients[i]._tcpSocket);
                }
            }
        }
    }
}


/* Sending Packets */

void NetworkServer::sendTcpPacketToAllClients(const std::string &data)
{
    for (int i = 0; i < 4; ++i)
        if (_clients[i]._isConnected)
            sendTcpPacket(data, i);
}

void NetworkServer::sendUdpPacketToAllClients(const std::string &data)
{
    for (int i = 0; i < 4; ++i)
        if (_clients[i]._isConnected)
            sendUdpPacket(data, i);
}

void NetworkServer::sendTcpPacket(const std::string &data, int clientId)
{
    if (clientId < 0 || clientId >= 4) {
        std::cerr << "Invalid client ID" << std::endl;
        return;
    }
    if (!_clients[clientId]._isConnected) {
        std::cerr << "Client " << clientId << " is not connected" << std::endl;
        return;
    }

    sf::Packet packet;
    packet << data;
    if (_clients[clientId]._tcpSocket.send(packet) != sf::Socket::Status::Done) {
        std::cerr << "Failed to send TCP packet" << std::endl;
    }
}

void NetworkServer::sendUdpPacket(const std::string &data, int clientId)
{
    if (clientId < 0 || clientId >= 4) {
        std::cerr << "Invalid client ID" << std::endl;
        return;
    }
    if (!_clients[clientId]._isConnected) {
        std::cerr << "Client " << clientId << " is not connected" << std::endl;
        return;
    }

    sf::Packet packet;
    packet << data;
    if (_udpSocket.send(packet, _clients[clientId]._ip, 54000) != sf::Socket::Status::Done) {
        std::cerr << "Failed to send UDP packet" << std::endl;
    }
}
