#ifndef IPA_MATH_H
#define IPA_MATH_H


float deg2rad(float degrees)
{
    float radians = 0.0f;

    float convert = M_PI / 180.0f;

    radians = degrees * convert;

    return radians;
}


#endif /* IPA_MATH_H */
