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
                {
                    cout<<"ADDED"<<endl;
                    cjtPrimero.push_back(valores[i]);}
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
            cout<<it->first<<"-->";
            bool cambios = true;
            while(cambios)
            {
                vector<string> vector_ = conjuntoprimero.find(it->first)->second;
                int vector_size = vector_.size(); //vector de  elementos en el conjunto primero de it->first
                vector<string> producciones = it->second; // cant de elementos  del vector de la lina 100

                for(int i = 0 ; i < producciones.size() ; i++ )
                {
                    string x1 = "";
                    int pos = producciones[i].find(" ");
                    cout<<"pos: "<<pos<<endl;
                    if(pos!=string::npos){
                        x1 = producciones[i].substr(0, pos);
                    }
                    else {
                        x1 = producciones[i];
                    }
                    cout<<"x1: "<<x1<<endl;
                    vector<string> toadd;
                    if (esNoTerminal(x1)){
                        cout<<"no esterminal"<<"\n";
                        toadd = conjuntoprimero.find(x1)->second;
                    }else{
                        cout<<"es terminal "<<x1<<"\n";
                        toadd.push_back(x1);
                    }    
                    auto aux1 = conjuntoprimero.find(it->first)->second;
                    agregarelementosaPrimero(aux1,toadd);
                    conjuntoprimero.find(it->first)->second = aux1;
                }
                //exit(0);
                if(vector_size == (conjuntoprimero.find(it->first)->second).size())
                    cambios = false;
                
                cout<<"vector_size: "<<vector_size<<"  (conjuntoprimero.find(it->first)->second).size(): "<< (conjuntoprimero.find(it->first)->second).size()<<"\n";
            }

        }
        printconjuntosprimeros();
    }

    void printconjuntosprimeros(){
        for (auto it = conjuntoprimero.begin() ; it!=conjuntoprimero.end(); it++){
            cout<<it->first<<" -->";
            for(auto ite = it->second.begin() ; ite!=it->second.end() ; ite++){
                cout<<*ite<<" ";
            }
            cout<<"\n\n\n";
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