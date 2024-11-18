#include <iostream>
#include "jogo.cpp"
#include "cobra.cpp"



int main(){

   srand(static_cast<unsigned>(time(0)));

    int i = 1; 
    
    Cobra cobra({4}, {4});

    while (true)
    {   
        
        
        cobra.recebeTecla();

        cobra.mudaDirecao();

        cobra.comeuMaca();
        
        if(cobra.checagameOver())
            break;

        cobra.tela();

        usleep(500000);

        i++;
    }

   cout << endl << "Game Over na tela " << i << endl;
  
  return 0;  
}