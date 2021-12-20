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

    Vector2 StaticWraithPos = {500, 300};

    InitWindow(WindowWidth, WindowHeight, "Game title");
    // TODO: what this function actually does
    SetTargetFPS(60);
    // TODO: how we can disable ESC quiting

    int CrabFrame = 0;
    Texture2D Crab[3];
    char* CrabPaths[] =
    {
        "./assets/right_0000.png",
        "./assets/right_0001.png",
        "./assets/right_0002.png",
    };

    for(int i = 0; i < 3; i++)
    {
        Crab[i] = LoadTexture(CrabPaths[i]);
    }

    float AnimationTimer = 0;
    int Frame = 0;
    int Step = 0;
    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_RIGHT)) CrabPosition.x += 2.0f;
        if (IsKeyDown(KEY_LEFT)) CrabPosition.x -= 2.0f;
        if (IsKeyDown(KEY_UP)) CrabPosition.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN)) CrabPosition.y += 2.0f;
        if (IsKeyDown(KEY_SPACE)) CrabPosition.x = 0.0f;
        if(Step == 1)
        {
            CrabPosition.x -= 1.0f;
            Step = 0;
        }

#if 0
        Vector2 Gravity = Vector2{0, +9.8};
        Vector2 ddP = Gravity;

        Vector2 dP = Vector2{dt*ddP.x, dt*ddP.y};

        CrabSpeed = Vector2{CrabSpeed.x + dP.x, CrabSpeed.y + dP.y};
        CrabPosition = Vector2{CrabPosition.x + ddP.x*dt + dt*dt + CrabSpeed.x*dt,
                               CrabPosition.y + ddP.y*dt + dt*dt + CrabSpeed.y*dt};
#endif

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        DrawRectangleV(CrabPosition, CrabDim, CrabColor);
        DrawRectangleV(CrabPosition, Vector2{5, 5}, BLUE);
        DrawRectangleV(Vector2{0, 0}, Vector2{5, 5}, BLUE);

        float Scale = 0.5;
        DrawTextureEx(Crab[0], CrabPosition, 0, Scale, PINK);

        float dt = GetFrameTime();
        AnimationTimer += dt;
        if(AnimationTimer > 0.1)
        {
            AnimationTimer = 0;
            Frame = (Frame + 1) % 12;
            CrabFrame = (CrabFrame + 1) % 3;
        }
        Step++;

        EndDrawing();
//        printf("CrabSpeed: %f %f\n", CrabSpeed.x, CrabSpeed.y);
    }


    return 0;
}
#if 0

enum entity_type
{
    Type_Crab,
    Type_Projectile,
    Type_Grenade,
};

u32 EntityCount;
entity* Entities;

struct entity
{
    /*
        Common

    */
    PhysicsBody b;

    union
    {
        struct
        {
            u32 Health
        } Crab;

        struct
        {
        } Projectile;

        struct
        {
            f32 Radius;
            f32 RemainingTimeUntilExplode;
        } Grenade;

    };
};
#endif
