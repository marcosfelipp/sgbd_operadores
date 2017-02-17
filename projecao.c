#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tupla T;

struct tupla{
	char linha[200];
};



/*Função projeção: recebe um vetor com uma flag 
 * se flag for 0 ele não projeta o campo
 * se flag for 1 ele projeto campo para saída
 * */

void closeProj(FILE *entrada, FILE *saida){
    fclose(entrada);
    fclose(saida);
}


void nextProj(FILE *p, FILE *saida,int camposSelecionados[7]){
    
    T tuplaArquivo;
    char stringRetorno[100];
    int j,t;
    while(!feof(p)){
        fgets (tuplaArquivo.linha,210,p);
         t=0;
         
         //Para cada campo:
         for(int i=0; i<7 ;i++){
            j=0;
            //Verifico se campo deve ser mandado para saída
            if(camposSelecionados[i] == 1){
                while(tuplaArquivo.linha[t] != '#' && j < 100 && tuplaArquivo.linha[t] != '\n'){
                    stringRetorno[j] = tuplaArquivo.linha[t];
                    t++; 
                    j++;
                }
                stringRetorno[j] = '\0';
                fprintf(saida,"%s",stringRetorno);
                fprintf(saida,"##");
            }else{
                while(tuplaArquivo.linha[t] != '#' && t < 200)
                    t++; 
            }   
            if(tuplaArquivo.linha[t] == '#') t++;
            if(tuplaArquivo.linha[t] == '#') t++;
        }
        
        fprintf(saida,"\n");
    }
    
}


void openProj(char *relacao,int camposSelecionados[7]){
    FILE *p = fopen(relacao,"r");
    FILE *saida = fopen("saida.txt","w");
    if(p == NULL || saida  == NULL){
            printf("Falhar ao abrir arquivo\n");
            return;
    }
    nextProj(p,saida,camposSelecionados);
    closeProj(p,saida);
}

void projecao(char *relacao,int camposSelecionados[7]){
    openProj(relacao,camposSelecionados);
}


void main(){
    int camposSelecionados[7] = {1,0,0,0,0,0,0};
    projecao("pessoa.txt",camposSelecionados);
    
}