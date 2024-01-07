#pragma once
#include "raylib.h"
#include <string>

class LoginMenu {
public:
    LoginMenu();

    void Draw();
    bool CheckReturnPressed() const;
    bool CheckLoginPressed() const;

    const std::string& GetUsernameInput() const;
    const std::string& GetPasswordInput() const;

    void ResetInputs();

private:
    bool isActive;
    Rectangle returnButton;
    Rectangle loginButton;
    std::string usernameInput;
    std::string passwordInput;
};
