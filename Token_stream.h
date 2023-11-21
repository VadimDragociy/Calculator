#pragma once

#include "Token.h"
#include "Const_symbols.h"

class Token_stream // буфер для токенов
{
  bool full{false};
  Token buffer{'\0'};

public:
  Token_stream() {}

  Token get ();
  void putback (Token t);

  void ignore (char);
};

void clean_up_mess ();




