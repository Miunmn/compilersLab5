#include "gramatica.cpp"
#include "parser.hpp"

#include <iostream>
#include <string>
#include <vector>


using namespace std;


int main( int /* argc */, char** /* argv */ )
{
   Parser p;
   p.parse();
   return 0;
}