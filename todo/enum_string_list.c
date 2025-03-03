#include <stdio.h>

#define MEMBERS \
        REGISTER( START, "Start" ) \
        REGISTER( ABORT, "Abort" ) \
        REGISTER( LIMIT, "Limit" )

typedef enum
{
    #define REGISTER(msg, str) msg,
    MEMBERS
    #undef REGISTER
} Identifiers;

static const char * text[] =
{
    #define REGISTER(msg, str) str,
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
