/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** CtrlC
*/

#include <CtrlC/CtrlC.hpp>

bool CtrlC::ctrlCPressed = false;

CtrlC::CtrlC()
{
}

CtrlC::~CtrlC()
{
}

bool CtrlC::checkCtrlCPressed() {
    #ifdef _WIN32
        return CheckCtrlCWindows();
    #else
        return CheckCtrlCUnix();
    #endif
}

#ifdef _WIN32

    bool CtrlC::CheckCtrlCWindows() {
        return (SetConsoleCtrlHandler(ConsoleHandler, TRUE) == TRUE);
    }

#else

    bool CtrlC::CheckCtrlCUnix() {
        if (signal(SIGINT, ctrlCHandler) == SIG_ERR) {
            return false;
        }
        return true;
    }

#endif
