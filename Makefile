all:
	gcc geraExemplos.c -o geradorExemplos
	g++ simulador.cpp -o simulador -lGL -lGLU -lglut

clean:
	rm simulador
	rm geradorExemplos
