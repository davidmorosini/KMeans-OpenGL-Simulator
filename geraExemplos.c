#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILED -1
#define ABORTED -2


int main(int argc, char * argv[]){

	if(argc != 4){
		printf("Parametros insuficientes!\n");
		printf("./[executavel] [qtd Exemplos] [Range pontos] [NomeArquivoSaida.extensao]\n\n");
		return FAILED;
	}else{
		FILE * arq;

		int qtdInsts = atoi(argv[1]);
		int range = atoi(argv[2]);
		arq = fopen(argv[3], "w");

		if(arq != NULL){
			int i;
			fprintf(arq, "%% Arquivo de exemplos, CLUSTERIZACAO com algoritmo KMeans");
			fprintf(arq, "\n%% (%% sao comentarios)");
			fprintf(arq, "\n%% Autor: David Morosini - IA (2017/1)");
			fprintf(arq, "\n%% Pontos gerados de forma aleatoria");
			fprintf(arq, "\n%% Caracteristicas de analise:  pontos X, Y");
			fprintf(arq, "\n%% Quantidade de pontos: %d", qtdInsts);
			fprintf(arq, "\n%% Range dos pontos: 0 - %d", range);
			fprintf(arq, "\n%d", qtdInsts);
			fprintf(arq, "\n%d\n", range);
			for(i = 0; i < qtdInsts; i++){
				fprintf(arq, "%d %d\n", rand()%range, rand()%range);
			}

			fclose(arq);
			return SUCCESS;	
		}else{
			return ABORTED;
		}	
	}
	return ABORTED;
}