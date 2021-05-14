#include <bits/stdc++.h>

using namespace std;

char generadores[1002];
char terminales[1002];
char nuevo_generador;
int opcionales[18] = {128,129,132,133,135,136,137,138,139,140,141,142,145,146,155,225,230,245};
int n_generadores;
int opcion_ocupada;

map <char,int> indices;
map <char,bool> existe_terminal;

struct produccion{
    char generador;
    string simbolos[1002];
    int num_simbolos;
    bool encontrado;
};

produccion producciones[1002];

void entradas()
{
    gets(generadores);
    gets(terminales);

    for (int i=0;i<strlen(terminales);i+=2) {
        existe_terminal[terminales[i]] = true;
    }

    for (int i=0;i<strlen(generadores);i+=2)
    {
        char generador;
        cin>>generador;
        producciones[n_generadores].generador = generador;

        indices[generador] = n_generadores;

        char elementos[10002];
        cin>>elementos;
        int pos_simbolos= -1;
        for(int j=0;j<strlen(elementos);j++)
        {
            string aux;
            while(elementos[j]!=',' && j<strlen(elementos)){
                aux+=elementos[j];
                j++;
            }
            pos_simbolos++;
            producciones[n_generadores].simbolos[pos_simbolos]=aux;
            producciones[n_generadores].num_simbolos++;

            produccion auxiliar;
            aux.erase();
        }
        n_generadores++;
    }
}
void imprimir_original()
{
    cout<<"Simbolos generadores: ";
    puts(generadores);
    cout<<"Simbolos terminales: ";
    puts(terminales);
    cout<<"***Gramatica original***"<<'\n';
    for (int i=0;i<n_generadores;i++){
        cout<<producciones[i].generador<<"->";
        for (int j=0;j<producciones[i].num_simbolos;j++){
            cout<<producciones[i].simbolos[j]<<"|";
        }
        cout<<'\n';
    }
    cout<<"****************"<<'\n';
}

void limpieza_inicial(char genera)
{
    int pos_indice = indices[genera];
    int aux_numSimbolos = producciones[pos_indice].num_simbolos;
    producciones[pos_indice].encontrado = true;

    for (int i=0;i<aux_numSimbolos;i++)
    {
        int len_string = producciones[pos_indice].simbolos[i].size();
        for (int j=0;j<len_string;j++)
        {
            int aux_indice = indices[producciones[pos_indice].simbolos[i].at(j)];
            if (producciones[aux_indice].encontrado){
                continue;
            }
            limpieza_inicial(producciones[pos_indice].simbolos[i].at(j));
        }
    }
}

void segunda_limpieza()
{
    for (int a=0;a<n_generadores;a++)
    {
        if (producciones[a].encontrado)
        {
            int aux_numSimbolos = producciones[a].num_simbolos;
            for (int i=0;i<aux_numSimbolos;i++)
            {
                int len_string = producciones[a].simbolos[i].size();
                for (int j=0;j<len_string;j++)
                {
                    bool bandera = false;
                    int aux_indice = indices[producciones[a].simbolos[i].at(j)];
                    if (producciones[aux_indice].num_simbolos==1 && producciones[aux_indice].simbolos[0].size()==1){
                        if (existe_terminal[producciones[aux_indice].simbolos[0].at(0)]){
                            producciones[a].simbolos[i].at(j) = producciones[aux_indice].simbolos[0].at(0);
                            producciones[aux_indice].encontrado = false;
                            bandera = true;
                        }
                        if (bandera) continue;
                    }
                    if (producciones[a].simbolos[i].at(j)=='E'){
                        producciones[a].num_simbolos = 1;
                        producciones[a].simbolos[i].at(j)=' ';
                        continue;
                    }
                }
            }
        }
    }
    for (int a=0;a<n_generadores;a++)
    {
        if (producciones[a].encontrado)
        {
            int aux_numSimbolos = producciones[a].num_simbolos;
            for (int i=0;i<aux_numSimbolos;i++)
            {
                int len_string = producciones[a].simbolos[i].size();
                for (int j=0;j<len_string;j++)
                {
                    bool bandera = false;
                    int aux_indice = indices[producciones[a].simbolos[i].at(j)];
                    int cont = 0;
                    if (producciones[aux_indice].num_simbolos==1)
                    {
                        for (int k=0;k<producciones[aux_indice].simbolos[0].size();k++)
                        {
                            if (existe_terminal[producciones[aux_indice].simbolos[0].at(k)])
                            {
                                cont++;
                            }
                        }
                        if (cont==producciones[aux_indice].simbolos[0].size())
                        {
                            producciones[a].simbolos[i] = producciones[aux_indice].simbolos[0];
                            producciones[aux_indice].encontrado = false;
                            bandera = true;
                        }
                        if (bandera) continue;
                    }
                }
            }
        }
    }
}
bool checar(string aux, char generador)
{
    for (int i=0;i<n_generadores;i++){
        if (producciones[i].encontrado)
        {
            for (int j=0;j<producciones[i].num_simbolos;j++)
            {
                if (producciones[i].simbolos[j]==aux && producciones[i].generador!=generador){
                    nuevo_generador = producciones[i].generador;
                    return true;
                }
            }
        }
    }
    return false;
}

