#include "raylib.h"
#include <string> 
#include <fstream>
#include <iostream>

struct CREDENTIAL_BOX
{
    char input[16];
    int charCount;
    Rectangle box;
    int framesCounter;
};

struct MAIN_MENU
{
    CREDENTIAL_BOX usernameBox;
    CREDENTIAL_BOX passwordBox;
    Rectangle continueButton;
    Rectangle createAccountButton;
};


struct User {
    std::string username;
    float balance;
};


struct REGISTRATION_FORM
{
    CREDENTIAL_BOX firstNameBox{ "", 0, {700, 140, 200, 30}, 0 };
    CREDENTIAL_BOX lastNameBox{ "", 0, {700, 200, 200, 30}, 0 };
    CREDENTIAL_BOX usernameBox{ "", 0, {700, 260, 200, 30}, 0 };
    CREDENTIAL_BOX passwordBox{ "", 0, {700, 320, 200, 30}, 0 };
    CREDENTIAL_BOX confirmPasswordBox{ "", 0, {700, 380, 200, 30}, 0 };
    Rectangle registerButton{ 700, 700, 200, 40 };
};

CREDENTIAL_BOX firstNameBox{ "", 0, {GetScreenWidth() / 2 + 300, 140, 200, 30}, 0 };
CREDENTIAL_BOX lastNameBox{ "", 0, {GetScreenWidth() / 2 + 300, 200, 200, 30}, 0 };
CREDENTIAL_BOX usernameBox{ "", 0, {GetScreenWidth() / 2 + 300, 260, 200, 30}, 0 };
CREDENTIAL_BOX passwordBox{ "", 0, {GetScreenWidth() / 2 + 300, 320, 200, 30}, 0 };
CREDENTIAL_BOX confirmPasswordBox{ "", 0, {GetScreenWidth() / 2 + 300, 380, 200, 30}, 0 };
Rectangle registerButton{ GetScreenWidth() / 2 + 300, 700, 200, 40 };

enum ActiveBox {
    FIRST_NAME,
    LAST_NAME,
    USERNAME,
    PASSWORD,
    CONFIRM_PASSWORD
};

ActiveBox activeBox = USERNAME;
bool registrationFormActive = false;

MAIN_MENU mainMenu = {
    { "", 0, {GetScreenWidth() / 2 + 310, GetScreenHeight() / 2 + 240, 200, 30}, 0 },
    { "", 0, {GetScreenWidth() / 2 + 310, GetScreenHeight() / 2 + 310, 200, 30}, 0 },
    { GetScreenWidth() / 2 + 310, GetScreenHeight() / 2 + 400, 200, 40 },
    { GetScreenWidth() / 2 + 310, GetScreenHeight() / 2 + 450, 200, 40 }
};

REGISTRATION_FORM registrationForm =
{
    { "", 0, {GetScreenWidth() / 2 + 300, 140, 200, 30}, 0 },
    { "", 0, {GetScreenWidth() / 2 + 300, 200, 200, 30}, 0 },
    { "", 0, {GetScreenWidth() / 2 + 300, 260, 200, 30}, 0 },
    { "", 0, {GetScreenWidth() / 2 + 300, 320, 200, 30}, 0 },
    { "", 0, {GetScreenWidth() / 2 + 300, 380, 200, 30}, 0 },
    { GetScreenWidth() / 2 + 500, 600, 200, 40 }
};

bool isMouseOverBox(Rectangle box)
{
    return CheckCollisionPointRec(GetMousePosition(), box);
}

void drawTextBox(CREDENTIAL_BOX& textBox, const char* label, bool showCharacters)
{
    DrawText(label, (int)textBox.box.x, (int)textBox.box.y - 19, 20, BLACK);
    DrawRectangleLinesEx(textBox.box, 3, BLACK);

    if (showCharacters)
    {
        DrawText(textBox.input, (int)textBox.box.x + 5, (int)textBox.box.y + 4, 20, BLACK);
    }
    else {
        for (int i = 0; i < textBox.charCount; i++)
        {
            DrawText("*", (int)textBox.box.x + 5 + i * MeasureText("*", 20), (int)textBox.box.y + 4, 20, BLACK);
        }
    }

    if (isMouseOverBox(textBox.box))
    {
        if (textBox.charCount < 13)
        {
            if (((textBox.framesCounter / 20) % 2) == 0)
            {
                DrawText("|", (int)textBox.box.x + 8 + MeasureText(textBox.input, 20), (int)textBox.box.y + 6, 20, BLACK);
            }
        }
    }
}



