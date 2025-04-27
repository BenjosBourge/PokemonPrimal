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

std::string NetworkServer::parseData(const std::string &data, int clientId)
{
    std::string inputs = "";

    if (data == "Up_P")
        inputs += "Up_P_P" + std::to_string(clientId) + ":";
    else if (data == "Up_R")
        inputs += "Up_R_P" + std::to_string(clientId) + ":";
    else if (data == "Do_P")
        inputs += "Do_P_P" + std::to_string(clientId) + ":";
    else if (data == "Do_R")
        inputs += "Do_R_P" + std::to_string(clientId) + ":";
    else if (data == "Ri_P")
        inputs += "Ri_P_P" + std::to_string(clientId) + ":";
    else if (data == "Ri_R")
        inputs += "Ri_R_P" + std::to_string(clientId) + ":";
    else if (data == "Le_P")
        inputs += "Le_P_P" + std::to_string(clientId) + ":";
    else if (data == "Le_R")
        inputs += "Le_R_P" + std::to_string(clientId) + ":";

    return inputs;
}