void evaluar(int len_string,int a, int i)
{
    string aux;
    string aux2;
    string fin_simbolo;
    int pos = 0;
    int secciones = 0;

    if (len_string==1) //to do esta popó de bebé apestoso
    {
        /*int aux_indice = indices[producciones[a].simbolos[i].at(0)];
        int pos_aux = producciones[a].num_simbolos - 1;
        for (int j=0;j<producciones[aux_indice].num_simbolos;j++)
        {
            cout<<"yo soy el simbolo a insertar en "<<j<<" : "<<producciones[aux_indice].simbolos[j]<<'\n';
            producciones[a].simbolos[pos_aux] = producciones[aux_indice].simbolos[j];
            producciones[a].num_simbolos++;
        }
        producciones[a].num_simbolos--;
        producciones[aux_indice].encontrado = false;*/

        /*int aux_indice = indices[producciones[a].simbolos[i].at(0)];
        for (int j=0;j<producciones[aux_indice].num_simbolos;j++)
        {
            int len_aux = producciones[aux_indice].simbolos[0].size();
            if (len_aux % 2 ==0) secciones = len_aux /2;
            else secciones = (len_aux/2)+1;

            producciones[n_generadores].generador = char(opcionales[opcion_ocupada]);
            producciones[n_generadores].encontrado = true;
            indices[opcionales[opcion_ocupada]] = n_generadores;
            opcion_ocupada++;

            for (int k=len_aux/2;k<len_aux;k++)
            {
                aux+=producciones[aux_indice].simbolos[0].at(k);
            }
            producciones[n_generadores].simbolos[0] = aux;
            aux.erase();
            aux = producciones[aux_indice].simbolos[0];
            for (int k=0;k<len_aux/2;k++){
                aux.pop_back();
            }
            producciones[aux_indice].simbolos[0] = aux;
            n_generadores++;
        }*/
    }
    else //tu si sirves, guapo
    {
        for (int j=0;j<len_string;j++)
        {
            bool genera = false;
            fin_simbolo+=producciones[a].simbolos[i].at(j);
            int aux_indice = indices[producciones[a].simbolos[i].at(j)];
            if (producciones[aux_indice].encontrado){
                genera = true;
            }
            if (genera)
            {
                aux.erase();
                aux+= producciones[a].simbolos[i].at(j);
                pos = j+1;
                for (int k=pos;k<len_string;k++)
                {
                    int aux_indice2 = indices[producciones[a].simbolos[i].at(k)];
                    if (producciones[aux_indice].encontrado)
                    {
                        aux+= producciones[a].simbolos[i].at(k);
                        if(checar(aux, producciones[a].generador))
                        {
                            fin_simbolo.pop_back();
                            fin_simbolo+=nuevo_generador;

                            for (int l=k+1;l<len_string;l++)
                            {
                                fin_simbolo+=producciones[a].simbolos[i].at(l);
                            }
                            producciones[a].simbolos[i] = fin_simbolo;
                            j++;
                        }
                        pos++;
                    }
                }
            }
            else
            {
                producciones[n_generadores].generador = char(opcionales[i]);
                producciones[n_generadores].encontrado = true;
                indices[opcionales[i]] = n_generadores;
                int indicador = 0;
                for (int k=j+1;k<len_string;k++)
                {
                    producciones[n_generadores].simbolos[indicador].at(k) = producciones[a].simbolos[i].at(j);
                }
                n_generadores++;
            }
        }
    }
}

void chomsky()
{
    int bandera = false;
    for (int a=0;a<n_generadores;a++)
    {
        if (producciones[a].encontrado)
        {
            int aux_numSimbolos = producciones[a].num_simbolos;
            for (int i=0;i<aux_numSimbolos;i++)
            {
                bandera = false;
                int len_string = producciones[a].simbolos[i].size();

                if (len_string==1)
                {
                    if (existe_terminal[producciones[a].simbolos[i].at(0)]){
                        bandera = true;
                    }
                }
                else if (len_string==2)
                {
                    int aux_indice = indices[producciones[a].simbolos[i].at(0)];
                    int aux_indice2 = indices[producciones[a].simbolos[i].at(1)];
                    if (producciones[aux_indice].encontrado && producciones[aux_indice2].encontrado){
                        bandera = true;
                    }
                }
                if (!bandera) evaluar(len_string,a, i);
            }
        }
    }
}

void imprimir_limpio()
{
    for (int i=0;i<n_generadores;i++){
        if (producciones[i].encontrado)
        {
            cout<<producciones[i].generador<<"->";
            for (int j=0;j<producciones[i].num_simbolos;j++)
            {
                cout<<producciones[i].simbolos[j]<<"|";
            }
            cout<<'\n';
        }
    }
    cout<<"****************"<<'\n';
}

int main()
{
    entradas();
    imprimir_original();
    limpieza_inicial(producciones[0].generador);
    segunda_limpieza();
    imprimir_limpio();
    chomsky();
    cout<<"Forma Normal de Chomsky"<<'\n'<<"*************"<<'\n';
    imprimir_limpio();
    return 0;
}
