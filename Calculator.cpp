#include "Token.h"
#include "Const_symbols.h"
#include "Token_stream.h"
#include "expression_reading.h"

extern Token_stream ts;

void calculate ()
{
  while (true)
    try
    {
      
      Token t = ts.get();
      while (t.kind == print){
        
         t = ts.get();
      }

      if (t.kind == quitkostilb)
        return;

      ts.putback(t);
      cout << result << statement() << endl;
      
    }
    catch (runtime_error& e)
    {
      cerr << e.what() << endl;
      // clean_up_mess();
    }
}

int main () 
try
{
  setlocale(LC_ALL,"Rus");
  cout << "You can start writing your math problem"<<endl
          << "    Only %,*,/,^,+,- operators are allowed"<<endl
              <<"When you finish, PLEASE, enter \"quit\""<<endl
                  << "    At the end of your math problem, enter \";\""<<endl;
  define_name("pi", 3.141592653589793);//
  define_name("e", 2.718281828459045);
  define_name("k", 1000);

  calculate();
}
catch (exception& e)
{
  cerr << "exception: " << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Smth went completely wrong..." << endl;
  return 2;
}




