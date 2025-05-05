/*
** Pokemon Primal
** File description:
** NetworkServer
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
    std::string _tcpBuffer;
};

class NetworkServer {
public:
    NetworkServer();
    ~NetworkServer();

    void host(int port);
    std::string receivePacket();

    void sendTcpPacketToAllClients(const std::string &data);
    void sendUdpPacketToAllClients(const std::string &data);
    void clearTcpBuffer(int clientId);
    void clearAllTcpBuffers();
    void flushTcpBuffer(int clientId);
    void flushAllTcpBuffers();
    void addToTcpBuffer(const std::string &data, int clientId);

    void sendTcpPacket(const std::string &data, int clientId);
    void sendUdpPacket(const std::string &data, int clientId);

    /* Send info to clients depending on the events from the engine */
    void processEngineInput(std::vector<NetworkEvent> &events);

    sf::TcpSocket _socket;
    bool _isConnected;
    sf::SocketSelector _selector;
    sf::TcpListener _listener;
    sf::UdpSocket _udpSocket;
    ClientConnection _clients[4];
};