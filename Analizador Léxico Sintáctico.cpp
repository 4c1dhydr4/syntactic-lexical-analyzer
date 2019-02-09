/*
Ejemplo de Analizador Léxico Sintáctico
Luis Augusto Quiroz Burga
*/

#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;

const int MAXIN = 50, MAXLEX = 10;
char entrada[MAXIN];
bool fin = true, error = false;
string patron = "(aba|bab)(a|b)*(ab|ba)", parse = "";
int estado = 0, contAux = 0, posIni = 0, posFin = 0;

struct Lexema{
	string parseIzq;
	string lexema;
};

Lexema lexemas[MAXLEX]; int numLex = 0;

void guardaToken(int &posIni, int &posFin);
void analisisSintactico();
void parseIzquierdo();
	
int main(int argc, char *argv[]) {
	cout << "Trabajo de Aplicacion Compiladores y Lenguajes de Programacion" << endl;
	
	cout << "Ingrese Tira: " << endl;
	gets(entrada);
	char *p = entrada;
	do{
		if(*p=='a' || *p=='b' || *p=='\0' || *p==' '){
			switch(estado){
			case 0:
				if(*p=='a'){
					parse += "1";
					estado = 1; posFin++;
				}
				else if(*p=='b'){
					parse += "2";
					estado = 2; posFin++;
				}
				else{
					error = true;
				}
				break;
			case 1:
				if(*p=='b'){
					parse += "3";
					estado = 3; posFin++;
				}
				else{
					error = true;
				}
				break;
			case 2:
				if(*p=='a'){
					parse += "4";
					estado = 4; posFin++;
				}
				else
					error = true;
				break;
			case 3:
				if(*p=='a'){
					parse += "5";
					estado = 5; posFin++;
				}
				else
					error = true;
				break;
			case 4:
				if(*p=='b'){
					parse += "6";
					estado = 5; posFin++;
				}
				else
					error = true;
				break;
			case 5:
				if((*p=='\0' || *p==' ') && contAux>=2){
					p--; p--;
					int tam = parse.length();
					if(*p=='a'){
						parse.erase(tam-2);
						parse += "9";
						estado = 6; posFin++;
					}
					else if(*p=='b'){
						parse.erase(tam-2);
						parse += "10";
						estado = 7; posFin++;
					}
					else{
						error = true; cout << "Debug 1" << endl;
					}
				}
				else if(*p=='a' || *p=='b'){
					if(*p=='a')
						parse += "7";
					else
						parse += "8";
					contAux++; posFin++;
				}
				else{
					error = true;
				}
				break;
			case 6:
				if(*p=='b'){
					parse += "11";
					estado = 8;
				}
				else
					error = true;
				break;
			case 7:
				if(*p=='a'){
					parse += "12";
					estado = 8;
				}
				else
					error = true;
				break;
			case 8:
				if((*p==' ') || (*p=='\0')){
					cout << "Token Leido!!!" << endl;
					lexemas[numLex].parseIzq = parse; parse = "";
					guardaToken(posIni,posFin);
					if(*p==' '){
						estado = 0;
					}else{
						fin = false;
					}
				}
				else{
					error = true;
				}
				break;
			default:
				cout << "Estado no Correcto" << endl;
				break;
			}
		}
		else
			error = true;
		p++;
		if(error)
			fin = false;
	}while(fin);
	
	if(error)
		cout << "Error" << endl;
	analisisSintactico();
	parseIzquierdo();
	return 0;
}

void guardaToken(int &posIni, int &posFin){
	string token = "";
	for(int i=posIni;i<posFin;i++){
		token += entrada[i];
	}
	lexemas[numLex].lexema = token; numLex++;
	posIni = posFin;
}

void analisisSintactico(){
	string impresos[MAXLEX]; int lexImpresos = 0; bool flagImpreso = false;
	int id = 0;
	cout << "================== Analisis Lexico ==================" << endl;
	cout << "Lexema" << setw(30) << "Patron" << setw(20) << "Token" << endl;
	for(int i=0;i<numLex;i++){
		for(int j=0;j<=lexImpresos;j++){
			if(lexemas[i].lexema==impresos[j])
				flagImpreso = true;
		}
		if(!flagImpreso){
			cout << lexemas[i].lexema << setw(30) << patron << setw(20) << "ID," << id << endl;
			impresos[lexImpresos] = lexemas[i].lexema; lexImpresos++;
			id++;
		}
		flagImpreso = false;
	}
}

void parseIzquierdo(){
	string impresos[MAXLEX]; int lexImpresos = 0; bool flagImpreso = false;
	cout << "================== Analisis Sintactico ==================" << endl;
	cout << "Lexema" << setw(20) << "Parse Izquierdo" << endl;
	for(int i=0;i<numLex;i++){
		for(int j=0;j<=lexImpresos;j++){
			if(lexemas[i].lexema==impresos[j])
				flagImpreso = true;
		}
		if(!flagImpreso){
			cout << lexemas[i].lexema << setw(20) << lexemas[i].parseIzq << endl;
			impresos[lexImpresos] = lexemas[i].lexema; lexImpresos++;
		}
		flagImpreso = false;
	}
}















