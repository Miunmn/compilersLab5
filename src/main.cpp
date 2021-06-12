#include <FlexLexer.h>

class Parser{
    FlexLexer* lexer;
    
    public:
    void parse(){
        //Consultar tabla LL1
        //Consultar teglas gramaticales
        while(lexer->yylex() != 0);
    }

   Parser(){
       lexer = new yyFlexLexer;
   }
};

int main( int /* argc */, char** /* argv */ )
{
   Parser p;
   p.parse();

   return 0;
}