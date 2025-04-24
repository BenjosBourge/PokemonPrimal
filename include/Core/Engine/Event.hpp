/*
** Pokemon Primal
** File description:
** Event
*/

#pragma once
#include <string>

enum CommunicationType {
    COM_UDP,
    COM_TCP,
    COM_BROADCAST,
    COM_SECURE_BROADCAST,
};

/*
 * COM_UDP: All clients receive in UDP
 * COM_TCP: All clients receive in TCP
 * COM_BROADCAST: All clients receive in UDP.
 * COM_SECURE_BROADCAST: All clients receive in UDP or in TCP if being the concerned entity.
 */

class NetworkEvent {
public:
    NetworkEvent() {}
    ~NetworkEvent() {}
    NetworkEvent(int entityId, const std::string &eventType, CommunicationType communicationType)
    {
        this->entityId = entityId;
        this->eventType = eventType;
        this->communicationType = communicationType;
        clientId = -1;
    }

    int entityId;
    int clientId;
    std::string eventType;
    CommunicationType communicationType;
};