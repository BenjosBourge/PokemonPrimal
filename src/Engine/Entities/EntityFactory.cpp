/*
** Pokemon Primal
** File description:
** EntityFactory
*/

#include <Engine/Entities/EntityFactory.hpp>
#include <Pokemon/Pokemon.hpp>

#if defined(_WIN32) || defined(_WIN64)
    #pragma warning(disable: 4244)
#endif

EntityFactory::EntityFactory(void)
{
}

EntityFactory::~EntityFactory() { }

Entity& EntityFactory::createEntity(std::string name) {
    auto *entity = new Entity();

    if (name == "Player") {
        entity->createComponent<Position>(1, 1);
        entity->createComponent<Input>();
        entity->createComponent<Player>();
        entity->createComponent<Trainer>();
        entity->getComponent<Trainer>()._pokemons[0] = getPokemonFromId(CHARMANDER);
    } else if (name == "NPC") {
        entity->createComponent<Position>(1, 1);
        entity->createComponent<NPC>();
    } else if (name == "DemoTrainer") {
        entity->createComponent<Trainer>();
        entity->getComponent<Trainer>()._pokemons[0] = getPokemonFromId(BULBASAUR);
    } else {
    std::cout << "Entity " << name << " not found" << std::endl;
    }   

    return *entity;
}

#if defined(_WIN32) || defined(_WIN64)
    #pragma warning(default: 4244)
#endif
