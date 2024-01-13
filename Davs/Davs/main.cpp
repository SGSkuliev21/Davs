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
    static const int MAX_TEXT_BUFFER_LENGTH = 15;
    char usernameBuffer[50] = "";
    char passwordBuffer[50] = "";
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
                DrawDeposit();
                break;
            case WITHDRAW:
                DrawWithdraw();
                break;
            case TRANSFER:
                DrawTransfer();
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

        // Draw the username text box
        DrawTextBox("Username:", screenWidth / 4 + 107, screenHeight / 2 - 100, 200, usernameBuffer);

        // Check if the password box is being clicked
        bool clickedPasswordBox = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), { (float)(screenWidth / 2 - 93), (float)265, (float)200, 30 });

        // If the password box is clicked, switch the focus to the password box
        if (clickedPasswordBox) {
            isEnteringPassword = true;
            // Clear password buffer when switching to the password state
        }
        else {
            isEnteringPassword = false;  // If not clicked, keep entering the username
        }

        // Draw the password text box
        DrawTextBox("Password:", screenWidth / 2 - 93, 265, 200, passwordBuffer, isEnteringPassword);

        bool incorrectInput = false;

        // Continue button logic
        if (Button("      Continue", screenWidth / 2 - 93, screenHeight / 2 + 75, 200)) {
            if (isEnteringPassword) {
                // Implement user login logic
                if (AuthenticateUser(usernameBuffer, passwordBuffer)) {
                    currentScreen = USER_MENU;
                }
                else {
                    // Set a flag for incorrect input
                    incorrectInput = true;

                    // Reset variables when login attempt is finished
                    usernameBuffer[0] = '\0';
                    passwordBuffer[0] = '\0';
                }
            }
            else {
                // Switch to entering password state when Continue is pressed
                isEnteringPassword = true;
            }
        }

        DrawText("or", screenWidth / 2 - MeasureText("or", 20) / 2, screenHeight / 2 + 120, 20, BLACK);
        DrawText("Create account", screenWidth / 2 - MeasureText("Create account", 20) / 2, screenHeight / 2 + 145, 20, BLUE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), { (float)(screenWidth / 2 - MeasureText("Create account", 20) / 2), (float)(screenHeight / 2 + 140), (float)MeasureText("Create account", 20), 20 })) {
            currentScreen = REGISTER;
            usernameBuffer[0] = '\0';
        }

        if (incorrectInput) {
            DrawText("Incorrect username or password!", screenWidth / 4, screenHeight / 2 + 120, 20, RED);
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

        
            DrawTextBox("Password:", 50, 220, 200, passwordBuffer, true);

            if (Button("Register", 50, 300, 200)) {
                // Implement user registration logic
                // You may want to add data validation and error handling
                currentUser.username = usernameBuffer;
                currentUser.password = passwordBuffer;
                currentUser.balance = 0.0f;
                currentScreen = USER_MENU;
                SaveUser(currentUser.username, currentUser.password);
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
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();

        ClearBackground(RAYWHITE);

        // Draw the user menu title
        DrawText("User Menu", screenWidth / 2 - MeasureText("User Menu", 30) / 2, 50, 30, BLACK);

        // Draw the user information
        DrawText("Username:", 100, 150, 20, BLACK);
        DrawText(currentUser.username.c_str(), 250, 150, 20, BLACK);

        DrawText("Balance:", 100, 200, 20, BLACK);
        DrawText(TextFormat("$ %.2f", currentUser.balance), 250, 200, 20, BLACK);

        // Draw buttons for different actions
        if (Button("Deposit", screenWidth / 2 - 100, 300, 200)) 
        {
            currentScreen = DEPOSIT;
        }

        if (Button("Withdraw", screenWidth / 2 - 100, 350, 200)) {
            currentScreen = WITHDRAW;
        }

        if (Button("Transfer", screenWidth / 2 - 100, 400, 200)) {
            currentScreen = TRANSFER;
        }

        if (Button("Log Out", screenWidth / 2 - 100, 450, 200)) {
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

        if (IsKeyPressed(KEY_BACKSPACE) && len > 0) {
            // Handle backspace
            buffer[len - 1] = '\0';
        }

        int key = GetKeyPressed();
        if (len < MAX_TEXT_BUFFER_LENGTH - 1) {
            // Handle all printable characters (ASCII range 32 to 126)
            if (key >= 32 && key <= 126) {
                buffer[len] = static_cast<char>(key);
                buffer[len + 1] = '\0';
            }
        }

        // Draw asterisks for password input
        if (isPassword) {
            DrawText(TextFormat("%.*s", len, "****************"), x + 10, y + 40, 20, BLACK);
        }
        else {
            // Draw the text inside the buffer
            DrawText(buffer, x + 10, y + 40, 20, BLACK);
        }
    }
    bool LoadUser(const std::string& username, User& user) {
        std::ifstream file("users.txt");
        if (file.is_open()) {
            std::string storedUsername, storedPassword;
            float storedBalance;
            while (file >> storedUsername >> storedPassword >> storedBalance) {
                if (storedUsername == username) {
                    user.username = storedUsername;
                    user.password = storedPassword;
                    user.balance = storedBalance;
                    file.close();
                    return true;  // User found
                }
            }
            file.close();
        }
        return false;  // User not found
    }

    void SaveUser(const User& user) {
        std::ifstream infile("users.txt");
        std::ofstream outfile("temp.txt", std::ios::app);

        if (infile.is_open() && outfile.is_open()) {
            std::string storedUsername, storedPassword;
            float storedBalance;

            while (infile >> storedUsername >> storedPassword >> storedBalance) {
                if (storedUsername == user.username) {
                    // Skip the line for the existing user
                    continue;
                }
                // Write other users to the temporary file
                outfile << storedUsername << " " << storedPassword << " " << storedBalance << std::endl;
            }

            // Write the updated user to the temporary file
            outfile << user.username << " " << user.password << " " << user.balance << std::endl;

            // Close the files
            infile.close();
            outfile.close();

            // Remove the original file
            remove("users.txt");

            // Rename the temporary file to the original file
            rename("temp.txt", "users.txt");
        }
    }

    void DrawDeposit() {
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();

        ClearBackground(RAYWHITE);

        DrawText("Deposit", screenWidth / 2 - MeasureText("Deposit", 30) / 2, 50, 30, BLACK);

        DrawText("Current Balance:", 100, 150, 20, BLACK);
        DrawText(TextFormat("$ %.2f", currentUser.balance), 300, 150, 20, BLACK);

        DrawText("Enter deposit amount:", 100, 200, 20, BLACK);

        static char depositAmountBuffer[MAX_TEXT_BUFFER_LENGTH] = "";
        DrawTextBox("", 300, 200, 200, depositAmountBuffer);

        if (Button("Confirm Deposit", screenWidth / 2 - 100, 300, 200)) {
            // Implement deposit logic
            float depositAmount = atof(depositAmountBuffer);
            if (depositAmount > 0) {
                currentUser.balance += depositAmount;
                SaveUser(currentUser);  // Save the updated user data
            }
            // You may want to add validation and error handling
            // Reset the deposit amount buffer
            depositAmountBuffer[0] = '\0';
        }

        if (Button("Back to Menu", screenWidth / 2 - 100, 350, 200)) {
            currentScreen = USER_MENU;
        }
    }

    void DrawWithdraw() {
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();

        ClearBackground(RAYWHITE);

        DrawText("Withdraw", screenWidth / 2 - MeasureText("Withdraw", 30) / 2, 50, 30, BLACK);

        DrawText("Current Balance:", 100, 150, 20, BLACK);
        DrawText(TextFormat("$ %.2f", currentUser.balance), 300, 150, 20, BLACK);

        DrawText("Enter withdrawal amount:", 100, 200, 20, BLACK);

        static char withdrawAmountBuffer[MAX_TEXT_BUFFER_LENGTH] = "";
        DrawTextBox("", 250, 200, 200, withdrawAmountBuffer);

        if (Button("Confirm Withdraw", screenWidth / 2 - 100, 300, 200)) {
            // Implement withdrawal logic
            float withdrawAmount = atof(withdrawAmountBuffer);
            if (withdrawAmount > 0 && withdrawAmount <= currentUser.balance) {
                currentUser.balance -= withdrawAmount;
                SaveUser(currentUser);  // Save the updated user data
            }
            // You may want to add validation and error handling
            // Reset the withdrawal amount buffer
            withdrawAmountBuffer[0] = '\0';
        }

        if (Button("Back to Menu", screenWidth / 2 - 100, 350, 200)) {
            currentScreen = USER_MENU;
        }
    }

    void DrawTransfer() {
        const int screenWidth = GetScreenWidth();
        const int screenHeight = GetScreenHeight();

        ClearBackground(RAYWHITE);

        DrawText("Transfer", screenWidth / 2 - MeasureText("Transfer", 30) / 2, 50, 30, BLACK);

        DrawText("Current Balance:", 100, 150, 20, BLACK);
        DrawText(TextFormat("$ %.2f", currentUser.balance), 300, 150, 20, BLACK);

        DrawText("Enter transfer amount:", 100, 200, 20, BLACK);

        static char transferAmountBuffer[MAX_TEXT_BUFFER_LENGTH] = "";
        DrawTextBox("", 250, 195, 200, transferAmountBuffer);

        DrawText("Enter recipient's username:", 100, 270, 20, BLACK);

        static char recipientUsernameBuffer[MAX_TEXT_BUFFER_LENGTH] = "";
        DrawTextBox("", 250, 275, 200, recipientUsernameBuffer);

        if (Button("Confirm Transfer", screenWidth / 2 - 100, 360, 200)) {
            // Implement transfer logic
            float transferAmount = atof(transferAmountBuffer);
            std::string recipientUsername(recipientUsernameBuffer);

            // You may want to add validation and error handling
            // Check if recipient username exists and transferAmount is valid
            // For simplicity, assuming recipient exists and the amount is valid
            if (transferAmount > 0 && transferAmount <= currentUser.balance) {
                // Deduct from the current user
                currentUser.balance -= transferAmount;
                SaveUser(currentUser);  // Save the updated user data

                // Add to the recipient (you should fetch recipient's data from the database)
                User recipientUser;
                if (LoadUser(recipientUsername, recipientUser)) {
                    recipientUser.balance += transferAmount;
                    SaveUser(recipientUser);  // Save the updated recipient data
                }
            }

            // Reset the transfer buffers
            transferAmountBuffer[0] = '\0';
            recipientUsernameBuffer[0] = '\0';
        }

        if (Button("Back to Menu", screenWidth / 2 - 100, 420, 200)) {
            currentScreen = USER_MENU;
        }
    }

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
        return false;
        file.close();
    }
    return false;  // User not found or authentication failed
}
int main() {
    BankSimulation bank;
    bank.Run();
    return 0;
}