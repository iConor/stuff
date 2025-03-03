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

typedef struct
{
    Identifiers key;
    const char * val;
} Map;

static const Map map[] =
{
    #define REGISTER(msg, str) { msg, str },
    MEMBERS
    #undef REGISTER
};


int main(int argc, char * argv[])
{
    const int MAX = LIMIT;

    for( int i = 0; i <= MAX; i++)
    {
        printf("[%d] %s\n", map[i].key, map[i].val);
    }
    return 0;
}
