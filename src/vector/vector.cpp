#include "vector.h"

//=======================================================================

Vector& Vector::operator = (const Vector &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;

    return *this;
}

//=======================================================================

Vector& Vector::operator += (const Vector &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

//=======================================================================

Vector& Vector::operator -= (const Vector &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

//=======================================================================

Vector& Vector::operator *= (const double scale)
{
    this->x *= scale;
    this->y *= scale;
    this->z *= scale;

    return *this;
}

//=======================================================================

Vector& Vector::operator /= (const double scale)
{
    this->x /= scale;
    this->y /= scale;
    this->z /= scale;

    return *this;
}

//=======================================================================

Vector& Vector::operator *= (const Vector &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

Vector operator * (const Vector &lhs, const Vector &rhs)
{
    Vector res = lhs;
    res *= rhs;

    return res;
}

//=======================================================================

double Vector::Len () const
{
    double len = this->Dot(*this);
    
    len = sqrt(len);

    return len;
}

//=======================================================================


Vector Vector::Normal () const
{
    Vector res(*this / this->Len());

    return res;
}


//=======================================================================

double Vector::Dot (const Vector &vec) const
{
    return  vec.x * this->x + 
            vec.y * this->y +
            vec.z * this->z;
}

//=======================================================================

Vector operator + (const Vector &vec1, const Vector &vec2)
{
    Vector res = vec1;
    res += vec2;

    return res;
}

//=======================================================================

Vector operator - (const Vector &vec1, const Vector &vec2)
{
    Vector res = vec1;
    res -= vec2;
    
    return res;
}

//=======================================================================

Vector operator * (const Vector &vec, const double scale)
{
    Vector res = vec;
    res *= scale;

    return res;
}

Vector operator * (const double scale, const Vector &vec)
{
    Vector res = vec;
    res *= scale;

    return res;
}

//=======================================================================

Vector operator / (const Vector &vec, const double scale)
{
    Vector res = vec;
    res /= scale;

    return res;
}

//=======================================================================

Vector Vector::Orthogonal () const
{
    Vector res(-this->y, this->x);
    return res;
}

//=======================================================================

Vector Vector::Reflection (const Vector &other) const
{
    Vector other_ortogonal = other.Orthogonal();
    other_ortogonal = other_ortogonal.Normal();

    Vector res = this->Dot(other_ortogonal) * 2.0 * other_ortogonal - *this;

    return res;
}

//=======================================================================

bool  Vector::operator == (const Vector &other)
{
    return  EqualityDouble(this->x, other.x) &&
            EqualityDouble(this->y, other.y) &&
            EqualityDouble(this->z, other.z);
}