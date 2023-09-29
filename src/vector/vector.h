#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <SFML/Graphics/Color.hpp>

#include <cmath>

#include "../generals_func/generals.h"
#include "../log_info/log_errors.h"

class Vector 
{
    public:
    
        Vector (const double x, const double y, const double z = 0.0): x_(x), y_(y), z_(z) {}
        Vector (): x_(0.0), y_(0.0), z_(0.0) {}

        Vector (const Vector &src): x_(src.x_), y_(src.y_), z_(src.z_) {} 

        ~Vector ()
        {
            x_ = NAN;
            y_ = NAN;
            z_ = NAN;
        }

        double GetX() const { return x_; }
        double GetY() const { return y_; }
        double GetZ() const { return z_; }

        void SetX(const double x) { x_ = x; return;}
        void SetY(const double y) { y_ = y; return;}
        void SetZ(const double z) { z_ = z; return;}

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


    private:     
        double x_;
        double y_;
        double z_;
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