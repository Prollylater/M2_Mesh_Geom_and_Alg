
#include "Mat.h"

namespace Transform
{
    // TODO Move to appropriate section

    inline float to_radians(float angle_degree)
    {
        return angle_degree * M_PI / 180;
    }
    Vec4 mat4mult(const Mat<float> &mat, const Vec4 &vec)
    {
        // Resultant vector
        Vec4 result;

        // Perform matrix-vector multiplication
        result.x = mat.value_at(0, 0) * vec.x + mat.value_at(0, 1) * vec.y + mat.value_at(0, 2) * vec.z + mat.value_at(0, 3) * vec.w;
        result.y = mat.value_at(1, 0) * vec.x + mat.value_at(1, 1) * vec.y + mat.value_at(1, 2) * vec.z + mat.value_at(1, 3) * vec.w;
        result.z = mat.value_at(2, 0) * vec.x + mat.value_at(2, 1) * vec.y + mat.value_at(2, 2) * vec.z + mat.value_at(2, 3) * vec.w;
        result.w = mat.value_at(3, 0) * vec.x + mat.value_at(3, 1) * vec.y + mat.value_at(3, 2) * vec.z + mat.value_at(3, 3) * vec.w;

        return result;
    }

    // Quick  Matrix inversion based on glu's
    bool Inverse(Mat<float> &to_invert)
    {

        if (to_invert.getRows() != to_invert.getCols() || to_invert.getRows() != 4)
        {
            // Or anything else
            return false;
        }
        // Determinant
        // LU Factorization
        Mat<float> new_mat;

        float inv[16], det;
        inv[0] = to_invert.at(1, 1) * to_invert.at(2, 2) * to_invert.at(3, 3) -
                 to_invert.at(1, 1) * to_invert.at(2, 3) * to_invert.at(3, 2) -
                 to_invert.at(1, 2) * to_invert.at(2, 1) * to_invert.at(3, 3) +
                 to_invert.at(1, 2) * to_invert.at(2, 3) * to_invert.at(3, 1) +
                 to_invert.at(1, 3) * to_invert.at(2, 1) * to_invert.at(3, 2) -
                 to_invert.at(1, 3) * to_invert.at(2, 2) * to_invert.at(3, 1);

        inv[4] = -to_invert.at(1, 0) * to_invert.at(2, 2) * to_invert.at(3, 3) +
                 to_invert.at(1, 0) * to_invert.at(2, 3) * to_invert.at(3, 2) +
                 to_invert.at(1, 2) * to_invert.at(2, 0) * to_invert.at(3, 3) -
                 to_invert.at(1, 2) * to_invert.at(2, 3) * to_invert.at(3, 0) -
                 to_invert.at(1, 3) * to_invert.at(2, 0) * to_invert.at(3, 2) +
                 to_invert.at(1, 3) * to_invert.at(2, 2) * to_invert.at(3, 0);

        inv[8] = to_invert.at(1, 0) * to_invert.at(2, 1) * to_invert.at(3, 3) -
                 to_invert.at(1, 0) * to_invert.at(2, 3) * to_invert.at(3, 1) -
                 to_invert.at(1, 1) * to_invert.at(2, 0) * to_invert.at(3, 3) +
                 to_invert.at(1, 1) * to_invert.at(2, 3) * to_invert.at(3, 0) +
                 to_invert.at(1, 3) * to_invert.at(2, 0) * to_invert.at(3, 1) -
                 to_invert.at(1, 3) * to_invert.at(2, 1) * to_invert.at(3, 0);

        inv[12] = -to_invert.at(1, 0) * to_invert.at(2, 1) * to_invert.at(3, 2) +
                  to_invert.at(1, 0) * to_invert.at(2, 2) * to_invert.at(3, 1) +
                  to_invert.at(1, 1) * to_invert.at(2, 0) * to_invert.at(3, 2) -
                  to_invert.at(1, 1) * to_invert.at(2, 2) * to_invert.at(3, 0) -
                  to_invert.at(1, 2) * to_invert.at(2, 0) * to_invert.at(3, 1) +
                  to_invert.at(1, 2) * to_invert.at(2, 1) * to_invert.at(3, 0);

        inv[1] = -to_invert.at(0, 1) * to_invert.at(2, 2) * to_invert.at(3, 3) +
                 to_invert.at(0, 1) * to_invert.at(2, 3) * to_invert.at(3, 2) +
                 to_invert.at(0, 2) * to_invert.at(2, 0) * to_invert.at(3, 3) -
                 to_invert.at(0, 2) * to_invert.at(2, 3) * to_invert.at(3, 0) -
                 to_invert.at(0, 3) * to_invert.at(2, 0) * to_invert.at(3, 2) +
                 to_invert.at(0, 3) * to_invert.at(2, 2) * to_invert.at(3, 0);

        inv[5] = to_invert.at(0, 0) * to_invert.at(2, 2) * to_invert.at(3, 3) -
                 to_invert.at(0, 0) * to_invert.at(2, 3) * to_invert.at(3, 2) -
                 to_invert.at(0, 2) * to_invert.at(2, 0) * to_invert.at(3, 3) +
                 to_invert.at(0, 2) * to_invert.at(2, 3) * to_invert.at(3, 0) +
                 to_invert.at(0, 3) * to_invert.at(2, 0) * to_invert.at(3, 2) -
                 to_invert.at(0, 3) * to_invert.at(2, 2) * to_invert.at(3, 0);

        inv[9] = -to_invert.at(0, 0) * to_invert.at(2, 1) * to_invert.at(3, 3) +
                 to_invert.at(0, 0) * to_invert.at(2, 3) * to_invert.at(3, 1) +
                 to_invert.at(0, 1) * to_invert.at(2, 0) * to_invert.at(3, 3) -
                 to_invert.at(0, 1) * to_invert.at(2, 3) * to_invert.at(3, 0) -
                 to_invert.at(0, 3) * to_invert.at(2, 0) * to_invert.at(3, 1) +
                 to_invert.at(0, 3) * to_invert.at(2, 1) * to_invert.at(3, 0);

        inv[13] = to_invert.at(0, 0) * to_invert.at(2, 1) * to_invert.at(3, 2) -
                  to_invert.at(0, 0) * to_invert.at(2, 2) * to_invert.at(3, 1) -
                  to_invert.at(0, 1) * to_invert.at(2, 0) * to_invert.at(3, 2) +
                  to_invert.at(0, 1) * to_invert.at(2, 2) * to_invert.at(3, 0) +
                  to_invert.at(0, 2) * to_invert.at(2, 0) * to_invert.at(3, 1) -
                  to_invert.at(0, 2) * to_invert.at(2, 1) * to_invert.at(3, 0);

        inv[2] = to_invert.at(0, 1) * to_invert.at(1, 2) * to_invert.at(3, 3) -
                 to_invert.at(0, 1) * to_invert.at(1, 3) * to_invert.at(3, 2) -
                 to_invert.at(0, 2) * to_invert.at(1, 1) * to_invert.at(3, 3) +
                 to_invert.at(0, 2) * to_invert.at(1, 3) * to_invert.at(3, 1) +
                 to_invert.at(0, 3) * to_invert.at(1, 1) * to_invert.at(3, 2) -
                 to_invert.at(0, 3) * to_invert.at(1, 2) * to_invert.at(3, 1);

        inv[6] = -to_invert.at(0, 0) * to_invert.at(1, 2) * to_invert.at(3, 3) +
                 to_invert.at(0, 0) * to_invert.at(1, 3) * to_invert.at(3, 2) +
                 to_invert.at(0, 2) * to_invert.at(1, 0) * to_invert.at(3, 3) -
                 to_invert.at(0, 2) * to_invert.at(1, 3) * to_invert.at(3, 0) -
                 to_invert.at(0, 3) * to_invert.at(1, 0) * to_invert.at(3, 2) +
                 to_invert.at(0, 3) * to_invert.at(1, 2) * to_invert.at(3, 0);

        inv[10] = to_invert.at(0, 0) * to_invert.at(1, 1) * to_invert.at(3, 3) -
                  to_invert.at(0, 0) * to_invert.at(1, 3) * to_invert.at(3, 1) -
                  to_invert.at(0, 1) * to_invert.at(1, 0) * to_invert.at(3, 3) +
                  to_invert.at(0, 1) * to_invert.at(1, 3) * to_invert.at(3, 0) +
                  to_invert.at(0, 3) * to_invert.at(1, 0) * to_invert.at(3, 1) -
                  to_invert.at(0, 3) * to_invert.at(1, 1) * to_invert.at(3, 0);

        inv[14] = -to_invert.at(0, 0) * to_invert.at(1, 1) * to_invert.at(2, 3) +
                  to_invert.at(0, 0) * to_invert.at(1, 3) * to_invert.at(2, 1) +
                  to_invert.at(0, 1) * to_invert.at(1, 0) * to_invert.at(2, 3) -
                  to_invert.at(0, 1) * to_invert.at(1, 3) * to_invert.at(2, 0) -
                  to_invert.at(0, 2) * to_invert.at(1, 0) * to_invert.at(2, 1) +
                  to_invert.at(0, 2) * to_invert.at(1, 1) * to_invert.at(2, 0);

        inv[3] = -to_invert.at(0, 1) * to_invert.at(1, 2) * to_invert.at(2, 3) +
                 to_invert.at(0, 1) * to_invert.at(1, 3) * to_invert.at(2, 2) +
                 to_invert.at(0, 2) * to_invert.at(1, 1) * to_invert.at(2, 3) -
                 to_invert.at(0, 2) * to_invert.at(1, 3) * to_invert.at(2, 1) -
                 to_invert.at(0, 3) * to_invert.at(1, 1) * to_invert.at(2, 2) +
                 to_invert.at(0, 3) * to_invert.at(1, 2) * to_invert.at(2, 1);

        inv[7] = to_invert.at(0, 0) * to_invert.at(1, 2) * to_invert.at(2, 3) -
                 to_invert.at(0, 0) * to_invert.at(1, 3) * to_invert.at(2, 2) -
                 to_invert.at(0, 2) * to_invert.at(1, 0) * to_invert.at(2, 3) +
                 to_invert.at(0, 2) * to_invert.at(1, 3) * to_invert.at(2, 0) +
                 to_invert.at(0, 3) * to_invert.at(1, 0) * to_invert.at(2, 2) -
                 to_invert.at(0, 3) * to_invert.at(1, 2) * to_invert.at(2, 0);

        inv[11] = -to_invert.at(0, 0) * to_invert.at(1, 1) * to_invert.at(2, 3) +
                  to_invert.at(0, 0) * to_invert.at(1, 3) * to_invert.at(2, 1) +
                  to_invert.at(0, 1) * to_invert.at(1, 0) * to_invert.at(2, 3) -
                  to_invert.at(0, 1) * to_invert.at(1, 3) * to_invert.at(2, 0) -
                  to_invert.at(0, 3) * to_invert.at(1, 0) * to_invert.at(2, 1) +
                  to_invert.at(0, 3) * to_invert.at(1, 1) * to_invert.at(2, 0);

        inv[15] = to_invert.at(0, 0) * to_invert.at(1, 1) * to_invert.at(2, 2) -
                  to_invert.at(0, 0) * to_invert.at(1, 2) * to_invert.at(2, 1) -
                  to_invert.at(0, 1) * to_invert.at(1, 0) * to_invert.at(2, 2) +
                  to_invert.at(0, 1) * to_invert.at(1, 2) * to_invert.at(2, 0) +
                  to_invert.at(0, 2) * to_invert.at(1, 0) * to_invert.at(2, 1) -
                  to_invert.at(0, 2) * to_invert.at(1, 1) * to_invert.at(2, 0);

        det = to_invert.at(0, 0) * inv[0] + to_invert.at(0, 1) * inv[4] + to_invert.at(0, 2) * inv[8] + to_invert.at(0, 3) * inv[12];
        if (det == 0)
        {
            return false;
        }

        det = 1.0f / det;

        for (int row = 0; row < 4; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                to_invert.at(row, col) = inv[row * 4 + col] * det;
            }
        }

