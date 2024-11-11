#ifndef MESH_HELP_HPP
#define MESH_HELP_HPP

#include <algorithm>
#include <vector>
#include <random>

#include "Vertices.h"

inline float orientation_test_2d(const Vertices &vert1,
                                 const Vertices &vert2, const Vertices &vert3)
{
    // Crossp rudct 2D ver1, ver2 and vert 1,vert3

    return (((vert2.x - vert1.x) * (vert3.y - vert1.y)) -
            ((vert2.y - vert1.y) * (vert3.x - vert1.x)));

    // Also determine which slop between vert2vert1is the biggst
    // 0 >  counter clockwise , and vert3 is on the left of vert1
    //== 0 They are collineeare
    //< 0
}

std::vector<unsigned int> grahamScan(std::vector<Vertices> &point_cloud, unsigned int &center);
std::vector<unsigned int> generateUniqueRandomNumbers(int size, std::vector<unsigned> &exclusions);
Vertices compute_circum_cirle(const Vertices &vert1, const Vertices &vert2, const Vertices &vert3);

Vertices compute_circumcenter(const Vertices &vert1, const Vertices &vert2, const Vertices &vert3);

// https://en.wikipedia.org/wiki/Delaunay_triangulation
inline float circumcircleDeterminant(const Vertices &A, const Vertices &B, const Vertices &C, const Vertices &D)
{
    return A.x * (B.y * (C.x * C.x + C.y * C.y) - C.y * (B.x * B.x + B.y * B.y) + D.y * (B.x * B.x + B.y * B.y - C.x * C.x - C.y * C.y)) -
           B.x * (A.y * (C.x * C.x + C.y * C.y) - C.y * (A.x * A.x + A.y * A.y) + D.y * (A.x * A.x + A.y * A.y - C.x * C.x - C.y * C.y)) + C.x * (A.y * (B.x * B.x + B.y * B.y) - B.y * (A.x * A.x + A.y * A.y) + D.y * (A.x * A.x + A.y * A.y - B.x * B.x - B.y * B.y)) + D.x * (A.y * (B.x * B.y - C.x * C.y) + B.y * (C.x * C.x + C.y * C.y - A.x * A.x - A.y * A.y) - C.y * (A.x * A.x + A.y * A.y - B.x * B.x - B.y * B.y));
}

// Function to calculate the sign of a determinant
double SignDeterminant(double a, double b, double c,
                       double d, double e, double f,
                       double g, double h, double i);
float determinant(const Vertices &A, const Vertices &B, const Vertices &C);

bool isInsideCircumcircle(const Vertices &vert1, const Vertices &vert2, const Vertices &vert3, const Vertices &vert4);

bool isInsideCircumcircle4(const Vertices &p, const Vertices &q, const Vertices &r, const Vertices &s);
// Function to determine if point s is inside the circle circumscribed by points p, q, r
bool isInsideCircumcircle3(const Vertices &p, const Vertices &q, const Vertices &r, const Vertices &s);

#endif

