#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <vector>
using namespace std;

int snk_len = 2;
vector<int> posx = {4, 4, 4, 4};
vector<int> posy = {4, 5, 6, 7};
int lenX = 8;
int lenY = 10;
int totalX = 2*(lenX+2);
int totalY = lenY+2;

bool gameOver = false;


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


// void tela(const vector<int>& vectorX, const vector<int>& vectorY) {
//     char display[totalY][totalX];

//     // Preenche a tela com espaços vazios
//     for (int i = 0; i < totalY; i++) {
//         for (int j = 0; j < totalX; j++) {
//             display[i][j] = ' ';
//         }
//     }

//     // Desenha as bordas da tela
//     for (int i = 0; i < totalY; i++) {
//         for (int j = 0; j < totalX; j++) {
//             if (i == 0 || j == 0 || j == totalX - 1 || i == totalY - 1) {
//                 display[i][j] = '*';  // Bordas
//             }
//         }
//     }

//     // Desenha a cobrinha com base nas coordenadas nos vetores X e Y
//     for (size_t i = 0; i < vectorX.size(); i++) {
//         int x = vectorX[i];
//         int y = vectorY[i];

//         // Certifique-se de que as coordenadas estão dentro dos limites da tela
//         // if (x >= 1 && x < totalX - 1 && y >= 1 && y < totalY - 1) {
//         display[y][2*x] = 'C';  // Coloca a "cabeça" da cobrinha na posição correta
//         // }
//     }

//     // Exibe a tela
//     for (int i = 0; i < totalY; i++) {
//         for (int j = 0; j < totalX; j++) {
//             cout << display[i][j];
//         }
//         cout << endl;
//     }
// }

void tela(const vector<int>& vectorX, const vector<int>& vectorY)
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
            for (size_t i = 0; i < vectorX.size(); i++) {
                int xl = vectorX[i];
                int yl = vectorY[i];

                // Certifique-se de que as coordenadas estão dentro dos limites da tela
                // if (x >= 1 && x < totalX - 1 && y >= 1 && y < totalY - 1) {
                display[yl][2*xl] = 'C';  // Coloca a "cabeça" da cobrinha na posição correta
                // }
            }
            
            cout << display[i][j];
        }
        cout << endl;
    }
}

// void tela(const X, int Y)
// {
    
//     char display[totalY][totalX];


//     for (int i = 0; i < totalY; i++) 
//     {      
//         for (int j = 0; j < totalX; j++){
//                 if(i==0 && j%2==0 || j==0 || j==totalX-2 || i==totalY-1 && j%2==0){
//                 display[i][j] = '*';
//                 }
        
//                 else{
//                     display[i][j] = ' ';
//                 }
//             display[Y][2*X] = 'C';
            
//             cout << display[i][j];
//         }
//         cout << endl;
//     }
// }


// se nao maça insert+popback
// se maça só insert

int x = posx[0];
int y = posy[0];

int main(){

    int i = 1; 
    int c = 1;
    dir = CIMA;


    while (true) {

        

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


        if(i>1){
            switch(dir){
                case ESQUERDA:
                    x--;
                    posx[0] = posx[0]-1;
                    break;
                case DIREITA:
                    x++;
                    posx[0] = posx[0]+1;
                    break;
                case CIMA:
                    y--;
                    posy[0] = posy[0]-1;
                    break;
                case BAIXO:
                    y++;
                    posy[0] = posy[0]+1;
                    break;
                default:
                    break;
            }
        }

        for (int b = 1; b < posx.size(); b++) {
            if (posx[b] == posx[0] && posy[b] == posy[0]) {
                gameOver = true;
                break;
            }
        }


        if(posx[0] == 0 || posy[0] == 0 || posx[0] == lenX+1 || posy[0] == lenY+1){
            gameOver = true;
        }
        
        if(gameOver==true){
            break;
        }
        

        system("clear");
        cout << "Tela " << i << endl;
        
        tela(posx, posy);
        
        if(i%3==0){
            posx.insert(posx.begin(), x);
            posy.insert(posy.begin(), y);
        }
        else{
            posx.insert(posx.begin(), x);
            posx.pop_back();
            posy.insert(posy.begin(), y);
            posy.pop_back();
        }
        

        

        usleep(500000);

        i++;

    }

    cout << endl << "Game Over na tela " << i << endl;


}

