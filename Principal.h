#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <time.h>
#include <math.h>
#include <windows.h>

#define LIGHT_PURPLE     0xD
#define GREEN            0x2

void gotoxy(int x, int y){
	
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void textbgcolor(WORD textcolor, WORD bgcolor){
    WORD color = (bgcolor & 0xF) << 4 | (textcolor & 0xF);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, color);
}
void textcolor(WORD textcolor){
    textbgcolor(textcolor, 255);
}

using namespace std;
class Principal{
	vector<int> opcs;
	vector<int> jugadasValidas;
	vector<int> jugadasFatales;
	
	int datoInit;
	int numOpc;
	
	char resp;
	public:
		void menuP();
		void main();
		void llenarVector(int datoInit);
		void initJugador();
		void jugar();
		
		int validarJugada(int op);
		int min(int datoInitAux);
		int player();
		int pc();
		
};

void Principal::main(){
	bool band = true;
	char tecla;
	
	srand(time(NULL));

	do{
		for(int i = 15; i < 50+15; i++){
			gotoxy(i,3);
			cout << "*";
			gotoxy(i,21);
			cout << "*";

		}
						
		for(int i = 4; i < 17+4; i++){
			gotoxy(15,i);
			cout << "*\t\t\t\t\t\t*"<<endl;
		}
	
		gotoxy(20,10);
		menuP();
	
		tecla = getch();

		switch(tecla){
			case '1':
				do{
					system("cls");
					
					for(int i = 0; i < 80; i++){
						cout << "*";
					}					
					cout<<"\n Ingrese un dato inicial entre 10 - 1000 : ";
					cin>>datoInit;
					if(datoInit<10 || datoInit>1000){
						cout<<endl<<"El dato no esta en el rango requerido!"<<endl;
						system("PAUSE");
					}
				}while(datoInit<10 || datoInit>1000);
				Principal::llenarVector(datoInit);
				Principal::jugar();
				cout<<endl;
				system("PAUSE");
				system("cls");
				break;
			case '2':
				system("cls");
				
					for(int i = 0; i < 80; i++){
						cout << "*";
					}		
				datoInit = rand()%990+10;
				Principal::llenarVector(datoInit);
				cout << endl << " ";				
				Principal::jugar();
				cout<<endl;
				system("PAUSE");
				system("cls");
				break;
			case '3':
				system("cls");
				band = false;
				break;
			default:
				system("cls");
				cout<<"OPCION INVALIDA."<<endl<<endl;
				system("PAUSE");
				system("cls");
		}
	}while(band);
	
	cout<<"Fin del Programa.";
}

int Principal::validarJugada(int op){
	if(pow(op,2)==datoInit) return 0;
	else return 1;
}

void Principal::llenarVector(int datoInit){
	int opciones = 1;
	opcs.clear();
	while(opciones*opciones<=datoInit){
		opcs.push_back(opciones);
		opciones++;
	}
}

void Principal::jugar(){
	int win;
	

	cout << endl;
	cout<<"Deseas Iniciar usted? s/n: ";
	cin>>resp;
	if(resp=='s' || resp=='S'){
		do{
			if(datoInit!=0) win = Principal::player();
			Principal::llenarVector(datoInit);
			if(datoInit!=0) win = Principal::pc();
			Principal::llenarVector(datoInit);
		}while(datoInit!=0);
	}else{
		do{
			if(datoInit!=0) win = Principal::pc();
			Principal::llenarVector(datoInit);
			if(datoInit!=0) win = Principal::player();
			Principal::llenarVector(datoInit);
		}while(datoInit!=0);
	}
	
	if(win==1){
		cout<<endl<<"\t\t******Gano el Jugador******"<< endl;
		for(int i = 0; i < 79; i++)
		cout << "-";
	} 
	else {
		cout<<endl<<"\t\t******Gano la Maquina*******"<< endl;
		for(int i = 0; i < 79; i++)
		cout << "-";
	}
}

