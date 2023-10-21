#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

const int height = 21;
const int width = 21;
int slength;
int sposx[height * width] = {};
int sposy[height * width] = {};
int score;

string filler = "🟩";
string apple = "🍎";
string body = "🔵";
string head = "🟦";
string back[height][width] = {};

int main();

void Print()
{
    system("clear");
    
    for (int y = 0; y <= height - 1; y++)
    {
        for (int x = 0; x <= width - 1; x++) { cout << back[y][x]; }
        cout << "\n";
    }

    cout << apple << " : " << score << "\n";
    return;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    printf("\33[2K\r");
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

void SnakeMove(int x, int y)
{
    for (int i = slength + score; i > 0; i--)
    {
        sposx[i] = sposx[i - 1];
        sposy[i] = sposy[i - 1];
        back[sposy[i]][sposx[i]] = body;
    }
    
    back[sposy[score + slength]][sposx[score + slength]] = filler;
    sposx[0] += x;
    sposy[0] -= y;

    if (sposx[0] == -1 || sposx[0] == width || sposy[0] == -1 || sposy[0] == height || back[sposy[0]][sposx[0]] == body)
    {
        system( "paplay death.mp3 &");
        for (;;)
        {
            system("clear");
            cout << "⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬛⬛\n⬛⬛⬛⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬛⬛⬛\n⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛\n⬛⬛⬛⬛⬛⬜⬛⬛⬜⬜⬜⬜⬜⬛⬛⬜⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬜⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬜⬛⬛⬛⬜⬛⬛⬛⬜⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬜⬜⬛⬜⬜⬜⬛⬜⬜⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬛⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬜⬛⬛⬜⬛⬜⬛⬜⬛⬛⬜⬛⬛⬛⬛⬛\n⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛\n⬛⬛⬛⬜⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬜⬛⬛⬛\n⬛⬛⬛⬛⬜⬜⬛⬛⬛⬛⬛⬛⬛⬛⬛⬜⬜⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\n⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛⬛\nYOU LOST!!! You Score Was : " << score << "\n";
            cout << "Press Enter To Play Again...";
            char input = (char)getchar();
            printf("\33[2K\r");
            if (input != 'w' && input != 'a' && input != 's' && input != 'd') { main(); }
        }
    }

    if (back[sposy[0]][sposx[0]] == apple)
    {
        system( "paplay applebite.mp3 &");
        int a = rand() % (width - 1) + 1;
        int b = rand() % (height - 1) + 1;
        while (back[b][a] != filler)
        {
            a = rand() % (width - 1) + 1;
            b = rand() % (height - 1) + 1;
        }
        back[b][a] = apple;
        score++;

    }
    back[sposy[0]][sposx[0]] = head;
    return;
}

int main()
{
    int a = 0;
    int b = 0;
    char direction;
    slength = 4;
    score = 0;
    sposx[0] = width / 5;
    sposy[0] = height / 2;
    srand(time(NULL));

    for (int y = 0; y <= height - 1; y++)
    {
        for (int x = 0; x <= width - 1; x++) { back[y][x] = filler; }
    }

    for (int i = 1; i < slength; i++) { SnakeMove(1, 0); }
    back[sposy[0]][4 * width / 5] = apple;
    Print();
    printf("\x1b[A\33[2K\r");
    cout << "Use W A S D To Move\n";

    for (;;)
    {
        while (!kbhit());
        char output = (char)getchar();
        if (output != 'w' && output != 's' && output != 'd') { continue; }
        if (output == 'w') { a = 0; b = 1; }
        if (output == 's') { a = 0; b = -1; }
        if (output == 'd') { a = 1; b = 0; }
        direction = output;
        break;
    }

    for (;;)
    {
        while (!kbhit())
        {
            SnakeMove(a, b);
            Print();
            usleep(120000);
        };
        char output = (char)getchar();
        if (output != 'w' && output != 'a' && output != 's' && output != 'd' || output == direction) { continue; }
        if (output == 'w' && direction != 's') { a = 0; b = 1; }
        if (output == 'a' && direction != 'd') { a = -1; b = 0; }
        if (output == 's' && direction != 'w') { a = 0; b = -1; }
        if (output == 'd' && direction != 'a') { a = 1; b = 0; }
        direction = output;
        system( "paplay turn.mp3 &");
        SnakeMove(a, b);
        Print();
        usleep(120000);
    }
    return 0;
}