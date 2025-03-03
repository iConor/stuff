#include <stdio.h>

#define MEMBERS \
        REGISTER( START ) \
        REGISTER( ABORT ) \
        REGISTER( LIMIT )

typedef enum
{
    #define REGISTER(x) x,
    MEMBERS
    #undef REGISTER
} Identifiers;

static const char * text[] =
{
    #define REGISTER(x) #x,
    MEMBERS
    #undef REGISTER
};


int main(int argc, char * argv[])
{
    const int MAX = LIMIT;
    Identifiers index;

    for( int i = 0; i <= MAX; i++)
    {
        index = (Identifiers) i;
        printf("[%d] %s\n", index, text[index]);
    }
    return 0;
}
