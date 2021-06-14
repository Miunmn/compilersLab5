#pragma once

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

        map<string, vector<vector<string>> gramatica;

        int estados = 11;

    public:
        Gramatica(){
            vector<vector<string>> temp1 = {exp};
            vector<vector<string>> temp2 = {exp_,exp2};
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
                map<string, vector<string>>::iterator it;
                int k;
                bool continuar;
                for(it = primeros.begin(); it != primeros.end(); ++it){
                    k = 1;
                    continuar = true;
                    while(continuar && )
                }
            }
        }

        map<string,vector<string>> conjuntos_primeros_sinep(){
            map<string, vector<string>> primeros;
            /*
            for(int i = 0; i < NO_TERMINALES.size(); i++){
                vector<string> terminales_primeros;
                primeros.insert(pair<string, vector<string> >(NO_TERMINALES[i], terminales_primeros));
            }
            */
            for(int i = 0; i < NO_TERMINALES.size(); i++){
                vector<string> terminales_primeros;
                bool existen_cambios = true;
                while(existen_cambios){
                    bool existen_cambios = false;
                    vector<vector<string>> producciones = gramatica.find(NO_TERMINALES[i])->second; 
                    int cant_producciones = producciones.size();
                    for(int i = 0 ; i < cant_producciones ; i++){
                        for(int j = 0 ; producciones[i].size(); j++)){
                            
                        }
                    }        
                }            
            }



        }

        map<string, vector<string>> conjuntos_siguientes(){

        }

};