int Principal::player(){
//	system("color F1");
	int datoInitAux;
	int numOpc=0;
	bool band;
		
	do{
		textcolor(GREEN);
		cout<<endl<<endl<<"Tu Turno";
		cout<<endl<<endl<<"Raiz: "<<datoInit<<" | Tablero: "<<endl;
		for(int i=0;i<opcs.size();i++){
			cout<<opcs[i]<<"^2  ";
		}
		do{
			cout<<endl;
			cout<<"Elija alguna Opcion: ";
			cin>>numOpc;
			if(numOpc>opcs[opcs.size()-1]) cout<<endl<<"Error - Dato Invalido!!"<<endl;
		}while(numOpc>opcs[opcs.size()-1]);
		
		for(int i=0;i<opcs.size();i++){
			if(opcs[i]==numOpc){
				band = true;
				break;
			}
		}
	}while(!band);
	
	datoInitAux = datoInit;
	datoInit -= pow(numOpc,2);
	cout<<"Resultado: "<<datoInitAux<<" - "<<numOpc<<"^2 = "<<datoInit << endl;
	for(int i = 0; i < 79; i++)
	cout << "-";
	cout << endl;
	if(datoInit==0) return 1;
	else return -1;
}

int Principal::pc(){
	
//	system("color F4");
	int datoInitAux=0;
	int auxRandom = 0;
	int minimun = 0;
	
	int auxopc;
	
	srand(time(NULL));
	jugadasValidas.clear();
	jugadasFatales.clear();
	
		textcolor(LIGHT_PURPLE);
		cout<<endl<<"Juega la Maquina";
		cout<<endl<<endl<<"Raiz: " << datoInit<<"| Tablero: "<<endl;
		for(int i=0;i<opcs.size();i++){
			cout<<opcs[i]<<"^2  ";
		}	
		
			for(int i=0;i<opcs.size();i++){
				if(validarJugada(opcs[opcs.size()-1])==0){
					numOpc = opcs[opcs.size()-1];
					datoInitAux = datoInit;
					datoInitAux -= pow(numOpc,2);
					break; 
				}else if(opcs.size()==1){
					numOpc = opcs[i];
					datoInitAux = datoInit;
					datoInitAux -= pow(numOpc,2); 
					break;
				}else if(validarJugada(opcs[i])==1){
					datoInitAux = datoInit;
					datoInit -= pow(opcs[i],2);
					llenarVector(datoInit);
					auxopc = Principal::min(datoInit);
					if(auxopc>=minimun){
						minimun = auxopc;
						jugadasValidas.push_back(opcs[i]);
					}else{
						jugadasFatales.push_back(opcs[i]);
					}
					datoInit = datoInitAux;
					llenarVector(datoInit);
				}
			}

			if(datoInitAux!=0 && opcs.size()>1){
				if(jugadasValidas.size()>0){
					auxRandom = rand()%jugadasValidas.size();
					numOpc = jugadasValidas[auxRandom];
				}else{
					auxRandom = rand()%jugadasFatales.size();
					numOpc = jugadasFatales[auxRandom];
				}
			}
			
			datoInitAux = datoInit;
			datoInit -= pow(numOpc,2);
			cout<<endl<<"Resultado: "<<datoInitAux<<" - "<<numOpc<<"^2 = "<<datoInit << endl;
				for(int i = 0; i < 79; i++)
				cout << "-";

	if(datoInit==0) return 2;
	else return -1;
}

int Principal::min(int nuevaRaiz){
		for(int i=0;i<opcs.size();i++){
			if(validarJugada(opcs[opcs.size()-1])==0){
				return -1;
			}else if(opcs.size()==1){
				numOpc = opcs[i];
				return -1;
			}else{
				return 1;
			}
		}
}

void Principal::menuP(){
		
		system("color F0");
		cout<<"1.- Ingresar dato inicial."<<endl;
		gotoxy(20,11);
		cout<<"2.- Dato inicial Random."<<endl;
		gotoxy(20,12);
		cout<<"3.- Salir.";
}

#endif
