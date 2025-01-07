union color
{
    struct
    {
        float r;
        float g;
        float b;
    };
    struct
    {
        float h;
        float s;
        float v;
    };
};

color hsv2rgb(float h, float s, float v)
{
    color out = {};

    float chroma = s * v;
    float hprime = h / 60.0f;

    float xfactor = chroma * (1.0f - fabsf(fmodf(hprime, 2.0f) - 1.0f));

    float m = v - chroma;

    out.r += m;
    out.g += m;
    out.b += m;

    if(0.0f <= hprime && hprime <= 1.0f)
    {
        out.r += chroma;
        out.g += xfactor;
    }
    else if(hprime <= 2.0f)
    {
        out.r += xfactor;
        out.g += chroma;
    }
    else if(hprime <= 3.0f)
    {
        out.g += chroma;
        out.b += xfactor;
    }
    else if(hprime <= 4.0f)
    {
        out.g += xfactor;
        out.b += chroma;
    }
    else if(hprime <= 5.0f)
    {
        out.r += xfactor;
        out.b += chroma;
    }
    else if(hprime <= 6.0f)
    {
        out.r += chroma;
        out.b += xfactor;
    }

    return out;
}
