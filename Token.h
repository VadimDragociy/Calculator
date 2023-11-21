#pragma once
#include "std_lib_facilities.h"

struct Token //класс для того, чтобы записывать лексемы
{
public:
  char kind;
  double value;
  string name;

    Token(char ch) : kind{ch}, value{0} {} //лексема просто символ
    Token(char ch, double val) : kind{ch}, value{val} {} //лексема цифры 
    Token(char ch,string n): kind{ch},name{n}{} // лексема переменной
};

