#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <vector>
using namespace std;

vector<int> posx = {4, 4, 4, 4};
vector<int> posy = {4, 5, 6, 7};
int lenX = 8;
int lenY = 10;
int totalX = 2*(lenX+2);
int totalY = lenY+2;
int x = posx[0];
int y = posy[0];
bool gameOver = false;
int macaX = 6;
int macaY = 6;

enum eDirecao { ESQUERDA = 0, DIREITA, CIMA, BAIXO, PARADO};
eDirecao dir;

int getch(){
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int kbhit(){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


void tela(const vector<int>& vectorX, const vector<int>& vectorY, int macaX, int macaY, int frame)
{
    system("clear");
    cout << "Tela " << frame << endl;
    char display[totalY][totalX];


    for (int i = 0; i < totalY; i++) 
    {      
        for (int j = 0; j < totalX; j++){
                if(i==0 && j%2==0 || j==0 || j==totalX-2 || i==totalY-1 && j%2==0){
                display[i][j] = '*';
                }
        
                else{
                    display[i][j] = ' ';
                }
            for (size_t i = 0; i < vectorX.size(); i++) {
                int xl = vectorX[i];
                int yl = vectorY[i];

                if(i==0){
                    display[yl][2*xl] = 'C';
                }
                else{
                    display[yl][2*xl] = 'o';
                }
                
                display[macaY][2*macaX] = '+';
                
                
            }
            
            cout << display[i][j];
        }
        cout << endl;
    }
}

void recebeTecla()
{
    if(kbhit())
    {
        char tecla = getch();

        while(kbhit()) getch();


        switch(tecla)
        {
            case 'a':
                dir = ESQUERDA;
                break;
            case 'd':
                dir = DIREITA;
                break;
            case 'w':
                dir = CIMA;
                break;
            case 's':
                dir = BAIXO;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void mudaDirecao()
{
    switch(dir)
    {
        case ESQUERDA:
            x--;
            break;
        case DIREITA:
            x++;
            break;
        case CIMA:
            y--;
            break;
        case BAIXO:
            y++;
            break;
        default:
            break;
    }
    posx.insert(posx.begin(), x);
    posy.insert(posy.begin(), y);
}

void checagameOver()
{
    for (int b = 1; b < posx.size(); b++)
    {
        if (posx[b] == posx[0] && posy[b] == posy[0])
        {
            gameOver = true;
            break;
        }
    }
    if(posx[0] == 0 || posy[0] == 0 || posx[0] == lenX+1 || posy[0] == lenY+1)
    {
        gameOver = true;
    }
}

bool geraMaca(int x, int y)
    {  
        for (int i = 0; i < posx.size(); ++i) 
        {
            if (posx[i] == x && posy[i] == y) 
            {
                return true;
            }
        }
        return false;
    };

void comeuMaca(){
    if(posx[0] == macaX && posy[0] == macaY)
        {
            while(geraMaca(macaX, macaY))
            {
                macaX = (rand() % lenX) + 1;
                macaY = (rand() % lenY) + 1;    
            }
        }
        else
        {
            posx.pop_back();
            posy.pop_back();
        }
}

int main(){

    int i = 1; 
    dir = CIMA;


    while (true)
    {
        recebeTecla();

        mudaDirecao();

        comeuMaca();

        checagameOver();
        if(gameOver){
            break;
        }

        tela(posx, posy, macaX, macaY, i);

        usleep(500000);

        i++;
    }

    cout << endl << "Game Over na tela " << i << endl;


}

