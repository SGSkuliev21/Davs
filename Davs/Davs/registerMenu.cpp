#include "RegisterMenu.h"

RegisterMenu::RegisterMenu() : isActive(false), returnButton({ 50, 400, 100, 50 }) {}

void RegisterMenu::Draw() {
    DrawText("Register", 50, 50, 30, BLACK);
    DrawText("Username:", 60, 150, 20, BLACK);
    DrawText(usernameInput.c_str(), 60, 180, 20, BLACK);

    DrawText("Password:", 60, 230, 20, BLACK);
    DrawText(passwordInput.c_str(), 60, 260, 20, BLACK);

    DrawRectangle(50, 400, 100, 50, LIGHTGRAY);
    DrawText("Return to Menu", 60, 410, 20, BLACK);
}

bool RegisterMenu::CheckReturnPressed() const {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), returnButton);
}

const std::string& RegisterMenu::GetUsernameInput() const {
    return usernameInput;
}

const std::string& RegisterMenu::GetPasswordInput() const {
    return passwordInput;
}

void RegisterMenu::ResetInputs() {
    usernameInput = "";
    passwordInput = "";
}