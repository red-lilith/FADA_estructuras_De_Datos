//============================================================================
// Name        : Formato_Comprimido_Columna.cpp
// Author 	   :
//               Carmona Larrotta, Carlos Arturo - 1532083
//               García Correa, Diana Marcela - 1531722
//               Parra Bravo, Diego Alejandro - 1529788
//               Suárez VIllegas, Andrés Felipe - 1527878
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

void creaRepresentacion(int **matriz, vector<int> &val,vector<int> &fs,vector<int> &cls, int f, int c, string des){
	//Pasa de una matriz a su representación. Permite almacenar la representación en un archivo.
	ofstream destino;
	destino.open (des.c_str());
	string valores = "valores = [";
	string filas = "filas = [";
	string columnas = "cColumnas = [";
	int cont=0;
	int aux=0;

	for (int i = 0; i < c; i++){
		std::ostringstream d;
		cls.push_back(cont);
		d <<" "<< cont;
		columnas += d.str();
		for (int j = 0; j < f; j++){
			if(matriz[j][i]!=0){
				std::ostringstream a;
				val.push_back(matriz[j][i]);
				a <<" "<< matriz[j][i];
				valores += a.str();
				std::ostringstream b;
				fs.push_back(j);
				b <<" "<< j;
				filas += b.str();
				aux++;
				cont++;
			}
		}
	}
	std::ostringstream e;
	cls.push_back(aux);
	e <<" "<< aux;
	columnas += e.str();
	destino << valores <<" ]"<<endl;
	destino << filas <<" ]"<<endl;
	destino << columnas <<" ]"<<endl;

	destino.close();
}

void obtenerMatriz(vector<int> &val,vector<int> &fs,vector<int> &cls, int f, int c, string des){
	ofstream destino;
	destino.open (des.c_str());
	destino << f <<" "<<c<<endl;

	int **matriz = (int **) malloc(sizeof(int *) * f);
	int *mem = (int*)malloc(sizeof(int) * (f * c));
	memset(mem, 0x0, sizeof(int) * (f * c));
	for (int i = 0; i < f; i++)
		matriz[i] = mem + i * c;

	for(int i=0;i<c;i++){
		for(int j=cls[i];j<cls[i+1];j++)
			matriz[fs[j]][i]=val.at(j);
	}

	for(int x=0;x<f;x++){
		for(int y=0;y<c;y++){
			destino<< matriz[x][y]<<" ";
		}
		destino<<endl;
	}
	destino.close();
}

int obtenerElemento(vector<int> &val,vector<int> &fs,vector<int> &cls, int f, int c){
	for (int i = cls.at(c); i < cls.at(c+1); i++){
		if(fs.at(i)==f)
			return val.at(i);
	}
	return 0;
}

void obtenerFila(vector<int> &val,vector<int> &fs,vector<int> &cls, int fila, int nCol){
	int tamF = fs.size();
	int f[nCol]={0};
	for(int i=0;i<tamF;i++){
		if(fs.at(i)==fila){
			for(int j=0;j<nCol;j++){
				if(i>=cls.at(j) && i<cls.at(j+1)){
					f[j]=val.at(i);
					break;
				}
			}

		}

	}
	cout<<"Fila "<<fila<<": "<<endl;
	for(int i=0; i<nCol; i++){
		cout << f[i]<< " ";
	}
	cout<<endl;
}

void obtenerColumna(vector<int> &val,vector<int> &fs,vector<int> &cls,  int columna, int nFil){
	int c[nFil]={0};
	for (int i = cls.at(columna); i < cls.at(columna+1); i++){
		c[fs.at(i)]=val.at(i);
	}
	cout << "Columna "<<columna <<":"<<endl;
	for(int i=0; i<nFil; i++){
		cout << c[i]<<endl;
	}
}

void modificarPosicion(vector<int> &val,vector<int> &fs,vector<int> &cls, int fila, int columna, int e, string des){
	int ft = fs.size();
	int ct = cls.size();
	ofstream destino;
	destino.open (des.c_str());
	bool x=true;
	for (int i = cls.at(columna); i < cls.at(columna+1); i++){
		if(fs.at(i)==fila){
			val.at(i)=e;
			x=false;
			break;
		}
	}

	if(x){
		for (int i = cls.at(columna); i < cls.at(columna+1); i++){
			if((fs.at(i)-1)==fila){
				val.insert(val.begin()+i, e);
				fs.insert(fs.begin()+i, fila);
				ft++;
				break;
			}
			else if((fs.at(i)+1)==fila){
				val.insert(val.begin()+i+1, e);
				fs.insert(fs.begin()+i+1, fila);
				ft++;
				break;
			}
		}
	}
	if(x)
		for(int i=columna+1;i<ct;i++)
			cls.at(i) = cls.at(i)+1;

	destino << "Valores = [ ";
	for(int i=0;i<ft;i++){
		destino << val.at(i) << " ";
	}
	destino <<"]"<<endl;
	destino <<"Filas = [ ";
	for(int i=0;i<ft;i++){
		destino << fs.at(i) << " ";
	}
	destino <<"]"<<endl;
	destino <<"cColumnas = [ ";
	for(int i=0;i<ct;i++){
		destino << cls.at(i) << " ";
	}
	destino <<"]"<<endl;
	destino.close();


}

