@echo off

rem Vérifier le dossier de lancement
if not "%cd:~-39%"=="B-CPP-500-LYN-5-2-rtype-erwann.laplante" (
    echo Lancer depuis l'explorateur de fichiers. Changement de répertoire.
    cd ../..
) else (
    echo Lancer en ligne de commande. Aucun changement de répertoire.
)

echo Lancement dans %cd%

rem Vérifier les argument
if not "%1"=="" (
    if "%1"=="build" (
        call :build
    ) else if "%1"=="pkg" (
        call :pkg
    ) else if "%1"=="rebuild" (
        call :rebuild
    ) else if "%1"=="doc" (
        call :doc
    ) else (
        call :usage
    )
    goto :finish
)

set /p action="What action do you whant to do? (build, rebuild [developper only], pkg or usage):"
set action=%action: =%

rem Exécuter l'action demandée
if "%action%"=="build" (
    call :build
) else if "%action%"=="pkg" (
    call :pkg
) else if "%action%"=="rebuild" (
    call :rebuild
) else if "%action%"=="doc" (
    call :doc
) else (
    call :usage
)

goto :finish



rem Fonction de construction du projet
:build
echo [INFO]: Building project.

rem Supprimer le répertoire build s'il existe déjà
rmdir /s /q build

rem Créer le répertoire build et s'y déplacer
mkdir build && cd build

rem Générer le fichier de solution avec CMake pour Visual Studio
cmake -G "Visual Studio 17 2022" ..

rem Construire le projet avec Visual Studio
cmake --build .
goto :eof



rem Fonction de re construction du projet
:rebuild
if not exist "build" (
    echo [INFO]: Not already build
    goto :build
) else (
    echo [INFO]: Re-Building project.

    rem Supprimer le répertoire build s'il existe déjà
    cd build

    rem Construire le projet avec Visual Studio
    cmake --build .
)
goto :eof



rem Fonction de re construction du projet
:doc
doxygen Doxyfile
goto :eof



:pkg
    if not exist "build" (
        call :build
    )

    cd build/

    mkdir R-Type-0.1.1-Windows
    copy ".\" "R-Type-0.1.1-Windows\"

    cd R-Type-0.1.1-Windows/
    mkdir assets/
    xcopy /s /e /y "..\..\src\Client\assets\" "assets\"
    xcopy /s /e /y "..\..\src\Engine\*.json" "config\src\Engine\"
    xcopy /s /e /y "..\..\src\Graph\*.json" "config\src\Graph\"
    xcopy /s /e /y "..\..\src\Server\scores\*.txt" "src\Server\scores\"
    xcopy /s /e /y "..\..\src\Server\scores\*.txt" "src\Server\scores\"
    cd ..

    powershell Compress-Archive -Path "R-Type-0.1.1-Windows" -DestinationPath "R-Type-0.1.1-Windows.zip" -Force
)
goto :eof



rem Fonction d'affichage de l'utilisation
:usage
echo Usage of windows build:
echo When ask for action, action can be:
echo    build       Build the whole project using cmake and Visual Studio.
echo    rebuild     Re-Build the whole project using cmake.
echo    pkg         Package the project into a .zip file.
echo    doc         Launch documentation generation.
echo    usage       Print this usage.
goto :eof



rem Fonction d'affichage de l'utilisation
:finish
echo [92m
echo ====================================================================================================
echo c'est finit
echo ====================================================================================================
echo [0m

pause
goto :eof
