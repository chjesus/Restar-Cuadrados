#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <time.h>

using namespace std;
class Principal{
	vector<int> opcs;
	int datoInit;
	public:
		void main();
		void llenarVector(int datoInit);
		void initJugador();
		void jugar();
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
	
	while(opciones*opciones<=datoInit){
		opcs.push_back(opciones);
		opciones++;
	}
}

void Principal::jugar(){
	cout<<"Tablero: "<<endl;
	for(int i=0;i<opcs.size();i++){
		cout<<opcs[i]<<"^2  ";
	}
}
#endif
