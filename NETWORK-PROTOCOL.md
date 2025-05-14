# Server Protocol

The server listens on the port 53000.
It accepts connections from clients by TCP.

Client -> Server : TCP
Server -> Client : TCP and UDP

Each client listens on the port 54000 for the UDP protocol.



## Client → Server

### UDP Port
**UDP**

Format: **Cmd**_Port

### Movement
**Up, Do, Le, Ri, Sp**

Format: **Cmd**_State

Cmd:
- Up: Up
- Do: Down
- Ri: Right
- Le: Left
- Sp: Space

State:
- P: Pressed
- R: Released

### Button CLicked
**Btn**
Format: **Cmd**_Id



## Server → Client

### PlayerCharacter Created
**Pc**

Format: **Cmd**_Id


### PlayerCharacter Disconnected
**Pd**

Format: **Cmd**_Id


### Players Position
**Pp**

Format: **Cmd**_Id_X_Y

When getting self position, always in TCP.


### Players Inputs Released
**Pir**

Format: **Cmd**_Id

To know when a character stop moving.


### Change State
**Cs**

Format: **Cmd**_IdState

IdState:
- 0: Overworld
- 1: Battle