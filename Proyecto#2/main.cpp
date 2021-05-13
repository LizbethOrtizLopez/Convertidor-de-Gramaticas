#include <bits/stdc++.h>

using namespace std;

char generadores[100002];
char terminales[100002];
//char opcionales = {128,129,132,133,135,136,137,138,139,140,141,142,145,146,155,225,230,245};
int n_generadores;

map <char,int> indices;
map <char,bool> existe_terminal;

struct produccion{
    char generador;
    string simbolos[1002];
    int num_simbolos;
    bool encontrado;
};

produccion producciones[10002];

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
                    if (producciones[aux_indice].num_simbolos==1){
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
                    }
                }
            }
        }
    }
}

void chomsky(char genera)
{
    for int a=0;a<n_generadores;a++)
    {
        if (producciones[a].encontrado)
        {
            int aux_numSimbolos = producciones[a].num_simbolos;
            for (int i=0;i<aux_numSimbolos;i++)
            {
                int len_string = producciones[a].simbolos[i].size();

                if (len_string==1)
                {
                    if (existe_terminal[producciones[a].simbolos[i].at(0)]){
                        bandera = true;
                    }
                    if (bandera) continue;
                    buscar(producciones[aux_indice].simbolos[0].at(0));
                }
                else if (len_string==2)
                {
                    int aux_indice = indices[producciones[a].simbolos[i].at(0)];
                    int aux_indice2 = indices[producciones[a].simbolos[i].at(1)];
                    if (producciones[aux_indice].encontrado && producciones[aux_indice2].encontrado){
                        bandera = true;
                    }
                    if (bandera) continue;
                }
                else
                {

                }
            }
        }
    }
}

void cambiar(int n_generadores, int indicador, int secciones, int pos_indice, int i)
{
    producciones[n_generadores].generador = opcionales[i];
    indices[opcionales[i]] = n_generadores;
    for (j=indicador;j<secciones;j++)
    {
        producciones[n_generadores].simbolos[j]=producciones[pos_indice].simbolos[j];
        producciones[n_generadores].num_simbolos++;
        indicador++;
    }
    return j;
}

void deshacer()
{
    len_string = producciones[pos_indice].simbolos[i].size();

    if (len_string % 2 == 0) secciones = len_string / 2;
    else secciones = (len_string / 2) + 1;

    for (int j=0;j<len_string;j++)
    {
        int pos_simbolos = 0;
        for (int k=0;k<secciones;k++)
        {
            producciones[n_generadores].generador = opcionales[k];
            indices[opcionales[k]] = n_generadores;
            string aux;
            aux+=producciones[pos_indice].simbolos[i].at(j);

            producciones[n_generadores].simbolos[pos_simbolos]=aux;
            producciones[n_generadores].num_simbolos++;
            pos_simbolos++;
            aux.erase();
        }
        n_generadores++;
    }
}

void buscar(char genera)
{
    int pos_indice = indices[genera];
    int aux_numSimbolos = producciones[pos_indice].num_simbolos;
    int secciones = 0;
    int len_string = 0;
    int indicador = 0;

    if (aux_numSimbolos % 2 == 0) secciones = aux_numSimbolos / 2;
    else secciones = (aux_numSimbolos / 2) + 1;

    for (int i=0;i<aux_numSimbolos;i++)
    {
        if (aux_numSimbolos>1 && (secciones%2==0))
        {
            j = cambiar(n_generadores,indicador,secciones,pos_indice,i);
        }
        else if (aux_numSimbolos>1 && (secciones%2!=0))
        {
            j = cambiar(n_generadores,indicador,secciones-1,pos_indice,i);
            producciones[n_generadores].simbolos[j]=producciones[pos_indice].simbolos[j+1];
            producciones[n_generadores].num_simbolos++;
        }
        else if (aux_numSimbolos == 1)
        {
            deshacer(genera);
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
    //cin.tie(0);
    //ios_base::sync_with_stdio(0);

    entradas();
    imprimir_original();
    limpieza_inicial(producciones[0].generador);
    imprimir_limpio();
    return 0;
}
