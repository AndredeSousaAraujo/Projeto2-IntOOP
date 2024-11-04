#include <iostream>
#include <unistd.h>
using namespace std;

int totalX = 8;
int totalY = 2*8-1;

void tela(int Y, int X)
{
    char display[totalX][totalY];

    for (int i = 0; i < totalX; i++) 
    {      
        for (int j = 0; j < totalY; j++){
                if((i==0 && j%2==0)|| j==0 || (i==totalX-1 && j%2==0) || j==totalY-1){
                     display[i][j] = '*';
                }
                else{
                    display[i][j] = ' ';
                }
            display[X][2*Y] = 'C';
            
            cout << display[i][j];
         }
        cout << endl;
    }
}

int main(){

int i = 1;

while (i < totalX-1) {
    system("clear");
    tela(i,1);
    usleep(500000);
    i++;
}

cout << endl << "Game Over!";


}