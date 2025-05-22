#pragma once
#include "Vector2.h"

class Transform
{
public:
	Vector2 position;	//���W
	float angle;		//�p�x(���W�A��)
	float scale;		//�g�k

	Transform() :
		angle(0),
		scale(1) {}
};