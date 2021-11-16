#include <stdio.h>
#include "raylib.h"

enum
{
    WindowWidth  = 800,
    WindowHeight = 600,
};

int main()
{

    Vector2 CrabPosition = {300, 300};
    Vector2 CrabSpeed = {0, 0};
    Vector2 CrabDim = {20, 20};
    Color CrabColor = RED;

    InitWindow(WindowWidth, WindowHeight, "Game title");
    // TODO: what this function actually does
    SetTargetFPS(60);
    // TODO: how we can disable ESC quiting
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_RIGHT)) CrabPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) CrabPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) CrabPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) CrabPosition.y += 2.0f;
        if (IsKeyDown(KEY_SPACE)) CrabPosition.y = 0.0f;

        Vector2 Gravity = Vector2{0, +9.8};
        Vector2 ddP = Gravity;

        Vector2 dP = Vector2{dt*ddP.x, dt*ddP.y};

        CrabSpeed = Vector2{CrabSpeed.x + dP.x, CrabSpeed.y + dP.y};
        CrabPosition = Vector2{CrabPosition.x + ddP.x*dt + dt*dt + CrabSpeed.x*dt,
                               CrabPosition.y + ddP.y*dt + dt*dt + CrabSpeed.y*dt};

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        DrawRectangleV(CrabPosition, CrabDim, CrabColor);
        DrawRectangleV(CrabPosition, Vector2{5, 5}, BLUE);
        DrawRectangleV(Vector2{0, 0}, Vector2{5, 5}, BLUE);
        EndDrawing();
        printf("CrabSpeed: %f %f\n", CrabSpeed.x, CrabSpeed.y);
    }


    return 0;
}
