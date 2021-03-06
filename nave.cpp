#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <list>

using namespace std;

//Definir variables de movimientos
#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 77
#define DERECHA 75
#define DISPARO 32

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

void Limites(){
	
	/*
		Se pintan los bordes horizontales
	*/
	for(int i = 2;i < 78 ; i++){
		
		gotoxy(i,3);
		printf("%c",205);
		gotoxy(i,33);
		printf("%c",205);
		
	}
	/*
		Se pintan los bordes Verticales
	*/
	for(int i = 4;i < 33 ; i++){
		
		gotoxy(2,i);
		printf("%c",186);
		gotoxy(77,i);
		printf("%c",186);
		
	}
	
	/*
		Se cambia las esquinas
	*/
	
	gotoxy(2,3);  printf("%c",201);
	gotoxy(2,33); printf("%c",200);
	gotoxy(77,3); printf("%c",187);
	gotoxy(77,33);printf("%c",188);
}

class NAVE{
	/*
		en una clase en poner cualquier atributo de esta manera , son automaticamente
	  	privados
	*/
	
	int x,y;
	int corazones;
	int vidas;
public:
	/*
		Se crean las funciones publicar y su constructor
	*/
	NAVE (int _x,int _y,int _corazones,int _vidas): x (_x),y (_y),corazones (_corazones),vidas (_vidas){};
	int  X(){ return x; }
	int  Y(){ return y; }
	int  VID(){	return vidas;}
	void Elimina_Corazon(){ corazones--; }
	void Pintar();
	void Borrar();
	void Mover();
	void Pintar_Corazones();
	void Morir();
};

class ASTEROIDE{
	
	int x,y;
	
public:
	ASTEROIDE(int _x,int _y):x (_x), y (_y){}
	int  X(){ return x;	}
	int  Y(){ return y;	}
	void Pintar();
	void Mover();
	void Colision(class NAVE &N);
};

class BALA{
	
	int x,y;
public:
	BALA(int _x, int _y): x (_x),y (_y){}
	int  X(){ return x;	}
	int  Y(){ return y;	}
	void Mover();
	bool Fuera();
};

void BALA::Mover(){
	
	 gotoxy(x,y);
	 printf(" ");
	 y--;
	 gotoxy(x,y);
	 printf("*");
}

bool BALA::Fuera(){
	
	if(y == 4){
		return true;
	}else{
		return false;
	}
}



void ASTEROIDE::Pintar(){
	gotoxy(x,y);
	printf("%c",184);
}

void ASTEROIDE::Mover(){
	
	gotoxy(x,y);
	printf(" ");
	y++;
	if(y > 32){
		
		x = rand() % 71 + 4;
		y = 4;
	}
	Pintar();
}

void ASTEROIDE::Colision(class NAVE &N){
	
	if(x >= N.X() && x <N.X()+6 && y >= N.Y() && y < N.Y()+2){
		
		N.Elimina_Corazon();
		N.Borrar();
		N.Pintar();
		N.Pintar_Corazones();
		x = rand() % 71 + 4;
		y = 4;
	}
	
}


/*
	Asi de estructura la funcion de una clase
*/
void NAVE::Pintar(){
	gotoxy(x,y);printf("  %c",254);
	gotoxy(x,y+1);printf(" %c%c%c",205,207,205);
	gotoxy(x,y+2);printf("%c%c %c%c",178,223,223,178);
}

void NAVE::Borrar(){
	gotoxy(x,y);  printf("              ");
	gotoxy(x,y+1);printf("              ");
	gotoxy(x,y+2);printf("          ");
}

void NAVE::Mover(){
	/*
		Kbhit() es una funcion que verifica si se preciono una tecla
	*/ 
	if(kbhit()){
		
		char tecla = getch();
		Borrar();
		//Cuando se presiona para derecha
		if(tecla == DERECHA   && x > 4)x--;
		//Cuando se presiona para izquierda
		if(tecla == IZQUIERDA && x+6 < 77)x++;
		//Cuando se presiona para arriba
		if(tecla == ARRIBA    && y   > 4)y--;
		//Cuando se presiona para abajo
		if(tecla == ABAJO     && y+3 < 33)y++;
		if(tecla == 'e') corazones--;
	 	Pintar();	
		Pintar_Corazones();	
	}
}

