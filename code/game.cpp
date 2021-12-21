#include <stdio.h>

#include "raylib.h"

#define PHYSAC_IMPLEMENTATION
#include "physac.h"

enum entity_type
{
    Type_Crab,
    Type_Projectile,
    Type_Grenade,
    Type_Box
};

enum weapon_type
{
    Pistol,
    Bow,
    Rifle,
    Shootgun
};

struct entity
{
    float density = 10;
    float crabSize = 50;
    float projectileSize = 5;
    float boxSize = 30;

    entity(Vector2 vec, entity_type type)
    {
        switch (type)
        {
        case Type_Crab:
            b = CreatePhysicsBodyRectangle(vec, crabSize, crabSize, density);
            b->freezeOrient = true;
            break;
        case Type_Projectile:
            b = CreatePhysicsBodyRectangle(vec, projectileSize, projectileSize, density-8);
            break;
        case Type_Box:
            b = CreatePhysicsBodyRectangle(vec, boxSize, boxSize, density+10);
            break;
        default:
            break;
        }
    }
    /*
        Common

    */
    PhysicsBody b;

    // TODO create projectile

    union
    {
        struct
        {
            unsigned int Health;
            weapon_type weapon;
        } Crab;

        struct
        {
        } Projectile;

        struct
        {
            float Radius;
            float RemainingTimeUntilExplode;
        } Grenade;

    };
};

enum
{
    WindowWidth  = 800,
    WindowHeight = 600,
};

int main()
{

    Vector2 CrabPosition = {250, 0};
    Vector2 CrabSpeed = {0, 0};
    Vector2 CrabDim = {20, 20};
    Color CrabColor = RED;

    Vector2 StaticWraithPos = {500, 300};

    InitWindow(WindowWidth, WindowHeight, "Game title");
    // TODO: what this function actually does
    
    InitPhysics();

    entity crabRec(CrabPosition, Type_Crab);
    PhysicsBody floor = CreatePhysicsBodyRectangle({ 800 / 2.0f, (float)450 }, (float)450, 100, 10);
    floor->enabled = false;

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
        UpdatePhysics();     

        if (IsKeyDown(KEY_SPACE)) entity bullet(CrabPosition, Type_Projectile);


        if (IsKeyDown(KEY_RIGHT)) crabRec.b->velocity.x += 0.1f;
        if (IsKeyDown(KEY_LEFT)) crabRec.b->velocity.x -= 0.1f;
        // if (IsKeyDown(KEY_UP)) CrabPosition.y -= 2.0f;
        // if (IsKeyDown(KEY_DOWN)) CrabPosition.y += 2.0f;
        // if (IsKeyDown(KEY_SPACE)) CrabPosition.x = 0.0f;
        if(Step == 10)
        {
            CrabPosition.x -= 0.5f;
            Step = 0;
        }

        if (IsKeyPressed(KEY_R))      // Reset physics input
        {
            // Reset movement physics body position, velocity and rotation
            crabRec.b->position = { 250, 0};
            crabRec.b->velocity = { 0, 0 };
            SetPhysicsBodyRotation(crabRec.b, 0);
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

        float Scale = 0.4;
        DrawTextureEx(Crab[0], {crabRec.b->position.x - 350 * Scale, crabRec.b->position.y - 324 * Scale } , 0, Scale, PINK);
        float dt = GetFrameTime();
        AnimationTimer += dt;
        if(AnimationTimer > 0.1)
        {
            AnimationTimer = 0;
            Frame = (Frame + 1) % 12;
            CrabFrame = (CrabFrame + 1) % 3;
        }
        Step++;

        int bodiesCount = GetPhysicsBodiesCount();
        for (int i = 0; i < bodiesCount; i++)
        {
            PhysicsBody body = GetPhysicsBody(i);

            int vertexCount = GetPhysicsShapeVerticesCount(i);
            for (int j = 0; j < vertexCount; j++)
            {
                // Get physics bodies shape vertices to draw lines
                // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                DrawLineV(vertexA, vertexB, BLACK);     // Draw a line between two vertex positions
            }
        }

        EndDrawing();
    }

    ClosePhysics();

    CloseWindow(); 

    return 0;
}
#if 1





#endif
