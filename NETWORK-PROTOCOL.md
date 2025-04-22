# Server Protocol

The server listens on the port 53000.
It accepts connections from clients by TCP.

Client -> Server : TCP
Server -> Client : TCP and UDP

Each client listens on the port 54000 for the UDP protocol.



## Client → Server

### Movement
**Up, Do, Le, Ri**

Format: **Cmd**_State

Cmd:
- Up: Up
- Do: Down
- Ri: Right
- Le: Left

State:
- P: Pressed
- R: Released

## Server → Client

### Players Position
**Pp**

Format: **Cmd**_Id_X_Y

When getting self position, always in TCP.