bool isValidNumber(const std::string& input) {
    try {
        std::stof(input);
        return true;
    }
    catch (...) {
        return false;
    }
}


void Deposit(User& currentUser)
{
    std::string input;
    float depositAmount;

    std::cout << "Enter the amount you want to deposit: ";
    std::getline(std::cin, input);

    while (!isValidNumber(input)) {
        std::cout << "Invalid input. Please enter a valid number: ";
        std::getline(std::cin, input);
    }

    depositAmount = std::stof(input);

    currentUser.balance += depositAmount;

    std::cout << "Deposit successful. Updated balance: " << currentUser.balance << std::endl;
}

void Withdraw(User& currentUser)
{
    std::string input;
    float withdrawAmount = 0;

    std::cout << "Enter the amount you want to withdraw: ";
    std::getline(std::cin, input);

    while (!isValidNumber(input)) {
        std::cout << "Invalid input. Please enter a valid number: ";
        std::getline(std::cin, input);
    }

    if (withdrawAmount > currentUser.balance) {
        std::cout << "Insufficient funds. Withdrawal unsuccessful." << std::endl;
    }
    else
    {
        currentUser.balance -= withdrawAmount;

        std::cout << "Withdrawal successful. Updated balance: " << currentUser.balance << std::endl;
    }
}

bool checkRequirements(const char* str) {
    bool hasCapital = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    const char* specialCharacters = "!@#$%^&*()-_+=[]{}|;:'\",.<>?";

    for (const char* temp = str; *temp != '\0'; temp++) {
        if (isupper(*temp)) {
            hasCapital = true;
        }
        else if (islower(*temp)) {
            hasLower = true;
        }
        else if (isdigit(*temp)) {
            hasDigit = true;
        }
        else if (strchr(specialCharacters, *temp) != nullptr)
        {
            hasSpecial = true;
        }
    }

    return hasCapital && hasLower && hasDigit && hasSpecial && (strlen(str) >= 6);
}

void saveUserData(const char* firstName, const char* lastName, const char* username, const char* password)
{
    std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        file << "First Name: " << firstName << std::endl;
        file << "Last Name: " << lastName << std::endl;
        file << "Username: " << username << std::endl;
        file << "Password: " << password << std::endl;
        file << "Balance: 0.0" << std::endl;
        file << "--------------------------" << std::endl;  // Separator for each user
        file.close();
    }
    else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}

bool checkExistingAccount(const char* username, const char* password)
{
    std::ifstream file("users.txt");
    std::string line;

    while (std::getline(file, line)) {
        if (line.find("Username: " + std::string(username)) != std::string::npos) {
            std::getline(file, line); // Skip the "Password: " line
            std::getline(file, line); // Get the actual password line

            // Check if the provided password matches
            return line.find("Password: " + std::string(password)) != std::string::npos;
        }
    }

    return false;
}


struct TextBox {
    std::string text;
    Rectangle rect;
};

struct Button {
    Rectangle rect;
    std::string label;
};

User currentUser;





