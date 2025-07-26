#include "raylib.h"


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WINDOW_CAPTION "catan"
#define WINDOW_FPS 60


int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_CAPTION);
    SetWindowMinSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    SetTargetFPS(WINDOW_FPS);

    InitAudioDevice();

    SetRandomSeed(0);

    Image icon = LoadImage("src/data/textures/icon.png");
    SetWindowIcon(icon);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    // Let OS deallocate after application is quit
}

