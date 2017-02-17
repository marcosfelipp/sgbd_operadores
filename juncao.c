#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamanhoMaxBuffer 100
#define tamanhoPessoa 40000
#define tamanhoEquipe 1500
#define tamanhoProducao 1023616
#define tamanhoPessoaReal 2062495
#define tamanhoEquipeReal 12849041
#define tamanhoProducaoReal 1023616

#define tamanhoHash 10
typedef struct tupla Tupla;
typedef struct hashTable HASHTABLE;

struct tupla{
	char linha[200];
};


struct hashTable{
    Tupla S;  
    HASHTABLE *prox;
};

Tupla S[tamanhoMaxBuffer];
Tupla T[tamanhoMaxBuffer];


HASHTABLE *tabelaHash[tamanhoMaxBuffer];


//-------------------FUNÇÕES DE HASH----------------------------------------------------

int hash(char *v) {
   int i, h = v[0];
   for (i = 1; v[i] != '\0'; i++) 
        h = h * 256 + v[i];
   return h % tamanhoMaxBuffer;
}

void IniciarTabela(){
    int i;
    for(i=0;i<tamanhoMaxBuffer;i++)
        tabelaHash[i] = NULL;
}

void finalizarTabela(){
    int i =0;
    for(i = 0 ; i <tamanhoMaxBuffer; i++){
        while(tabelaHash[i]!=NULL){
            HASHTABLE *aux;
            aux = tabelaHash[i];
            tabelaHash[i] = tabelaHash[i]->prox;
            free(aux);
        }
    }
}

void mostrarTabela(){
    int i =0;
    for(i = 0 ; i <tamanhoMaxBuffer; i++){
            HASHTABLE *aux;
            aux = tabelaHash[i];
        while(aux!=NULL){
            printf("%s",aux->S.linha);
            aux =  aux->prox;
        }
        if(aux == NULL)
            printf("\nNULL");
        
    }

}

void adicionaNaTabelaHash(int posTabelaHash,int posicaoTupla){
    
    HASHTABLE *novo = malloc(sizeof(HASHTABLE));
    novo->prox = tabelaHash[posTabelaHash];
    strcpy(novo->S.linha,S[posicaoTupla].linha);
    tabelaHash[posTabelaHash] = novo;
    
}

void verificaNaTabelaHash(){

}


//-----------------------------------------------------------------------


void limparSeT(){
    int i;
    for(i= 0 ; i < tamanhoMaxBuffer; i++){
        S[i].linha[0] = 0;
        T[i].linha[0] = 0;
    }


}



void NLJClose(FILE *arquivo1,FILE *arquivo2,FILE *saida){
	fclose(arquivo1); 
	fclose(arquivo2); 
        fclose(saida);
}




char * verificaCondicaoT(int condicao,int pos){
    int j;
    char *chaveJuncao = (char*) malloc(20 * sizeof(char));
    
    if(condicao == 1){
        j=0;
        while(T[pos].linha[j] != '#'){
           chaveJuncao[j] = T[pos].linha[j];
            j++;
        }
        chaveJuncao[j] = '\0';
        return chaveJuncao;
        
    }else 
        if(condicao == 2){
            j = 0;
            while(T[pos].linha[j] != '#' ){
                    j++;
            }
            j = j+2;
            while(T[pos].linha[j] != '#' ){
                chaveJuncao[j] = T[pos].linha[j];
                j++;
            }
            chaveJuncao[j] = '\n';
            return chaveJuncao;
    }
}


char * verificaCondicaoS(int condicao,int pos){
    int j;
    char *chaveJuncao = (char*) malloc(20 * sizeof(char));
    
    
    
    if(condicao == 1){
        j=0;
        while(S[pos].linha[j] != '#'){
           chaveJuncao[j] = S[pos].linha[j];
            j++;
        }
        chaveJuncao[j] = '\0';
        return chaveJuncao;
        
    }else 
        if(condicao == 2){
            j = 0;
            while(S[pos].linha[j] != '#' ){
                    j++;
            }
            j = j+2;
            while(S[pos].linha[j] != '#' ){
                chaveJuncao[j] = S[pos].linha[j];
                j++;
            }
            chaveJuncao[j] = '\n';
            return chaveJuncao;
    }
}

