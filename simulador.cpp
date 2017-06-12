#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <stack>
#include <vector>
#include <time.h>
#include "parser.c"
#include "globais.h"
#include "kmeans.cpp"

using namespace std;

/*
	David Morosini de Assumpção
	IA - 2017/1
*/


void desenha(void);
void inicializa(void);
void Timer(int value);
void TeclasEspeciais(int key, int x, int y);
void TeclasNormais(unsigned char key, int x, int y);
void exibe_cluster(void);
void reseta(void);

cluster * c;
pnt * pontos;

std::stack<cluster *> timeline_cluster;
std::stack<pnt *> timeline_pontos;


int t = 1;

int main(int argc, char * argv[]){
	if(argc != 3){
		cout << endl << "Parametros incorretos!" << endl;
		cout << "./[executavel] [nomeArquivo.extensao] [Qtd Clusters]" << endl << endl;
	}else{
		srand(time(NULL));
		pontos = getPontos(argv[1]);

		c = inicializaCluster(pontos, atoi(argv[2]));

		cout << endl << "****************************" << endl;
		cout <<         "*     Simulador Kmeans     *" << endl;
		cout <<         "*                          *" << endl;
		cout <<         "*       IA - 2017/1        *" << endl;
		cout <<         "*      David Morosini      *" << endl;
		cout <<         "****************************" << endl;
		cout << endl << "Como usar:" << endl;
		cout << endl << "Space = Inicia a simulacao automaticamente" << endl;
		cout << "  * caso a simulacao estiver acontecendo, space pausa a mesma" << endl;
		cout << "-->  = Avanca um passo na simulacao" << endl;
		cout << "<--  = Retorna um passo na simulacao" << endl;
		cout << "Esc (Sai do programa)" << endl << endl;
		cout << "--------------------------------------------------------" << endl;

		xi = -100;
		yi = xi;
		tamX = 800;
		tamY = 800;

		glutInit(&argc, argv);
	    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	    glutInitWindowSize(tamX, tamY);
	    glutInitWindowPosition(100,100);
	    glutCreateWindow("IA 2017/1 - Simulador Kmeans");

	    inicializa();
	    glutDisplayFunc(desenha);
	    glutTimerFunc(tempo, Timer, STOP);
	    glutSpecialFunc(TeclasEspeciais);
	    glutKeyboardFunc(TeclasNormais);

	    glutMainLoop();
	}

	return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//OpenGl Functions

void exibe_cluster(void){
	cout << endl << "Iteracoes: " << count << endl;
	cout <<  "Locais atuais dos Clusters:" << endl << endl;
	for(int i = 0; i < c -> qtdClusters; i++){
		cout << "Cluster " << i << ": X = " << (c -> x)[i] << ", Y = " << (c -> y)[i] << endl;
	}
}

void inicializa(void){
	gluOrtho2D(xi, tamX, yi, tamY); 
}

void draw_element(float x, float y, int grupo){//desenha com o centro na origem
	int r = 4;
	int NUM_LINHAS = 50;
			
	glBegin(GL_POLYGON);
		glColor3f((c -> r)[grupo], (c -> g)[grupo], (c -> b)[grupo]);
		for(int i = 0; i < NUM_LINHAS; i++){
			float ang = i * 2 * M_PI / NUM_LINHAS;		
			glVertex3f(x + (cos(ang) * r), y + (sin(ang) * r), 0);
		}
	glEnd();
}

void draw_cluster(float x, float y, float r, float g, float b){//desenha com o centro na origem
	int comp = 16, larg = 4;
	glBegin(GL_QUADS);
		glColor3f(r, g, b);
		glVertex3f(x - comp, y - larg, 0);
		glVertex3f(x + comp, y - larg, 0);
		glVertex3f(x + comp, y + larg, 0);
		glVertex3f(x - comp, y + larg, 0);

		glVertex3f(x - larg, y - comp, 0);
		glVertex3f(x + larg, y - comp, 0);
		glVertex3f(x + larg, y + comp, 0);
		glVertex3f(x - larg, y + comp, 0);
	glEnd();
}

void DesenhaTextoStroke(void *font, char *string){  
	// Exibe caractere a caractere
	while(*string)
		glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++); 
}

void desenhaTriangulo(void){

    int lado = 10;

	glBegin(GL_TRIANGLES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-lado, 0, 0);
		glVertex3f(lado, 0, 0);
		glVertex3f(lado * COS60, 2* lado * SEN60, 0);
	glEnd();
    

}

void desenha(void){
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//desenhando eixos
	glPushMatrix();
		glTranslatef(-23, tamY - 16, 0);
		desenhaTriangulo();	
	glPopMatrix();

	glPushMatrix();
		glTranslatef(tamX - 16, -17, 0);
		glRotatef(270, 0, 0, 1);
		desenhaTriangulo();	
	glPopMatrix();

	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-100, -20);
		glVertex2f(tamX, -20);
		glVertex2f(-20, -100);
		glVertex2f(-20, tamY);
	glEnd();

	//fim dos eixos

	// Posiciona o texto stroke usando transformações geométricas
	glPushMatrix();	
		glTranslatef(750, -50,0);
		glScalef(0.16, 0.16, 0.16); // diminui o tamanho do fonte
		glLineWidth(2); // define a espessura da linha
		DesenhaTextoStroke(GLUT_STROKE_ROMAN, texto_x);
	glPopMatrix();

	glPushMatrix();	
		glTranslatef(-50, 740,0);
		glScalef(0.16, 0.16, 0.16); // diminui o tamanho do fonte
		glLineWidth(2); // define a espessura da linha
		DesenhaTextoStroke(GLUT_STROKE_ROMAN, texto_y);
	glPopMatrix();


	//desenha Elementos
	for(int i = 0; i < pontos -> qtd; i++){
		draw_element((pontos -> x)[i], (pontos -> y)[i], (pontos -> grupo)[i]);
	}

	//desenha Clusters
	for(int i = 0; i < c -> qtdClusters; i++){
		draw_cluster((c -> x)[i], (c -> y)[i], (c -> r)[i], (c -> g)[i], (c -> b)[i]);
	}
	
	glutSwapBuffers();	
}

