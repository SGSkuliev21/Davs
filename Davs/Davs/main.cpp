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

enum ActiveBox {
    FIRST_NAME,
    LAST_NAME,
    USERNAME,
    PASSWORD,
    CONFIRM_PASSWORD
};

ActiveBox activeBox = FIRST_NAME;

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
        file.close();
    }
    else {
        std::cout << "Unable to open file for writing." << std::endl;
    }
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Registration Form");

    CREDENTIAL_BOX firstNameBox = { "", 0, {screenWidth / 2 - 100, 150, 200, 30}, 0 };
    CREDENTIAL_BOX lastNameBox = { "", 0, {screenWidth / 2 - 100, 210, 200, 30}, 0 };
    CREDENTIAL_BOX usernameBox = { "", 0, {screenWidth / 2 - 100, 270, 200, 30}, 0 };
    CREDENTIAL_BOX passwordBox = { "", 0, {screenWidth / 2 - 100, 330, 200, 30}, 0 };
    CREDENTIAL_BOX confirmPasswordBox = { "", 0, {screenWidth / 2 - 100, 390, 200, 30}, 0 };
    Rectangle tickBox = { screenWidth / 2 + 120, 450, 30, 30 };
    Rectangle crossBox = { screenWidth / 2 + 160, 510, 30, 30 };
    Rectangle registerButton = { screenWidth / 2 - 100, 480, 200, 40 };


    while (!WindowShouldClose()) {
        int key = GetCharPressed();

        if (isMouseOverBox(firstNameBox.box)) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (firstNameBox.charCount < 15)) {
                    firstNameBox.input[firstNameBox.charCount] = (char)key;
                    firstNameBox.input[firstNameBox.charCount + 1] = '\0';
                    firstNameBox.charCount++;
                }

                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(lastNameBox.box)) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (lastNameBox.charCount < 15)) {
                    lastNameBox.input[lastNameBox.charCount] = (char)key;
                    lastNameBox.input[lastNameBox.charCount + 1] = '\0';
                    lastNameBox.charCount++;
                }

                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(usernameBox.box)) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (usernameBox.charCount < 15)) {
                    usernameBox.input[usernameBox.charCount] = (char)key;
                    usernameBox.input[usernameBox.charCount + 1] = '\0';
                    usernameBox.charCount++;
                }

                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(passwordBox.box)) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (passwordBox.charCount < 15)) {
                    passwordBox.input[passwordBox.charCount] = (char)key;
                    passwordBox.input[passwordBox.charCount + 1] = '\0';
                    passwordBox.charCount++;
                }

                key = GetCharPressed();
            }
        }

        if (isMouseOverBox(confirmPasswordBox.box)) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (confirmPasswordBox.charCount < 15)) {
                    confirmPasswordBox.input[confirmPasswordBox.charCount] = (char)key;
                    confirmPasswordBox.input[confirmPasswordBox.charCount + 1] = '\0';
                    confirmPasswordBox.charCount++;
                }

                key = GetCharPressed();
            }
        }
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
            if (isMouseOverBox(firstNameBox.box)) {
                activeBox = FIRST_NAME;
            }
            else if (isMouseOverBox(lastNameBox.box)) {
                activeBox = LAST_NAME;
            }
            else if (isMouseOverBox(usernameBox.box)) {
                activeBox = USERNAME;
            }
            else if (isMouseOverBox(passwordBox.box)) {
                activeBox = PASSWORD;
            }
            else if (isMouseOverBox(confirmPasswordBox.box)) {
                activeBox = CONFIRM_PASSWORD;
            }
        

        // Draw Title
        DrawText("Register", screenWidth / 2 - MeasureText("Register", 30) / 2, 50, 30, BLACK);

        drawTextBox(firstNameBox, "First Name:", true);
        drawTextBox(lastNameBox, "Last Name:", true);
        drawTextBox(usernameBox, "Username:", true);
        drawTextBox(passwordBox, "Password:", false);
        drawTextBox(confirmPasswordBox, "Confirm Password:", false);

        if (IsKeyPressed(KEY_BACKSPACE)) {
            switch (activeBox) {
            case FIRST_NAME:
                if (firstNameBox.charCount > 0) {
                    firstNameBox.input[firstNameBox.charCount - 1] = '\0';
                    firstNameBox.charCount--;
                }
                break;
            case LAST_NAME:
                if (lastNameBox.charCount > 0) {
                    lastNameBox.input[lastNameBox.charCount - 1] = '\0';
                    lastNameBox.charCount--;
                }
                break;
            case USERNAME:
                if (usernameBox.charCount > 0) {
                    usernameBox.input[usernameBox.charCount - 1] = '\0';
                    usernameBox.charCount--;
                }
                break;
            case PASSWORD:
                if (passwordBox.charCount > 0) {
                    passwordBox.input[passwordBox.charCount - 1] = '\0';
                    passwordBox.charCount--;
                }
                break;
            case CONFIRM_PASSWORD:
                if (confirmPasswordBox.charCount > 0) {
                    confirmPasswordBox.input[confirmPasswordBox.charCount - 1] = '\0';
                    confirmPasswordBox.charCount--;
                }
                break;
            }
        }

        DrawText(checkRequirements(passwordBox.input) ? "The password must contains: special character, capital letter and be at least 6 characters long." : "The password must contains: special character, capital letter and be at least 6 characters long.", screenWidth / 2 - MeasureText("Register", 20) / 2 - 240, 430, 13, checkRequirements(passwordBox.input) ? GREEN : RED);   
        if (isMouseOverBox(registerButton)) 
        {
            DrawRectangleRec(registerButton, { 0, 160, 0, 255 }); 
        }
        else 
        {
            DrawRectangleRec(registerButton, GREEN);
        }
        DrawText("Register", screenWidth / 2 - MeasureText("Register", 20) / 2, 487, 20, WHITE);

        // Check if the Register button is clicked
        if (isMouseOverBox(registerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (strcmp(passwordBox.input, confirmPasswordBox.input) == 0 && checkRequirements(passwordBox.input)) {
                
                if (strlen(firstNameBox.input) > 0 && strlen(lastNameBox.input) > 0) {
                    
                    saveUserData(firstNameBox.input, lastNameBox.input, usernameBox.input, passwordBox.input);
                }
            }
        }

        EndDrawing();
    }
}