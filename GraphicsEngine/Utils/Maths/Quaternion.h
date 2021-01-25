#ifndef _QUATERNION_H_
#define _QUATERNION_H_
#include <float.h>
#include <math.h>
#include <sstream>

#include "Vector3D.h"


#include <iostream>
#include <vector>
#include <iterator>

struct Quaternion
{
    double r; //real

    double i; //x
    double j; //y
    double k; //z

    Quaternion() : r(0), i(0), j(0), k(0) 
    {

    }

    Quaternion(double _r, double _i, double _j, double _k) :  r(_r), i(_i), j(_j), k(_k)
    {

    }

	char* ToString()
	{
		std::stringstream ss = std::stringstream();
        ss << r << ' ' << i << ' ' << j << ' ' << k;
		const std::string& tmp = ss.str();
		char* chara = new char[tmp.length() + 1];
		tmp.copy(chara, tmp.length());
		chara[tmp.length()] = '\0';
        return chara;
	}

	void Parse(char* string)
	{
		std::stringstream ss = std::stringstream(string);
		char* current;

		ss >> r;
		ss >> i;
		ss >> j;
		ss >> k;
	}

    void Normalise()
    {
        double d = r*r + i*i + j*j + k*k;

        if(d < FLT_EPSILON)
        {
            r = 1;
            return;
        }

        d = 1.0 / sqrt(d);
        r *= d;
        i *= d;
        j *= d;
        k *= d;
    }

    void operator *=(const Quaternion &multiplier)
	{
		Quaternion q = *this;
		r = q.r*multiplier.r - q.i*multiplier.i -
			q.j*multiplier.j - q.k*multiplier.k;
		i = q.r*multiplier.i + q.i*multiplier.r +
			q.j*multiplier.k - q.k*multiplier.j;
		j = q.r*multiplier.j + q.j*multiplier.r +
			q.k*multiplier.i - q.i*multiplier.k;
		k = q.r*multiplier.k + q.k*multiplier.r +
			q.i*multiplier.j - q.j*multiplier.i;
	}

    bool operator ==(const Quaternion &rhs)
	{
		return !(*this != rhs);
	}

    bool operator !=(const Quaternion &rhs)
	{
		return (this->r != rhs.r || this->i != rhs.i || this->j != rhs.j || this->k != rhs.k);
	}

    void addScaledVector(const Vector3& vector, float scale)
	{
		Quaternion q(0,
			vector.x * scale,
			vector.y * scale,
			vector.z * scale);
		q *= *this;
		r += q.r * 0.5f;
		i += q.i * 0.5f;
		j += q.j * 0.5f;
		k += q.k * 0.5f;
	}

    void rotateByVector(const Vector3& vector)
	{
		Quaternion q(0, vector.x, vector.y, vector.z);
		(*this) *= q;
	}
};

#include <DirectXMath.h>

static inline void CalculateTransformMatrixColumnMajor(DirectX::XMMATRIX &transformMatrix,
    const DirectX::XMFLOAT3 &position,
	const Quaternion &orientation)
{
	transformMatrix.r[0] = DirectX::XMVectorSetX(transformMatrix.r[0], (float)(1 - 2 * orientation.j*orientation.j - 2 * orientation.k*orientation.k));
	transformMatrix.r[0] = DirectX::XMVectorSetY(transformMatrix.r[0], (float)(2 * orientation.i*orientation.j -	2 * orientation.r*orientation.k));
	transformMatrix.r[0] = DirectX::XMVectorSetZ(transformMatrix.r[0], (float)(2 * orientation.i*orientation.k +	2 * orientation.r*orientation.j));
	transformMatrix.r[0] = DirectX::XMVectorSetW(transformMatrix.r[0], 0.0f);

	transformMatrix.r[1] = DirectX::XMVectorSetX(transformMatrix.r[1], (float)(2 * orientation.i*orientation.j +	2 * orientation.r*orientation.k));
	transformMatrix.r[1] = DirectX::XMVectorSetY(transformMatrix.r[1], (float)(1 - 2 * orientation.i*orientation.i -	2 * orientation.k*orientation.k));
	transformMatrix.r[1] = DirectX::XMVectorSetZ(transformMatrix.r[1], (float)(2 * orientation.j*orientation.k -	2 * orientation.r*orientation.i));
	transformMatrix.r[1] = DirectX::XMVectorSetW(transformMatrix.r[1], 0.0f);

	transformMatrix.r[2] = DirectX::XMVectorSetX(transformMatrix.r[2], (float)(2 * orientation.i*orientation.k -	2 * orientation.r*orientation.j));
	transformMatrix.r[2] = DirectX::XMVectorSetY(transformMatrix.r[2], (float)(2 * orientation.j*orientation.k +	2 * orientation.r*orientation.i));
	transformMatrix.r[2] = DirectX::XMVectorSetZ(transformMatrix.r[2], (float)(1 - 2 * orientation.i*orientation.i -	2 * orientation.j*orientation.j));
	transformMatrix.r[2] = DirectX::XMVectorSetW(transformMatrix.r[2], 0.0f);

	transformMatrix.r[3] = DirectX::XMVectorSetX(transformMatrix.r[3], (float)(position.x));
	transformMatrix.r[3] = DirectX::XMVectorSetY(transformMatrix.r[3], (float)(position.y));
	transformMatrix.r[3] = DirectX::XMVectorSetZ(transformMatrix.r[3], (float)(position.z));
	transformMatrix.r[3] = DirectX::XMVectorSetW(transformMatrix.r[3], 1.0f);
}

