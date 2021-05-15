#include <bits/stdc++.h>

using namespace std;

char generadores[1002];
char terminales[1002];
char nuevo_generador;
int opcionales[18] = {129,132,133,135,136,137,138,139,140,141,142,145,146,155,225,230,245};
int n_generadores;
int opcion_ocupada;

map <char,int> indices;
map <char,bool> existe_terminal;

queue <int> posiciones_sustituir;

struct produccion{
    char generador;
    string simbolos[1002];
    int num_simbolos;
    bool encontrado;
    bool soy_FNG;
};

produccion producciones[1002];

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
    cout<<"************************"<<'\n';
    cout<<"Gramatica original"<<'\n';
    cout<<"************************"<<'\n';
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
    producciones[pos_indice].soy_FNG = false;

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

void sustitucion_fng(int a, int i,int indice_aux)
{
     int indice_sustituir = indices[producciones[a].simbolos[i].at(0)];
     int pos = i;
     string aux_2;
     for (int j=1;j<producciones[a].simbolos[i].size();j++){
            aux_2+=producciones[a].simbolos[i].at(j);
     }

     int posicion = producciones[indice_sustituir].num_simbolos;
     produccion aux_produccion = producciones[a];
     for (int j=1;j<producciones[a].num_simbolos;j++)
     {
         producciones[a].simbolos[posicion] = aux_produccion.simbolos[j];
         posicion++;
     }
     producciones[a].num_simbolos = (producciones[a].num_simbolos + producciones[indice_sustituir].num_simbolos)-1;

     for (int j=0;j<producciones[indice_sustituir].num_simbolos;j++)
     {
       string aux = producciones[indice_sustituir].simbolos[j];
       aux+=aux_2;
       producciones[a].simbolos[pos] = aux;
       pos++;
     }
}

void fng()
{
    //Paso 1. Sustitucion y Reflexion
    for (int a=0;a<n_generadores;a++)
    {
        int genera_indice = indices[producciones[a].generador];
        int aux_numSimbolos = producciones[a].num_simbolos;
        if (producciones[a].encontrado && !producciones[a].soy_FNG)
        {
            for (int i=0;i<aux_numSimbolos;i++)
            {
                if (!existe_terminal[producciones[a].simbolos[i].at(0)])
                {
                    int indice_aux = indices[producciones[a].simbolos[i].at(0)];
                    if (genera_indice>indice_aux)
                    {
                        //aplicamos sustitución
                        sustitucion_fng(a,i,indice_aux);
                        fng();
                    }
                    else if (genera_indice==indice_aux)
                    {
                        string alfa[15];
                        string beta[15];
                        int pos_alfa = 0;
                        int pos_beta = 0;
                        for (int j=0;j<producciones[a].num_simbolos;j++)
                        {
                            if (existe_terminal[producciones[a].simbolos[j].at(0)])
                            {
                                beta[pos_beta] = producciones[a].simbolos[j];
                                pos_beta++;
                            }
                            else
                            {
                                string aux;
                                for (int k=1;k<producciones[a].simbolos[j].size();k++){
                                    aux+=producciones[a].simbolos[j].at(k);
                                }
                                alfa[pos_alfa]=aux;
                                pos_alfa++;
                            }
                        }
                        int aux = producciones[a].num_simbolos;
                        for (int j=0;j<aux;j++){
                            producciones[a].simbolos[j].erase();
                        }
                        producciones[a].num_simbolos = 0;
                        int aux_pos = 0;
                        for (int j=0;j<pos_beta*2;j+=2)
                        {
                            char op = opcionales[opcion_ocupada];
                            producciones[a].simbolos[j] = beta[aux_pos];
                            producciones[a].simbolos[j+1] = beta[aux_pos]+op;
                            producciones[a].num_simbolos+=2;
                            aux_pos++;
                        }
                        aux_pos = 0;
                        for (int j=0;j<pos_alfa*2;j+=2)
                        {
                            char op = opcionales[opcion_ocupada];
                            producciones[n_generadores].simbolos[j] = alfa[aux_pos];
                            producciones[n_generadores].simbolos[j+1] = alfa[aux_pos]+op;
                            producciones[n_generadores].num_simbolos+=2;
                            aux_pos++;
                        }
                        producciones[n_generadores].generador = opcionales[opcion_ocupada];
                        producciones[n_generadores].encontrado = true;
                        producciones[n_generadores].soy_FNG = true;
                        posiciones_sustituir.push(n_generadores);
                        opcion_ocupada++;
                        n_generadores++;
                        fng();
                    }
                }
            }
        }
    }

    int susti = posiciones_sustituir.front();

    //Paso 2. Sustitucion resto de elementos
    for (int a=susti-1;a>=0;a--)
    {
        int genera_indice = indices[producciones[a].generador];
        int aux_numSimbolos = producciones[a].num_simbolos;
        if (producciones[a].encontrado && !producciones[a].soy_FNG)
        {
            for (int i=0;i<aux_numSimbolos;i++)
            {
                if (!existe_terminal[producciones[a].simbolos[i].at(0)])
                {
                    int indice_aux = indices[producciones[a].simbolos[i].at(0)];
                    //aplicamos sustitución
                    sustitucion_fng(a,i,indice_aux);
                }
            }
        }
    }
    //Paso 3. Sustitucion en las Zn
    for (int a=n_generadores-1;a>=0;a--)
    {
        int genera_indice = indices[producciones[a].generador];
        int aux_numSimbolos = producciones[a].num_simbolos;
        if (producciones[a].soy_FNG)
        {
            for (int i=0;i<aux_numSimbolos;i++)
            {
                if (!existe_terminal[producciones[a].simbolos[i].at(0)])
                {
                    int indice_aux = indices[producciones[a].simbolos[i].at(0)];
                    //aplicamos sustitución
                    sustitucion_fng(a,i,indice_aux);
                }
            }
        }
    }
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
    cout<<"Forma Normal de Greibach"<<'\n'<<"*************"<<'\n';
    fng();
    imprimir_limpio();
    return 0;
}
