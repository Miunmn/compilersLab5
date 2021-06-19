#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Gramatica
{
private:
    vector<string> NO_TERMINALES = {"exp", "exp_", "opsuma", "term", "term_", "opmult", "factor"};
    vector<string> TERMINALES = {"+", "-", "*", "(", ")", "numero", "epsilon"};
    
    map<string, vector<string> > gramatica;
    map<string, vector<string> > conjuntoprimero;
    map<string, vector<string> > conjuntosiguiente;
    string LL1 [8][8];

    vector<string> exp = {"term exp_"};
    vector<string> exp_ = {"opsuma term exp_", "epsilon"};
    vector<string> opsuma= {"+", "-"};
    vector<string> term = {"factor term_"};
    vector<string> term_ = {"opmult factor term_", "epsilon"};
    vector<string> opmult_ = {"*"};
    vector<string> factor = {"( exp )", "numero"};

    int estados = 11;

public:
    Gramatica()
    {
        gramatica.insert(make_pair("exp", exp));
        gramatica.insert(make_pair("exp_", exp_));
        gramatica.insert(make_pair("opsuma", opsuma));
        gramatica.insert(make_pair("term", term));
        gramatica.insert(make_pair("term_", term_));
        gramatica.insert(make_pair("opmult", opmult_));
        gramatica.insert(make_pair("factor", factor));

        vector<string> vec;
        conjuntoprimero.insert(make_pair("exp",vec ));
        conjuntoprimero.insert(make_pair("exp_", vec));
        conjuntoprimero.insert(make_pair("opsuma", vec));
        conjuntoprimero.insert(make_pair("term", vec));
        conjuntoprimero.insert(make_pair("term_", vec));
        conjuntoprimero.insert(make_pair("opmult", vec));
        conjuntoprimero.insert(make_pair("factor", vec));

        for(int j = 1; j < 8; j++){
            if(j == 7) LL1[0][j] = "$";
            else LL1[0][j] = TERMINALES[j - 1];
            LL1[j][0] = NO_TERMINALES[j - 1];
        }

    }
    void agregarelementosaPrimero(vector<string> &cjtPrimero, vector<string> valores)
    {
        for (int i = 0; i < valores.size(); i++)
        {
            if (find(cjtPrimero.begin(), cjtPrimero.end(), valores[i]) != cjtPrimero.end())
                cjtPrimero.push_back(valores[i]);
        }
    }

    bool esTerminal(string value)
    {
        if (find(TERMINALES.begin(), TERMINALES.end(), value) != TERMINALES.end())
        {
            return true;
        }
        return false;
    }

    bool esNoTerminal(string value)
    {
        if (find(NO_TERMINALES.begin(), NO_TERMINALES.end(), value) != NO_TERMINALES.end())
        {
            return true;
        }
        return false;
    }

    map<string, vector<string> > conjuntos_primeros()
    {
        if (find(TERMINALES.begin(), TERMINALES.end(), "epsilon") != TERMINALES.end())
            return conjuntos_primeros_conep();
        else
            return conjuntos_primeros_sinep();
    }

    map<string, vector<string> > conjuntos_primeros_conep()
    {
        bool existen_cambios = true;
        while(existen_cambios){
            for(auto it = gramatica.begin(); it != gramatica.end(); it++){
                int k = 0;
                int n = 0;
                bool continuar = true;
                bool primera_vez = false;
                vector<string> temp;
                if(primera_vez){
                    stringstream s(it->second[1]);
                    string token;
                    while(s >> token){
                        n++;
                        temp.push_back(token);
                    }
                }
                else{
                    if(it->second.size() > 1) primera_vez = true;
                    stringstream s(it->second[0]);
                    string token;
                    while(s >> token){
                        n++;
                        temp.push_back(token);
                    }
                }
                while(continuar && k < n){
                    if(esTerminal(temp[k]) && temp[k] != "epsilon") conjuntoprimero[it->first].push_back(temp[k]);
                    else if(esNoTerminal(temp[k])) {
                        if(conjuntoprimero[temp[k]].size() > 0){
                            for(int i = 0; i < conjuntoprimero[temp[k]].size(); i++){
                                if(conjuntoprimero[temp[k]][i] != "epsilon"){
                                    conjuntoprimero[it->first].push_back(conjuntoprimero[temp[k]][i]);
                                } else if(conjuntoprimero[temp[k]][i] == "epsilon") continuar = false;
                            }
                        }
                    } else continuar = false;
                    k++;
                }
                if(continuar) conjuntoprimero[it->first].push_back("epsilon");
            }
        }
        return conjuntoprimero;
    }

    map<string, vector<string> > conjuntos_primeros_sinep()
    {
        for(auto it = gramatica.begin(); it != gramatica.end(); it++)
        {
            cout<<it->first<<endl;
            bool cambios = true;
            while(cambios)
            {
                cambios = false;
                vector<string> vector_ = it->second;
                int vector_size = vector_.size();

                for(int i = 0 ; i < vector_.size() ; i++ )
                {
                    string x1 = "";
                    size_t pos = it->second[0].find(" ");
                    if(pos < it->second[0].size())
                        x1 = it->second[0].substr(0, pos);
                    else x1 = it->second[0];

                    vector<string> toadd;
                    if (esTerminal(x1)){
                        toadd = conjuntoprimero.find(x1)->second;
                    }else{
                        toadd = {x1};
                    }        

                    //vector<string> vec = conjuntoprimero.find(it->first)->second;
                    agregarelementosaPrimero(conjuntoprimero.find(it->first)->second,conjuntoprimero.find(x1)->second);
                }

                if(vector_size!=conjuntoprimero.find(it->first)->second.size())
                    cambios = true;
                
            }

        }

    }

    map<string, vector<string> > conjuntos_siguientes()
    {
    }

    bool es_tabla_LL1(){return true;}

    bool in_produccion(string terminal, string produccion){
        stringstream s(produccion);
        string token;
        while(s >> token) if(terminal == token) return true;
        return false;
    }

    void tabla_LL1()
    {
        if(es_tabla_LL1){
            for(int i = 0; i < 8; i++){
                for(int j = 1; j < 8; j++){
                    if(in_produccion(LL1[0][j], gramatica[LL1[j][0]][0])){
                        if(gramatica[LL1[j][0]].size() == 1) LL1[i + 1][j] = LL1[j][0] + "->" + gramatica[LL1[j][0]][0];
                        else{
                            if(in_produccion(LL1[0][j], gramatica[LL1[j][0]][0])) LL1[i + 1][j] = LL1[j][0] + "->" + gramatica[LL1[j][0]][0];
                            else if(in_produccion(LL1[0][j], gramatica[LL1[j][0]][1])) LL1[i + 1][j] = LL1[j][0] + "->" + gramatica[LL1[j][0]][1];
                            else{
                                
                            }
                        }
                    }
                        
                }
            }
        }
    }

};

int main(){
    Gramatica gramatica;
    // gramatica.conjuntos_primeros_sinep();
    // gramatica.conjuntos_primeros_conep();

    return 0;
}