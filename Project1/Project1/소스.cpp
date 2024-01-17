#include <iostream>
#include <conio.h> // _getch �Լ��� ����ϱ� ���� ��� ����
#include <chrono>
#include <windows.h>
using namespace std;

const int width = 20; // ������ �ʺ�
const int height = 10; // ������ ����

int x, y; // �������� ���� ��ġ
int fruitX, fruitY; // ������ ��ġ
int score; // ����
int tailX[100], tailY[100]; // ������ ������ ��ġ �迭
int nTail; // ���� �������� ���� ����

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// ���� �ʱ�ȭ �Լ�
void Setup()
{
    dir = STOP; // �ʱ⿡�� ���� ����
    x = width / 2; // �������� �ʱ� x ��ġ
    y = height / 2; // �������� �ʱ� y ��ġ
    fruitX = rand() % width; // ������ �ʱ� x ��ġ
    fruitY = rand() % height; // ������ �ʱ� y ��ġ
    score = 0; // �ʱ� ����
}

// ������ �׸��� �Լ�
void Draw()
{
    Sleep(100);
    system("cls"); // �ܼ� â �����

    // ��� ��
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // �߰� �κ�
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // ���� ��

            // ������, ����, �� ���� ���
            if (i == y && j == x)
                cout << "O"; // ������
            else if (i == fruitY && j == fruitX)
                cout << "*"; // ����
            else
            {
                bool printTail = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // �������� ����
                        printTail = true;
                    }
                }

                if (!printTail)
                    cout << " "; // �� ����
            }

            if (j == width - 1)
                cout << "#"; // ���� ��
        }
        cout << endl;
    }

    // �ϴ� ��
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // ���� ���
    cout << "Score:" << score << endl;
}

// ����� �Է� ó�� �Լ�
void Input()
{
    if (_kbhit()) // Ű���� �Է��� �ִ� ���
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
            // ���� ����
            exit(0);
        }
    }
}

// ���� ���� ������Ʈ �Լ�
void Logic()
{
    // ������ ������ ��ġ ������Ʈ
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

    // ������ �̵�
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

    // �����̰� ���� ����� �� ó��
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // �����̰� �ڱ� �ڽſ��� ����� �� ó��
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            exit(0);

    // �����̰� ���̸� �Ծ��� �� ó��
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
    Setup(); // ���� �ʱ�ȭ

    while (true)
    {
        Draw(); // ������ �׸���
        Input(); // ����� �Է� ó��
        Logic(); // ���� ���� ������Ʈ
    }

    return 0;
}