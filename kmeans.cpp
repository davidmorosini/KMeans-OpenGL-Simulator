#include <iostream>
#include <cmath>
#include "globais.h"

using namespace std;

float dist_heuclidiana(float x1, float y1, float x2, float y2){//criar uma generica depois, para qualquer N
	float deltaX = x1 - x2;
	float deltaY = y1 - y2;
	return sqrt(deltaY*deltaY + deltaX*deltaX);
}

void kmeans(pnt * e, cluster * c){
	//c -> clusters, e -> elementos
	float * ex = e -> x;
	float * ey = e -> y;
	float * cx = c -> x;
	float * cy = c -> y;

	int i, j;

	for(i = 0; i < e -> qtd; i++){
		int index = 0;
		float D0 = dist_heuclidiana(ex[i], ey[i], cx[0], cy[0]);
		for(j = 1; j < c-> qtdClusters; j++){
			float Dj = dist_heuclidiana(ex[i], ey[i], cx[j], cy[j]);
			if(Dj < D0){
				index = j;
				D0 = Dj;
			}
		}
		(e -> grupo)[i] = index;
		(c -> deltaX)[index] += ex[i];
		(c -> deltaY)[index] += ey[i];
		((c -> qtdPontos)[index])++;

	}

	for(i = 0; i < c -> qtdClusters; i++){
		if((c -> qtdPontos)[i] > 0){
			float xAnt = (c -> x)[i];
			float yAnt = (c -> y)[i];
			(c -> x)[i] = (c -> deltaX)[i] / (c -> qtdPontos)[i];
			(c -> y)[i] = (c -> deltaY)[i] / (c -> qtdPontos)[i]; 
			if(xAnt == (c -> x)[i] && yAnt == (c -> y)[i]){
				(c -> qtdEstaveis)++;
			}
		}
		(c -> deltaX)[i] = 0;
		(c -> deltaY)[i] = 0;
		((c -> qtdPontos)[i]) = 0;
	}

	if(c -> qtdEstaveis != c -> qtdClusters)
		c -> qtdEstaveis = 0;
}