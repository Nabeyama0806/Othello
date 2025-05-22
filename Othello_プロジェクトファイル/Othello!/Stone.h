#pragma once
#include "Actor.h"
#include "DxLib.h"

class Stone : public Actor
{
public:
	enum class Color
	{
		Black,
		White,

		Length,
	};

	static constexpr Vector2 Size = Vector2(46, 46);
	static constexpr float SizeOffset = 0.1f;

private:
	static const char* Texture[static_cast<int>(Color::Length)];
	static const char* ColorName[static_cast<int>(Color::Length)];

	int m_se;
	Color m_color;
	Vector2 m_boardPos;

protected:
	virtual void Release() override;

public:
	Stone(const Vector2& boardPos, Color color);

	//���g�̐F��n��
	Color GetColor() const
	{
		return m_color;
	}

	//���g�̔Ֆʍ��W��n��
	const Vector2& GetBoardPos() const
	{
		return m_boardPos;
	}

	//�F�𔽓]������
	void Flip();
};