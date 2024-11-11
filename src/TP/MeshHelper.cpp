#include "MeshHelper.h"


std::vector<unsigned int> generateUniqueRandomNumbers(int size, std::vector<unsigned> &exclusions)
{
    // Create a vector with all numbers in the range
    std::vector<unsigned int> numbers;
    for (int i = 0; i < size; ++i)
    {
        numbers.push_back(i);
    }
    for (unsigned int excl : exclusions)
    {
        numbers.erase(std::remove(numbers.begin(), numbers.end(), excl), numbers.end());
    }
    // Shuffle the vector
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);

    return numbers;
}

Vertices compute_circum_cirle(const Vertices &vert1, const Vertices &vert2, const Vertices &vert3)
{
    auto tan = [&](const Vertices &A, const Vertices &B, const Vertices &C)
    {
        Vertices crss = crossProduct(C - B, A - B);
        int sign = dotProduct(crss, Vertices(0, 0, 1));
        if (sign > 0)
        {
            sign = 1;
        }
        else if (sign < 0)
        {
            sign = -1;
        }
        else if (sign == 0)
        {
            sign = 0;
        }
        return sign * magn(crss) / dotProduct(C - B, A - B);
    };

    float tan_a = tan(vert1, vert2, vert3);
    float tan_b = tan(vert2, vert3, vert1);
    float tan_c = tan(vert3, vert1, vert2);
    float tan_sum = tan_a + tan_b + tan_c;

    return (vert2 * (tan_b + tan_c) + vert3 * (tan_c + tan_a) + vert2 * (tan_a + tan_b)) / tan_sum;
}

Vertices compute_circumcenter(const Vertices &vert1, const Vertices &vert2, const Vertices &vert3)
{
    auto det = [&](const Vertices &A, const Vertices &B, const Vertices &C)
    {
        double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));

        if (D == 0)
        {
            return Vertices(0, 0, 0);
        }

        double Ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) +
                     (B.x * B.x + B.y * B.y) * (C.y - A.y) +
                     (C.x * C.x + C.y * C.y) * (A.y - B.y)) /
                    D;

        double Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) +
                     (B.x * B.x + B.y * B.y) * (A.x - C.x) +
                     (C.x * C.x + C.y * C.y) * (B.x - A.x)) /
                    D;
        return Vertices(Ux, Uy, 0);
    };

    return det(vert1, vert2, vert3);
}

bool isInsideCircumcircle(const Vertices &vert1, const Vertices &vert2, const Vertices &vert3, const Vertices &vert4)
{

    /*if (orientation_test_2d(vert1, vert2, vert3) < 0)
    {
        return isInsideCircumcircle(vert3, vert2, vert1, vert4);
    }*/
    Vertices center = compute_circumcenter(vert1, vert2, vert3);

    double radius_squared = (center.x - vert1.x) * (center.x - vert1.x) +
                            (center.y - vert1.y) * (center.y - vert1.y);
    double distance_squared = (center.x - vert4.x) * (center.x - vert4.x) +
                              (center.y - vert4.y) * (center.y - vert4.y); // Squared distance

    if (distance_squared < radius_squared)
    {
        return true;
    }
    else
    {
        return false;
    };
}