void NAVE::Pintar_Corazones(){
	
	gotoxy(50,2);
	printf("VIDAS %d",vidas);
	gotoxy(64,2);
	printf("Salud");
	gotoxy(70,2);
	printf("        ");
	for(int i = 0; i < corazones;i++){
		
		gotoxy(70+i,2);
		printf("%c",3);
	}
	
}

void NAVE::Morir(){
	
	if(corazones == 0){
		
		Borrar();
		gotoxy(x,y);
		printf("   **   ");
		gotoxy(x,y+1);
		printf("  ****  ");
		gotoxy(x,y+2);
		printf("   **   ");
		Sleep(400);
		
		Borrar();
		gotoxy(x,y);
		printf(" * ** * ");
		gotoxy(x,y+1);
		printf("  ****  ");
		gotoxy(x,y+2);
		printf(" * ** * ");
		Sleep(400);
		
		Borrar();
		gotoxy(x,y);
		printf("   **   ");
		gotoxy(x,y+1);
		printf("  ****  ");
		gotoxy(x,y+2);
		printf("   **   ");
		Sleep(400);
		
		Borrar();
		gotoxy(x,y);
		printf(" * ** * ");
		gotoxy(x,y+1);
		printf("  ****  ");
		gotoxy(x,y+2);
		printf(" * ** * ");
		Sleep(400);
		
		
		Borrar();
		vidas--;
		corazones = 3;
		Pintar_Corazones();
		Pintar();
	}
}

int main(){
	
	Ocultar();
	Limites();
	
	NAVE N(37,29,3,3);
 	N.Pintar();
 	N.Pintar_Corazones();
 	
 	list<ASTEROIDE*> A;
 	list<ASTEROIDE*>::iterator itA;
 	
 	for(int i=0; i<5;i++){
 		
 		A.push_back(new ASTEROIDE(rand()%75 + 3, rand()%5 + 4));
 		
	 }
 	
 	/*
		Se hace una lista de punteros del objeto balas 
	*/
 	list<BALA*> B;
 	list<BALA*>::iterator it;
 	
 	
 	bool game_over = false;
 	int puntos     = 0;
 	while(!game_over){
 		
 		
 		gotoxy(4,2);
 		printf("Puntos %d",puntos);
 		if(kbhit()){
 			
			char tecla = getch();
			if(tecla == DISPARO){
				
				B.push_back(new BALA(N.X() + 2 , N.Y() - 1));
			}	
		}
		
		for(it = B.begin();it != B.end(); it++){
			
			(*it)->Mover();
			if((*it)->Fuera()){
				
				gotoxy((*it)->X(),(*it)->Y());
				printf(" ");
				delete(*it);
				it = B.erase(it);
			}
		}
 		
 		for(itA = A.begin();itA != A.end();itA++){
 			
 			(*itA)->Mover();
 			(*itA)->Colision(N);
		}
 		
		 
		for(itA = A.begin();itA != A.end();itA++){
			
			for(it = B.begin();it != B.end(); it++){
				
				if((*itA)->X() == (*it)->X() && (*itA)->Y() +1 == (*it)->Y() || (*itA)->Y() == (*it)->Y()){
					
					gotoxy((*it)->X(),(*it)->Y());
					printf(" ");
					delete(*it);
					it = B.erase(it);
					
					A.push_back(new ASTEROIDE(rand()%74 +3 ,4));
					gotoxy((*itA)->X(),(*itA)->Y());
					printf(" ");
					delete(*itA);
					itA = A.erase(itA);
					
					puntos += 5;
					
				}
				
			}
			
		}
		
		if(N.VID() == 0){
			game_over = true;
		}
		
 		N.Morir();
 		N.Mover();
 		
 		Sleep(30);
	 }
 	
 	return 0;

}
