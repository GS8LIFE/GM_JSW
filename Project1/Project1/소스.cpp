#include <iostream>
#include <conio.h> // _getch 함수를 사용하기 위한 헤더 파일
#include <chrono>
#include <windows.h>
using namespace std;

const int width = 20; // 게임판 너비
const int height = 10; // 게임판 높이

int x, y; // 지렁이의 현재 위치
int fruitX, fruitY; // 먹이의 위치
int score; // 점수
int tailX[100], tailY[100]; // 지렁이 꼬리의 위치 배열
int nTail; // 현재 지렁이의 꼬리 길이

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// 게임 초기화 함수
void Setup()
{
    dir = STOP; // 초기에는 멈춤 상태
    x = width / 2; // 지렁이의 초기 x 위치
    y = height / 2; // 지렁이의 초기 y 위치
    fruitX = rand() % width; // 먹이의 초기 x 위치
    fruitY = rand() % height; // 먹이의 초기 y 위치
    score = 0; // 초기 점수
}

// 게임판 그리기 함수
void Draw()
{
    Sleep(100);
    system("cls"); // 콘솔 창 지우기

    // 상단 벽
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // 중간 부분
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // 좌측 벽

            // 지렁이, 먹이, 빈 공간 출력
            if (i == y && j == x)
                cout << "O"; // 지렁이
            else if (i == fruitY && j == fruitX)
                cout << "*"; // 먹이
            else
            {
                bool printTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // 지렁이의 꼬리
                        printTail = true;
                    }
                }

                if (!printTail)
                    cout << " "; // 빈 공간
            }

            if (j == width - 1)
                cout << "#"; // 우측 벽
        }
        cout << endl;
    }

    // 하단 벽
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // 점수 출력
    cout << "Score:" << score << endl;
}

// 사용자 입력 처리 함수
void Input()
{
    if (_kbhit()) // 키보드 입력이 있는 경우
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            // 게임 종료
            exit(0);
        }
    }
}

// 게임 로직 업데이트 함수
void Logic()
{
    // 지렁이 꼬리의 위치 업데이트
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // 지렁이 이동
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // 지렁이가 벽에 닿았을 때 처리
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // 지렁이가 자기 자신에게 닿았을 때 처리
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            exit(0);

    // 지렁이가 먹이를 먹었을 때 처리
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup(); // 게임 초기화

    while (true)
    {
        Draw(); // 게임판 그리기
        Input(); // 사용자 입력 처리
        Logic(); // 게임 로직 업데이트
    }

    return 0;
}