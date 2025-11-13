#include "game.h"

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
    srand(0);

    Image icon = LoadImage("src/data/textures/icon.png");
    SetWindowIcon(icon);

    Game game = {0};
    game_start(&game);

    float hexagon_height = 90;
    float hexagon_width = hexagon_height * sqrt(3);

    int width = 5;
    int height = 5;
    int offset_x = 200;
    int offset_y = 200;
    bool grid[5][5] = {
        {false, true, true, true, false},
        {true, true, true, true, false},
        {true, true, true, true, true},
        {true, true, true, true, false},
        {false, true, true, true, false}
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (!grid[y][x]) continue;
                DrawPolyLines(
                    (Vector2){
                        ((float)x + ((y % 2) * 0.5)) * hexagon_width + offset_x,
                        (float)y * 3/2 * hexagon_height + offset_y
                    },
                    6,
                    hexagon_height,
                    90,
                    MAGENTA
                );
            }
        }

        EndDrawing();
    }

    // Let OS deallocate program memory itself after application is quit
}

