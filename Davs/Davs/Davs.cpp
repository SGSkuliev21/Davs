#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Davs");

    Image image1 = LoadImage("Davs/img/brown.png");
    Texture2D texture1 = LoadTextureFromImage(image1);
    UnloadImage(image1);

    Image image2 = LoadImage("Davs/img/ginger.png");
    Texture2D texture2 = LoadTextureFromImage(image2);
    UnloadImage(image2);

    Vector2 imagePosition = { (float)(screenWidth - texture1.width) / 2, (float)(screenHeight - texture1.height) / 2 };

    bool showForwardArrow = false;
    bool showBackwardArrow = false;

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Rectangle forwardArrowBounds = { 10, 10, 30, 30 };
            Rectangle backwardArrowBounds = { screenWidth - 40, 10, 30, 30 };
            Vector2 mousePoint = GetMousePosition();

            if (CheckCollisionPointRec(mousePoint, forwardArrowBounds)) {
                UnloadTexture(texture1);
                texture1 = texture2;
            }
            else if (CheckCollisionPointRec(mousePoint, backwardArrowBounds)) {
                UnloadTexture(texture1);
                texture1 = LoadTextureFromImage(image1);
            }

            showForwardArrow = true;
            showBackwardArrow = true;
        }
        else {
            showForwardArrow = false;
            showBackwardArrow = false;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (showForwardArrow) {
            DrawText(">", 15, 15, 20, BLACK);
            DrawRectangle(10, 10, 30, 30, WHITE);
        }

        if (showBackwardArrow) {
            DrawText("<", screenWidth - 35, 15, 20, BLACK);
            DrawRectangle(screenWidth - 40, 10, 30, 30, WHITE);
        }

        DrawTexture(texture1, static_cast<int>(imagePosition.x), static_cast<int>(imagePosition.y), WHITE);

        EndDrawing();
    }
    UnloadTexture(texture1);
    UnloadTexture(texture2);

}