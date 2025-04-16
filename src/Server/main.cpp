/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** main.cpp
*/

#include <Engine/Engine.hpp>
#include <Server/Server.hpp>
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
    }
}


int start_engine() {
    sf::Clock clock;
    float timeElapsed = 0;
    bool isRunning = true;
    
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    engine->start();

    NetworkServer server;
    server.host(53000);

    while (isRunning) {
        float deltaTime = clock.restart().asSeconds();

        server.receivePacket();
        engine->update(deltaTime);
    }
    return 0;
}

int main(int argc, char** argv)
{
    (void)argv;
    std::cout << "Starting server..." << std::endl;
    return start_engine();
}
