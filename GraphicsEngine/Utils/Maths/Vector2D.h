#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <cmath>
#include "MathsUtils.h"

#define APROXIMATION 0.00001f

struct Vector2;

static bool operator==(const Vector2& left, const Vector2& right);
static Vector2 operator*(const int& left, const Vector2& right);
static Vector2 operator*(const float& left, const Vector2& right);
static Vector2 operator*(const double& left, const Vector2& right);

struct Vector2{
    double x = 0.0;
    double y = 0.0;

    Vector2()
    {
        x = 0.0;
        y = 0.0;
    }
    Vector2(float _x, float _y)
    {
        x = _x;
        y = _y;
    }
    Vector2(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    Vector2(int _x, int _y)
    {
        x = _x;
        y = _y;
    }

    double const sqrMagnitude()
    {
        return (x*x) + (y*y); 
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
    }

    static Vector2 Down;
    static Vector2 Up;
    static Vector2 Left;
    static Vector2 Right;
    static Vector2 Zero;

    Vector2 Vector2::operator*(const int& other)
    {
        return Vector2(this->x * other, this->y * other);
    }

    Vector2 Vector2::operator*(const float& other)
    {
        return Vector2(this->x * other, this->y * other);
    }
    
    Vector2 Vector2::operator*(const double& other)
    {
        return Vector2(this->x * other, this->y * other);
    }

    Vector2 Vector2::operator/(const int& other)
    {
        _ASSERT(other != 0);
        return Vector2(this->x / other, this->y / other);
    }

    Vector2 Vector2::operator/(const float& other)
    {
        _ASSERT(other != 0.f);
        return Vector2(this->x / other, this->y / other);
    }
    
    Vector2 Vector2::operator/(const double& other)
    {
        _ASSERT(other != 0.0);
        return Vector2(this->x / other, this->y / other);
    }
    
    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return Vector2(this->x + other.x, this->y + other.y);
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return Vector2(this->x - other.x, this->y - other.y);
    }   

    // returns the angle in degrees -179.9 to 180
    static double SignedAngle(Vector2 from, Vector2 to)
    {
        float angle = Dot(from, to); // 1 = infront -1 = behind
        Vector2 right = Perpendicular(from);
        float rightDot = Dot(right, to); // 1 = right -1 = left

        if(rightDot < 0)
        {
            float inverseAngle = 0.0 - RadiansToDegrees(acos(angle));
            return inverseAngle;
        }
        return acos(angle);
        
    }

    // returns the angle in degrees 0 to 359.9
    static double Angle(Vector2 from, Vector2 to)// degrees or radians ???
    {
        float angle = Dot(from, to); // 1 = infront -1 = behind
        Vector2 right = Perpendicular(from);
        float rightDot = Dot(right, to); // 1 = right -1 = left

        if(rightDot < 0)
        {
            float inverseAngle = 180.0 - RadiansToDegrees(acos(angle));
            return 180.0 + inverseAngle;
        }

        return acos(angle);
    }
    
    static double Distance(Vector2 from, Vector2 to)
    {
		Vector2 vec = from - to;

		return sqrt(vec.x*vec.x + vec.y*vec.y);
    }

    static double Dot(Vector2 a, Vector2 b)
    {
        return (a.x*b.x) + (a.y * b.y); 
    }

    static Vector2 LerpUnclamped (Vector2 a, Vector2 b, float t)
    {
        double xDiff = b.x - a.x;
        double yDiff = b.y - a.y;

        xDiff *= t;
        yDiff *= t;

        return Vector2(a.x + xDiff, a.y + yDiff);
    }

    static Vector2 Lerp(Vector2 a, Vector2 b, float t)
    {
        // clamp t to 0 and 1
        t > 1 ? t = 1.f : t < 0 ? t = 0.0f : false;
        return LerpUnclamped(a, b, t);
    }

    static Vector2 Max(Vector2 a, Vector2 b)
    {
        return Vector2(fmax(a.x, b.x), fmax(a.y, b.y));
    }

    static Vector2 Min(Vector2 a, Vector2 b)
    {
        return Vector2(fmin(a.x, b.x), fmin(a.y, b.y));
    }

    static Vector2 MoveTowards(Vector2 current, Vector2 target, float maxDistance)
    {
        Vector2 direction = Vector2(target.x - current.x, target.y - current.y);
        direction.Normalise();
        
        direction.x *= maxDistance;
        direction.y *= maxDistance;

        return current + direction;
    }

    static Vector2 Perpendicular(Vector2 vec)
    {
        if(vec.x != 0)
        {
            if(vec.y != 0)
            {
                int xmod = vec.x * abs(vec.x), ymod = vec.y * abs(vec.y);

                Vector2 newVec = vec;
                xmod == ymod? newVec.y *= -1 : newVec.x *= -1;

                return newVec;
            }
            return Vector2(0.0,-vec.y * abs(vec.y) );
        }
        return Vector2(-vec.x * abs(vec.x), 0.0);
    }

    static Vector2 Reflect(Vector2 vec, Vector2 reflectionNormal)
    {   
        reflectionNormal.Normalise();
        return (2 * reflectionNormal * Dot(reflectionNormal, vec));
    }

    static Vector2 Scale(Vector2 current, Vector2 scale)
    {
        return Vector2(current.x * scale.x, current.y * scale.y);
    }

};

static bool operator==(const Vector2& left, const Vector2& right)
{
	Vector2 subtracted = left - right;
	return (abs(subtracted.x) < APROXIMATION) && (abs(subtracted.y) < APROXIMATION);
}

static Vector2 operator*(const int& left, const Vector2& right)
{
	return Vector2(right.x * left, right.y * left);
}

static Vector2 operator*(const float& left, const Vector2& right)
{
	return Vector2(right.x * left, right.y * left);
}

static Vector2 operator*(const double& left, const Vector2& right)
{
	return Vector2(right.x * left, right.y * left);
}

#endif //!_VECTOR2D_H_