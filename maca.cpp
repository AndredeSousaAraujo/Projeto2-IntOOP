#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "jogo.cpp"
using namespace std;



class Maca: public Jogo{
    protected:
        int macaX;
        int macaY;
    public:
        Maca(){
            geraMaca(3,3);
        }

        void geraMaca(int macaX, int macaY){
            this-> macaX = (rand() % lenX) + 1;
            this-> macaY = (rand() % lenY) + 1;
        }
        

        int getMacaX(){
            return macaX;
        }

        int getMacaY(){
            return macaY;
        }

        
};
