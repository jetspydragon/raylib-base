#include "raylib.h"
#include <string>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void);

constexpr Color CELESTE{37, 177, 247, 255};

struct Player {
    float x;
    float y;
    float r;
    float speed;
};
struct Axe {
    float x;
    float y;
    float w;
    float h;
    float speed;
    float dir = 1;
};

constexpr int width{800};
constexpr int height{600};

bool gameOver = false;
Player player = Player{width*.2f, (float)height/2, 30.f, 10.f};
Axe axe = Axe{(float)width/2 - 40/2, 0, 40, 40, 20};

int main() {
    std::string title{"Raylib!"};
    InitWindow(width, height, title.c_str());

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void) {
    BeginDrawing();
    ClearBackground(CELESTE);

    DrawCircle(player.x, player.y, player.r, RED);
    DrawRectangle(axe.x, axe.y, axe.w, axe.h, YELLOW);

    if (!gameOver) {
        // Axe
        axe.y += axe.speed * axe.dir;
        if (axe.y > height - axe.h || axe.y < 0) {
            axe.dir *= -1;
        }

        // Player
        if (IsKeyDown(KEY_LEFT)) {
            player.x -= player.speed;
        } else if (IsKeyDown(KEY_RIGHT)) {
            player.x += player.speed;
        }
        if (IsKeyDown(KEY_UP)) {
            player.y -= player.speed;
        } else if (IsKeyDown(KEY_DOWN)) {
            player.y += player.speed;
        }
        if (player.x > width - player.r) player.x = width - player.r;
        if (player.x < player.r) player.x = player.r;
        if (player.y > height - player.r) player.y = height - player.r;
        if (player.y < player.r) player.y = player.r;

        // Collision
        bool isColliding = player.x + player.r > axe.x 
            && player.x - player.r < axe.x + axe.w 
            && player.y + player.r > axe.y 
            && player.y - player.r < axe.y + axe.h;
        if (isColliding) {
            gameOver = true;
        }
    } else {
        DrawText("Game Over!!", 37, 53, 50, BLACK);
        DrawText("Game Over!!", 40, 50, 50, ORANGE);
        DrawText("Press <R> to restart...", 38, 122, 20, BLACK);
        DrawText("Press <R> to restart...", 40, 120, 20, ORANGE);
        if (IsKeyPressed(KEY_R)) {
            // Restart game
            gameOver = false;
            player.x = width*.2f;
            player.y = height/2;
            axe.y = width/2 - 40/2;
        }
    }

    EndDrawing();
}