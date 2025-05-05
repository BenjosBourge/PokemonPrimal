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

std::string NetworkServer::receivePacket()
{
    std::string inputs = "";

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
                inputs += "P" + std::to_string(n) + "_NC" + ":";
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
                    inputs += "P" + std::to_string(i) + "_" + data + ":";
                } else if (status == sf::Socket::Status::Disconnected) {
                    std::cout << "Client " << i << " Disconnected : " << _clients[i]._ip << std::endl;
                    _clients[i]._isConnected = false;
                    _selector.remove(_clients[i]._tcpSocket);
                    _clients[i]._tcpSocket.disconnect();
                    inputs += "P" + std::to_string(i) + "_RC" + ":";
                }
            }
        }
    }
    return inputs;
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

void NetworkServer::clearTcpBuffer(int clientId)
{
    if (clientId < 0 || clientId >= 4) {
        std::cerr << "Invalid client ID" << std::endl;
        return;
    }
    if (!_clients[clientId]._isConnected) {
        std::cerr << "Client " << clientId << " is not connected" << std::endl;
        return;
    }
    _clients[clientId]._tcpBuffer.clear();
}

void NetworkServer::clearAllTcpBuffers()
{
    for (int i = 0; i < 4; ++i)
        if (_clients[i]._isConnected)
            clearTcpBuffer(i);
}

void NetworkServer::flushTcpBuffer(int clientId)
{
    if (clientId < 0 || clientId >= 4) {
        std::cerr << "Invalid client ID" << std::endl;
        return;
    }
    if (!_clients[clientId]._isConnected) {
        std::cerr << "Client " << clientId << " is not connected" << std::endl;
        return;
    }
    if (_clients[clientId]._tcpBuffer.empty())
        return;
    sendTcpPacket(_clients[clientId]._tcpBuffer, clientId);
    _clients[clientId]._tcpBuffer.clear();
}

void NetworkServer::flushAllTcpBuffers()
{
    for (int i = 0; i < 4; ++i)
        if (_clients[i]._isConnected)
            flushTcpBuffer(i);
}

void NetworkServer::addToTcpBuffer(const std::string &data, int clientId)
{
    if (clientId < 0 || clientId >= 4) {
        std::cerr << "Invalid client ID" << std::endl;
        return;
    }
    if (!_clients[clientId]._isConnected) {
        std::cerr << "Client " << clientId << " is not connected" << std::endl;
        return;
    }
    _clients[clientId]._tcpBuffer += data + ":";
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

void NetworkServer::processEngineInput(std::vector<NetworkEvent> &events)
{
    clearAllTcpBuffers();

    for (auto &event : events) {
        std::string data = event.eventType;

        if (event.communicationType == COM_UDP) {
            sendUdpPacket(event.eventType, event.clientId);
        } else if (event.communicationType == COM_TCP) {
            addToTcpBuffer(event.eventType, event.clientId);
        } else if (event.communicationType == COM_BROADCAST) {
            sendUdpPacketToAllClients(event.eventType);
        } else if (event.communicationType == COM_SECURE_BROADCAST) {
            if (event.clientId == -1)
                continue;
            for (int i = 0; i < 4; ++i) {
                if (!_clients[i]._isConnected)
                    continue;
                if (i == event.clientId)
                    addToTcpBuffer(event.eventType, i);
                else
                    sendUdpPacket(event.eventType, i);
            }
        } else if (event.communicationType == COM_TCP_BROADCAST) {
            for (int i = 0; i < 4; ++i) {
                if (!_clients[i]._isConnected)
                    continue;
                addToTcpBuffer(event.eventType, i);
            }
        }
    }

    flushAllTcpBuffers();
}