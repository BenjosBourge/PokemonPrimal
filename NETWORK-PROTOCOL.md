# Server Protocol

The server listens on the port 53000.
It accepts connections from clients by TCP.

Client -> Server : TCP
Server -> Client : TCP and UDP

Each client listens on the port 54000 for the UDP protocol.



## Client → Server

### Movement
Direction_State

Direction:
- Up: Up
- Do: Down
- Ri: Right
- Le: Left

State:
- P: Pressed
- R: Released

## Server → Client

### Players Position
**02** byte(0x00..0x03) : int : int ...

First byte: Player ID (0 being self)

X position

Y position
