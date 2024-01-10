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
    static const int MAX_TEXT_BUFFER_LENGTH = 64;
    char usernameBuffer[100] = "";
    char passwordBuffer[100] = "";
    bool isConfirmingUsername = false;
    std::string confirmedUsername;
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
                // Implement deposit scene
                break;
            case WITHDRAW:
                // Implement withdraw scene   
                break;
            case TRANSFER:
                // Implement transfer scene
                break;
            case CHECK_BALANCE:
                // Implement check balance scene
                break;
            }

            EndDrawing();
        }

    }

private:
    Screen currentScreen = MAIN_MENU;
    User currentUser;
    bool isEnteringPassword = false;  // New state variable

    void DrawMainMenu() {
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();

        DrawText("Welcome to Davs", screenWidth / 2 - MeasureText("Welcome to Davs", 40) / 2, screenHeight / 7, 40, BLACK);
        DrawText("Enter your username and password", screenWidth / 2 - MeasureText("Enter your username and password", 20)/4.5, screenHeight / 5, 10, BLACK);

        DrawText("Username:", screenWidth / 4 + 110, screenHeight / 2 - 100, 20, BLACK);
        DrawTextBox(usernameBuffer, screenWidth / 2 - 93, 190, 200, usernameBuffer);

        DrawText("Passowrd:", screenWidth / 4 + 110, screenHeight / 2 - 35, 20, BLACK);
        DrawTextBox(confirmedUsername.c_str(), screenWidth / 2 - 93, 255, 200, passwordBuffer, true);

        if (Button("      Continue", screenWidth / 2 - 93, screenHeight / 2 + 75, 200)) {
            // Implement user login logic
            // You may want to add data validation and error handling
            currentUser.username = usernameBuffer;
            currentScreen = USER_MENU;
        }

        DrawText("or", screenWidth / 2 - MeasureText("or", 20) / 2, screenHeight / 2 + 120, 20, BLACK);
        DrawText("Create account", screenWidth / 2 - MeasureText("Create account", 20) / 2, screenHeight / 2 + 145, 20, BLUE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), { (float)(screenWidth / 2 - MeasureText("Create account", 20) / 2), (float)(screenHeight / 2 + 140), (float)MeasureText("Create account", 20), 20 })) {
            currentScreen = REGISTER;
            usernameBuffer[0] = '\0';
        }
    }

    void DrawRegister() {
        DrawText("Register", 50, 50, 30, BLACK);

        DrawTextBox("Username:", 50, 150, 200, usernameBuffer);

        // If Enter is pressed, switch to entering password state
        if (IsKeyPressed(KEY_ENTER)) {
            isEnteringPassword = true;
            // Clear password buffer when switching to the password state
            passwordBuffer[0] = '\0';
        }

        if (isEnteringPassword) {
            DrawTextBox("Password:", 50, 200, 200, passwordBuffer, true);

            if (Button("Register", 50, 300, 200)) {
                // Implement user registration logic
                // You may want to add data validation and error handling
                currentUser.username = usernameBuffer;
                currentUser.password = passwordBuffer;
                currentUser.balance = 0.0f;
                currentScreen = USER_MENU;
            }
        }

        if (Button("Return to Menu", 50, 350, 200)) {
            currentScreen = MAIN_MENU;
            // Reset both username and password buffers when returning to the main menu
            usernameBuffer[0] = '\0';
            passwordBuffer[0] = '\0';
            // Reset the state to entering username
            isEnteringPassword = false;
        }
    }

    void DrawLogin() 
    {
        static bool isEnteringPassword = false;
        static bool isConfirmingUsername = false;
        static std::string confirmedUsername;  // Store the confirmed username

        DrawText("Log In", 50, 50, 30, BLACK);

        if (!isEnteringPassword && !isConfirmingUsername) {
            DrawTextBox("Username:", 50, 150, 200, usernameBuffer);

            if (IsKeyPressed(KEY_ENTER)) {
                isConfirmingUsername = true;
                confirmedUsername = usernameBuffer;  // Store the entered username for confirmation
            }
        }
        else if (isConfirmingUsername) {
            DrawText("Confirm Username:", 50, 150, 30, BLACK);
            DrawTextBox(confirmedUsername.c_str(), 50, 200, 200, usernameBuffer);

            if (Button("Confirm", 50, 300, 200)) {
                // Implement user login logic
                // You may want to add data validation and error handling
                if (currentUser.username == confirmedUsername) {
                    currentScreen = USER_MENU;
                }
                else {
                    // Username doesn't match, handle accordingly
                }

                // Reset variables when login attempt is finished
                isConfirmingUsername = false;
                confirmedUsername.clear();
            }

            if (Button("Return to Menu", 50, 350, 200)) {
                currentScreen = MAIN_MENU;
                // Reset both username and confirmation variables when returning to the main menu
                usernameBuffer[0] = '\0';
                isConfirmingUsername = false;
                confirmedUsername.clear();
            }
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
        else {
            // Draw the text inside the buffer
            DrawText(buffer, x + 10, y + 40, 20, BLACK);
        }
    }
};

int main() {
    BankSimulation bank;
    bank.Run();
    return 0;
}