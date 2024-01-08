#include "raylib.h"
#include <string>

enum Screen {
    MAIN_MENU,
    REGISTER,
    LOGIN,
    USER_MENU,
    DEPOSIT,
    WITHDRAW,
    TRANSFER,
    CHECK_BALANCE
};

struct User {
    std::string username;
    std::string password;
    float balance;
};

class BankSimulation {
public:
    void Run() {
        InitWindow(800, 600, "Davs Bank Simulation");

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            switch (currentScreen) {
            case MAIN_MENU:
                DrawMainMenu();
                break;
            case REGISTER:
                DrawRegister();
                break;
            case LOGIN:
                DrawLogin();
                break;
            case USER_MENU:
                DrawUserMenu();
                break;
            case DEPOSIT:
                break;
            case WITHDRAW:
                break;
            case TRANSFER:
                break;
            case CHECK_BALANCE:
                break;
            }

            EndDrawing();
        }

    }

private:
    Screen currentScreen = MAIN_MENU;
    User currentUser;
    static const int MAX_TEXT_BUFFER_LENGTH = 64;
    char usernameBuffer[MAX_TEXT_BUFFER_LENGTH] = "";
    char passwordBuffer[MAX_TEXT_BUFFER_LENGTH] = "";
    void DrawMainMenu() {
        DrawText("Davs Bank", GetScreenWidth() / 2 - MeasureText("Davs Bank", 40) / 2, 100, 40, BLACK);

        if (Button("Register", 50, 200, 200)) {
            currentScreen = REGISTER;
        }

        if (Button("Log In", 50, 250, 200)) {
            currentScreen = LOGIN;
        }

        if (Button("Exit", 50, 300, 200)) {
            exit(0);
        }
    }

    void DrawRegister() {
        DrawText("Register", 50, 50, 30, BLACK);

        DrawTextBox("Username:", 50, 150, 200, usernameBuffer);
        DrawTextBox("Password:", 50, 210, 200, passwordBuffer, true);

        if (Button("Register", 50, 300, 200)) {
            // Implement user registration logic
            currentUser.username = usernameBuffer;
            currentUser.password = passwordBuffer;
            currentUser.balance = 0.0f;
            currentScreen = USER_MENU;
        }

        if (Button("Return to Menu", 50, 350, 200)) {
            currentScreen = MAIN_MENU;
            // Reset both username and password buffers when returning to the main menu
            usernameBuffer[0] = '\0';
            passwordBuffer[0] = '\0';
        }
    }

    void DrawLogin() {
        DrawText("Log In", 50, 50, 30, BLACK);

        DrawTextBox("Username:", 50, 150, 200, usernameBuffer);
        DrawTextBox("Password:", 50, 220, 200, passwordBuffer, true);

        if (Button("Log In", 50, 300, 200)) {
            if (currentUser.username == usernameBuffer && currentUser.password == passwordBuffer) {
                currentScreen = USER_MENU;
            }
        }

        if (Button("Return to Menu", 50, 350, 200)) {
            currentScreen = MAIN_MENU;
            // Reset both username and password buffers when returning to the main menu
            usernameBuffer[0] = '\0';
            passwordBuffer[0] = '\0';
        }
    }

    void DrawUserMenu() {
        DrawText("User Menu", 50, 50, 30, BLACK);

        if (Button("Deposit", 50, 150, 200)) {
            currentScreen = DEPOSIT;
        }

        if (Button("Withdraw", 50, 200, 200)) {
            currentScreen = WITHDRAW;
        }

        if (Button("Transfer", 50, 250, 200)) {
            currentScreen = TRANSFER;
        }

        if (Button("Check Balance", 50, 300, 200)) {
            currentScreen = CHECK_BALANCE;
        }

        if (Button("Log Out", 50, 350, 200)) {
            currentUser = {};  // Clear current user data
            currentScreen = MAIN_MENU;
        }
    }

    bool Button(const char* text, float x, float y, float width) {
        Rectangle buttonRect = { x, y, width, 40 };
        DrawRectangleRec(buttonRect, LIGHTGRAY);

        if (CheckCollisionPointRec(GetMousePosition(), buttonRect)) {
            DrawRectangleLinesEx(buttonRect, 2, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                return true;
            }
        }

        DrawText(text, x + 10, y + 10, 20, BLACK);

        return false;
    }
    void DrawTextBox(const char* label, float x, float y, float width, char* buffer, bool isPassword = false) {
        DrawText(label, x, y, 20, BLACK);
        
        Rectangle textBoxRect = { x, y + 30, width, 30 };
        DrawRectangleRec(textBoxRect, LIGHTGRAY);
        DrawRectangleLinesEx(textBoxRect, 2, BLACK);

        // Update buffer with input text
        int len = strlen(buffer);
        int key = GetKeyPressed();
        if (len < MAX_TEXT_BUFFER_LENGTH - 1) {
            if (IsKeyPressed(KEY_BACKSPACE) && len > 0) {
                // Handle backspace
                buffer[len - 1] = '\0';
            }
            else if (key >= 32 && key <= 125) {
                // Handle regular characters
                buffer[len] = static_cast<char>(key);
                buffer[len + 1] = '\0';
            }
        }

        // Draw asterisks for password input
        if (isPassword) {
            DrawText((len > 0) ? "*" : "", x + 10, y + 40, 20, BLACK);
        }
        else 
        {
            DrawText(buffer, x + 10, y + 40, 20, BLACK);
        }
    }
};


int main() {
    BankSimulation bank;
    bank.Run();
}