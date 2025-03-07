#include <string>
#include <iostream>

enum Token_Type
{
    IDENTIFIER,
    NUMBER,
    END_OF_FILE,
};



static int last_char = ' ';
static std::string token;



static int get_token()
{
    // eat whitespace
    while(isspace(last_char))
    {
      last_char = getchar();
    }
    token = last_char;

    // 
    if(isalpha(last_char))
    {
        while (isalnum(last_char = getchar()))
        {
            token += last_char;
        }
        return Token_Type::IDENTIFIER;
    }

    if(isdigit(last_char) || last_char == '.')
    {
        last_char = getchar();
	while(isalnum(last_char) || last_char == '.')
	{
	    token += last_char;
	    last_char = getchar();
	}
	return Token_Type::NUMBER;
    }

    if(last_char == EOF)
    {
      return Token_Type::END_OF_FILE;
    }

    int unknown_char = last_char;
    last_char = getchar();
    return unknown_char;
}


static int parse_token()
{
    int token_type = get_token();

    switch(token_type)
    {
        case Token_Type::IDENTIFIER:
	  std::cout << "Identifier:   ";
	  break;
        case Token_Type::NUMBER:
	  std::cout << "Number:       ";
	  break;
        case Token_Type::END_OF_FILE:
	  std::cout << "End of file:  ";
	  break;
        default:
	  std::cout << "Unknown:      ";
    }
    std::cout << token << std::endl;

    return token_type;
}


int main(int argc, char** argv)
{
  while(parse_token() != Token_Type::END_OF_FILE);

  return 0;
}
