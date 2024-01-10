#include "raylib.h"
#include <string>
#include <fstream> 

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
    static const int MAX_TEXT_BUFFER_LENGTH = 16; // Change maximum length to 16 characters
    char usernameBuffer[MAX_TEXT_BUFFER_LENGTH + 1] = ""; // +1 for null-terminator
    char passwordBuffer[MAX_TEXT_BUFFER_LENGTH + 1] = ""; // +1 for null-terminator

    void SaveUser(const std::string& username, const std::string& password);
    bool AuthenticateUser(const std::string& username, const std::string& password);
    bool isConfirmingUsername = false;
    std::string confirmedUsername;
    void Run() {
        InitWindow(800, 600, "Davs Bank");

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
    bool isEnteringPassword = false;

    void DrawMainMenu() {
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();

        DrawText("Welcome to Davs", screenWidth / 2 - MeasureText("Welcome to Davs", 40) / 2, screenHeight / 7, 40, BLACK);
        DrawText("Enter your username and password", screenWidth / 2 - MeasureText("Enter your username and password", 20) / 4.5, screenHeight / 5, 10, BLACK);

        DrawTextBox("Username:", screenWidth / 4 + 107, screenHeight / 2 - 100, 200, usernameBuffer);
        DrawTextBox("Password:", screenWidth / 2 - 93, 265, 200, passwordBuffer, true);

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
            passwordBuffer[0] = '\0';
        }
    }

    void DrawRegister() {
        DrawText("Register", 50, 50, 30, BLACK);

        static bool isEnteringUsername = true;

        if (isEnteringUsername) {
            DrawTextBox("Username:", 50, 150, 200, usernameBuffer);

            // Check if the username text box is full
            if (strlen(usernameBuffer) >= MAX_TEXT_BUFFER_LENGTH) {
                isEnteringUsername = false;
                // Clear password buffer when switching to the password state
                passwordBuffer[0] = '\0';
            }
        }
        else {
            DrawTextBox("Password:", 50, 200, 200, passwordBuffer, true);

            if (Button("Register", 50, 300, 200)) {
                // Implement user registration logic
                // You may want to add data validation and error handling
                currentUser.username = usernameBuffer;
                currentUser.password = passwordBuffer;
                currentUser.balance = 0.0f;
                currentScreen = USER_MENU;
                SaveUser(currentUser.username, currentUser.password);
            }
        }

        if (Button("Return to Menu", 50, 350, 200)) {
            currentScreen = MAIN_MENU;
            // Reset both username and password buffers when returning to the main menu
            usernameBuffer[0] = '\0';
            passwordBuffer[0] = '\0';
            isEnteringUsername = true; // Reset the state to entering username
        }
    }

    void DrawLogin() {
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
                if (AuthenticateUser(currentUser.username, currentUser.password)) {
                    currentScreen = USER_MENU;
                }
                else {
                    DrawText("User not found!", 400, 300, 20, BLACK);
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

        if (CheckCollisionPointRec(GetMousePosition(), textBoxRect)) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                activeTextBox = buffer;
            }
        }

        if (activeTextBox == buffer) {
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
    }

    std::string activeTextBox;  // Track the active text box
};

void BankSimulation::SaveUser(const std::string& username, const std::string& password) {
    std::ofstream file("users.txt", std::ios::app);  // Open file in append mode
    if (file.is_open()) {
        file << "Username: " << username << " " << "Password: " << password << std::endl;
        file.close();
    }
    else {
        // Handle file open failure
    }
}

bool BankSimulation::AuthenticateUser(const std::string& username, const std::string& password) {
    std::ifstream file("users.txt");
    if (file.is_open()) {
        std::string storedUsername, storedPassword;
        while (file >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                file.close();
                return true;  // User found and authenticated
            }
        }
        file.close();
    }
    return false;  // User not found or authentication failed
}

int main() {
    BankSimulation bank;
    bank.Run();
    return 0;
}