// Function to calculate the sign of a determinant
double SignDeterminant(double a, double b, double c,
                       double d, double e, double f,
                       double g, double h, double i)
{
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

float determinant(const Vertices &A, const Vertices &B, const Vertices &C)
{
    return A.x * (B.y * C.z - C.y * B.z) - A.y * (B.x * C.z - C.x * B.z) + A.z * (B.x * C.y - C.x * B.y);
}
bool isInsideCircumcircle4(const Vertices &p, const Vertices &q, const Vertices &r, const Vertices &s)
{
    if (orientation_test_2d(p, q, r) > 0)
    {
        return isInsideCircumcircle4(p, r, q, s);
    };
    auto lift = [](const Vertices &vert)
    {
        return Vertices(vert.x, -vert.y, vert.x * vert.x + vert.y * vert.y);
    };
    Vertices lp = lift(p);
    Vertices lq = lift(q);
    Vertices lr = lift(r);
    Vertices ls = lift(s);
    double d = determinant(lq - lp, lr - lp, ls - lp);
    return -d > 0 ? true : false;
}

// Function to determine if point s is inside the circle circumscribed by points p, q, r
bool isInsideCircumcircle3(const Vertices &p, const Vertices &q, const Vertices &r, const Vertices &s)
{
    // Calculate the terms for the determinant
    // Possiblement pas utile
    if (orientation_test_2d(p, q, r) > 0)
    {
        std::cout << "pqr orientaiton was BADBABDBAD" << std::endl;
        return isInsideCircumcircle3(p, r, q, s);
    };
    double qpx = q.x - p.x;
    double qpy = q.y - p.y;
    double rpx = r.x - p.x;
    double rpy = r.y - p.y;
    double spx = s.x - p.x;
    double spy = s.y - p.y;

    double p_dist_squared = p.x * p.x + p.y * p.y;

    double q_dist_squared = q.x * q.x + q.y * q.y;
    double r_dist_squared = r.x * r.x + r.y * r.y;
    double s_dist_squared = s.x * s.x + s.y * s.y;

    double determinant = SignDeterminant(
        qpx, qpy, q_dist_squared - p_dist_squared,
        rpx, rpy, r_dist_squared - p_dist_squared,
        spx, spy, s_dist_squared - p_dist_squared);
    //(-determinant > 0) This had better result
    return (determinant > 0); // If true it is inside
}




std::vector<unsigned int> grahamScan(std::vector<Vertices> &point_cloud, unsigned int &center)
{

    // std::cout << "In scan" << std::endl;
    int n = point_cloud.size();
    if (n < 3)
    {
        std::cout << "Convex Hull need at least 3 points " << std::endl;
        std::vector<unsigned int> ret;
        return ret;
    }

    int sum_x = point_cloud[0].x;
    int sum_y = point_cloud[0].y;

    // trouver le pivot et le conserver à  [0];
    int curr_bottom = 0;
    for (int i = 1; i < n; i++)
    {
        sum_x += point_cloud[i].x;
        sum_y += point_cloud[i].y;
        if (point_cloud[i].y < point_cloud[curr_bottom].y || (point_cloud[i].y == point_cloud[curr_bottom].y && point_cloud[i].x < point_cloud[curr_bottom].x))
        {
            curr_bottom = i;
        }
    }
    // Approximate the centroid
    Vertices centroid(sum_x / n, sum_y / n, 0.0);
    std::swap(point_cloud[curr_bottom], point_cloud[0]);

    // Tri par ordre polaire par rapport au pivot
    std::sort(point_cloud.begin() + 1, point_cloud.end(), [&point_cloud](const Vertices &vert1, const Vertices &vert2)
              {
        int orientation = orientation_test_2d(point_cloud[0],vert1, vert2);
        if (orientation == 0){return (point_cloud[0].x - vert1.x) * (point_cloud[0].x - vert1.x) + (point_cloud[0].y - vert1.y) * (point_cloud[0].y - vert1.y) < 
                   (point_cloud[0].x - vert2.x) * (point_cloud[0].x - vert2.x) + (point_cloud[0].y - vert2.y) * (point_cloud[0].y - vert2.y);
                           //return (vert1.x < vert2.x) || (vert1.x ==vert2.x && vert1.y < vert2.y);
                           }else{
        return (orientation > 0);} });

    // Mettre les premiers points dans une pile
    std::vector<Vertices> hull_stack;
    hull_stack.push_back(point_cloud[0]);
    hull_stack.push_back(point_cloud[1]);
    std::vector<unsigned int> hull_stack_indices;
    hull_stack_indices.emplace_back(0);
    hull_stack_indices.emplace_back(1);

    double min_dist = std::numeric_limits<double>::max();
    // Step 4: Process remaining points
    unsigned int nearest = 0;
    for (int i = 2; i < n; i++)
    {
        // TODO rvoirr tout ça
        while (hull_stack.size() > 1 && orientation_test_2d(hull_stack[hull_stack.size() - 2], hull_stack.back(), point_cloud[i]) < 0)
        {
            hull_stack.pop_back();
            hull_stack_indices.pop_back();
        }
        hull_stack.push_back(point_cloud[i]); // Add the current point
        hull_stack_indices.emplace_back(i);

        // Also treating the centroid
        double distance = std::sqrt(std::pow(point_cloud[i].x - centroid.x, 2) + pow(point_cloud[i].y - centroid.y, 2));
        if (distance < min_dist)
        {
            min_dist = distance;
            nearest = i;
        }
    }
    center = nearest;
    // std::cout << "nb is hull  " << hull_stack_indices.size() << std::endl;

    return hull_stack_indices; // Return pairs of indices in the hull
}

