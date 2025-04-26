#include <stdio.h>


void MovimentoTorre(){

    for (int i = 1; i <= 5; i++)
    {
        printf("Direita \n");

    }
}

void movimentoBispo(){

    int i = 1;

    while (i <= 5)
    {
        printf("Cima, Direita \n");

       i++;
    }

}

void movimentoRainna(){

    int i = 1;
    
    do
    {
        printf("Esquerda \n");
        i++;

    } while (i <= 8);
    

}


/*



void movimentoCavalo(){

}

*/


int main()
{
    
    
    printf("\nMOVIMENTO TORRE \n");
    MovimentoTorre();

    printf("\nMOVIMENTO BISPO \n");
    movimentoBispo();

    printf("\nMOVIMENTO RAINHA \n");
    movimentoRainna();

    //movimentoCavalo();
    
    /* code */
    return 0;
}