void DrawUserMenu()
{
    Button depositButton;
    depositButton.label = "Deposit";
    depositButton.rect = { 600, 50, 150, 40 };

    Button withdrawButton;
    withdrawButton.label = "Withdraw";
    withdrawButton.rect = { 600, 100, 150, 40 };

    Button transferButton;
    transferButton.label = "Transfer";
    transferButton.rect = { 600, 150, 150, 40 };

    Button leaveWillButton;
    leaveWillButton.label = "Leave a Will";
    leaveWillButton.rect = { 600, 200, 150, 40 };

    Button investButton;
    investButton.label = "Invest";
    investButton.rect = { 600, 250, 150, 40 };

    TextBox depositTextBox;
    depositTextBox.rect = { 50, 50, 150, 40 };

    TextBox withdrawTextBox;
    withdrawTextBox.rect = { 50, 100, 150, 40 };

    TextBox transferTextBox;
    transferTextBox.rect = { 50, 150, 150, 40 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        DrawText(("Balance: " + std::to_string(currentUser.balance)).c_str(), 10, 20, 20, BLACK);

        if (CheckCollisionPointRec(GetMousePosition(), depositButton.rect))
        {
            DrawRectangleRec(depositButton.rect, { 0, 160, 0, 255 });
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Deposit(currentUser);
            }
        }
        else
        {
            DrawRectangleRec(depositButton.rect, GREEN);
        }
        DrawText(depositButton.label.c_str(), depositButton.rect.x + 10, depositButton.rect.y + 10, 20, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), withdrawButton.rect))
        {
            DrawRectangleRec(withdrawButton.rect, { 0, 160, 0, 255 });
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Withdraw(currentUser);
            }
        }
        else
        {
            DrawRectangleRec(withdrawButton.rect, GREEN);
        }
        DrawText(withdrawButton.label.c_str(), withdrawButton.rect.x + 10, withdrawButton.rect.y + 10, 20, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), transferButton.rect))
        {
            DrawRectangleRec(transferButton.rect, { 0, 160, 0, 255 });
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
            }
        }
        else
        {
            DrawRectangleRec(transferButton.rect, GREEN);
        }
        DrawText(transferButton.label.c_str(), transferButton.rect.x + 10, transferButton.rect.y + 10, 20, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), leaveWillButton.rect))
        {
            DrawRectangleRec(leaveWillButton.rect, { 0, 160, 0, 255 });
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
            }
        }
        else
        {
            DrawRectangleRec(leaveWillButton.rect, GREEN);
        }
        DrawText(leaveWillButton.label.c_str(), leaveWillButton.rect.x + 10, leaveWillButton.rect.y + 10, 20, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), investButton.rect))
        {
            DrawRectangleRec(investButton.rect, { 0, 160, 0, 255 });
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
            }
        }
        else
        {
            DrawRectangleRec(investButton.rect, GREEN);
        }
        DrawText(investButton.label.c_str(), investButton.rect.x + 10, investButton.rect.y + 10, 20, WHITE);

        EndDrawing();
    }
}

