#!/bin/bash

# Mise à jour des packages
brew update

# Installer les dépendances nécessaires
brew install flac ninja freetype libvorbis

# Vérifier et afficher le statut d'installation pour CMake
if command -v cmake > /dev/null 2>&1; then
    installed_version=$(cmake --version | grep version | awk '{print $3}')
    major_version=$(echo $installed_version | cut -d'.' -f1)
    minor_version=$(echo $installed_version | cut -d'.' -f2)

    if [[ $major_version -eq 3 && $minor_version -ge 22 ]]; then
        echo "CMake $installed_version is already installed."
    else
        echo "Updating CMake to version 3.22 or higher..."
        # Supprimer la version existante de CMake si elle ne correspond pas à la version souhaitée
        brew uninstall cmake
        # Installer CMake version 3.22 avec Homebrew
        brew install cmake@3.22
        echo "CMake 3.22 or higher installed successfully."
    fi
else
    echo "Installing CMake version 3.22..."
    # Installer CMake version 3.22 avec Homebrew
    brew install cmake@3.22
    echo "CMake 3.22 installed successfully."
fi

brew install just gcovr graphviz doxygen

echo "Installation complete."
