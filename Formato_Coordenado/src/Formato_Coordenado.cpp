//============================================================================
// Name        : Formato_Coordenado.cpp
// Author      : lilith.bvndy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>
#include <sstream>
#include <fstream>
using namespace std;

void creaRepresentacion(int **matriz, int val[],int fs[], int cls[], int f, int c, string des){
	//Pasa de una matriz a su representación. Permite almacenar la representación en un archivo.
	ofstream destino;
	destino.open (des.c_str());
	string valores = "valores = [";
	string filas = "filas = [";
	string columnas = "columnas = [";
	int cont=0;
	for (int i = 0; i < f; i++){
		for (int j = 0; j < c; j++){
			if(matriz[i][j]!=0){
				std::ostringstream a;
				val[cont] = matriz[i][j];
				a <<" "<< val[cont];
				valores += a.str();
				std::ostringstream b;
				fs[cont] = i;
				b <<" "<< i;
				filas += b.str();
				std::ostringstream c;
				cls[cont] = j;
				c <<" "<< j;
				columnas += c.str();
				cont++;
			}
		}
	}
	destino << valores <<" ]"<<endl;
	destino << filas <<" ]"<<endl;
	destino << columnas <<" ]"<<endl;

	destino.close();

}

void obtenerMatriz(int val[],int fs[], int cls[],int f, int c, int tam, string des){
	ofstream destino;
	destino.open (des.c_str());
	destino << f <<" "<<c<<endl;

	int matriz[f][c]={0,0,0};
	for(int i=0;i<f;i++){
		for(int j=0;j<c;j++){
			matriz[i][j]=0;
		}
	}

	for(int j=0;j<tam;j++)
		matriz[fs[j]][cls[j]]=val[j];

	for(int x=0;x<f;x++){
		for(int y=0;y<c;y++){
			destino<< matriz[x][y]<<" ";
		}
		destino<<endl;
	}
	destino.close();
}

int obtenerElemento(int val[],int fs[], int cls[], int f, int c, int tamF){
	for (int i = 0; i < tamF; i++){
		if(fs[i]==f && cls[i]==c)
			return val[i];
	}
	return 0;
}

void obtenerFila(int val[],int fs[], int cls[], int fila, int nCol, int tamF){
	int f[nCol]={0};
	for(int i=0;i<tamF;i++){
		if(fs[i]==fila)
			f[cls[i]]=val[i];
	}
	cout<<"Fila "<<fila<<": "<<endl;
	for(int i=0; i<nCol; i++){
		cout << f[i]<< " ";
	}
	cout<<endl;
}

void obtenerColumna(int val[],int fs[], int cls[], int columna, int nFil, int tamC){
	int c[nFil]={0};
	for(int i=0;i<tamC;i++){
		if(cls[i]==columna)
			c[fs[i]] = val[i];
	}
	cout << "Columna "<<columna <<":"<<endl;
	for(int i=0; i<nFil; i++){
		cout << c[i]<<endl;
	}
}

void modificarPosicion(int val[],int fs[], int cls[], int fila, int columna, int e, int tamF, string des){
	ofstream destino;
	destino.open (des.c_str());
	bool aux=false;
	for(int i=0;i<tamF;i++){
		if(fs[i]==fila)
			for(int j=i;j<tamF;j++) //hasta tamaño de columna
				if(cls[i]==columna && fs[i]==fila){
					val[i]=e;
					aux=true;
					break;
				}
	}

	if(!aux){
		int v2[tamF+1];
		int f2[tamF+1];
		int c2[tamF+1];
		int t=0;
		int k=0;
		for(int i=0;i<tamF+1;i++){
			if(t==1){
				v2[i] = e;
				f2[i] = fila;
				c2[i] = columna;
				t=2;
				i++;
			}
			v2[i] = val[k];
			f2[i] = fs[k];
			c2[i] =cls[k];
			if(f2[i]==fila && t==0)
				for(int j=i;j<tamF+1;j++) //hasta tamaño de columna
					if(cls[i]==columna-1 && f2[i]==fila)
						t=1;
			k++;
		}
		destino << "Valores = [ ";
		for(int i=0;i<tamF+1;i++){
			destino << v2[i] << " ";
		}
		destino <<"]"<<endl;
		destino <<"Filas = [ ";
		for(int i=0;i<tamF+1;i++){
			destino << f2[i] << " ";
		}
		destino <<"]"<<endl;
		destino <<"Columnas = [ ";
		for(int i=0;i<tamF+1;i++){
			destino << c2[i] << " ";
		}
		destino <<"]"<<endl;
		destino.close();
	}else{
		destino << "Valores = [ ";
		for(int i=0;i<tamF;i++){
			destino << val[i] << " ";
		}
		destino <<"]"<<endl;
		destino <<"Filas = [ ";
		for(int i=0;i<tamF;i++){
			destino << fs[i] << " ";
		}
		destino <<"]"<<endl;
		destino <<"Columnas = [ ";
		for(int i=0;i<tamF;i++){
			destino << cls[i] << " ";
		}
		destino <<"]"<<endl;
		destino.close();
	}


}

