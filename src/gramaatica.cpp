#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Gramatica
{
private:
    vector<string> NO_TERMINALES = {"exp", "exp_", "opsuma", "term", "term_", "opmult", "factor"};
    vector<string> TERMINALES = {"+", "-", "*", "(", ")", "numero", "epsilon"};
    
    map<string, vector<string>> gramatica;
    map<string, vector<string>> conjuntoprimero;
    map<string, vector<string>> conjuntosiguiente;

    vector<string> exp = {"term exp_"};
    vector<string> exp_ = {"opsuma term exp_", "epsilon"};
    vector<string> opsuma = {"+", "-"};
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

        vector<string> vec = {};
        conjuntoprimero.insert(make_pair("exp",vec ));
        conjuntoprimero.insert(make_pair("exp_", vec));
        conjuntoprimero.insert(make_pair("opsuma", vec));
        conjuntoprimero.insert(make_pair("term", vec));
        conjuntoprimero.insert(make_pair("term_", vec));
        conjuntoprimero.insert(make_pair("opmult", vec));
        conjuntoprimero.insert(make_pair("factor", vec));


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

    map<string, vector<string>> conjuntos_primeros()
    {
        if (find(TERMINALES.begin(), TERMINALES.end(), "epsilon") != TERMINALES.end())
            return conjuntos_primeros_conep();
        else
            return conjuntos_primeros_sinep();
    }

    map<string, vector<string>> conjuntos_primeros_conep()
    {
    }

    map<string, vector<string>> conjuntos_primeros_sinep()
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

    map<string, vector<string>> conjuntos_siguientes()
    {
    }
};

int main(){
    Gramatica gramatica;
    gramatica.conjuntos_primeros_sinep();
}