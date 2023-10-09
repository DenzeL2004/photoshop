#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <SFML/Graphics/Color.hpp>

#include <cmath>

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

class Vector 
{
    public:
    
        Vector (const double x, const double y, const double z = 0.0): x(x), y(y), z(z) {}
        Vector (): x(0.0), y(0.0), z(0.0) {}

        Vector (const Vector &src): x(src.x), y(src.y), z(src.z) {} 

        ~Vector ()
        {
            x = NAN;
            y = NAN;
            z = NAN;
        }

        bool operator == (const Vector &other);

        Vector& operator  = (const Vector &other);
        Vector& operator += (const Vector &other);
        Vector& operator -= (const Vector &other);
        Vector& operator *= (const double scale);
        Vector& operator /= (const double scale);

        Vector& operator *= (const Vector &other);

        Vector  Normal     () const;
        Vector  Orthogonal  () const;
        Vector  Reflection (const Vector &other) const;  
        
        double  Dot      (const Vector &vec) const;
        double  Len      () const;


        double x;
        double y;
        double z; 
        
};

Vector operator + (const Vector &vec1, const Vector &vec2);
Vector operator - (const Vector &vec1, const Vector &vec2);

Vector operator * (const Vector &vec, const double scale);
Vector operator * (const double scale, const Vector &vec);
Vector operator * (const Vector &lhs,  const Vector &rhs);


Vector operator / (const Vector &vec, const double scale);

typedef Vector Dot;

//===================================================================

const Dot Null_dot = Vector(0.0, 0.0, 0.0);

const Vector Unit_vector_x = Vector(1.0, 0.0, 0.0);
const Vector Unit_vector_y = Vector(0.0, 1.0, 0.0);
const Vector Unit_vector_z = Vector(0.0, 0.0, 1.0);

const Vector Err_vector    = Vector(NAN, NAN, NAN);


#endif //#endif _VECTOR_H_