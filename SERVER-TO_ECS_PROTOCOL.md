# Server To ECS Protocol

The Server and the ECS communicate with string. The server function 
receivePacket() returns a string, and the ECS parse it to get updates on client inputs or events.

## IDs

**Pn** :Player ID (n is the id of the player, ex: P1, P2...)

## Connected Entities
The EntityManager store a vector of connections. Connections are pairs
of tag (string) and id (int).

## New Player
**NC**_id

## Movements
**Up, Do, Le, Ri**
**Cmd**_State_clientId

