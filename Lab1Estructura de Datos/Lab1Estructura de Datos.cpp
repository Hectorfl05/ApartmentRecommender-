
#include <iostream>
#include <json/json.h>
#include <string>
#include <fstream>
#include <list>
#include "Apartment.h"



using namespace std;


int BuscarApartamento(vector<Apartment> Mapa, string negocio, int index)
{
    //Inicialización de pasos que debe recorrer hacia arriba y hacia abajo
    int pasosBack = -1;

    int pasosFront = -1;

    //Lista temporal de string
    list<string> Temp;


    //Iterador que recorre el mapa de apartamentos del índice selccionado hacia atras
    for (auto it3 = Mapa.begin() + index; it3 != Mapa.begin(); it3--)
    {
        Temp = it3->getBusiness();

        if (find(Temp.begin(), Temp.end(), negocio) != Temp.end())
        {
            //Obtiene la distancia desde el apartamento hasta el negocio
            pasosBack = distance(it3, Mapa.begin() + index);

            break;

        }

    }

    //Iterador que recorre el mapa de apartamentos del indice seleccionado hacia después
    for (auto it2 = Mapa.begin() + index; it2 != Mapa.end(); it2++)
    {
        Temp = it2->getBusiness();

        if (find(Temp.begin(), Temp.end(), negocio) != Temp.end())
        {
            //Obtiene la distancia desde el apartamento hasta el negocio
            pasosFront = distance(Mapa.begin() + index, it2);

            break;

        }
    }


    //Si no encontró un negocio en un recorrido hacia abajo o hacia arriba, devuelve el primer apartamento que encontró
    if (pasosFront == -1 || pasosBack == -1)
    {
    
        return max(pasosBack, pasosFront);
    
    //Si no encontro el negocio en el mapa, retorna -1
    }else if( pasosFront == -1 && pasosBack == -1)
    {
    
        return -1;

    }

    //Retorna la cantidad minima de pasos necesarios para encontrar el negocio
      return min(pasosBack, pasosFront);

}


int Recomendacion(vector<Apartment> Mapa, vector<string> B)
{   
    //Inicialización de variables comparativas
    int MinPasos = numeric_limits<int>::max();
    int BestIndex = -1;
    int BestMaxpasitos = 0;

    //Recorre el mapa de apartamentos
    for(int i = 0; i < Mapa.size(); i++)
    {
        //Inicialización de variables contadoras de pasos
        int totalPasos = 0;
        int Maxpasitos = 0;

        //Foreach que recorre el vector de negocios
        for(const string& negocio:B)
        {
            //Inicializa la cantidad de pasos necesarios para encontrar un negocio
            int pasitos = BuscarApartamento(Mapa,negocio,i);

            //Registra la mayor cantidad de pasos por recorrido
            if(pasitos > Maxpasitos)
            {
                Maxpasitos = pasitos;
            
            }

            //Detiene la función si no se encontro un negocio
            if(pasitos == -1)
            {
            
                BestIndex = NULL;

                return BestIndex;
            }
        
            //Realiza la sumatoria de pasos 
            totalPasos += pasitos;

        }

        //Compara la cantidad de pasos para cada apartamento
        if(totalPasos < MinPasos)
        {
            //Si es menor, el apartamento se vuelve el "Recomendado"
            MinPasos = totalPasos;
        
            BestIndex = i;

            BestMaxpasitos = Maxpasitos;

         
        }else if(totalPasos == MinPasos) 
        {
           if(Maxpasitos < BestMaxpasitos) //Verifica la maxima cantidad de pasos recorridos en ambos apartamentos
           {
               //Si la maxima cantidad pasos del Apartamento actual es menor que el "Recomendado", declara el nuevo "Recomendado
               MinPasos = totalPasos;

               BestIndex = i;

               BestMaxpasitos = Maxpasitos;
          
           }
        }       
    }

    //Regresa el Index del Apartamento recomendado
    return BestIndex;

}

template<typename T>

    void EmptyVector(vector<T> &vector )
    {
        vector.clear();
    }




int main()
{ 
    //Inicializaciónd de variables de ruta de archivo
    string ruta;
    bool open = false;
    ifstream file;
    ofstream Archivo;
    string ruta2;

    //Bucle While que impide el avance del programa, hasta que no se haya completado la lectura del archivo JSON Line
    do
    {
        cout << "Ingrese la ruta de archivo del archivo JSON Line (sin comillas)" << endl;

        cin >> ruta;

        //Lee el Json Line
        file.open(ruta,ios::in);

        cin.clear();

        system("cls");

        cout << "Error al abrir archivo" << endl;
        
    } while (!file.is_open());

    system("cls");

    do
    {
        
        cout << "Ingrese la direccion donde desea exportar los apartamentos recomendados (sin comillas)" << endl;
        cin >> ruta2;

        Archivo.open(ruta2 + "/Recomendacion Apartamentos.txt");

       
        cin.clear();

        system("cls");

        cerr << "No se pudo generar el Archivo.text" << endl;

    } while (Archivo.fail());

    system("cls");

	// Crea un lector de JSON
	Json::Reader reader;
	Json::Value json;

    //String que representa cada linea del archivo
    string line;


    // Lee el archivo línea por línea
    while (getline(file, line))
    {
   
        // Parsea la línea JSON
        bool parsed = reader.parse(line, json, false);

        //Valida si se pudo parsear la línea JSON
        if (!parsed) {
            cerr << "Error al analizar la línea JSON: " << reader.getFormattedErrorMessages() << endl;
            return 1;
        }


        //Separa la linea JSON en dos inputs
        const Json::Value input1Array = json["input1"];
        const Json::Value input2Array = json["input2"];


        //Inicializa el vector de Apartamentos y de parámetros
        vector<Apartment> Map;

        vector<string> input2;


        //Recorre cada elemento del Array: Input 1
        for (const auto& item : input1Array) 
        {  
            //Crea una lista temporal de negocios
            list<string> negocios;
       
            //Recorre el listado de nombres del elemento 
            for(const auto& itemB : item.getMemberNames())
            {

                if(item[itemB].asBool())//Verifica que el negocio se encuentre en el apartamento
                {
                    //Si se encuentra, agrega el negocio al listado 
                    negocios.push_back(itemB);

                }
            }
            
            //Crea una instancia de la clase Apartment,teniendo la lista temporal de negocios como parámetro
            Apartment apartment(negocios);

            //Añade el apartamento al mapa de apartamentos
            Map.push_back(apartment);
            
        }

        //Recorre cada elemento del input 2, y lo añade al vector de parámetros
        for (const auto& item : input2Array) {
            
            input2.push_back(item.asString());
        }
            
        //Declara una variable con el resultado del índice del apartamento "Recomendado"
        int resultado = Recomendacion(Map, input2);

      

        if(resultado == 0)
        {
        
           Archivo << "[" << "]" << endl;
           cout << "[" << "]" << endl;

        }else
        {
        
            Archivo << "[" << resultado << "]" << endl;
            cout << "[" << resultado << "]" << endl;
        }
        
        //Vacia los vectores 
        EmptyVector(Map);

        EmptyVector(input2);
                    
        Archivo.clear();
    }

    // Cerrar el archivo
    file.close();
    Archivo.close();
}

