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
    COM_TCP_BROADCAST,
    COM_SET_UDP
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
    NetworkEvent(int clientId, const std::string &eventType, CommunicationType communicationType)
    {
        this->eventType = eventType;
        this->communicationType = communicationType;
        this->clientId = clientId;
    }

    int entityId;
    int clientId;
    std::string eventType;
    CommunicationType communicationType;
};