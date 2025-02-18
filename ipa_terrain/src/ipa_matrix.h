#ifndef IPA_MATRIX_H
#define IPA_MATRIX_H

#include "ipa_vector.h"

union m4
{
    float m[4][4];
    float e[16];
};

inline v4 operator*(m4 lhs, v4 rhs)
{
    v4 product;

    product.x = lhs.m[0][0] * rhs.x +
                lhs.m[0][1] * rhs.y +
                lhs.m[0][2] * rhs.z +
                lhs.m[0][3] * rhs.w;

    product.y = lhs.m[1][0] * rhs.x +
                lhs.m[1][1] * rhs.y +
                lhs.m[1][2] * rhs.z +
                lhs.m[1][3] * rhs.w;

    product.z = lhs.m[2][0] * rhs.x +
                lhs.m[2][1] * rhs.y +
                lhs.m[2][2] * rhs.z +
                lhs.m[2][3] * rhs.w;

    product.w = lhs.m[3][0] * rhs.x +
                lhs.m[3][1] * rhs.y +
                lhs.m[3][2] * rhs.z +
                lhs.m[3][3] * rhs.w;

    return product;
}

#endif /* LIB_MATRIX_H */
