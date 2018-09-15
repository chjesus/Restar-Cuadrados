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
	vector<int> auxPos;
	vector<int> playerGana; //Jugador Puede Ganar en el siguiente turno
	vector<int> pcGana; //Pc Puede Ganar en el siguiente Turno
	int datoInit;
	char resp;
	public:
		void main();
		void llenarVector(int datoInit);
		void initJugador();
		void jugar();
		int validar(int dataInicial,int aux);
		
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
	
	if(win==1) cout<<endl<<"Gano el Jugador";
	else cout<<endl<<"Gano la Maquina;";
}

int Principal::player(){
	int datoInitAux;
	int numOpc;
	bool band;
	
	do{
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
	datoInit -= numOpc*numOpc;
	cout<<"Resultado: "<<datoInitAux<<" - "<<numOpc<<"^2 = "<<datoInit;
	
	if(datoInit==0) return 1;
	else return -1;
}

int Principal::pc(){
	
	int datoInitAux;
	int numOpc;
	bool band;
	int aux, auxopc;
	
	srand(time(NULL));

	playerGana.clear();
	pcGana.clear();
	
	cout<<endl<<endl<<"Raiz: " << datoInit<<"| Tablero: "<<endl;
	for(int i=0;i<opcs.size();i++){
		cout<<opcs[i]<<"^2  ";
	}	
		for(int i=0;i<opcs.size();i++){
			if(validar(datoInit,opcs[i])==0){
				numOpc = opcs[i];
				break;
			}else if(validar(datoInit,opcs[i+1])==1){
				playerGana.push_back(opcs[i]);
			}else if(validar(datoInit,opcs[i+1])==2){
				pcGana.push_back(opcs[i]);
			}
		}

		if(datoInit!=0){
			if(playerGana.size()==0){
				numOpc = rand()%pcGana.size();
			}else if(playerGana.size()>0){
				numOpc = rand()%playerGana.size();
			}
		}

	datoInitAux = datoInit;
	datoInit -= numOpc*numOpc;
	cout<<endl<<"Resultado: "<<datoInitAux<<" - "<<numOpc<<"^2 = "<<datoInit;
	
	if(datoInit==0) return 2;
	else return -1;
}

int Principal::validar(int datoInicial,int aux){
	int nuevoDatoInit = datoInicial - (aux*aux);
	int opciones = 1;
	
	if(aux*aux == datoInicial) return 0;
	
	auxPos.clear();
	while(opciones*opciones<=nuevoDatoInit){
		auxPos.push_back(opciones);
		opciones++;
	}
	
	if(nuevoDatoInit-pow(auxPos[auxPos.size()-1],2)==1){
		return 1;
	}else return 2;
}
#endif
