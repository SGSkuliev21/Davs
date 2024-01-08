//#include "bank.h"
//
//BankSimulation::BankSimulation() : isLoggedIn(false) {}
//
//void BankSimulation::Run() {
//    const int screenWidth = 800;
//    const int screenHeight = 600;
//    InitWindow(screenWidth, screenHeight, "Davs Bank Simulation");
//
//    while (!WindowShouldClose()) {
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//
//        if (!isLoggedIn) {
//            mainMenu.Draw();
//
//            if (mainMenu.CheckRegisterPressed()) {
//                // Transition to Register menu
//                registerMenu.ResetInputs();
//                registerMenu.Draw();
//
//                if (registerMenu.CheckReturnPressed()) {
//                    // Return to the main menu
//                }
//            }
//            else if (mainMenu.CheckLoginPressed()) {
//                // Transition to Login menu
//                loginMenu.ResetInputs();
//                loginMenu.Draw();
//
//                if (loginMenu.CheckReturnPressed()) {
//                    // Return to the main menu
//                }
//                else if (loginMenu.CheckLoginPressed()) {
//                    // Implement logic for handling successful login
//                    isLoggedIn = true;
//                }
//            }
//            else if (mainMenu.CheckExitPressed()) {
//                // Exit the program
//            }
//        }
//        else {
//            // Implement logic for handling actions after login
//        }
//
//        EndDrawing();
//    }
//}