char * verificaCondicaoHash(int condicao,int pos){
    int j;
    char *chaveJuncao = (char*) malloc(20 * sizeof(char));
    
    
    
    if(condicao == 1){
        j=0;
        while(tabelaHash[pos]->S.linha[j] != '#'){
           chaveJuncao[j] = tabelaHash[pos]->S.linha[j];
            j++;
        }
        chaveJuncao[j] = '\0';
        return chaveJuncao;
        
    }else 
        if(condicao == 2){
            j = 0;
            while(tabelaHash[pos]->S.linha[j] != '#' ){
                    j++;
            }
            j = j+2;
            while(tabelaHash[pos]->S.linha[j] != '#' ){
                chaveJuncao[j] = tabelaHash[pos]->S.linha[j];
                j++;
            }
            chaveJuncao[j] = '\n';
            return chaveJuncao;
    }
}


void NLJNext(FILE *p,FILE *q,FILE *saida,int cond1, int cond2){
	
        char *chaveJuncao;
        char *newchaveJuncao;
        int chaveHash;
        int newChaveHash;
        int i = 0;
        int t = 0;
        int j = 0;
        
        //Para toda a relação S:
        int repeticao = (tamanhoPessoa / tamanhoMaxBuffer) + 1;
        printf("Numero de IO do primeiro while:%d\n",repeticao);
        int contador=0, contador2 =0;

        int repeticao2 = (tamanhoEquipe / tamanhoMaxBuffer)+1;
        printf("Numero de IO do segundo Whille:%d\n",repeticao2);
        
        while(contador < repeticao){
            //Ler buffers da relacao1:
            //printf("%d\n",contador);
            IniciarTabela();
            //printf("\n\n\nInicio\n");
            //mostrarTabela();
            i = 0;
            while(i<tamanhoMaxBuffer && !feof(p)){
                    fgets (S[i].linha,512,p);
                    i++;
            }
        
            int pos=0;
            while(pos < tamanhoMaxBuffer){
                chaveJuncao = verificaCondicaoS(cond1,pos);
                chaveHash = hash(chaveJuncao); //Aplca hash sobre a condição
                adicionaNaTabelaHash(chaveHash,pos); //Adiciona tupla na EB
                pos++;
            }
            contador2 = 0 ;
            while(contador2 < repeticao2){
                      printf("%d\n",contador2*contador);
            //Ler buffers da relacao2:
                i = 0;
                while(i<tamanhoMaxBuffer && !feof(q)){
                        fgets (T[i].linha,100,q);
                        T[i].linha[strlen(T[i].linha)-1] = 0;
                        i++;
                }
                pos = 0;
                //Para cada tupla de R:
                while(pos < tamanhoMaxBuffer && !feof(q)){
                    chaveJuncao = verificaCondicaoT(cond1,pos);
                    //printf("%s\n\n",chaveJuncao);
                    
                    chaveHash = hash(chaveJuncao);
                    int k =0 , l;

                    while(k < tamanhoMaxBuffer){              
                    if(tabelaHash[k] != NULL ){
                            newchaveJuncao = verificaCondicaoHash(cond1,k);
                            newChaveHash = hash(newchaveJuncao);
                            //printf("Chave Hash T:%s\nChave Hash S:%s\n",chaveJuncao,newchaveJuncao);
                            if(chaveHash == newChaveHash){
                                HASHTABLE *aux;
                                aux = tabelaHash[k];
                                //printf("%d:%d\n",chaveHash,newChaveHash);
                                while(aux!= NULL ){
                                    char str[1024] ="";
                                    strcat(str,T[pos].linha);
                                    strcat(str,"##");
                                    strcat(str,aux->S.linha);
                                    fprintf(saida,"%s",str);
                                    aux = aux->prox;
                                    free(aux);
                                }
                            }
                            

                    }
                        
                        k++;
                    }


                    pos++;
                    //Verificar se existe tupla de S  == T e jogar para saida
                }
            contador2++;
            }
        
        contador++;
        /*printf("\n\n\nMeio\n");
        mostrarTabela();
       
        printf("\n\n\nFim\n");
        mostrarTabela();*/
        finalizarTabela();
        }

        
}


void NLJOpen(){
	FILE *p = fopen("pessoa.txt","r");
	FILE *q =fopen("equipe.txt","r");
    FILE *saida = fopen("saida.txt","w");
	if(p == NULL || q == NULL){
                printf("Falhar ao abrir arquivo\n");
                return;
        }
        NLJNext(p,q,saida,1,1);
        NLJClose(p,q,saida);
}



void nestedLoopJoin(/*char *relacao1, char relacao2*/){
	NLJOpen();
	//NLJNext(1,1);
	//NLJClose();
}

void main(){
    
    nestedLoopJoin();
    printf("\n\n\n\n\n\n\n\nAcabou, e treta !!");
}