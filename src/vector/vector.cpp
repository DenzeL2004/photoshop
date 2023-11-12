#include "vector.h"

//=======================================================================

double Vec2d::length2() const
{
    return x * x + y * y; 
}

double Vec2d::length() const 
{
    return sqrt(this->length2());
}


//=======================================================================

double dot(const Vec2d &lhs, const Vec2d &rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

double cross(const Vec2d &lhs, const Vec2d &rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

Vec2d normalize(const Vec2d &src)
{
    double len = src.length();
    return src / len;
}

//=======================================================================

Vec2d& Vec2d::operator = (const Vec2d &other)
{
    this->x = other.x;
    this->y = other.y;

    return *this;
}

//=======================================================================

Vec2d& Vec2d::operator += (const Vec2d &other)
{
    this->x += other.x;
    this->y += other.y;

    return *this;
}

//=======================================================================

Vec2d& Vec2d::operator -= (const Vec2d &other)
{
    this->x -= other.x;
    this->y -= other.y;

    return *this;
}

//=======================================================================

Vec2d& Vec2d::operator *= (const double scale)
{
    this->x *= scale;
    this->y *= scale;

    return *this;
}


Vec2d& Vec2d::operator *= (const Vec2d &other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

//=======================================================================

Vec2d& Vec2d::operator /= (const double scale)
{
    this->x /= scale;
    this->y /= scale;

    return *this;
}


Vec2d& Vec2d::operator /= (const Vec2d &other)
{
    x /= other.x;
    y /= other.y;

    return *this;
}

//=======================================================================


Vec2d operator * (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res *= rhs;

    return res;
}


Vec2d operator / (const Vec2d &lhs, const Vec2d &rhs)
{
    Vec2d res = lhs;
    res /= rhs;

    return res;
}


//=======================================================================

Vec2d operator + (const Vec2d &vec1, const Vec2d &vec2)
{
    Vec2d res = vec1;
    res += vec2;

    return res;
}

//=======================================================================

Vec2d operator - (const Vec2d &vec1, const Vec2d &vec2)
{
    Vec2d res = vec1;
    res -= vec2;
    
    return res;
}

//=======================================================================

Vec2d operator * (const Vec2d &vec, const double scale)
{
    Vec2d res = vec;
    res *= scale;

    return res;
}

Vec2d operator * (const double scale, const Vec2d &vec)
{
    Vec2d res = vec;
    res *= scale;

    return res;
}

//=======================================================================

Vec2d operator / (const Vec2d &vec, const double scale)
{
    Vec2d res = vec;
    res /= scale;

    return res;
}



//=======================================================================

bool  Vec2d::operator == (const Vec2d &other)
{
    return  EqualityDouble(this->x, other.x) &&
            EqualityDouble(this->y, other.y);
}