void RegisterForm()
{
    int key = 0;
    activeBox = USERNAME;

    while (!WindowShouldClose())
    {
        key = GetCharPressed();

        if (isMouseOverBox(registrationForm.firstNameBox.box))
        {
            activeBox = FIRST_NAME;
            while (key > 0)
            {

                if ((key >= 32) && (key <= 125) && (registrationForm.firstNameBox.charCount < 15))
                {

                    registrationForm.firstNameBox.input[registrationForm.firstNameBox.charCount] = (char)key;
                    registrationForm.firstNameBox.input[registrationForm.firstNameBox.charCount + 1] = '\0';
                    registrationForm.firstNameBox.charCount++;

                }
                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(registrationForm.lastNameBox.box))
        {
            activeBox = LAST_NAME;
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (registrationForm.lastNameBox.charCount < 15))
                {
                    registrationForm.lastNameBox.input[registrationForm.lastNameBox.charCount] = (char)key;
                    registrationForm.lastNameBox.input[registrationForm.lastNameBox.charCount + 1] = '\0';
                    registrationForm.lastNameBox.charCount++;
                }
                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(registrationForm.usernameBox.box))
        {
            activeBox = USERNAME;
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (registrationForm.usernameBox.charCount < 15))
                {
                    registrationForm.usernameBox.input[registrationForm.usernameBox.charCount] = (char)key;
                    registrationForm.usernameBox.input[registrationForm.usernameBox.charCount + 1] = '\0';
                    registrationForm.usernameBox.charCount++;
                }
                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(registrationForm.passwordBox.box))
        {
            activeBox = PASSWORD;
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (registrationForm.passwordBox.charCount < 15))
                {
                    registrationForm.passwordBox.input[registrationForm.passwordBox.charCount] = (char)key;
                    registrationForm.passwordBox.input[registrationForm.passwordBox.charCount + 1] = '\0';
                    registrationForm.passwordBox.charCount++;
                }
                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(registrationForm.confirmPasswordBox.box))
        {
            activeBox = CONFIRM_PASSWORD;
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125) && (registrationForm.confirmPasswordBox.charCount < 15))
                {
                    registrationForm.confirmPasswordBox.input[registrationForm.confirmPasswordBox.charCount] = (char)key;
                    registrationForm.confirmPasswordBox.input[registrationForm.confirmPasswordBox.charCount + 1] = '\0';
                    registrationForm.confirmPasswordBox.charCount++;
                }
                key = GetCharPressed();
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawText("Register", GetScreenWidth() / 2 - MeasureText("Register", 30) / 2, 50, 30, BLACK);
        drawTextBox(registrationForm.firstNameBox, "First Name:", true);
        drawTextBox(registrationForm.lastNameBox, "Last Name:", true);
        drawTextBox(registrationForm.usernameBox, "Username:", true);
        drawTextBox(registrationForm.passwordBox, "Password:", false);
        drawTextBox(registrationForm.confirmPasswordBox, "Confirm Password:", false);

        registrationForm.registerButton.x = GetScreenWidth() / 2 - registrationForm.registerButton.width / 2;
        registrationForm.registerButton.y = GetScreenHeight() / 2 + 120;


        if (IsKeyPressed(KEY_BACKSPACE)) {
            switch (activeBox) {
            case FIRST_NAME:
                if (registrationForm.firstNameBox.charCount > 0) {
                    registrationForm.firstNameBox.input[registrationForm.firstNameBox.charCount - 1] = '\0';
                    registrationForm.firstNameBox.charCount--;
                }
                break;
            case LAST_NAME:
                if (registrationForm.lastNameBox.charCount > 0) {
                    registrationForm.lastNameBox.input[registrationForm.lastNameBox.charCount - 1] = '\0';
                    registrationForm.lastNameBox.charCount--;
                }
                break;
            case USERNAME:
                if (registrationForm.usernameBox.charCount > 0) {
                    registrationForm.usernameBox.input[registrationForm.usernameBox.charCount - 1] = '\0';
                    registrationForm.usernameBox.charCount--;
                }
                break;
            case PASSWORD:
                if (registrationForm.passwordBox.charCount > 0) {
                    registrationForm.passwordBox.input[registrationForm.passwordBox.charCount - 1] = '\0';
                    registrationForm.passwordBox.charCount--;
                }
                break;
            case CONFIRM_PASSWORD:
                if (registrationForm.confirmPasswordBox.charCount > 0) {
                    registrationForm.confirmPasswordBox.input[registrationForm.confirmPasswordBox.charCount - 1] = '\0';
                    registrationForm.confirmPasswordBox.charCount--;
                }
                break;
            }
        }

        DrawText(checkRequirements(registrationForm.passwordBox.input) ? "The password must contain: a special character, a capital letter, and be at least 6 characters long." : "The password must contain: a special character, a capital letter, and be at least 6 characters long.", GetScreenWidth() / 2 - MeasureText("Register", 20) / 2 - 260, 520, 13, checkRequirements(registrationForm.passwordBox.input) ? GREEN : RED);

        if (isMouseOverBox(registrationForm.registerButton))
        {
            DrawRectangleRec(registrationForm.registerButton, BLUE);
        }
        else
        {
            DrawRectangleRec(registrationForm.registerButton, DARKBLUE);
        }
        DrawText("Register", registrationForm.registerButton.x + 60, registrationForm.registerButton.y + 10, 20, WHITE);

        if (isMouseOverBox(registrationForm.registerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (strcmp(registrationForm.passwordBox.input, registrationForm.confirmPasswordBox.input) == 0 && checkRequirements(registrationForm.passwordBox.input)) {

                if (strlen(registrationForm.firstNameBox.input) > 0 && strlen(registrationForm.lastNameBox.input) > 0) {

                    saveUserData(registrationForm.firstNameBox.input, registrationForm.lastNameBox.input, registrationForm.usernameBox.input, registrationForm.passwordBox.input);

                    registrationForm.firstNameBox.charCount = 0;
                    registrationForm.lastNameBox.charCount = 0;
                    registrationForm.usernameBox.charCount = 0;
                    registrationForm.passwordBox.charCount = 0;
                    registrationForm.confirmPasswordBox.charCount = 0;

                    memset(registrationForm.firstNameBox.input, 0, sizeof(registrationForm.firstNameBox.input));
                    memset(registrationForm.lastNameBox.input, 0, sizeof(registrationForm.lastNameBox.input));
                    memset(registrationForm.usernameBox.input, 0, sizeof(registrationForm.usernameBox.input));
                    memset(registrationForm.passwordBox.input, 0, sizeof(registrationForm.passwordBox.input));
                    memset(registrationForm.confirmPasswordBox.input, 0, sizeof(registrationForm.confirmPasswordBox.input));

                    registrationFormActive = false;
                    break;
                }
            }
        }

        if (CheckCollisionPointRec(GetMousePosition(), registrationForm.registerButton))
        {
            DrawRectangleRec(registrationForm.registerButton, BLUE);
            DrawText("Register", registrationForm.registerButton.x + 60, registrationForm.registerButton.y + 10, 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                const char* firstName = "";
                const char* lastName = "";
                const char* username = "";
                const char* password = "";

                saveUserData(firstName, lastName, username, password);
                DrawUserMenu();
            }
        }

        EndDrawing();
    }
}

