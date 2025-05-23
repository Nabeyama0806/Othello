#pragma once
#include <cmath>

class Vector2
{
public:
	float x;
	float y;

	//�R���X�g���N�^
	constexpr Vector2():
		x(0),
		y(0){}

	template<typename T1, typename T2>
	constexpr Vector2(T1 x, T2 y) :
		x(static_cast<float>(x)),
		y(static_cast<float>(y)){}

	//���Z
	constexpr Vector2 operator + (const Vector2& other) const	//vector2 + Vector2
	{
		return Vector2(x + other.x, y + other.y);
	}
	constexpr Vector2& operator += (const Vector2& other)		//vector2 += Vector2
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	//���Z
	constexpr Vector2 operator - (const Vector2& other) const	//vector2 - Vector2
	{
		return Vector2(x - other.x, y - other.y);
	}
	constexpr Vector2& operator -= (const Vector2& other)		//vector2 -= Vector2
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	//��Z
	constexpr Vector2 operator * (const float& scalar) const //Vector2 * scalar
	{
		return Vector2(x * scalar, y * scalar);
	}
	constexpr friend Vector2 operator * (const float& scalar, const Vector2& v)//scalar * Vector2
	{
		return v * scalar;
	}
	constexpr Vector2& operator *= (const float& scalar)		//vector2 *= scalar
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	//���Z
	constexpr Vector2 operator / (const float& scalar) const //Vector2 / scalar
	{
		return Vector2(x / scalar, y / scalar);
	}
	constexpr Vector2& operator /= (const float& scalar)		//vector2 /= scalar
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	//��(�P��)
	constexpr Vector2 operator - () const	//-Vector2
	{
		return Vector2(-x, -y);
	}

	//����
	constexpr bool operator == (const Vector2& other) const	//Vector2 == Vector2
	{
		return (x == other.x) && (y == other.y);
	}

	//�񓙉�
	constexpr bool operator != (const Vector2& other) const	//Vector2 != Vector2
	{
		return !(*this == other);
	}

	//�[������(�s���S)
	constexpr bool IsZero() const
	{
		return (x == 0) && (y == 0);
	}

	//������2����擾
	constexpr float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	//�������擾
	//�������擾
	float Magnitude() const
	{
		return std::sqrtf(SqrMagnitude());
	}
};