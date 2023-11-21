#pragma once
#include "std_lib_facilities.h"

struct Variable //класс для реализации переменных
{
  string name;
  double value;

  Variable(string n, double v) : name{n}, value{v} {}
};

double primary();

double term();

double expression ();

double get_value (string s);

void set_value (string s, double d);

bool is_declared (string s);

double define_name (string var, double val);


double declaration ();


double statement ();