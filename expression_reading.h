#include "Variables.h"



double primary () // приоритетные части выражения
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '(':
  {
    double d = expression();
    t = ts.get();
    if (t.kind != ')')
      error("В выражении не хватает закрывающей скобки");
  }

  case '-':
    return -primary();
  case '+':
    return +primary();

  case number:
    return t.value;

  case name:
    return get_value(t.name);

  default:
    error("primary expected");
    
  }
}

double term ()
{
  double left = primary();

  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '*':
      left *= primary();
      break;

    case '/':
    {
      double d = primary();
      if (d == 0)
        error("деление на ноль не определено");
      left /= d;
      break;
    }
    case '^':
    {
      double stepenb = primary();
      if (stepenb ==0.5){
        if (left <0)
          error("комплексные числа не определены");
          
        left= sqrt(left);
          
      }
      else{
        if(double(int(stepenb))!=stepenb)
          error("нецелые степени (кроме 0.5) не определены");

        left =pow(left,stepenb);
      }
      
      break;

    }
      
    default:
      ts.putback(t);
      return left;
    }
  }
}

double expression ()
{
  double left = term();

  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '+':
      left += term();
      break;

    case '-':
      left -= term();
      break;

    default:
      ts.putback(t);
      return left;
    }
  }
}
