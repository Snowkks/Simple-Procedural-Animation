#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;

Vector2 target_pos = {(float)SCR_WIDTH/2, (float)SCR_HEIGHT/2};
Vector2 head_pos = {(float)SCR_WIDTH/2, (float)SCR_HEIGHT/2};

float head_speed = 0.55;

int num_segments = 12;
float segment_radius = 30;
float segment_lenght = 20;

struct Segments{
    Vector2 position;
    float size;
};


int main(){

    InitWindow(SCR_WIDTH, SCR_HEIGHT, "procedural animation");
    SetTargetFPS(60);

    //initialize the head and body
    struct Segments segments[num_segments];
    int spawnoffset = 0;
    for(int i = 0; i < num_segments; i++){
        segments[i].position = (Vector2){(float)SCR_WIDTH/2 + spawnoffset , (float)SCR_HEIGHT/2 + spawnoffset};
        segments[i].size = segment_radius - 2 * i;
        spawnoffset += 10;
    }

    while ( !WindowShouldClose() )
    {

        if ( IsMouseButtonDown(1) ){
            target_pos = GetMousePosition();
        }

        Vector2 current_target = head_pos;

        for( int i = 0; i < num_segments; i++ ){

            // Calculate a position for each body segment
            Vector2 dir_to_target = Vector2Subtract(current_target, segments[i].position);
            Vector2 norm_dir = Vector2Normalize(dir_to_target);
            Vector2 offset = Vector2Scale(norm_dir, segment_lenght);
            Vector2 next_pos = Vector2Subtract(current_target, offset);

            segments[i].position = Vector2Lerp(segments[i].position, next_pos, 10 * GetFrameTime());

            current_target = segments[i].position;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw a Head
        DrawCircleLines(head_pos.x, head_pos.y, segment_radius, WHITE);

        // Draw the bodies
        for(int i = 0; i < num_segments; i++){
            DrawCircleLines(segments[i].position.x, segments[i].position.y, segments[i].size, WHITE);
        }

        EndDrawing();

        // Lerp to make movement smoother
        head_pos = Vector2Lerp(head_pos, target_pos, head_speed * GetFrameTime());
    }

    CloseWindow() ;

    return 0;
}

