#include "expression_reading.h"


void calculate ()
{
  while (true)
    try
    {
      
      Token t = ts.get();
      while (t.kind == print ){
        
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
      clean_up_mess();
    }
}

int main () 
try
{
  cout << "Можете начинать вводить выражения."<<endl
          << "    Разрешены операции %,*,/,^,+,-"<<endl
              <<"По завершении работы введите \"quit\""<<endl
                  << "    В конце выражения введите \";\""<<endl;
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
  cerr << "Что-то пошло не так..." << endl;
  return 2;
}