static inline void CalculateTransformMatrixRowMajor(DirectX::XMMATRIX &transformMatrix,
	const DirectX::XMFLOAT3 &position,
	const Quaternion &orientation)
{

	CalculateTransformMatrixColumnMajor(transformMatrix, position, orientation);
	transformMatrix = DirectX::XMMatrixTranspose(transformMatrix);
}

static inline void CalculateRotationMatrix(DirectX::XMMATRIX &transformMatrix,
	const Quaternion &orientation)
{
	transformMatrix.r[0] = DirectX::XMVectorSetX(transformMatrix.r[0], 1 - 2 * orientation.j*orientation.j - 2 * orientation.k*orientation.k);
	transformMatrix.r[0] = DirectX::XMVectorSetY(transformMatrix.r[0], 2 * orientation.i*orientation.j - 2 * orientation.r*orientation.k);
	transformMatrix.r[0] = DirectX::XMVectorSetZ(transformMatrix.r[0], 2 * orientation.i*orientation.k + 2 * orientation.r*orientation.j);
	transformMatrix.r[0] = DirectX::XMVectorSetW(transformMatrix.r[0], 0.0f);
	transformMatrix.r[1] = DirectX::XMVectorSetX(transformMatrix.r[1], 2 * orientation.i*orientation.j + 2 * orientation.r*orientation.k);
	transformMatrix.r[1] = DirectX::XMVectorSetY(transformMatrix.r[1], 1 - 2 * orientation.i*orientation.i - 2 * orientation.k*orientation.k);
	transformMatrix.r[1] = DirectX::XMVectorSetZ(transformMatrix.r[1], 2 * orientation.j*orientation.k - 2 * orientation.r*orientation.i);
	transformMatrix.r[1] = DirectX::XMVectorSetW(transformMatrix.r[1], 0.0f);
	transformMatrix.r[2] = DirectX::XMVectorSetX(transformMatrix.r[2], 2 * orientation.i*orientation.k - 2 * orientation.r*orientation.j);
	transformMatrix.r[2] = DirectX::XMVectorSetY(transformMatrix.r[2], 2 * orientation.j*orientation.k + 2 * orientation.r*orientation.i);
	transformMatrix.r[2] = DirectX::XMVectorSetZ(transformMatrix.r[2], 1 - 2 * orientation.i*orientation.i - 2 * orientation.j*orientation.j);
	transformMatrix.r[2] = DirectX::XMVectorSetW(transformMatrix.r[2], 0.0f);
	transformMatrix.r[3] = DirectX::XMVectorSetX(transformMatrix.r[3], 0.0f);
	transformMatrix.r[3] = DirectX::XMVectorSetY(transformMatrix.r[3], 0.0f);
	transformMatrix.r[3] = DirectX::XMVectorSetZ(transformMatrix.r[3], 0.0f);
	transformMatrix.r[3] = DirectX::XMVectorSetW(transformMatrix.r[3], 1.0f);

	transformMatrix = DirectX::XMMatrixTranspose(transformMatrix);
}


/**
* Inline function that creates a quaternion from
* a eular angle. eular should
*/
/***************************************************************************************
*    Title: Conversion between quaternions and Euler angles
*    Author: wikipedia
*    Date: 01/05/2019
*    Code version: 1.0
*    Availability: https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
*
***************************************************************************************/
static inline void CalculateQuaternionAngle(Quaternion &result,
	const Vector3 &degreesRotation)
{

	Vector3 radiansRotation = degreesRotation * (DirectX::XM_PI / 180.0f);

	double cosX = cos(radiansRotation.x * 0.5);
	double sinX = sin(radiansRotation.x * 0.5);

	double cosY = cos(radiansRotation.y * 0.5);
	double sinY = sin(radiansRotation.y * 0.5);

	double cosZ = cos(radiansRotation.z * 0.5);
	double sinZ = sin(radiansRotation.z * 0.5);



	result.r = cosZ * cosY * cosX + sinZ * sinY * sinX;
	result.i = cosZ * cosY * sinX - sinZ * sinY * cosX;
	result.j = sinZ * cosY * sinX + cosZ * sinY * cosX;
	result.k = sinZ * cosY * cosX - cosZ * sinY * sinX;
}

static inline Quaternion Slerp(Quaternion a, Quaternion b, float t)
{
	Quaternion lerpedQuaternion;

	double coshalfTheta = a.r * b.r + a.i * b.i + a.j * b.j + a.k * b.k;

	if(abs(coshalfTheta) >= 1)
	{
		lerpedQuaternion.r = a.r;
		lerpedQuaternion.i = a.i;
		lerpedQuaternion.j = a.j;
		lerpedQuaternion.k = a.k;

		return lerpedQuaternion;
	}

	double halfTheta = acos(coshalfTheta);
	double sinHalfTheta = sqrt(1.0f - coshalfTheta * halfTheta);

	if(fabs(sinHalfTheta) < 0.001)
	{
		lerpedQuaternion.r = (a.r * 0.5 + b.r * 0.5);
		lerpedQuaternion.i = (a.i * 0.5 + b.i * 0.5);
		lerpedQuaternion.j = (a.j * 0.5 + b.j * 0.5);
		lerpedQuaternion.k = (a.k * 0.5 + b.k * 0.5);
		return lerpedQuaternion;
	}

	double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
	double ratioB = sin(t * halfTheta) / sinHalfTheta;

	lerpedQuaternion.r = (a.r * ratioA + b.r *ratioB);
	lerpedQuaternion.i = (a.i * ratioA + b.i *ratioB);
	lerpedQuaternion.j = (a.j * ratioA + b.j *ratioB);
	lerpedQuaternion.k = (a.k * ratioA + b.k *ratioB);


	return lerpedQuaternion;
}

#endif //!_QUATERNION_H_   