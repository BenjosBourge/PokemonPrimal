/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** main.cpp
*/

#include <Error/Error.hpp>
#include <Engine/Engine.hpp>
#include <Server/Server.hpp>
#include <SFML/System/Clock.hpp>


int start_engine() {
    sf::Clock clock;
    float timeElapsed = 0;
    bool isRunning = true;
    
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();
    engine->start();

    while (isRunning) {
        float deltaTime = clock.restart().asSeconds();
        timeElapsed += deltaTime;

        if (timeElapsed >= 1.0f) {
            std::cout << "Updating engine..." << std::endl;
            engine->update(timeElapsed);
            timeElapsed = 0;
        }
    }
    return 0;
}

int main(int argc, char** argv)
{
    (void)argv;
    return start_engine();
 

}
