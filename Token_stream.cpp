#include "Token_stream.h"
#include "Const_symbols.h"

Token_stream ts;

void clean_up_mess () { 
  ts.ignore(print); 
}

void Token_stream::putback(Token t) // функция возврата символов обратно в поток, чтобы можно было дальше с нимим работать
{
  if (full)
    error("putback() into a full buffer");

  buffer = t;
  full = true;
}

Token Token_stream::get()// поток символов, из которого достаем значения 
{
  if (full)
  {
    full = false;
    return buffer;
  }

  char ch;
  cin.get(ch);


  switch (ch)
  {
  case declkey:
    return Token{let};
  case '\n':
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case print:
  case '=':
  case '^':
    return Token{ch};
  
   
  
  case '.':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  {
    cin.putback(ch);
    double val;
    cin >> val;
    return Token{number, val};
  }

  default:
    if (isalpha(ch))
    {
      string s;
      s+=ch;
      while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
        s += ch;
        
            
      cin.putback(ch);
  
      if (s == quit)
        return Token{'q'};
        
      if (s == sum)
        return Token{Token_sum};
      
      if (s == tr_sin)
        return Token{Token_sin};
      

      return Token{name, s};
    }
    error("Wrong lexem");
  }
}


void Token_stream::ignore(char c) // игнорирование символов
{
  if (full && c == buffer.kind )
  {
    full = false;
    return;
  }
  full = false;

  char ch;
  while (cin >> ch){
    if (ch == c)
      return;
    break;
  }
}



