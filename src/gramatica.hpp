#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Gramatica{
    private:
        vector<string> NO_TERMINALES = {"exp", "exp_","opsuma","term","term_","opmult","factor"};
        vector<string> TERMINALES = {"+","-","*","(",")","numero","epsilon"};

        vector<string> exp = {"term", "exp_"};

        vector<string> exp_ = {"opsuma", "term", "exp_"};
        vector<string> exp_2 = {"epsilon"};

        vector<string> opsuma = {"+"};
        vector<string> opsuma2 = {"-"};

        vector<string> term = {"factor", "term_"};


        vector<string> term_ = {"opmult", "factor", "term"};
        vector<string> term_2 = {"epsilon"};

        vector<string> opmult = {"*"};

        vector<string> factor = {"(", "exp", ")"};
        vector<string> factor2 = {"numero"};

        std::map<string, vector<vector<string>*>> gramatica;

        int estados = 11;

    public:
        Gramatica(){
            vector<vector<string>> temp1 = {exp};
            vector<vector<string>> temp2 = {exp_,exp_2};
            vector<vector<string>> temp3 = {opsuma, opsuma2};
            vector<vector<string>> temp4 = {term};
            vector<vector<string>> temp5 = {term_,term_2};
            vector<vector<string>> temp6 = {opmult};
            vector<vector<string>> temp7 = {factor, factor2};

            gramatica.insert(pair<string, vector<vector<string>> >("exp", vector<vector<string>> = {temp1}));
            gramatica.insert(pair<string, vector<vector<string>> >("exp_", vector<vector<string>> = {temp2}));
            gramatica.insert(pair<string, vector<vector<string>> >("opsuma", vector<vector<string>> = {temp3}));
            gramatica.insert(pair<string, vector<vector<string>> >("term", vector<vector<string>> = {temp4}));
            gramatica.insert(pair<string, vector<vector<string>> >("term_", vector<vector<string>> = {temp5}));
            gramatica.insert(pair<string, vector<vector<string>> >("opmult", vector<vector<string>> = {temp6}));
            gramatica.insert(pair<string, vector<vector<string>> >("factor", vector<vector<string>> = {temp7}));
        }

        void agregarelementosaPrimero(vector<string> &cjtPrimero, vector<string> valores){
            for(int i = 0 ; i < valores.size() ; i++){
                if (find(cjtPrimero.begin(), cjtPrimero.end(), valores[i]) != cjtPrimero.end())
                    cjtPrimero.push_back(valores[i]);
            }
        }

        bool esTerminal(string value){
            if (find(TERMINALES.begin(), TERMINALES.end(), value) != TERMINALES.end()){
                return true;
            }
            return false;
        }

        bool esNoTerminal(string value){
            if (find(NO_TERMINALES.begin(), NO_TERMINALES.end(), value) != NO_TERMINALES.end()){
                return true;
            }
            return false;
        }


        map<string,vector<string>> conjuntos_primeros(){
            if (find (TERMINALES.begin(), TERMINALES.end(), "epsilon") != TERMINALES.end())
                return conjuntos_primeros_conep();
            else return conjuntos_primeros_sinep();
        }

        map<string,vector<string>> conjuntos_primeros_conep(){
            map<string, vector<string>> primeros;
            for(int i = 0; i < NO_TERMINALES.size(); i++){
                vector<string> terminales_primeros;
                primeros.insert(pair<string, vector<string> >(NO_TERMINALES[i], terminales_primeros));
            }

            bool existen_cambios = true;
            while(existen_cambios){
                map<string, vector<vector<string>*>>::iterator it;
                int k;
                bool continuar;
                for(it = primeros.begin(); it != primeros.end(); ++it){
                    k = 0;
                    continuar = true;
                    while(continuar && k <= it->second.size()){
                        if(it->second.size() > 2){
                            for(int i = 0; i < it->second.size(); i++){
                                if(esTerminal(it->second[i][k]))
                            }
                        } else{
                            if(esTerminal(it->second[k]) && it->second[k] != "epsilon"){
                                primeros[it->first].push_back(it->second[k]);
                            } else if(esNoTerminal(it->second[k])){
                                if(primeros[it->second[k]].size() > 0){
                                    for(int i = 0; i < primeros[it->second[k]].size(); i++){
                                        if(!find(primeros[it->first].begin(), primeros[it->first].end(), primeros[it->second[k]][i]) && primeros[it->second[k]][i] != "epsilon")
                                            primeros[it->first].push_back(primeros[it->second[k]][i]);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        map<string,vector<string>> conjuntos_primeros_sinep(){
            map<string, vector<string>> primeros;
            
            for(int i = 0; i < NO_TERMINALES.size(); i++){
                vector<string> terminales_primeros;
                primeros.insert(pair<string, vector<string> >(NO_TERMINALES[i], terminales_primeros));
            }

            for(int i = 0; i < NO_TERMINALES.size(); i++){
                vector<string> terminales_primeros;
                bool existen_cambios = true;
                while(existen_cambios){
                    bool existen_cambios = false;
                    vector<vector<string>> producciones = gramatica.find(NO_TERMINALES[i])->second; 
                    int cant_producciones = producciones.size();
                    for(int i = 0 ; i < cant_producciones ; i++){
                        for(int j = 0 ; j < producciones[i].size(); j++){
                            vector<string> primerosA =  primeros.find(NO_TERMINALES[i])->second; 
                            int cantA = primerosA.size();
                            if (esTerminal(producciones[i][j])){
                                vector<string> primerosdenoterminales = primeros.find(producciones[i][j])->second;
                                if (primerosdenoterminales.empty()) continue;
                                else{
                                    agregarelementosaPrimero(primerosA,primerosdenoterminales);
                                }
                            }
                            else{
                                vector<string> primeroTerminal = {producciones[i][j]};
                                agregarelementosaPrimero(primerosA, primeroTerminal);
                            }
                            if (cantA != primerosA.size()) {existen_cambios = true;}
                        }
                    }        
                }            
            }



        }

        map<string, vector<string>> conjuntos_siguientes(){

        }

};
