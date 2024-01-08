//#include "LoginMenu.h"
//
//LoginMenu::LoginMenu() : isActive(false), returnButton({ 50, 400, 100, 50 }), loginButton({ 50, 400, 100, 50 }) {}
//
//void LoginMenu::Draw() {
//    DrawText("Login", 50, 50, 30, BLACK);
//    DrawText("Username:", 60, 150, 20, BLACK);
//    DrawText(usernameInput.c_str(), 60, 180, 20, BLACK);
//
//    DrawText("Password:", 60, 230, 20, BLACK);
//    DrawText(passwordInput.c_str(), 60, 260, 20, BLACK);
//
//    // Simulate text input for username and password
//    // ... (Same as before)
//
//    DrawRectangleRec(returnButton, LIGHTGRAY);
//    DrawRectangleRec(loginButton, LIGHTGRAY);
//
//    DrawText("Return to Menu", 60, 410, 20, BLACK);
//    DrawText("Login", 60, 410, 20, BLACK);
//}
//
//bool LoginMenu::CheckReturnPressed() const {
//    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), returnButton);
//}
//
//bool LoginMenu::CheckLoginPressed() const {
//    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), loginButton);
//}
//
//const std::string& LoginMenu::GetUsernameInput() const {
//    return usernameInput;
//}
//
//const std::string& LoginMenu::GetPasswordInput() const {
//    return passwordInput;
//}
//
//void LoginMenu::ResetInputs() {
//    usernameInput = "";
//    passwordInput = "";
//}