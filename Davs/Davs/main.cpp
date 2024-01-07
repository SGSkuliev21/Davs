#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>

struct User
{
    std::string username;
    std::string password;
    float balance;
};

std::vector<User> users;

void DrawMainMenu() 
{
    DrawText("Davs Bank", GetScreenWidth() / 2 - MeasureText("Davs Bank", 40) / 2, 100, 40, BLACK);

    DrawRectangle(GetScreenWidth() / 2 - 100, 200, 200, 50, LIGHTGRAY);
    DrawRectangle(GetScreenWidth() / 2 - 100, 260, 200, 50, LIGHTGRAY);
    DrawRectangle(GetScreenWidth() / 2 - 100, 320, 200, 50, LIGHTGRAY);

    DrawText("Register", GetScreenWidth() / 2 - MeasureText("Register", 20) / 2, 210, 20, BLACK);
    DrawText("Login", GetScreenWidth() / 2 - MeasureText("Login", 20) / 2, 270, 20, BLACK);
    DrawText("Exit", GetScreenWidth() / 2 - MeasureText("Exit", 20) / 2, 330, 20, BLACK);
}

void DrawRegisterMenu(std::string& username, std::string& password) 
{
    DrawText("Register", 50, 50, 30, BLACK);
    DrawText("Username:", 60, 150, 20, BLACK);
    DrawText(username.c_str(), 60, 180, 20, BLACK);

    DrawText("Password:", 60, 230, 20, BLACK);
    DrawText(password.c_str(), 60, 260, 20, BLACK);

    // Simulate text input
    if (IsKeyPressed(KEY_BACKSPACE) && username.length() > 0)
    {
        username.pop_back();
    }
    else if (IsKeyPressed(KEY_ENTER)) 
    {
        //databasa 
    }
    else {
        int key = GetKeyPressed();
        if (key != 0) {
            username.push_back(static_cast<char>(key));
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE) && password.length() > 0) {
        password.pop_back();
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        // Handle Enter key press if needed
    }
    else {
        int key = GetKeyPressed();
        if (key != 0) {
            password.push_back('*');
        }
    }

    DrawRectangle(50, 400, 100, 50, LIGHTGRAY);
    DrawText("Return to Menu", 60, 410, 20, BLACK);
}

void DrawLoginMenu(std::string& username, std::string& password, bool& loggedInUser) {
    DrawText("Login", 50, 50, 30, BLACK);
    DrawText("Username:", 60, 150, 20, BLACK);
    DrawText(username.c_str(), 60, 180, 20, BLACK);

    DrawText("Password:", 60, 230, 20, BLACK);
    DrawText(password.c_str(), 60, 260, 20, BLACK);

    // Simulate text input
    if (IsKeyPressed(KEY_BACKSPACE) && username.length() > 0) {
        username.pop_back();
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        // databasas
    }
    else {
        int key = GetKeyPressed();
        if (key != 0) {
            username.push_back(static_cast<char>(key));
        }
    }

    // Simulate text input for password
    if (IsKeyPressed(KEY_BACKSPACE) && password.length() > 0) {
        password.pop_back();
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        // Handle Enter key press
        loggedInUser = true;
    }
    else {
        int key = GetKeyPressed();
        if (key != 0) {
            password.push_back('*');
        }
    }

    DrawRectangle(50, 400, 100, 50, LIGHTGRAY);

    if (loggedInUser) {
        DrawText("Login Successful", 60, 410, 20, GREEN);
    }
    else {
        DrawText("Return to Menu", 60, 410, 20, BLACK);
    }
}

void DrawUserMenu(User& currentUser) {
    DrawText("User Menu", 50, 50, 30, BLACK);
    DrawRectangle(50, 150, 200, 50, LIGHTGRAY);
    DrawRectangle(50, 220, 200, 50, LIGHTGRAY);
    DrawRectangle(50, 290, 200, 50, LIGHTGRAY);
    DrawRectangle(50, 360, 200, 50, LIGHTGRAY);
    DrawRectangle(50, 400, 100, 50, LIGHTGRAY);
    DrawText("Deposit", 60, 160, 20, BLACK);
    DrawText("Withdraw", 60, 230, 20, BLACK);
    DrawText("Transfer", 60, 300, 20, BLACK);
    DrawText("Check Balance", 60, 370, 20, BLACK);
    DrawText("Logout", 60, 410, 20, BLACK);
}

User* AuthenticateUser(const std::string& username, const std::string& password) 
{
    for (User& user : users) {
        if (user.username == username && user.password == password) {
            return &user;
        }
    }
    return nullptr;
}
void DrawMainMenu();
void DrawRegisterMenu(std::string& username, std::string& password);
void DrawLoginMenu(std::string& username, std::string& password, bool& loggedInUser);
void DrawUserMenu(User& currentUser);
User* AuthenticateUser(const std::string& username, const std::string& password);

int main() {
    // Initialize Raylib
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Davs Bank Simulation");

    // Set up initial state
    bool inMainMenu = true;
    bool inRegisterMenu = false;
    bool inLoginMenu = false;
    bool inUserMenu = false;
    User currentUser;
    bool loggedInUser = false;

    std::string usernameInput = "";
    std::string passwordInput = "";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (inMainMenu) {
            DrawMainMenu();

            if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 100, 200, 200, 50 })) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    inMainMenu = false;
                    inRegisterMenu = true;
                }
            }
            else if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 100, 260, 200, 50 })) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    inMainMenu = false;
                    inLoginMenu = true;
                    // Reset username and password when transitioning to login
                    usernameInput = "";
                    passwordInput = "";
                }
            }
            else if (CheckCollisionPointRec(GetMousePosition(), { screenWidth / 2 - 100, 320, 200, 50 })) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    exit(0);
                }
            }
        }
        else if (inRegisterMenu) {
            DrawRegisterMenu(usernameInput, passwordInput);

            if (CheckCollisionPointRec(GetMousePosition(), { 50, 400, 100, 50 })) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    inRegisterMenu = false;
                    inMainMenu = true;
                    // Reset username and password when returning to the main menu
                    usernameInput = "";
                    passwordInput = "";
                }
            }
        }
        else if (inLoginMenu) {
            DrawLoginMenu(usernameInput, passwordInput, loggedInUser);

            if (CheckCollisionPointRec(GetMousePosition(), { 50, 400, 100, 50 }) && loggedInUser) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    // Implement logic for saving or using the logged-in user
                    inLoginMenu = false;
                    inUserMenu = true;
                    currentUser = *AuthenticateUser(usernameInput, passwordInput);
                }
            }
        }
        else if (inUserMenu) {
            DrawUserMenu(currentUser);

            if (CheckCollisionPointRec(GetMousePosition(), { 50, 400, 100, 50 })) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    inUserMenu = false;
                    inMainMenu = true;
                }
            }
        }
        EndDrawing();
    }
}
