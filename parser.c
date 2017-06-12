#include <stdio.h>
#include <stdlib.h>
#include "globais.h"

#define MAXLINE 150

pnt * getPontos(char path[500]){
	pnt * resp = NULL;
	if(path != NULL){
		FILE * arq = fopen(path, "r");
		if(arq != NULL){
			char buffer[MAXLINE];
			do {
				if (fgets(buffer, MAXLINE, arq) == NULL) {
					printf("ERRO: ARQUIVO SEM INFORMACOES!\n");
					exit(1);
				}
			} while (buffer[0] == '%');

			int qtdExemplos = atoi(buffer);

			int range;
			fscanf(arq, "%d", &range);
			
			resp = (pnt *)malloc(sizeof(pnt));

			float * pntsX = (float *)malloc(qtdExemplos * sizeof(float));
			float * pntsY = (float *)malloc(qtdExemplos * sizeof(float));
			int * grupo = (int *)malloc(qtdExemplos * sizeof(int));

			int i;
			float X, Y;

			for(i = 0; i < qtdExemplos; i++){
				fscanf(arq, "%f %f", &X, &Y);
				pntsX[i] = X;
				pntsY[i] = Y;
				grupo[i] = -1;
			}

			resp -> qtd = qtdExemplos;
			resp -> range = range;
			resp -> x = pntsX;
			resp -> y = pntsY;
			resp -> grupo = grupo;

			fclose(arq); 
		}

	}
	return resp;
}

cluster * inicializaCluster(pnt * pontos, int K){
	cluster * c = (cluster *)malloc(sizeof(cluster));
	if(c != NULL){
		c -> qtdClusters = K;
		int i;
		float *x, *y, *dx, *dy, *cr, *cg, *cb;
		int *qtdP;
		x = (float *)malloc(K * sizeof(float));
		y = (float *)malloc(K * sizeof(float));
		dx = (float *)malloc(K * sizeof(float));
		dy = (float *)malloc(K * sizeof(float));
		qtdP = (int *)malloc(K * sizeof(int));
		cr = (float *)malloc(K * sizeof(float));
		cg = (float *)malloc(K * sizeof(float));
		cb = (float *)malloc(K * sizeof(float));
		for(i = 0; i < K; i++){
			int r = rand()%(pontos -> qtd);
			x[i] = (pontos -> x)[r];
			y[i] = (pontos -> y)[r];
			dx[i] = 0;
			dy[i] = 0;
			qtdP[i] = 0;
			cr[i] = cores[i][0];
			cg[i] = cores[i][1];
			cb[i] = cores[i][2];
		}
		c -> x = x;
		c -> y = y;
		c -> deltaX = dx;
		c -> deltaY = dy;
		c -> qtdPontos = qtdP;
		c -> r = cr;
		c -> g = cg;
		c -> b = cb;
		c -> qtdEstaveis = 0;
	}
	return c;
}

cluster * copy_cluster(cluster * c_ext){
	cluster * c = (cluster *)malloc(sizeof(cluster));
	if(c != NULL){
		float *x, *y, *dx, *dy, *cr, *cg, *cb;
		int *qtdP;
		int K = c_ext -> qtdClusters;

		x = (float *)malloc(K * sizeof(float));
		y = (float *)malloc(K * sizeof(float));
		dx = (float *)malloc(K * sizeof(float));
		dy = (float *)malloc(K * sizeof(float));
		qtdP = (int *)malloc(K * sizeof(int));
		cr = (float *)malloc(K * sizeof(float));
		cg = (float *)malloc(K * sizeof(float));
		cb = (float *)malloc(K * sizeof(float));

		int i;
		for(i = 0; i < K; i++){
			x[i] = (c_ext -> x)[i];
			y[i] = (c_ext -> y)[i];
			dx[i] = (c_ext -> deltaX)[i];
			dy[i] = (c_ext -> deltaY)[i];
			qtdP[i] = 0;
			cr[i] = (c_ext -> r)[i];
			cg[i] = (c_ext -> g)[i];
			cb[i] = (c_ext -> b)[i];
		}

		c -> x = x;
		c -> y = y;
		c -> deltaX = dx;
		c -> deltaY = dy;
		c -> r = cr;
		c -> g = cg;
		c -> b = cb;
		c -> qtdClusters = c_ext -> qtdClusters;
		c -> qtdEstaveis = c_ext -> qtdEstaveis;
		c -> qtdPontos = qtdP;
	}
	return c;
}

pnt * copy_elemento(pnt * p_ext){
	pnt * p = (pnt *)malloc(sizeof(pnt));
	if(p != NULL){
		int qtdExemplos = p_ext -> qtd;
		float * pntsX = (float *)malloc(qtdExemplos * sizeof(float));
		float * pntsY = (float *)malloc(qtdExemplos * sizeof(float));
		int * grupo = (int *)malloc(qtdExemplos * sizeof(int));

		int i;
		for(i = 0; i < qtdExemplos; i++){
			pntsX[i] = (p_ext -> x)[i];
			pntsY[i] = (p_ext -> y)[i];
			grupo[i] = (p_ext -> grupo)[i];
		}

		p -> x = pntsX;
		p -> y = pntsY;
		p -> grupo = grupo;
		p -> range = p_ext -> range;
		p -> qtd = qtdExemplos;
	}

	return p;			
}