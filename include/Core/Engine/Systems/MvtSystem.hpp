/*
** Pokemon Primal
** File description:
** MvtSystem
*/

#ifndef MVTSYSTEM_HPP_
#define MVTSYSTEM_HPP_
#include <Engine/Systems/ISystem.hpp>
#include <Engine/Components/Position.hpp>
#include <Maps/MapManager.hpp>

class MvtSystem : virtual public ISystem {
public:
    MvtSystem();
    ~MvtSystem();

    std::vector<NetworkEvent> update(std::shared_ptr<EntityManager>&, float deltaTime);

protected:
private:
    MapManager mapManager;
};

#endif /* !MVTSYSTEM_HPP_ */