        return true;
    }

    // TODO Direct initialisation in T* data instead of the allocation + copy

    Mat<float> Translation(float tx, float ty, float tz)
    {
        Mat<float> translate_mat(4, 4, 1);

        translate_mat.at(0, 0) = 1.0f;
        translate_mat.at(0, 3) = tx;
        translate_mat.at(1, 1) = 1.0f;
        translate_mat.at(1, 3) = ty;
        translate_mat.at(2, 2) = 1.0f;
        translate_mat.at(2, 3) = tz;
        translate_mat.at(3, 3) = 1.0f;

        return translate_mat;
    }

    Mat<float> Scale(float sx, float sy, float sz)
    {
        Mat<float> scale_mat(4, 4, 1); // 4x4 matrix for homogeneous coordinates

        scale_mat.at(0, 0) = sx;
        scale_mat.at(1, 1) = sy;
        scale_mat.at(2, 2) = sz;
        scale_mat.at(3, 3) = 1.0f;

        return scale_mat;
    }

    Mat<float> RotationY(float angle_de)
    {
        Mat<float> rotate_mat(4, 4, 1);
        float angle = to_radians(angle);

        float angle_cos = cos(angle);
        float angle_sin = sin(angle);

        rotate_mat.at(0, 0) = angle_cos;
        rotate_mat.at(0, 2) = angle_sin;
        rotate_mat.at(1, 1) = 1.0f;
        rotate_mat.at(2, 0) = -angle_sin;
        rotate_mat.at(2, 2) = angle_cos;
        rotate_mat.at(3, 3) = 1.0f;

        return rotate_mat;
    }
    Mat<float> RotationX(float angle_de)
    {
        Mat<float> rotate_mat(4, 4, 1);
        float angle = to_radians(angle);

        float angle_cos = cos(angle);
        float angle_sin = sin(angle);

        rotate_mat.at(0, 0) = angle_cos;
        rotate_mat.at(0, 1) = -angle_sin;
        rotate_mat.at(1, 0) = angle_sin;
        rotate_mat.at(1, 1) = angle_cos;
        rotate_mat.at(2, 2) = 1.0f;
        rotate_mat.at(3, 3) = 1.0f;

        return rotate_mat;
    }

    Mat<float> RotationZ(float angle_de)
    {
        Mat<float> rotate_mat(4, 4, 1);
        float angle = to_radians(angle);
        float angle_cos = cos(angle);
        float angle_sin = sin(angle);

        rotate_mat.at(0, 0) = angle_cos;
        rotate_mat.at(0, 1) = -angle_sin;
        rotate_mat.at(1, 0) = angle_sin;
        rotate_mat.at(1, 1) = angle_cos;
        rotate_mat.at(2, 2) = 1.0f;
        rotate_mat.at(3, 3) = 1.0f;

        return rotate_mat;
    }

    Mat<float> Perspective(float fov, float aspect_ratio, float znear, float zfar)
    {
        Mat<float> persp_mat(4, 4, 1);

        float tan_fov = tan(to_radians(fov) / 2.0f);
        float inv_tan_fov = 1 / tan_fov;

        float pre_calc = 1 / (znear - zfar);

        persp_mat.at(0, 0) = inv_tan_fov / (aspect_ratio);
        persp_mat.at(1, 1) = inv_tan_fov;
        persp_mat.at(2, 2) = -(zfar + znear) * pre_calc;
        persp_mat.at(2, 3) = 2.0f * zfar * znear * pre_calc;
        persp_mat.at(3, 2) = -1.0f;

        return persp_mat;
    }
    Mat<float> Ortho(float left, float right, float bottom, float top, float znear, float zfar)
    {
        Mat<float> ortho_mat(4, 4, 1);

        ortho_mat.at(0, 0) = 2.0f / (right - left);
        ortho_mat.at(1, 1) = 2.0f / (top - bottom);
        ortho_mat.at(2, 2) = -2.0f / (zfar - znear);
        ortho_mat.at(3, 3) = 1.0f;

        ortho_mat.at(0, 3) = -(right + left) / (right - left);
        ortho_mat.at(1, 3) = -(top + bottom) / (top - bottom);
        ortho_mat.at(2, 3) = -(zfar + znear) / (zfar - znear);

        return ortho_mat;
    }
    Mat<float> LookAt(const Vec<float> &cam_pos, const Vec<float> &target_pos, const Vec<float> &up)
    {
        // Theory:
        //  Move to camera world through a translation
        //  Compute the camera axes one the obkect
        Vec<float> dir = Norm(target_pos - cam_pos);   // Translation
        Vec<float> right = Norm(Cross(Norm(up), dir)); // X-axis
        Vec<float> newup = Norm(Cross(dir, right));    // Y-axis

        // Construct the look-at matrix
        // Theory:: An affine transformation matrix that transpose an object to camera
        Mat<float> view(4, 4, 1);

        // Coordinate/axes components
        view.at(0, 0) = right.x;
        view.at(1, 0) = right.y;
        view.at(2, 0) = right.z;
        view.at(0, 1) = up.x;
        view.at(1, 1) = up.y;
        view.at(2, 1) = up.z;
        view.at(0, 2) = -dir.x;
        view.at(1, 2) = -dir.y;
        view.at(2, 2) = -dir.z;
        // Translation component
        view.at(3, 0) = -Dot(right, cam_pos);
        view.at(3, 1) = -Dot(up, cam_pos);
        view.at(3, 2) = -Dot(dir, cam_pos);

        view.at(3, 3) = 1.0f;

        return view;
    }
    /*
       Mat<float> LookAt(const Vec<float> &cam_pos, const Vec<float> &target_pos, const Vec<float> &up)
    {
        // Theory:
        //  Move to camera world through a translation
        //  Compute the camera axes one the obkect
        Vec<float> dir = Norm(target_pos - cam_pos);   // Translation
        Vec<float> right = Norm(Cross(Norm(up), dir)); // X-axis
        Vec<float> newup = Norm(Cross(dir, right));    // Y-axis

        // Construct the look-at matrix
        // Theory:: An affine transformation matrix that transpose an object to camera
        Mat<float> view(4, 4, 1);

        // Coordinate/axes components
        view.at(0, 0) = right.x;
        view.at(0, 1) = right.y;
        view.at(0, 2) = right.z;
        view.at(1, 0) = up.x;
        view.at(1, 1) = up.y;
        view.at(1, 2) = up.z;
        view.at(2, 0) = -dir.x;
        view.at(2, 1) = -dir.y;
        view.at(2, 2) = -dir.z;
        // Translation component
        view.at(0, 3) = -Dot(right, cam_pos);
        view.at(1, 3) = -Dot(up, cam_pos);
        view.at(2, 3) = -Dot(dir, cam_pos);

        view.at(3, 3) = 1.0f;

        return view;
    }
    */

    Mat<float> Identity()
    {
        Mat<float> identity_mat(4, 4, 1);

        identity_mat.at(0, 0) = 1.0f;
        identity_mat.at(1, 1) = 1.0f;
        identity_mat.at(2, 2) = 1.0f;
        identity_mat.at(3, 3) = 1.0f;

        return identity_mat;
    }
}

// https://docs.opencv.org/3.4/de/d25/imgproc_color_conversions.html
// https://www.easyrgb.com/en/math.php
//  For RGB
float gamma_correctLab(double c)
{
    if (c <= Gamma_C_V)
    {
        return c / Gamma_C_D;
    }
    else
    {
        return std::pow((c + 0.055) / 1.055, 2.4);
    }
}

// For XYZ
float functiontt(float c, float a, float b)
{
    if (c <= 0.008856)
    {
        return a * c + b;
    }
    else
    {
        return std::pow(c, 1 / 3.f);
    }
}