void DrawMainMenu()
{
    int key = 0;
    activeBox = USERNAME;

    while (!WindowShouldClose())
    {
        key = GetCharPressed();

        if (isMouseOverBox(mainMenu.usernameBox.box))
        {
            activeBox = FIRST_NAME;
            while (key > 0)
            {

                if ((key >= 32) && (key <= 125) && (mainMenu.usernameBox.charCount < 15))
                {

                    mainMenu.usernameBox.input[mainMenu.usernameBox.charCount] = (char)key;
                    mainMenu.usernameBox.input[mainMenu.usernameBox.charCount + 1] = '\0';
                    mainMenu.usernameBox.charCount++;

                }
                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(mainMenu.passwordBox.box))
        {
            activeBox = FIRST_NAME;
            while (key > 0)
            {

                if ((key >= 32) && (key <= 125) && (mainMenu.passwordBox.charCount < 15))
                {

                    mainMenu.passwordBox.input[mainMenu.passwordBox.charCount] = (char)key;
                    mainMenu.passwordBox.input[mainMenu.passwordBox.charCount + 1] = '\0';
                    mainMenu.passwordBox.charCount++;

                }
                key = GetCharPressed();
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Davs", GetScreenWidth() / 2 - MeasureText("Davs", 40) / 2, 50, 40, BLACK);
        if (isMouseOverBox(mainMenu.usernameBox.box))
        {
            activeBox = USERNAME;
        }
        else if (isMouseOverBox(mainMenu.passwordBox.box))
        {
            activeBox = PASSWORD;
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            switch (activeBox) {
            case USERNAME:
                if (registrationForm.usernameBox.charCount > 0) {
                    registrationForm.usernameBox.input[registrationForm.usernameBox.charCount - 1] = '\0';
                    registrationForm.usernameBox.charCount--;
                }
                break;
            case PASSWORD:
                if (registrationForm.passwordBox.charCount > 0) {
                    registrationForm.passwordBox.input[registrationForm.passwordBox.charCount - 1] = '\0';
                    registrationForm.passwordBox.charCount--;
                }
                break;
            }
        }

        mainMenu.usernameBox.box.x = GetScreenWidth() / 2 - mainMenu.usernameBox.box.width / 2;
        mainMenu.usernameBox.box.y = GetScreenHeight() / 2 - 60;
        mainMenu.passwordBox.box.x = GetScreenWidth() / 2 - mainMenu.passwordBox.box.width / 2;
        mainMenu.passwordBox.box.y = GetScreenHeight() / 2;

        drawTextBox(mainMenu.usernameBox, "Username:", true);
        drawTextBox(mainMenu.passwordBox, "Password:", false);

        mainMenu.continueButton.x = GetScreenWidth() / 2 - mainMenu.continueButton.width / 2;
        mainMenu.continueButton.y = GetScreenHeight() / 2 + 60;
        mainMenu.createAccountButton.x = GetScreenWidth() / 2 - mainMenu.createAccountButton.width / 2;
        mainMenu.createAccountButton.y = GetScreenHeight() / 2 + 135;

        if (isMouseOverBox(mainMenu.continueButton))
        {
            DrawRectangleRec(mainMenu.continueButton, BLUE);
        }
        else
        {
            DrawRectangleRec(mainMenu.continueButton, DARKBLUE);
        }
        DrawText("Continue", mainMenu.continueButton.x + 60, mainMenu.continueButton.y + 10, 20, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), mainMenu.continueButton))
        {

            DrawRectangleRec(mainMenu.continueButton, BLUE);
            DrawText("Continue", mainMenu.continueButton.x + 60, mainMenu.continueButton.y + 10, 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                const char* username = "";
                const char* password = "";

                // Check if the account exists
                if (checkExistingAccount(username, password))
                {
                    DrawUserMenu();
                }
                else
                {
                    std::cout << "Invalid username or password. Please try again." << std::endl;
                }
            }
        }


        if (CheckCollisionPointRec(GetMousePosition(), mainMenu.createAccountButton))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                RegisterForm();
            }
        }
        DrawLine(280, mainMenu.createAccountButton.y - 10, 520, mainMenu.createAccountButton.y - 10, BLUE);
        DrawText("or", mainMenu.createAccountButton.x + 85, mainMenu.createAccountButton.y - 5, 20, BLACK);
        DrawText("Create Account", mainMenu.createAccountButton.x + 20, mainMenu.createAccountButton.y + 20, 20, BLACK);
        EndDrawing();
    }
}



int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Davs");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);
        DrawMainMenu();
    }
}