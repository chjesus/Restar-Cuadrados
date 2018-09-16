#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <time.h>
#include <math.h>

using namespace std;
class Principal{
	vector<int> opcs;
	vector<int> jugadasValidas;
	vector<int> jugadasFatales;
	
	int datoInit;
	int numOpc;
	
	char resp;
	public:
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
		cout<<"1.- Ingresar dato inicial."<<endl;
		cout<<"2.- Dato inicial Random."<<endl;
		cout<<"3.- Salir.";
		tecla = getch();
		switch(tecla){
			case '1':
				do{
					system("cls");
					cout<<"Ingrese un dato inicial entre 10 - 1000 : ";
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
				datoInit = rand()%990+10;
				Principal::llenarVector(datoInit);
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
	
	if(win==1) cout<<endl<<endl<<"Gano el Jugador";
	else cout<<endl<<endl<<"Gano la Maquina;";
}

int Principal::player(){
	int datoInitAux;
	int numOpc=0;
	bool band;
		
	do{
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
	cout<<"Resultado: "<<datoInitAux<<" - "<<numOpc<<"^2 = "<<datoInit;
	
	if(datoInit==0) return 1;
	else return -1;
}

int Principal::pc(){
	
	int datoInitAux=0;
	int auxRandom = 0;
	int minimun = 0;
	
	int auxopc;
	
	srand(time(NULL));
	jugadasValidas.clear();
	jugadasFatales.clear();
		cout<<endl<<endl<<"Juega la Maquina";
		cout<<endl<<endl<<"Raiz: " << datoInit<<"| Tablero: "<<endl;
		for(int i=0;i<opcs.size();i++){
			cout<<opcs[i]<<"^2  ";
		}	
		
			for(int i=0;i<opcs.size();i++){
				if(validarJugada(opcs[opcs.size()-1])==0){
					numOpc = opcs[opcs.size()-1];
					break;
				}else if(opcs.size()==1){
					numOpc = opcs[i];
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
			if(opcs.size()==1){
				datoInitAux = datoInit;
				datoInit -= pow(numOpc,2);
				cout<<endl<<"Resultado: "<<datoInitAux<<" - "<<numOpc<<"^2 = "<<datoInit;
			}else {
				if(jugadasValidas.size()>1){
					auxRandom = rand()%jugadasValidas.size();
					numOpc = jugadasValidas[auxRandom];
				}else{
					auxRandom = rand()%jugadasFatales.size();
					numOpc = jugadasFatales[auxRandom];
				}
				datoInitAux = datoInit;
				datoInit -= pow(numOpc,2);
				cout<<endl<<"Resultado: "<<datoInitAux<<" - "<<numOpc<<"^2 = "<<datoInit;
			}
			
	if(datoInit==0) return 2;
	else return -1;
}

int Principal::validarJugada(int op){
	if(pow(op,2)==datoInit) return 0;
	else return 1;
}

int Principal::min(int nuevaRaiz){
//	if(nuevaRaiz==0) return 1;

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

#endif
