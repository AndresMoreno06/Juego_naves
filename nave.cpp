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

class NAVE{
	/*
		en una clase en poner cualquier atributo de esta manera , son automaticamente
	  	privados
	*/
	
	int x,y;
public:
	/*
		Se crean las funciones publicar y su constructor
	*/
	NAVE (int _x,int _y): x (_x),y(_y){};
	void Pintar();
	void Borrar();
	void Mover();

};

/*
	Asi de estructura la funcion de una clase
*/
void NAVE::Pintar(){
	gotoxy(x,y);printf("  %c",30);
	gotoxy(x,y+1);printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2);printf("%c%c %c%c",30,190,190,30);
}

void NAVE::Borrar(){
	gotoxy(x,y);printf("     ");
	gotoxy(x,y+1);printf("     ");
	gotoxy(x,y+2);printf("     ");
}

void NAVE::Mover(){
	/*
		Kbhit() es una funcion que verifica si se preciono una tecla
	*/ 
	if(kbhit()){
		
		char tecla = getch();
		Borrar();
		//Cuando se presiona para derecha
		if(tecla == DERECHA)x--;
		//Cuando se presiona para izquierda
		if(tecla == IZQUIERDA)x++;
		//Cuando se presiona para arriba
		if(tecla == ARRIBA)y--;
		//Cuando se presiona para abajo
		if(tecla == ABAJO)y++;
	 	Pintar();		
	}
}

int main(){
	
	Ocultar();
	NAVE N(7,7);
 	N.Pintar();
 	bool game_over = false;
 	while(!game_over){
 		
 		N.Mover();
 		Sleep(30);
	 }
 	
 	return 0;

}
