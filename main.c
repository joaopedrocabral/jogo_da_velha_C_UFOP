#include <stdio.h>
#include <stdlib.h>

#define RED   "\033[31m"
#define GREEN "\033[32m"
#define BLUE  "\033[34m"
#define RESET "\033[0m"


void exibir_menu(){ //Exibi o menu inicial
    printf("\n========== MENU ==========\n");
    printf("\n1 - Novo Jogo");
    printf("\n0 - Sair\n");
    printf("\nEscolha uma opcao: ");
}

void reset_jogo(char tab[3][3]){ //Reseta o jogo, limpando todas posições
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tab[i][j] = ' ';
        }
    }
}

void exibir_tab(char tab[3][3]) { //Exibi a tabela

    printf("    ");
    printf(RED "0   1   2" RESET "\n");

    for (int i = 0; i < 3; i++) {

        printf(" ");
        printf(RED "%d" RESET " ", i);

        printf(" %c |", tab[i][0]);
        printf(" %c |", tab[i][1]);
        printf(" %c ",  tab[i][2]);
        printf("\n");

        if (i < 2) {
            printf("   ---+---+---\n");
        }
    }
}


int verificar_resultado(char tab[3][3], char simbolo){ //Verifica se há um ganhador

    // Verifica linhas
    for (int i = 0; i < 3; i++)
    {
        if (tab[i][0] == simbolo &&
            tab[i][1] == simbolo &&
            tab[i][2] == simbolo)
        {
            return 1;
        }
    }

    //Verifica colunas
    for (int j = 0; j < 3; j++)
    {
        if (tab[0][j] == simbolo &&
            tab[1][j] == simbolo &&
            tab[2][j] == simbolo)
        {
            return 1;
        }
    }

    //Verifica diagonal principal
    if (tab[0][0] == simbolo &&
        tab[1][1] == simbolo &&
        tab[2][2] == simbolo)
    {
        return 1;
    }

    //Verifica diagonal segundaria
    if (tab[0][2] == simbolo &&
        tab[1][1] == simbolo &&
        tab[2][0] == simbolo)
    {
        return 1;
    }

    //Caso não houver ganhador
    return 0;
}

void novo_jogo(char tab[3][3]){ //Inicia um novo jogo
    int rodadas = 0;
    int jogador = 1;
    int vencedor = 0;
    char nome1[20];
    char nome2[20];
    char simbolo;

    reset_jogo(tab);

    printf("\nDigite o nome para o Jogador 1: ");
    scanf(" %19s", nome1);

    printf("\nDigite o nome do Jogador 2: ");
    scanf(" %19s", nome2);

    while(rodadas < 10){

        system("clear");

        exibir_tab(tab);

        //Defini (X) para jogador 1 e (O) para jogador 2
        if(jogador == 1){
            simbolo = 'X';
            printf(BLUE"\nVez de %s (X)\n"RESET, nome1);
        } else {
            simbolo = 'O';
            printf(GREEN"\nVez de %s (O)\n"RESET, nome2);
        }

        int linha, coluna;
        int posicao_valida;

        //Verifica se a posição escolhida é válida
        do {
            posicao_valida = 1;

            printf("\nDigite a linha e coluna (0 0): ");
            scanf(" %d %d", &linha, &coluna);
            
            if(linha < 0 || linha > 2 || coluna < 0 || coluna > 2){
                printf("\nPosicao Invalida. Tente novamente!");
                posicao_valida = 0;
            } else if(tab[linha][coluna] != ' '){
                printf("\nPosicao ocupada. Tente novamente!");
                posicao_valida = 0;
            } else {
                tab[linha][coluna] = simbolo;
            }

        } while(!posicao_valida);

        rodadas++;

        //Verifica se até o momento existe ganhador
        if(verificar_resultado(tab, simbolo) == 1){
            if(jogador == 1){
                exibir_tab(tab);
                printf(BLUE"\nParabens %s! Voce ganhou!\n"RESET, nome1);
                printf("\nPressione ENTER para voltar ao menu...");
                getchar();
                getchar();
                vencedor = 1;
                break;
            } else {
                exibir_tab(tab);
                printf(GREEN"\nParabens %s! Voce ganhou!\n"RESET, nome2);
                printf("\nPressione ENTER para voltar ao menu...");
                getchar();
                getchar();
                vencedor = 1;
                break;
            }
        } else {
            jogador = 3 - jogador; //Troca o jogador
        }   
    }

    if(vencedor == 0){
        system("clear");
        exibir_tab(tab);
        printf(RED"\nHouve um empate, niguem ganhou!"RESET);
        printf("\nPressione ENTER para voltar ao menu...");
        getchar();
        getchar();
    }
}

int main(){ //Responsável por criar a matriz e exibir o menu
    char tab[3][3];
    int opcao;

    printf("\nBEM-VINDO AO JOGO DA VELHA\n");

    do{
        system("clear");
        exibir_menu();

        scanf("%d", &opcao);

        switch(opcao){

            case 1:
            novo_jogo(tab);
            break;

            case 0:
            printf("\nSaindo...\n");
            break;

            default:
            printf("\nOpcao Invalida! Digite novamente!");            

        }
    } while(opcao != 0);

    return 0;
}