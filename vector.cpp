union v2
{
    struct
    {
        float x;
        float y;
    };
    struct
    {
        float u;
        float v;
    };
    float e[2];
};


union v3
{
    struct
    {
        float x;
        float y;
        float z;
    };
    struct
    {
        float r;
        float g;
        float b;
    };
    float e[3];
};


union v4
{
    struct
    {
        union
        {
            v3 xyz;
            struct
            {
                float x;
                float y;
                float z;
            };
        };
        float w;
    };
    struct
    {
        union
        {
            v3 rgb;
            struct
            {
                float r;
                float g;
                float b;
            };
        };
        float a;
    };
    float e[4];
};
