#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tupla T;

struct tupla{
	char linha[200];
};


void selecao(char *condicao, int posicao){
    FILE *p = fopen("producao.txt","r");
    FILE *saida = fopen("saida.txt","w");
    if(p == NULL || saida  == NULL){
            printf("Falhar ao abrir arquivo\n");
            return;
    }
    
    int j;
    T tuplaArquivo;
    char chaveJuncao[100];
    int t;
    float size = 0;
    
    
    while(!feof(p)){
        fgets (tuplaArquivo.linha,210,p);
        
        t=0;
        
        for(int i=1;i<posicao;i++){
            if(tuplaArquivo.linha[t] == '#') t++;
            if(tuplaArquivo.linha[t] == '#') t++;
            while(tuplaArquivo.linha[t] != '#' && t < 200)
                t++; 
        }
        j=0;
        
        if(tuplaArquivo.linha[t] == '#') t++;
        if(tuplaArquivo.linha[t] == '#') t++;
        
        while(tuplaArquivo.linha[t] != '#' && j < 100 && tuplaArquivo.linha[t] != '\n'){
           chaveJuncao[j] = tuplaArquivo.linha[t];
           t++; 
           j++;
        }
        chaveJuncao[j] = '\0';
        //Verifica condicao:
        if(strcmp(condicao,chaveJuncao) == 0){
            fprintf(saida,"%s",tuplaArquivo.linha);
            fprintf(saida,"\n");
            size = size + 1;
        }
        
    }
    printf("%f\n",size);
    fclose(saida);
    fclose(p);
    
}


void main(){
   
    selecao("1",4);
    
    
    
}