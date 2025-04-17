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

ClientConnection::ClientConnection()
{
    _isConnected = false;
}

ClientConnection::~ClientConnection()
{
    _socket.disconnect();
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
}

void NetworkServer::receivePacket()
{
    if (_selector.wait(sf::milliseconds(10))) {
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
            else if (_listener.accept(_clients[n]._socket) == sf::Socket::Status::Done) {
                std::cout << "Client connected : " << _clients[n]._socket.getRemoteAddress()->toString() << std::endl;
                _clients[n]._ip = _clients[n]._socket.getRemoteAddress()->toString();
                _clients[n]._port = _clients[n]._socket.getRemotePort();
                _clients[n]._isConnected = true;
                _selector.add(_clients[n]._socket);
            }
        }

        for (int i = 0; i < 4; i++) {
            if (_clients[i]._isConnected && _selector.isReady(_clients[i]._socket)) {
                sf::Packet receivedData;
                sf::Socket::Status status;

                do {
                    status = _clients[i]._socket.receive(receivedData);
                } while (status == sf::Socket::Status::Partial);

                if (status == sf::Socket::Status::Done) {
                    std::cout << "Data: " << receivedData.getData() << std::endl;
                    std::string data;
                    receivedData >> data;
                    std::cout << "Received data from client " << i << ": " << data << std::endl;
                } else if (status == sf::Socket::Status::Disconnected) {
                    std::cout << "Client " << i << " Disconnected : " << _clients[i]._ip << std::endl;
                    _clients[i]._isConnected = false;
                    _selector.remove(_clients[i]._socket);
                }
            }
        }
    }
}
