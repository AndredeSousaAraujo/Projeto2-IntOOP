#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
using namespace std;

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

int lenX = 8;
int lenY = 10;
int totalX = 2*(lenX+2);
int totalY = lenY+2;

bool gameOver = false;


enum eDirecao { ESQUERDA = 0, DIREITA, CIMA, BAIXO };
eDirecao dir;

void tela(int X, int Y)
{
    
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
            display[Y][2*X] = 'C';
            
            cout << display[i][j];
        }
        cout << endl;
    }
}


int main(){

    int i = 2;
    int x = 2;
    int y = 1;
    int c = 1;
    dir = DIREITA;

    //tela(x,y);

    while (!gameOver) {
        
        if(kbhit()){
            char tecla = getch();

            while(kbhit()) getch();


            switch(tecla){
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

        switch(dir){
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

        if(x == 0 || y == 0 || x == lenX+1 || y == lenY+1){
            gameOver = true;
            break;
        }

        system("clear");
        cout << "Tela " << i << endl;
        tela(x,y);
        usleep(500000);

        i++;

    }

    cout << endl << "Game Over na tela " << i << endl;


}

