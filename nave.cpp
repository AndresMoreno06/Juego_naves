#include <stdio.h>
#include <windows.h>
#include <conio.h>

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

int main(){
	
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
			if(tecla == 'j')x--;
			if(tecla == 'l')x++;
			if(tecla == 'i')y--;
			if(tecla == 'k')y++;
		 	gotoxy(x,y);
		 	printf("*");
 			
		}
	 }
 	
 	return 0;

}
