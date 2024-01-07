#pragma once
#include "raylib.h"
#include "MainMenu.h"
#include "RegisterMenu.h"
#include "LoginMenu.h"

class BankSimulation {
public:
    BankSimulation();
    void Run();

private:
    MainMenu mainMenu;
    RegisterMenu registerMenu;
    LoginMenu loginMenu;
    bool isLoggedIn;
};