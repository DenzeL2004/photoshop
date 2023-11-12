#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <SFML/Graphics/Color.hpp>

#include <cmath>

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

class Vec2d 
{
    public:

        double x;
        double y;       


        Vec2d (const double coord_x, const double coord_y): x(coord_x), y(coord_y) {}
        Vec2d (): x(0.0), y(0.0) {}

        Vec2d (const Vec2d &src): x(src.x), y(src.y){} 

        ~Vec2d ()
        {
            x = NAN;
            y = NAN;
        }

        double length2() const;
        double length()  const;

        bool operator == (const Vec2d &other);

        Vec2d& operator  = (const Vec2d &other);
        Vec2d& operator += (const Vec2d &other);
        Vec2d& operator -= (const Vec2d &other);
        Vec2d& operator *= (const double scale);
        Vec2d& operator /= (const double scale);

        Vec2d& operator *= (const Vec2d &other);
        Vec2d& operator /= (const Vec2d &other);
};

double dot(const Vec2d &lhs, const Vec2d &rhs);

Vec2d operator + (const Vec2d &vec1, const Vec2d &vec2);
Vec2d operator - (const Vec2d &vec1, const Vec2d &vec2);

Vec2d operator * (const Vec2d &vec, const double scale);
Vec2d operator * (const double scale, const Vec2d &vec);
Vec2d operator * (const Vec2d &lhs,  const Vec2d &rhs);

Vec2d operator / (const Vec2d &vec, const double scale);
Vec2d operator / (const Vec2d &lhs, const Vec2d &rhs);

using Dot = Vec2d;

//===================================================================


#endif //#endif _VECTOR_H_