#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <random>
#include <vector>
#include <time.h>

using namespace std;

vector<Color> colors;
vector<Sound> weeknd;
const int screenWidth = 800;
const int screenHeight = 600;


int main(void) {
ChangeDirectory("/Users/joshuajenkins/Desktop/Personal\ Projects/Balls");
cout << GetWorkingDirectory() << endl;
InitAudioDevice();
srand(time(NULL));
for (int i = 0; i < 2; i++) {
    weeknd.push_back(LoadSound("audio/long_F.wav")); weeknd.push_back(LoadSound("audio/long_F.wav")); weeknd.push_back(LoadSound("audio/Eb.wav")); weeknd.push_back(LoadSound("audio/short_F.wav")); weeknd.push_back(LoadSound("audio/G.wav")); weeknd.push_back(LoadSound("audio/C.wav")); weeknd.push_back(LoadSound("audio/long_Eb.wav")); 
}
for (int i = 0; i < 2; i++) {
    weeknd.push_back(LoadSound("audio/Bb.wav"));weeknd.push_back(LoadSound("audio/G.wav"));weeknd.push_back(LoadSound("audio/short_F.wav"));weeknd.push_back(LoadSound("audio/long_Eb.wav"));
}
weeknd.push_back(LoadSound("audio/Long_F.wav"));
colors.push_back(RED); colors.push_back(BLUE); colors.push_back(GREEN); colors.push_back(WHITE); colors.push_back(MAGENTA); colors.push_back(YELLOW); colors.push_back(VIOLET); colors.push_back(LIGHTGRAY); colors.push_back(ORANGE); colors.push_back(LIME); colors.push_back(BROWN); colors.push_back(SKYBLUE);

struct ball {
        ball(): ball_x(400), ball_y(300), ball_radius(10), x_speed(rand()%5+1), y_speed(rand()%5+1) { 
            if (rand()%2 == 0) {
                x_speed*=-1;
            }
            if (rand()%2 == 0) {
                y_speed*=-1;
            }
            col = colors[rand()%colors.size()];
        }

        void move() {
            ball_x += x_speed;
            ball_y += y_speed;
        }

        bool checkEdge() {
            bool increase = false;
            if(ball_x + ball_radius >= screenWidth  || ball_x - ball_radius <= 0)
            {
                if (ball_x + ball_radius >= screenWidth) {
                    ball_x = screenWidth-ball_radius-1;
                } else {
                    ball_x = ball_radius+1;
                }
                x_speed *= -1;
                int r = rand()%3;
                if (r == 0 && x_speed <= 10) {
                    x_speed+=1;
                } else if (r == 1 && x_speed >= -10) {
                    x_speed-=1;
                }
                increase = true;
            }
            if(ball_y + ball_radius >= screenHeight  || ball_y - ball_radius <= 0)
            {
                if (ball_y + ball_radius >= screenHeight) {
                    ball_y = screenHeight-ball_radius-1;
                } else {
                    ball_y = ball_radius+1;
                }
                y_speed *= -1;
                int r = rand()%3;
                if (r == 0 && y_speed <= 10) {
                    y_speed+=1;
                } else if (r == 1 && y_speed >= -10) {
                    y_speed-=1;
                }
                increase = true;
            }

            if (increase) {
                ball_radius++;
                return true;
            }
            return false;
        }

        void drawBall() {
            DrawCircle(ball_x,ball_y,ball_radius, col);
        }


        int ball_x;
        int ball_y;
        int ball_radius;
        int x_speed;
        int y_speed;
        Color col;
    };
    vector<Sound>::iterator soundIt = weeknd.begin();
    InitWindow(screenWidth, screenHeight, "balls");
    SetTargetFPS(60);
    vector<ball> balls;
    balls.push_back(ball());

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < balls.size(); i++) {
            balls[i].move();
            if (balls[i].checkEdge() && rand()%10 == 0) {
                balls.push_back(ball());
                PlaySound(*soundIt);
                soundIt++;
                if (soundIt == weeknd.end()) {
                    soundIt = weeknd.begin();
                }

            }
            balls[i].drawBall();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

