#include "Token.h"
#include "expression_reading.h"
#include "Const_symbols.h"
#include "Token_stream.h"
#include "math.h"

extern Token_stream ts;

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
      error("No closing ')' found");
  }

  case '-':
    return -primary();

  case '+':
    return +primary();
  
  case number:
    return t.value;
  
  case Token_sum:
    cout<<"bruhh";

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
        error("division by zero");
      left /= d;
      break;
    }
    case '^':
    {
      double stepenb = primary();
      if (stepenb ==0.5){
        if (left <0)
          error("complex numbers ???? ");
          
        left= sqrt(left);
          
      }
      else{
        if(double(int(stepenb))!=stepenb)
          error("only can raise to an integer or 0.5");

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

    case '\n':
      return left;
    default:
      ts.putback(t);
      return left;
    }
  }
}

vector<Variable> var_table; // Вектор с переменными

double get_value (string s) // штука чтобы по имени переменной получать значение из вектора
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return var_table[i].value;

  error("get: unknown variable ", s);
}

void set_value (string s, double d) // штука чтобы менять значения переменных
{
  for (int i = 0; i <= var_table.size(); ++i)
  {
    if (var_table[i].name == s)
    {
      var_table[i].value = d;
      return;
    }
  }

  error("set: unknown variable ", s);
}

bool is_declared (string s) // фигня чтобы понять, что есть в векторе с перменными
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return true;

  return false;
}

double define_name (string var, double val) //штука для добавления новых переменных
{
  if (is_declared(var))
    error(var, " second declaration ");

  var_table.push_back(Variable{var, val});

  return val;
}


double declaration () //обозначение переменной
{
  Token t = ts.get();
  if (t.kind != name)
    error(" No variable name");

  string var = t.name;
  if (is_declared(var))
    error(var, " second declaration");

  t = ts.get();
  if (t.kind != '=')
    error("'=' is missing in declaration ", var);

  return define_name(var, expression());
}


double statement () {//Функция для обработки переменных 

  Token t = ts.get();
  switch (t.kind)
  {
  case let:
      return declaration();

  default:
      ts.putback(t);
      return expression();
  }
}