void matrizCuadrada(vector<int> &val,vector<int> &fs,vector<int> &cls, int f, int c, string des){
	int tamF = fs.size();
	ofstream destino;
	destino.open (des.c_str());
	destino << f <<" "<<c<<endl;
	int **matriz = (int **) malloc(sizeof(int *) * f);
	int *mem = (int*)malloc(sizeof(int) * (f * c));
	memset(mem, 0x0, sizeof(int) * (f * c));
	for (int i = 0; i < f; i++)
		matriz[i] = mem + i * c;

	for(int j=0;j<c;j++){
		int ini = cls.at(j);
		int fin=cls.at(j+1);
		int aux=0;
		int r=0;
		while(aux<f){
			int valor=0;
			for(int i=ini;i<fin;i++){ //vuelve a buscar con la columna 0 por la siguiente fila=aux
				for(int k=r;k<tamF;k++){
					if(fs.at(k)==aux){
						if(k>=cls.at(fs.at(i))&&k<cls.at(fs.at(i)+1)){
							valor += val.at(i)*val.at(k);
							r=k+1;
							break;
						}
					}
				}
			}
			matriz[aux][j]=valor;
			aux++;
			r=0;
		}

	}

	for(int x=0;x<f;x++){
		for(int y=0;y<c;y++){
			destino<< matriz[x][y]<<" ";
		}
		destino<<endl;
	}
	destino.close();
}

void organizarFilas(vector<int> &auxF,vector<int> &auxFi){
	vector<int> orden(auxF.size());

    int count[auxF.size() + 1];
    memset(count, 0, sizeof(count));

    for(unsigned i = 0; i<auxF.size(); i++)
        count[auxF.at(i)]++;

    for (unsigned i = 1; i <= auxF.size(); i++)
        count[i] += count[i-1];

    for (unsigned i = 0; i<auxF.size(); i++){
    	int x = auxF.at(i);
    	orden.at(count[x]-1) = i;
        count[auxF.at(i)]--;
    }

    for (unsigned i = 0; i<auxF.size(); i++)
    	auxFi.at(i) = orden.at(i);

}

void matrizTranspuesta(vector<int> &val,vector<int> &fs,vector<int> &cls, string des){
	int c = cls.size()-1;
	int tamF= fs.size();
	ofstream destino;
	destino.open (des.c_str());
	vector<int> auxF;
	vector<int> auxFi;

	for(int i=0;i<tamF;i++)
		auxFi.push_back(i);

	organizarFilas(fs, auxFi);
	destino << "Valores = [ ";
	for(int i=0;i<tamF;i++){
		auxF.push_back(fs.at(auxFi.at(i)));
		destino << val.at(auxFi.at(i)) << " ";
	}
	destino <<"]"<<endl;
	destino <<"Filas = [ ";
	int cont=0;
	for(int j=0;j<c;j++){
		int ini=cls.at(j);
		int fin=cls.at(j+1);
		if(cont>tamF-1)
			break;
		if(auxFi.at(cont)>=ini&&auxFi.at(cont)<fin){
			destino << j << " ";
			cont++;
			j=-1;
		}
	}

	destino <<"]"<<endl;
	destino <<"cColumnas = [ ";
	int aux=auxF.at(0);
	destino << 0 << " ";
	for(int i=1;i<tamF;i++){
		if(auxF.at(i)>aux){
			destino << i << " ";
			aux++;
		}
	}
	destino <<tamF<<" ]"<<endl;
	destino.close();
}


