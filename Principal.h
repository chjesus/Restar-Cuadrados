#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <conio.h>

using namespace std;
class Principal{
	public:
		void main();
};

void Principal::main(){
	bool band = true;
	char tecla;
	
	do{
		cout<<"1.- Ingresar dato inicial."<<endl;
		cout<<"2.- Dato inicial Random."<<endl;
		cout<<"3.- Salir.";
		tecla = getch();
		switch(tecla){
			case '1':
				system("cls");
				cout<<"Opcion 1."<<endl;
				system("PAUSE");
				system("cls");
				break;
			case '2':
				system("cls");
				cout<<"Opcion 1."<<endl;
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
#endif