void next_step(void){

}


void Timer(int value){
	if(value == START && status == START){

		if(c -> qtdEstaveis < c -> qtdClusters){ //critério de parada
			cout << endl << endl << "********************************" << endl;
			cout << "Iteracao avancada automaticamente" << endl;

			count++;

			cluster * aux_c = copy_cluster(c);
			pnt * aux_p = copy_elemento(pontos);

			timeline_cluster.push(aux_c);
			timeline_pontos.push(aux_p);

			kmeans(pontos, c);	//modifica pontos e c
			glutPostRedisplay();

			glutTimerFunc(tempo,Timer, START);

			exibe_cluster();
			cout << endl << "********************************" << endl;

		}else{
			cout << endl << "################## FIM DA SIMULACAO #################" << endl;
			exibe_cluster();
			cout << endl << "################## FIM DA SIMULACAO #################" << endl;

			cout << endl << "Possiveis Comandos:" << endl;
			cout << "<-- (Retorna uma iteracao)" << endl;
			cout << "r   (Retorna ao estado inicial)" << endl;
			cout << "Esc (Sai do programa)" << endl;
			cout << "--------------------------------------------------------" << endl;
		}
	}	
}

void TeclasEspeciais(int key, int x, int y){
	if(key == GLUT_KEY_LEFT && count > 0){
		cout << endl << endl << "********************************" << endl;
		cout << "Iteracao retornada manualmente" << endl;

		status = START;
		step = START;

		count--;	

		c = timeline_cluster.top();
		pontos = timeline_pontos.top();

		timeline_pontos.pop();
		timeline_cluster.pop();

		glutPostRedisplay();

		exibe_cluster();

		cout << endl << "********************************" << endl;

	}
	else if(key == GLUT_KEY_RIGHT){
		cout << endl << endl << "********************************" << endl;
		cout << "Iteracao avancada manualmente" << endl;
		status = START;
		step = START;

		if(c -> qtdEstaveis < c -> qtdClusters){
			count++;

			cluster * aux_c = copy_cluster(c);
			pnt * aux_p = copy_elemento(pontos);

			timeline_cluster.push(aux_c);
			timeline_pontos.push(aux_p);

			kmeans(pontos, c);
						
			glutPostRedisplay();

			exibe_cluster();
			cout << endl << "********************************" << endl;

		}else{
			cout << endl << "################## FIM DA SIMULACAO #################" << endl;
			exibe_cluster();
			cout << endl << "################## FIM DA SIMULACAO #################" << endl;

			cout << endl << "Possiveis Comandos:" << endl;
			cout << "<-- (Retorna uma iteracao)" << endl;
			cout << "r   (Retorna ao estado inicial)" << endl;
			cout << "Esc (Sai do programa)" << endl;
			cout << "--------------------------------------------------------" << endl;
		}
	}

}

void TeclasNormais(unsigned char key, int x, int y){
	if(key == 32){//space
		if(status == STOP){
			cout << endl << "Simulacao iniciada, aguarde..." << endl;
			status = START;

			glutTimerFunc(tempo, Timer, START);
		}
		else if(status == START && step == STOP){
			cout << endl << "Simulacao pausada, pressione Space para continuar..." << endl;
			status = STOP;
		}
		else if(status == START && step == START){
			cout << endl << "Simulacao iniciada, aguarde..." << endl;
			step = STOP;
			glutTimerFunc(tempo, Timer, START);
			
		}
	}
	else if(key == 'r' || key == 'R'){
		cout << endl << "Resetando..." << endl;
		reseta();
		cout << endl << "Como usar:" << endl;
		cout << endl << "Space = Inicia a simulacao automaticamente" << endl;
		cout << "  * caso a simulacao estiver acontecendo, space pausa a mesma" << endl;
		cout << "-->  = Avanca um passo na simulacao" << endl;
		cout << "<--  = Retorna um passo na simulacao" << endl;
		cout << "Esc (Sai do programa)" << endl << endl;
		cout << "--------------------------------------------------------" << endl;

	}
	else if(key == 27){
		cout << endl << "Saindo..." << endl;
		exit(1);
	}
}

void reseta(void){
	if(timeline_cluster.size() > 0){
		status = STOP;
		step = STOP;
		count = 0;

		while(timeline_cluster.size() > 1){
			timeline_cluster.pop();
			timeline_pontos.pop();
		}

		c = timeline_cluster.top();
		timeline_cluster.pop();
		pontos = timeline_pontos.top();
		timeline_pontos.pop();

		glutPostRedisplay();
	}
}