int main() {
	int seleccion=0, repetir=1;
	string ruta =""; //ejemplo de entrada
	string destino;
	int f, c;
	string fila;
	int** matriz;
	int tam=0;
	cout << " ************************************ " << endl;
	cout << " ***********  ESTRUCTURAS  ********** " << endl;
	cout << " ************* DE DATOS ************* " << endl;
	cout << " ******** Formato Comprimido ******** " << endl;
	cout << " ************ Por Columna *********** " << endl;
	cout << " ******* CREAR REPRESENTACIÓN ******* " << endl;
	cout << " ************************************ " << endl;
	cout<<endl;
	cout << "Ingrese Ruta + NombreFuente.txt:" << endl;
	cin >> ruta;
	cout << "Ingrese Ruta Destino + NombreDestino.txt:" << endl;
	cin >> destino;
	{
		ifstream cin(ruta.c_str());
		cin >> f >> c; //Almacena la fila y la columna
			matriz = new int*[f];
			for (int i = 0; i < f; ++i)
				matriz[i] = new int[c];
			for (int i = 0; i < f; i++)
				for (int j = 0; j < c; j++){
					cin >> matriz[i][j]; //Almacena los valores en la matriz
					if(matriz[i][j]!=0)
					tam++;
				}
	}

	vector<int>valores;
	vector<int>filas;
	vector<int>columnas;

	creaRepresentacion(matriz, valores, filas, columnas, f, c, destino);
	cout << "Representación Guardada Exitosamente En " << destino<<endl;

	do {
		system("clear");
		cout << " **************  MENU  ********** " << endl;
		cout << " * 1. Obtener Matriz		* " << endl;
		cout << " * 2. Obtener Elemento		* " << endl;
		cout << " * 3. Obtener Fila		* " << endl;
		cout << " * 4. Obtener Columna		* " << endl;
		cout << " * 5. Modificar Posición	* " << endl;
		cout << " * 6. Matriz Cuadrada		* " << endl;
		cout << " * 7. Matriz Transpuesta	* " << endl;
		cout << " * 8. Terminar			* " << endl;
		cout << " ******************************** " << endl;
		cin >>  seleccion;
		int i =0;
		int j=0;
		int e=0;
		switch(seleccion) {
		case 1:
			system("clear");
			cout << " ********** OBTENER MATRIZ ********** " << endl;
			cout << "Ingrese Ruta Destino + NombreDestino.txt:" << endl;
			cin >> destino;
			obtenerMatriz(valores,filas, columnas,f,c, destino);
			cout << "Matriz Guardada Exitosamente En " << destino<<endl;
			cin.get();
			cin.get();
			break;
		case 2:
			system("clear");
			cout << " ********* OBTENER ELEMENTO ********* " << endl;
			cout << "Ingrese N° de Fila:" << endl;
			cin >> i;
			cout << "Ingrese N° de Columna:" << endl;
			cin >> j;
			if(i<f && j<c)
				printf("El elemento en la posición (%i,%i) es: %i\n",i,j,obtenerElemento(valores, filas, columnas, i, j));
			else
				cout << "Ocurrió un Error. Intente de Nuevo con Indices Válidos"<<endl;
			cin.get();
			cin.get();
			break;
		case 3:
			system("clear");
			cout << " *********** OBTENER FILA *********** " << endl;
			cout << "Ingrese N° de Fila:" << endl;
			cin >> i;
			if(i<f)
				obtenerFila(valores, filas, columnas,i,c);
			else
				cout << "Ocurrió un Error. Intente de Nuevo con un Indice Válido"<<endl;
			cin.get();
			cin.get();
			break;
		case 4:
			system("clear");
			cout << " ********** OBTENER COLUMNA ********* " << endl;
			cout << " ************************************ " << endl;
			cout<<endl;
			cout << "Ingrese N° de Columna:" << endl;
			cin >> j;
			if(j<c)
				obtenerColumna(valores, filas, columnas,j,f);
			else
				cout << "Ocurrió un Error. Intente de Nuevo con un Indice Válido"<<endl;
			cin.get();
			cin.get();
			break;
		case 5:
			system("clear");
			cout << " ******** MODIFICAR POSICIÓN ******** " << endl;
			cout << "Ingrese N° de Fila:" << endl;
			cin >> i;
			cout << "Ingrese N° de Columna:" << endl;
			cin >> j;
			cout << "Ingrese El Nuevo Número: " << endl;
			cin >> e;
			cout << "Ingrese Ruta Destino + NombreDestino.txt:" << endl;
			cin >> destino;
			if(i<f && j<c){
				modificarPosicion(valores, filas, columnas,i,j,e,destino);
				cout << "Matriz Modificada Guardada Exitosamente En " << destino<<endl;
			}
			else
				cout << "Ocurrió un Error. Intente de Nuevo con Indices Válidos"<<endl;
			cin.get();
			cin.get();
			break;
		case 6:
			system("clear");
			cout << " ********** MATRIZ CUADRADA ********* " << endl;
			if(f==c){
				cout << "Ingrese Ruta Destino + NombreDestino.txt:" << endl;
				cin >> destino;
				matrizCuadrada(valores, filas, columnas,f,c,destino);
				cout << "Matriz Cuadrada Guardada Exitosamente En " << destino<<endl;
			}else
				cout << "La Matriz Debe Ser Cuadrada (nxn)" << endl;

			cin.get();
			cin.get();
			break;
		case 7:
			system("clear");
			cout << " ******** MATRIZ TRANSPUESTA ******** " << endl;
			cout << "Ingrese Ruta Destino + NombreDestino.txt:" << endl;
			cin >> destino;
			matrizTranspuesta(valores, filas, columnas,destino);
			cout << "Representación de Matriz Transpuesta Guardada Exitosamente En " << destino<<endl;
			cin.get();
			cin.get();
			break;
		case 8:
			system("clear");
			cout << " ********* ¡¡HASTA PRONTO!! ********* " << endl;
			cout << " ************************************ " << endl;
			cin.get();
			cin.get();
			repetir=0;
			break;
		default: {
			system("clear");
			cout << "Opción Inválida" << endl;
			cin.get();
			cin.get();
			}
		}
	}
	while (repetir==1);
}
