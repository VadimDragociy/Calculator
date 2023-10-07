#include "Token_stream.h"

double expression ();

struct Variable //класс для реализации переменных
{
  string name;
  double value;

  Variable(string n, double v) : name{n}, value{v} {}
};
vector<Variable> var_table; // Вектор с переменными

double get_value (string s) // штука чтобы по имени переменной получать значение из вектора
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return var_table[i].value;

  error("get: неизместная переменная ", s);
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

  error("set: неизвестная переменная ", s);
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
    error(var, " обозначено дважды");

  var_table.push_back(Variable{var, val});

  return val;
}

double declaration () //обозначение переменной
{
  Token t = ts.get();
  if (t.kind != name)
    error("нет имени у переменной");

  string var = t.name;
  if (is_declared(var))
    error(var, " имя обозначено дважды");

  t = ts.get();
  if (t.kind != '=')
    error("'=' отсутствует в обозначении переменной ", var);

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

