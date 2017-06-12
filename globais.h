#ifndef GLOBAIS_H
#define GLOBAIS_H

#define QTD_CORES 10

#define STOP 0
#define START 1
#define END 2

#define SEN60 0.8660254
#define COS60 0.5


typedef struct pnt{
	int qtd, range;
	float * x, * y;
	int * grupo;
}pnt;

typedef struct cluster{
	float * x, * y, * deltaX, * deltaY;
	int * qtdPontos, qtdClusters;
	int qtdEstaveis;
	float *r, *g, *b;
}cluster;


float cores[QTD_CORES][3] = {
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{75/255.0, 0 , 130/255.0},
	{1.0, 0.0, 1.0},
	{100/255.0, 149/255.0, 237/255.0},
	{1.0, 140/255.0, 0.5},
	{0.0, 100/255.0, 0.0},
	{139/255.0,69/255.0,19/255.0},
	{1.0, 1.0, 0.0}
};

unsigned int tempo = 600; //time in ms

int tamX, tamY, xi, yi;

int count = 0;
int status = STOP;
int step = STOP;

char texto_x[] = "X";
char texto_y[] = "Y";

int redesenhaClusters = 0;

#endif