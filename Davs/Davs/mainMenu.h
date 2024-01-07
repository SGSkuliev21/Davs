#include "raylib.h"

class MainMenu {
public:
    MainMenu();

    void Draw();
    bool CheckRegisterPressed() const;
    bool CheckLoginPressed() const;
    bool CheckExitPressed() const;

private:
    bool isActive;
    Rectangle registerButton;
    Rectangle loginButton;
    Rectangle exitButton;
};