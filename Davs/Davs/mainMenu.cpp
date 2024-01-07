#include "MainMenu.h"

MainMenu::MainMenu() : isActive(true), registerButton{ (float)GetScreenWidth() / 2 - 100, 200, 200, 50 },
loginButton{ (float)GetScreenWidth() / 2 - 100, 260, 200, 50 },
exitButton{ (float)GetScreenWidth() / 2 - 100, 320, 200, 50 } {}

void MainMenu::Draw() {
    DrawText("Davs Bank", GetScreenWidth() / 2 - MeasureText("Davs Bank", 40) / 2, 100, 40, BLACK);
    DrawRectangle(GetScreenWidth() / 2 - 100, 200, 200, 50, LIGHTGRAY);
    DrawRectangle(GetScreenWidth() / 2 - 100, 260, 200, 50, LIGHTGRAY);
    DrawRectangle(GetScreenWidth() / 2 - 100, 320, 200, 50, LIGHTGRAY);
    DrawText("Register", GetScreenWidth() / 2 - MeasureText("Register", 20) / 2, 210, 20, BLACK);
    DrawText("Login", GetScreenWidth() / 2 - MeasureText("Login", 20) / 2, 270, 20, BLACK);
    DrawText("Exit", GetScreenWidth() / 2 - MeasureText("Exit", 20) / 2, 330, 20, BLACK);
}

bool MainMenu::CheckRegisterPressed() const {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), registerButton);
}

bool MainMenu::CheckLoginPressed() const {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), loginButton);
}

bool MainMenu::CheckExitPressed() const {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), exitButton);
}