#pragma once
#include <iostream>
#include <vector>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
using namespace std;


class Jogo{
    protected:
        int lenX = 8;
        int lenY = 6;
        int totalX = 2 * (lenX + 2);
        int totalY = lenY + 2;
        int frame = 1;
        bool gameOver = false;

    public:
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

    

        void framecounter(){
            frame++;
        }

         virtual void tela(){
            system("clear");
            framecounter();
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
                    
                    cout << display[i][j];
                }
                cout << endl;
            }
        }
};