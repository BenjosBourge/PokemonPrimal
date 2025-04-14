# Pokemon Primal

## Install

#### Linux
```bash
./scripts/linux/install.sh
```

#### Windows
```bash
./scripts/windows/install.bat
```

## Build

#### Linux
```bash
./scripts/linux/build.sh
```

#### Windows
```bash
./scripts/windows/install.bat
```

## Server binary
```bash
./build/r-type_server
```

## Client binary
```bash
./build/r-type_client
```


Sure! Here's a markdown-formatted architecture description for the project structure you've provided:

---

# 🏗️ Project Architecture Overview

This document outlines the architecture and directory structure of the project.

## 📁 Root Directory

- **`CMakeLists.txt`**: Top-level CMake configuration for building the entire project.
- **`justfile`**: Command automation using `just`, a handy alternative to `make`.
- **`LICENSE`**: License file for the project.
- **`README.md`**: Project overview, setup instructions, and documentation.
- **`SERVER-PROTOCAL.md`**: Documentation for the server communication protocol.

---

## 📁 include/

This directory contains all the public headers organized by module. It defines the interface for the core components of the application.

### ▶️ Client/
- **`Client.hpp`**: Interface and logic for the client application.

### 🧠 Engine/

#### 🔌 Components/
- **`IComponent.hpp`**: Abstract base class for components in the ECS (Entity-Component-System) architecture.
- **`Position.hpp`**: Position component representing spatial data.

#### 🏗️ Entities/
- **`Entity.hpp`**: Basic entity class.
- **`EntityManager.hpp`**: Manages creation, destruction, and querying of entities.
- **`EntityFactory.hpp`**: Factory pattern for creating predefined entity types.

#### ⚙️ Systems/
- **`ISystem.hpp`**: Abstract base class for all systems.
- **`MvtSystem.hpp`**: Handles entity movement logic.

#### 🧠 Engine.hpp
- Central header that ties together engine subsystems.

### 🎮 Graph/
- **`Game.hpp`**: High-level game loop and rendering logic.

### 🌐 Server/
- **`Server.hpp`**: Server-side application interface and core logic.

---

## 📁 src/

Contains the actual implementations corresponding to the headers in `include/`.

### ▶️ Client/
- **`main.cpp`**: Entry point for the client application.

### 🧼 CtrlC/
- **`CtrlC.cpp`**: Handles graceful shutdowns (e.g., SIGINT).
- **`CMakeLists.txt`**: CMake config specific to CtrlC handling.

### 🧠 Engine/
- **`Engine.cpp`**: Engine initialization and management logic.

#### 🏗️ Entities/
- Implementation files for Entity, EntityFactory, and EntityManager.

#### ⚙️ Systems/
- **`MvtSystem.cpp`**: Implements movement system logic.

### 🎮 Graph/
- **`Game.cpp`**: Implements the game loop and graphical interface.
- **`CMakeLists.txt`**: Build configuration for the Graph module.

### 🌐 Server/
- **`main.cpp`**: Entry point for the server application.

---

## 📁 scripts/

Build and install scripts for different operating systems.

### 🐧 linux/
- **`build.sh`**: Linux build script.
- **`install.sh`**: Linux installation script.
- **`build/`**: Temporary or output directory for Linux builds.

### 🪟 windows/
- **`build.bat`**: Windows build script.
- **`install.bat`**: Windows installation script.

---

# 🧩 Design Highlights

- **ECS Architecture**: The `Engine` module is structured using Entity-Component-System principles for scalability and flexibility.
- **Client-Server Model**: Separated client and server logic to allow for networked or multiplayer applications.
- **Modular Design**: Each subsystem is encapsulated in its own directory for clarity and maintainability.

---

Let me know if you want a visual diagram too or want to expand on specific parts like the ECS!