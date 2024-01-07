#pragma once
#include "raylib.h"
#include <string>

class RegisterMenu {
public:
    RegisterMenu();

    void Draw();
    bool CheckReturnPressed() const;

    const std::string& GetUsernameInput() const;
    const std::string& GetPasswordInput() const;

    void ResetInputs();

private:
    bool isActive;
    Rectangle returnButton;
    std::string usernameInput;
    std::string passwordInput;
};