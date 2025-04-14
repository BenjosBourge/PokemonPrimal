## Client → Server

### Lobby
- **Create inf lobby**: `10`
- **Join lobby**: `12`

### Move
- **Movement haut**: `20`
- **Movement bas**: `21`
- **Movement gauche**: `22`
- **Movement droite**: `23`
- **Movement X cancel**: `24`
- **Movement Y cancel**: `25`

### Deconnexion
- **Player Deconnexion**: `40`
- **Logout**: `42`

---

## Server → Client

### Lobby
- **Join lobby**: `12 + ID`
- **Closed**: `13`

### Move
- **Move**: `20 + ID + x position + y position`

### Infos Entity (health, rect collide, size, etc.)
- **RectCollide**: `36 + ID + with + Height`

### Deconnexion
- **Player Deconnexion**: `40 + ID`

### Errors
- **Error**: `50` (only to sender)

### Game Results
- **Lose**: `68 + Score + Best Score`
- **Win**: `69 + Score + Best Score`
- **Score**: `70 + Score`
