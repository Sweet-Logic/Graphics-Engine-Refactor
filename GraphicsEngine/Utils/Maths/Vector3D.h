#ifndef _VECTOR_3D_H_
#define _VECTOR_3D_H_

#include <cmath>
#include "MathsUtils.h"
#include <sstream>


#define APROXIMATION 0.00001f

struct Vector3;

static bool operator==(const Vector3& left, const Vector3& right);
static Vector3 operator*(const int& left, const Vector3& right);
static Vector3 operator*(const float& left, const Vector3& right);
static Vector3 operator*(const double& left, const Vector3& right);
static Vector3 operator*(const Vector3& right, const int& left);
static Vector3 operator*(const Vector3& right, const float& left);
static Vector3 operator*(const Vector3& right, const double& left);

struct Vector3{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vector3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    Vector3(float _x, float _y,float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    Vector3(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    Vector3(int _x, int _y, int _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    double const sqrMagnitude()
    {
        return (x*x) + (y*y) + (z*z);
    }

    double const Magnitude()
    {
        return pow(sqrMagnitude(), 0.5);
    }

    void const Normalise()
    {
        double mag = this->Magnitude();
        x = x/mag;
        y = y/mag;
        z = z/mag;
    }

    const char* ToString()
    {
        std::stringstream ss;
        ss << x << ',' << y << ',' << z;
        return (ss.str().c_str());
    }

    static Vector3 Down;
    static Vector3 Up;
    static Vector3 Forward;
    static Vector3 Back;
    static Vector3 Left;
    static Vector3 Right;
    static Vector3 Zero;

    Vector3 Vector3::operator*(const int& other)
    {
        return Vector3(this->x * other, this->y * other, this->z * other);
    }

    Vector3 Vector3::operator*(const float& other)
    {
        return Vector3(this->x * other, this->y * other, this->z * other);
    }
    
    Vector3 Vector3::operator*(const double& other)
    {
        return Vector3(this->x * other, this->y * other, this->z * other);
    }

    Vector3 Vector3::operator/(const int& other)
    {
        _ASSERT(other != 0);
        return Vector3(this->x / other, this->y / other, this->z / other);
    }

    Vector3 Vector3::operator/(const float& other)
    {
        _ASSERT(other != 0.f);
        return Vector3(this->x / other, this->y / other, this->z / other);
    }
    
    Vector3 Vector3::operator/(const double& other)
    {
        _ASSERT(other != 0.0);
        return Vector3(this->x / other, this->y / other, this->z / other);
    }
    
    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return Vector3(this->x - other.x, this->y - other.y,  this->z - other.z);
    }   

    // returns the angle in degrees 0 to 359.9
    static double Angle(Vector3 from, Vector3 to)// degrees or radians ???
    {
        if(from.sqrMagnitude() != 1)
            from.Normalise();
        if(to.sqrMagnitude() != 1)
            to.Normalise();

        return acos(Dot(from, to));
    }
    
    static double Distance(Vector3 from, Vector3 to)
    {
        return 0.0;
    }

    static double Dot(Vector3 a, Vector3 b)
    {
        return (a.x*b.x) + (a.y * b.y) + (a.z*b.z); 
    }

    static Vector3 Cross(Vector3 a, Vector3 b)
    {
        return Vector3((a.y*b.z - a.z*b.y), (a.y*b.z - a.z*b.y), (a.y*b.z - a.z*b.y));
    }

    static Vector3 LerpUnclamped (Vector3 a, Vector3 b, float t)
    {
        double xDiff = b.x - a.x;
        double yDiff = b.y - a.y;
        double zDiff = b.z - a.z;

        xDiff *= t;
        yDiff *= t;
        zDiff *= t;

        return Vector3(a.x + xDiff, a.y + yDiff, a.z + zDiff);
    }

    static Vector3 Lerp(Vector3 a, Vector3 b, float t)
    {
        // clamp t to 0 and 1
        t > 1 ? t = 1.f : t < 0 ? t = 0.0f : false;
        return LerpUnclamped(a, b, t);
    }

    static Vector3 Max(Vector3 a, Vector3 b)
    {
        return Vector3(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z));
    }

    static Vector3 Min(Vector3 a, Vector3 b)
    {
        return Vector3(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z));
    }

    static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistance)
    {
        Vector3 direction = Vector3(target.x - current.x, target.y - current.y, target.z - current.z);
        direction.Normalise();
        
        direction.x *= maxDistance;
        direction.y *= maxDistance;
        direction.z *= maxDistance;

        return current + direction;
    }

    static Vector3 Reflect(Vector3 vec, Vector3 reflectionNormal)
    {   
        reflectionNormal.Normalise();
        return (2 * reflectionNormal * Dot(reflectionNormal, vec));
    }

    static Vector3 Scale(Vector3 current, Vector3 scale)
    {
        return Vector3(current.x * scale.x, current.y * scale.y,  current.z * scale.z);
    }

};

static bool operator==(const Vector3& left, const Vector3& right)
{
	Vector3 subtracted = left - right;
	return (abs(subtracted.x) < APROXIMATION) && (abs(subtracted.y) < APROXIMATION);
}

static Vector3 operator*(const int& left, const Vector3& right)
{
	return Vector3(right.x * left, right.y * left, right.z * left);
}

static Vector3 operator*(const float& left, const Vector3& right)
{
	return Vector3(right.x * left, right.y * left, right.z * left);
}

static Vector3 operator*(const double& left, const Vector3& right)
{
	return Vector3(right.x * left, right.y * left, right.z * left);
}

static Vector3 operator*(const Vector3& right, const int& left)
{
	return Vector3(right.x * left, right.y * left, right.z * left);
}

static Vector3 operator*(const Vector3& right, const float& left)
{
	return Vector3(right.x * left, right.y * left, right.z * left);
}

static Vector3 operator*(const Vector3& right, const double& left)
{
	return Vector3(right.x * left, right.y * left, right.z * left);
}

#endif //!_VECTOR_3D_H_