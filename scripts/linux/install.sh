#!/bin/bash

sudo apt-get update

sudo apt-get install -y ninja-build libudev-dev libxrandr-dev libxcursor-dev libfreetype6-dev libopenal-dev libvorbis-dev libflac-dev libgl1-mesa-dev bc graphviz doxygen

if command -v cmake > /dev/null 2>&1; then
    installed_version=$(cmake --version | grep version | awk '{print $3}')
    major_version=$(echo $installed_version | cut -d'.' -f1)
    minor_version=$(echo $installed_version | cut -d'.' -f2)

    if [[ $major_version -eq 3 && $minor_version -ge 22 ]]; then
        echo "CMake $installed_version is already installed."
    else
        echo "Updating CMake to version 3.22 or higher..."

        sudo apt-get remove --purge cmake -y

        wget https://cmake.org/files/v3.22/cmake-3.22.0-linux-x86_64.sh

        chmod +x cmake-3.22.0-linux-x86_64.sh

        sudo bash cmake-3.22.0-linux-x86_64.sh --skip-license --prefix=/usr/local

        rm cmake-3.22.0-linux-x86_64.sh

        echo "CMake 3.22 or higher installed successfully."
    fi
else
    echo "Installing CMake version 3.22..."

    wget https://cmake.org/files/v3.22/cmake-3.22.0-linux-x86_64.sh

    chmod +x cmake-3.22.0-linux-x86_64.sh

    sudo bash cmake-3.22.0-linux-x86_64.sh --skip-license --prefix=/usr/local

    rm cmake-3.22.0-linux-x86_64.sh

    echo "CMake 3.22 installed successfully."
fi

sudo snap install --edge just --classic

mkdir -p $HOME/bin

curl --proto '=https' --tlsv1.2 -sSf https://just.systems/install.sh | bash -s -- --to $HOME/bin

export PATH="$PATH:$HOME/bin"

just --help



sudo apt install gcovr -y


echo "Installation complete."
