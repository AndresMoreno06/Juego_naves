#include <stdio.h>
#include <windows.h>
#include <conio.h>

//Definir variables de movimientos
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 77
#define DERECHA 75

void gotoxy(int x, int y){
 	
 	/* 
		Estamos creando un identificador para obtener su posicion
	*/
	
 	HANDLE hCon;
 	
 	/*
	 	aqui se recupera el identificador de la consola al correr el programa
	 	si se pone un STD_OUTPUT_HANDLE se toma el control de la salida en la consola
	 	
 	*/
 	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
 	
 	/*
		tiene dos atributos que seria las variables de posicion X y Y 
	*/
 	COORD dwPos;
 	
 	dwPos.X = x;
 	dwPos.Y = y;
 	
 	/*
		Se toma la variable de salida y se le imprime en las posiciones que se le manda
	*/
 	SetConsoleCursorPosition(hCon, dwPos);
}

void Ocultar(){
	
	HANDLE hCon;
 	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
 	
 	/*
 		Con la estructura CONSOLE_CURSOR_INFO controla la apariencia del 
		 cursor que se muestra en pantalla 
	*/
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize   = 1;
	cci.bVisible = FALSE;
 	
	/*
		Con esta funcion se puede controlar las caracteristicas del cursor 
		que se muestra en pantalla, para pasar el segundo parametro se DEBE
		hacer referencia a el por la cual se DEBE poner '&'
	*/
	SetConsoleCursorInfo(hCon,&cci);
}

int main(){
	
	Ocultar();
 	int x = 2 , y = 2;
 	gotoxy(x,y);
 	printf("*");
 	
 	bool game_over = false;
 	while(!game_over){
 		/*
			Kbhit() es una funcion que verifica si se preciono una tecla
		*/ 
		if(kbhit()){
 			
 			char tecla = getch();
 			gotoxy(x,y);
 			printf(" ");
 			//Cuando se presiona para derecha
			if(tecla == DERECHA)x--;
			//Cuando se presiona para izquierda
			if(tecla == IZQUIERDA)x++;
			//Cuando se presiona para arriba
			if(tecla == ARRIBA)y--;
			//Cuando se presiona para abajo
			if(tecla == ABAJO)y++;
		 	gotoxy(x,y);
		 	printf("*");
 			
		}
	 }
 	
 	return 0;

}
