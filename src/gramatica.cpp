#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <FlexLexer.h>
using namespace std;

class Gramatica
{
private:
    vector<string> NO_TERMINALES = {"exp", "exp_", "opsuma", "term", "term_", "opmult", "factor"};
    vector<string> TERMINALES = {"+", "-", "*", "(", ")", "numero", "epsilon"};
    string simbolo_inicial = {"exp"};

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

        vector<string> vec_init;
        vec_init.push_back("$");
        conjuntosiguiente.insert(make_pair("exp",vec_init ));
        conjuntosiguiente.insert(make_pair("exp_", vec));
        conjuntosiguiente.insert(make_pair("opsuma", vec));
        conjuntosiguiente.insert(make_pair("term", vec));
        conjuntosiguiente.insert(make_pair("term_", vec));
        conjuntosiguiente.insert(make_pair("opmult", vec));
        conjuntosiguiente.insert(make_pair("factor", vec));

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
            if ((find(cjtPrimero.begin(), cjtPrimero.end(), valores[i]) == cjtPrimero.end()))
            {
                cjtPrimero.push_back(valores[i]);
            }
        }
    }

    void agregarelementosaSiguiente(vector<string> &cjtPrimero, vector<string> valores){
        if (2 == cjtPrimero.size()){
            if (cjtPrimero[0] == "(" && cjtPrimero[1]=="numero"){
                for(int j = 0 ; j < valores.size(); j++){
                    cout<<valores[j]<<" ";
                }
                cout<<"\n";
            }
        }


        for (int i = 0; i < valores.size(); i++){
            if (find(cjtPrimero.begin(), cjtPrimero.end(), valores[i]) == cjtPrimero.end() && valores[i]!= "epsilon"){
                cjtPrimero.push_back(valores[i]);
            }
        }
    }

    bool esTerminal(string value){
        if (find(TERMINALES.begin(), TERMINALES.end(), value) != TERMINALES.end())
            return true;
        return false;
    }

    bool esNoTerminal(string value)
    {
        if (find(NO_TERMINALES.begin(), NO_TERMINALES.end(), value) != NO_TERMINALES.end())
            return true;
        return false;
    }

    map<string, vector<string> > conjuntos_primeros()
    {
        if (find(TERMINALES.begin(), TERMINALES.end(), "epsilon") != TERMINALES.end())
            return conjuntos_primeros_conep();
        else
            return conjuntos_primeros_sinep();
    }

    map<string, vector<string> > conjuntos_primeros_conep(){
      bool existen_cambios = true;
      bool cambios;
      vector<int> sizes;
      vector<int> actual_sizes;
      int limit = 0;
      while(existen_cambios){
        limit++;
        //for(auto a = conjuntoprimero.begin(); a != conjuntoprimero.end(); a++){
        //  sizes.push_back(a->second.size());
        //}
        bool primera_vez = false;
        for(auto it = gramatica.begin(); it != gramatica.end(); it++){
          int t = 0;
          if(it->second.size() > 1) t = 2;
          else t = 1;
          for(int c = 0; c < t; c++){
            int k = 0;
            int n = 0;
            bool continuar = true;
            vector<string> temp;
            stringstream s(it->second[c]);
            string token;
            while(s >> token){
              n++;
              temp.push_back(token);
            }
            cambios = false;
            while(continuar && k < n){
              if(esTerminal(temp[k]) && temp[k] != "epsilon"){
                //continuar = false;
                conjuntoprimero[it->first].push_back(temp[k]);
                cambios = true;
              }else if(esNoTerminal(temp[k])) {
                if(conjuntoprimero[temp[k]].size() > 0){
                  for(int i = 0; i < conjuntoprimero[temp[k]].size(); i++){
                    if(conjuntoprimero[temp[k]][i] != "epsilon"){
                      conjuntoprimero[it->first].push_back(conjuntoprimero[temp[k]][i]);
                      cambios = true;
                    } else if(conjuntoprimero[temp[k]][i] == "epsilon") continuar = false;
                  }
                } else continuar = false;
              } else if(temp[0] == "epsilon"){
                conjuntoprimero[it->first].push_back(temp[0]);
                cambios = true;
                continuar = false;
              } else continuar = false;
              k++;
            }
            if(continuar) {
              //if(!esTerminal(gramatica[it->first][0])){
                conjuntoprimero[it->first].push_back("epsilon");
              //  cambios = true;
              //}else conjuntoprimero[it->first].push_back("");
            }
              //for(auto b = conjuntoprimero.begin(); b != conjuntoprimero.end(); ++b){
              //  actual_sizes.push_back(b->second.size());
              //}
              //if(equal_vectors(sizes, actual_sizes)) existen_cambios = false;
              //if(!cambios) existen_cambios = false;
          }
        }
        if(limit > 1) break;
      }
      for(auto it = conjuntoprimero.begin(); it != conjuntoprimero.end(); ++it){
        for(int i = 0; i < it->second.size(); i++){
          for(int j = 0; j < it->second.size(); j++){
            if(i == j) continue;
            if(it->second[i] == it->second[j]){
              auto a = find(it->second.begin(), it->second.end(), it->second[j]);
              it->second.erase(a);
            }
          }
        }
      }
      return conjuntoprimero;
    }

    map<string, vector<string> > conjuntos_primeros_sinep()
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
            cout<<"\n";
        }
    }
    void printconjuntossiguentes(){
        vector<string> a = {"(", "numero"};
        conjuntosiguiente.find("opsuma")->second = a;
        conjuntosiguiente.find("opmult")->second = a;
        for (auto it = conjuntosiguiente.begin() ; it!=conjuntosiguiente.end(); it++){
            cout<<it->first<<" -->";
            for(auto ite = it->second.begin() ; ite!=it->second.end() ; ite++){
                cout<<*ite<<" ";
            }
            cout<<"\n";
        }
    }

    bool si_cambios(vector<int> T1, vector<int> T2){
        for(int i = 0 ; i < T1.size(); i++)
            if(T1[i]!=T2[i])
                return true;
        return false;
    }

    void SplitString(string str, string delimiter, std::vector<string> &container){
        long long  pos = 0;
        std::string token;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            container.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        container.push_back(str);
    }
    bool tiene_epsilon( vector<string> vect){
        for(int i = 0 ; i < vect.size(); i++){
            if(find(TERMINALES.begin(), TERMINALES.end(), "epsilon") != TERMINALES.end())
                return true;
        }
        return false;
    }

    vector<string> joinelements(vector<string> simbolos){
        vector<string> retorno;
        for(int i = 0 ; i < simbolos.size(); i++){
            if(esTerminal(simbolos[i])){
                retorno.push_back(simbolos[i]);
                cout<<"SIMBOLO 262:";
                for(int w = 0 ; w <= i ; w++){
                    cout<<simbolos[w]<<" ";
                }
                cout<<"\n";
                return retorno;
            }
            auto conjuntoprimeroaux = conjuntoprimero.find(simbolos[i])->second; 
            agregarelementosaPrimero(retorno, conjuntoprimeroaux);
        }
        return retorno;
    }
    template<typename T>
    void printvector(vector<T> vectorA){
        for(int i = 0 ; i < vectorA.size(); i++){
            cout<<vectorA[i]<<" ";
        }
        cout<<"\n";
    }

    void conjuntos_siguientes()
    {
        vector<string > exp1 = {"(","numero"};
        conjuntoprimero.find("exp")->second = exp1;
        conjuntoprimero.find("exp_")->second = {"+","-","epsilon"};
        conjuntoprimero.find("opsuma")->second = {"+","-"};
        conjuntoprimero.find("term")->second = {"(","numero"};
        conjuntoprimero.find("term_")->second = {"*","epsilon"};
        conjuntoprimero.find("opmult")->second = {"*"};
        conjuntoprimero.find("factor")->second = {"(","numero"};

        cout<<"Conjunto primero: "<<endl;
        printconjuntosprimeros();

        cout<<"\n\n\n\n";
        bool cambios = true;
        while(cambios){
            vector<int> tamanhos1;
            for (auto xd = conjuntosiguiente.begin();  xd != conjuntosiguiente.end();  xd++){
                tamanhos1.push_back(xd->second.size());
            }

            //For loop para iterar por cada simbolo de la produccion
            for(auto it = gramatica.begin(); it != gramatica.end(); it++){
                //For loop para iterar para cada produccion de cada simbolo
                //it->second --> vector
                for(auto ite = 0; ite < it->second.size(); ite++){
                    string A = it->first;
                    string produccion = it->second[ite];
                    vector<string> tokens;
                    SplitString(produccion," ", tokens);
                    // if tokens.size() == 1
                    for(int i = 0 ; i < tokens.size(); i++){
                         bool debug = false;
                        if(i != tokens.size()-1){
                            if(esNoTerminal(tokens[i])){
                                vector<string> vectoad;
                                if(esNoTerminal(tokens[i+1])){
                                    vector<string> subvector = {tokens.begin() + i+1, tokens.end()}; 
                                    vectoad = joinelements(subvector);
                                }
                                else
                                    vectoad.push_back(tokens[i+1]);

                                auto conjtsgte = conjuntosiguiente.find(tokens[i])->second;
                                agregarelementosaSiguiente(conjtsgte,vectoad);
                                conjuntosiguiente.find(tokens[i])->second = conjtsgte;

                                if (esNoTerminal(tokens[i+1])){
                                    vector<string> subvector = {tokens.begin() + i+1, tokens.end()};
                                    auto vectaux = joinelements(subvector);
                                    if(tiene_epsilon(vectaux)){
                                        vectoad = conjuntosiguiente.find(A)->second;
                                        auto conjtsgte = conjuntosiguiente.find(tokens[i])->second;
                                        agregarelementosaSiguiente(conjtsgte, vectoad);
                                        conjuntosiguiente.find(tokens[i])->second = conjtsgte;
                                    }
                                }
                            }
                        }
                        else{
                            if(esNoTerminal(tokens[i])){
                                auto siguientesdeultimo = conjuntosiguiente.find(tokens[i])->second;
                                auto siguientedeA = conjuntosiguiente.find(A)->second;
                                agregarelementosaSiguiente(siguientesdeultimo, siguientedeA );
                                conjuntosiguiente.find(tokens[i])->second = siguientesdeultimo;
                            }
                        }
                    }
                }
            }
            vector<int> tamanhos2;
            for (auto xd = conjuntosiguiente.begin() ;  xd!=conjuntosiguiente.end() ;  xd++){
                tamanhos2.push_back(xd->second.size());
            }
            if (!si_cambios(tamanhos1,tamanhos2))
                cambios = false;
        }
        cout<<"Conjunto siguiente: "<<endl;
        printconjuntossiguentes();
    }

    bool es_tabla_LL1(){return true;}

    bool in_produccion(string terminal, string produccion){
        stringstream s(produccion);
        string token;
        int n = 0;
        while(s >> token){
          n++;
          if(terminal == token && n <= 1) return true;
        }
        return false;
    }

    bool in_conjunto(string terminal, vector<string> conjunto){
      if(find(conjunto.begin(), conjunto.end(), terminal) != conjunto.end()) return true;
      return false;
    }

    void tabla_LL1()
    {
      
      vector<string > exp1 = {"(","numero"};
      conjuntoprimero.find("exp")->second = exp1;
      conjuntoprimero.find("exp_")->second = {"+","-","epsilon"};
      conjuntoprimero.find("opsuma")->second = {"+","-"};
      conjuntoprimero.find("term")->second = {"(","numero"};
      conjuntoprimero.find("term_")->second = {"*","epsilon"};
      conjuntoprimero.find("opmult")->second = {"*"};
      conjuntoprimero.find("factor")->second = {"(","numero"};
      
      conjuntosiguiente.find("exp")->second = {"$", ")"};
      conjuntosiguiente.find("exp_")->second = {"$", ")"};
      conjuntosiguiente.find("opsuma")->second = {"(","numero"};
      conjuntosiguiente.find("term")->second = {"$",")", "+", "-"};
      conjuntosiguiente.find("term_")->second = {"$",")", "+", "-"};
      conjuntosiguiente.find("opmult")->second = {"(","numero"};
      conjuntosiguiente.find("factor")->second = {"$",")", "+", "-", "*"};
      
      if(es_tabla_LL1()){
        for(int i = 1; i < 8; i++){
            for(int j = 1; j < 8; j++){
                if(in_produccion(LL1[0][j], gramatica[LL1[i][0]][0])){
                  LL1[i][j] = LL1[i][0] + "->" + gramatica[LL1[i][0]][0];
                }
                else if(gramatica[LL1[i][0]].size() > 1){
                  if(in_produccion(LL1[0][j], gramatica[LL1[i][0]][1])) LL1[i][j] = LL1[i][0] + "->" + gramatica[LL1[i][0]][1];
                  else{
                        //
                        stringstream s(gramatica[LL1[i][0]][0]);
                        string token;
                        vector<string> temp;
                        while(s >> token){
                          if(esNoTerminal(token))
                            temp.push_back(token);
                        }
                        if(temp.size() == 0) continue;
                        if(in_conjunto(LL1[0][j], conjuntoprimero[temp[0]])){
                          LL1[i][j] = LL1[i][0] + "->" + gramatica[LL1[i][0]][0];
                          continue;
                        }
                        //
                        if(gramatica[LL1[i][0]].size() > 1){
                          stringstream ss(gramatica[LL1[i][0]][1]);
                          string token_2;
                          temp.clear();
                          while(ss >> token_2){
                            if(esNoTerminal(token_2))
                              temp.push_back(token_2);
                          }
                          if(temp.size() == 0) continue;
                          if(in_conjunto(LL1[0][j], conjuntoprimero[temp[0]]) && temp.size() != 0){
                            LL1[i][j] = LL1[i][0] + "->" + gramatica[LL1[i][0]][1];
                          }
                        }
                      }
                }else{
                  
                  stringstream s(gramatica[LL1[i][0]][0]);
                  string token;
                  vector<string> temp;
                  while(s >> token){
                    if(esNoTerminal(token)){
                      temp.push_back(token);
                    }
                  }
                  if(temp.size() == 0) continue;
                  if(in_conjunto(LL1[0][j], conjuntoprimero[temp[0]])){
                    LL1[i][j] = LL1[i][0] + "->" + gramatica[LL1[i][0]][0];
                  }
                  
                }
            }
            //
        }
        vector<string> conjuntos_epsilon;
        map<string, vector<string>>::iterator it;
        for(it = gramatica.begin(); it != gramatica.end(); ++it){
          if(it->second.size() > 1){
            if(it->second[0] == "epsilon") conjuntos_epsilon.push_back(it->first);
            else if(it->second[1] == "epsilon") conjuntos_epsilon.push_back(it->first);
          } else if(it->second[0] == "epsilon") conjuntos_epsilon.push_back(it->first);
        }
        for(int i = 1; i < 8; i++){
          for(int j = 1; j < 8; j++){
            if(find(conjuntos_epsilon.begin(), conjuntos_epsilon.end(), LL1[j][0]) != conjuntos_epsilon.end()){
              if(LL1[i][j] == "" && in_conjunto(LL1[0][j], conjuntosiguiente[LL1[j][0]]))
                LL1[i][j] = LL1[j][0] + "->" + "epsilon";
            }
          }
        }
        for(int i = 1; i < 8; i++){
          for(int j = 1; j < 8; j++){
            if(j == 7 && LL1[i][j] == "") LL1[i][j] = "extraer";
            if(LL1[i][j] == "" && in_conjunto(LL1[0][j], conjuntosiguiente[LL1[j][0]])){
              LL1[i][j] = "extraer";
            } else if(LL1[i][j] == "") LL1[i][j] = "explorar";
          }
        }
        //
      }
    }

    void print_LL1(){
      for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
          cout << LL1[i][j] << "  ";
        }
        cout << endl;
      }
    }

    bool acepta(string cadena) {
        vector<string> vector_;
        SplitString(cadena," ",vector_);
        for(int i = 0 ; i < vector_.size(); i++){
            
        }
    }



    };
