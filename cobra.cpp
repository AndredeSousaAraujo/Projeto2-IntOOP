#pragma once
#include <iostream>
#include <vector>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>
#include "jogo.cpp"
#include "maca.cpp"
using namespace std;

class Cobra : public Jogo{
    protected:
        vector<int> posx;
        vector<int> posy;
        int x = posx[0];
        int y = posy[0];
        bool gameOver = false;
        Maca maca;
        enum eDirecao { ESQUERDA = 0, DIREITA, CIMA, BAIXO, PARADO};
            eDirecao dir;
        


    public:
        Cobra(vector<int> posx , vector<int> posy):
        posx{posx}, posy{posy} {}      


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

        bool checagameOver()
        {
            for (int b = 1; b < posx.size(); b++)
            {
                if (posx[b] == posx[0] && posy[b] == posy[0])
                {
                    return true;
                    break;
                }
            }
            if(posx[0] == 0 || posy[0] == 0 || posx[0] == lenX+1 || posy[0] == lenY+1)
            {
                return true;
            }

            return false;
        }

    void comeuMaca(){
        if(posx[0] == maca.getMacaX() && posy[0] == maca.getMacaY())
        {
            bool corpo;
            do{
                maca.geraMaca(maca.getMacaX(), maca.getMacaY());
                corpo = false;

                for(int i = 0; i<posx.size(); i++){
                    if(posx[i] == maca.getMacaX() && posy[i] == maca.getMacaY()){
                        corpo = true;
                        break;
                    }
                }
            }while(corpo);
        }
       
        else
        {
            posx.pop_back();
            posy.pop_back();
        }
        
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
                    for (size_t i = 0; i < posx.size(); i++) {
                        int xl = posx[i];
                        int yl = posy[i];

                        if(i==0){
                            display[yl][2*xl] = 'C';
                        }
                        else{
                            display[yl][2*xl] = 'o';
                        }
                        
                        display[maca.getMacaY()][2*maca.getMacaX()] = '+';
                        
                        
                    }
                    
                    cout << display[i][j];
                }
                cout << endl;
            
            }
        }
                  
};

