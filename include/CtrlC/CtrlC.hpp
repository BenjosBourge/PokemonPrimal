/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** CtrlC
*/

#pragma once

#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <csignal>
#endif

/*
 * This class is used to handle Ctrl+C events for Windows and Unix systems.
 *
 * This class for handling Ctrl+C events and setting a flag when pressed.
*/
class CtrlC {
    public:
        CtrlC();
        ~CtrlC();

        bool checkCtrlCPressed();

        static bool ctrlCPressed;

    private:
        #ifdef _WIN32
            static BOOL WINAPI ConsoleHandler(DWORD dwCtrlType) {
                switch (dwCtrlType) {
                    case CTRL_C_EVENT:
                        std::cout << "Ctrl+C captured. Cleaning up and exiting..." << std::endl;
                        ctrlCPressed = true;
                        return TRUE;

                    default:
                        return FALSE;
                }
            }

            bool CheckCtrlCWindows();

        #else
            static void ctrlCHandler(int signum) {
                std::cout << "Ctrl+C captured. Cleaning up and exiting..." << std::endl;
                ctrlCPressed = 1;
                signal(signum, SIG_DFL);
            }

            bool CheckCtrlCUnix();
        #endif

    protected:
};