void matrizCuadrada(int val[],int fs[], int cls[], int f, int c, int tamF, string des){
	ofstream destino;
	destino.open (des.c_str());
	destino << f <<" "<<c<<endl;
	int matriz[f][c]={0,0,0};
	for(int i=0;i<f;i++){
		for(int j=0;j<f;j++){
			matriz[i][j]=0;
		}
	}

	int ini=0;
	int index=0;
	int count=0;
	for(int i=0;i<tamF;i++){
		count=0;
		index=fs[i];
		for(int j=ini;j<tamF;j++){ //tamaño de valores
			if(cls[j]==count){
				if(fs[j]==cls[i]){
					matriz[index][count] += val[i]*val[j];
					count++;
				}else
					count=0;
			}else{
				count++;
				j--;
			}
			if(count==f){
				ini=j+1;
				if(ini==tamF) //tamaño de valores
					ini=0;
				break;
			}

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

void sort(int val[], int fs[], int cls[], int p, int q, int r){
    int i, j, k;
    int n1 = q - p + 1;
    int n2 =  r - q;
    int izq[n1],der[n2];
    int fs1[n1], fs2[n2];
    int vl1[n1], vl2[n2];

    for (i = 0; i < n1; i++){
    	izq[i] = cls[p + i];
    	fs1[i] = fs[p+i];
    	vl1[i] = val[p+i];
    }

    for (j = 0; j < n2; j++){
        der[j] = cls[q + 1+ j];
        fs2[j] =  fs[q + 1+ j];
        vl2[j] =  val[q + 1+ j];
    }

    i = 0;
    j = 0;
    k = p;
    while (i < n1 && j < n2)
    {
        if (izq[i] <= der[j])
        {
        	cls[k] = izq[i];
        	fs[k] = fs1[i];
        	val[k] = vl1[i];
        	i++;
        }
        else
        {
        	cls[k] = der[j];
        	fs[k] = fs2[j];
        	val[k] = vl2[j];
        	j++;
        }
        k++;
    }

    while (i < n1)
    {
    	cls[k] = izq[i];
    	fs[k] = fs1[i];
    	val[k] = vl1[i];
    	k++;
    	i++;
    }

    while (j < n2)
    {
    	cls[k] = der[j];
    	fs[k] = fs2[j];
    	val[k] = vl2[j];
    	j++;
    	k++;
    }
}

void mergeSort(int val[], int fs[], int cls[], int p, int r){
	if(p<r){
		int q = p+(r-p)/2;
		mergeSort(val, fs, cls,p,q);
		mergeSort(val, fs, cls,q+1,r);
		sort(val, fs, cls,p,q,r);
	}
}

void matrizTranspuesta(int val[],int fs[], int cls[], int tam, string des){
	ofstream destino;
	destino.open (des.c_str());
	int v2[tam];
	int f2[tam];
	int c2[tam];
	copy(val,val+tam, v2);
	copy(fs,fs+tam, f2);
	copy(cls,cls+tam, c2);

	destino << "Valores = [ ";
	mergeSort(v2,f2,c2,0,tam-1);
	for(int i=0;i<tam;i++){
		destino << v2[i] << " ";
	}
	destino <<"]"<<endl;
	destino <<"Filas = [ ";
	for(int i=0;i<tam;i++){
		destino << c2[i] << " ";
	}
	destino <<"]"<<endl;
	destino <<"Columnas = [ ";
	for(int i=0;i<tam;i++){
		destino << f2[i] << " ";
	}
	destino <<"]"<<endl;
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
	cout << " ******** Formato Coordenado ******** " << endl;
	cout << " ************************************ " << endl;
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

	int valores[tam];
	int filas[tam];
	int columnas[tam];
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
			obtenerMatriz(valores,filas, columnas,f,c,tam, destino);
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
				printf("El elemento en la posición (%i,%i) es: %i\n",i,j,obtenerElemento(valores, filas, columnas, i, j, tam));
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
				obtenerFila(valores, filas, columnas,i,c, tam);
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
				obtenerColumna(valores, filas, columnas,j,f, tam);
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
				modificarPosicion(valores, filas, columnas,i,j,e,tam,destino);
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
				matrizCuadrada(valores, filas, columnas,f,c,tam,destino);
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
			matrizTranspuesta(valores, filas, columnas,tam,destino);
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
