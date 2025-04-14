@echo off

:: Vérifier si l'exécution est en mode administrateur
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
if %errorlevel% neq 0 (
    echo Vous devez exécuter ce script en tant qu'administrateur.
    goto :eof
) else (
    echo Installation en cours...
)

setlocal enabledelayedexpansion

rem Vérifier si Chocolatey est déjà installé
where choco > nul 2>&1
if %errorlevel% neq 0 (
    echo Installing Chocolatey...

    rem Télécharger le fichier MSI
    curl -L https://github.com/chocolatey/choco/releases/download/2.2.2/chocolatey-2.2.2.0.msi -o chocolatey-2.2.2.0.msi

    rem Installer Chocolatey
    msiexec /i chocolatey-2.2.2.0.msi /quiet /qn /norestart

    rem Supprimer les fichiers d'installation inutiles de Chocolatey
    del chocolatey-2.2.2.0.msi

    rem Ajouter Chocolatey au PATH
    setx PATH "%PATH%;C:\ProgramData\chocolatey\bin"

) else (
    rem Obtenir et afficher la version actuelle de Chocolatey
    set "message=Chocolatey is already installed with version"
    set "version="
    for /f "tokens=*" %%a in ('choco --version') do set version=!version! %%a

    echo !message!!version!
)

endlocal

rem Vérifier et afficher le statut d'installation pour CMake
cmake --version >nul 2>nul
if %errorlevel% neq 0 (
    echo Installing CMake...
    choco install cmake --version=3.27.9 --force --confirm

    rem Vérifier si l'installation s'est bien déroulée
    cmake --version >nul 2>nul
    if %errorlevel% neq 0 (
        echo CMake 3.27.9 installation failed.
    ) else (
        for /f "tokens=*" %%v in ('cmake --version ^| findstr version') do echo CMake %%v installed successfully.
    )
) else (
    for /f "tokens=*" %%v in ('cmake --version ^| findstr version') do echo CMake %%v is already installed.
)

rem Vérifier et afficher le statut d'installation pour Visual Studio Build Tools
vswhere.exe -latest -products '*' -requires Microsoft.Component.MSBuild >nul 2>nul
if %errorlevel% neq 0 (
    echo Installing Visual Studio Build Tools...
    choco install visualstudio2019buildtools --package-parameters "--add Microsoft.VisualStudio.Component.VC.Tools.x86.x64" --force --confirm

    setx PATH "%PATH%;C:\Program Files (x86)\Microsoft Visual Studio\Installer"

    rem Vérifier si l'installation s'est bien déroulée
    vswhere.exe -latest -products '*' -requires Microsoft.Component.MSBuild >nul 2>nul
    if %errorlevel% neq 0 (
        echo Visual Studio Build Tools installation failed.
    ) else (
        echo Visual Studio Build Tools installed successfully.
    )
) else (
    echo Visual Studio Build Tools is already installed.
)

rem Vérifier et afficher le statut d'installation pour doxygen
doxygen --version
if %errorlevel% neq 0 (
    echo Installing doxygen...
    choco install doxygen.install --force --confirm

    setx PATH "%PATH%;C:\Program Files\doxygen\bin"

    rem Vérifier si l'installation s'est bien déroulée
    doxygen --version
    if %errorlevel% neq 0 (
        echo doxygen installation failed.
    ) else (
        echo doxygen installed successfully.
    )
) else (
    echo doxygen is already installed.
)

rem Vérifier et afficher le statut d'installation pour graphviz
set "graphvizExecutable=C:\Program Files\Graphviz\bin\dot.exe"

rem Vérifier si Graphviz est déjà installé
if not exist "%graphvizExecutable%" (
    echo Installing graphviz...
    choco install graphviz --force --confirm

    setx PATH "%PATH%;C:\Program Files\Graphviz\bin"

    set "graphvizExecutable=C:\Program Files\Graphviz\bin\dot.exe"
    rem Vérifier si l'installation s'est bien déroulée
    C:\Program Files\Graphviz\bin\dot.exe
    if not exist "%graphvizExecutable%" (
        echo graphviz installation failed.
    ) else (
        echo graphviz installed successfully.
    )
) else (
    echo graphviz is already installed.
)

pause
