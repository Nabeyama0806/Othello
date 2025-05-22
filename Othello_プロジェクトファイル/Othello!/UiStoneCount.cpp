#include "UiStoneCount.h"
#include "Screen.h"
#include "ImageLoader.h"
#include "Time.h"
#include "DxLib.h"

UiStoneCount::UiStoneCount(Vector2 drawPos) :
	m_fontTextureId(0),
	m_stoneCount(2),
	m_drawStoneCount(0),
	m_se(0)
{
	m_transform.position = drawPos;
}

void UiStoneCount::Load()
{
	m_fontTextureId = ImageLoader::GetInstance()->Load("score_font.png");
	ChangeVolumeSoundMem(128, m_se);
}

void UiStoneCount::Release()
{
	ImageLoader::GetInstance()->Delete("score_font.png");
}

void UiStoneCount::Update()
{
	if (m_stoneCount != m_drawStoneCount)
	{
		//差分の5%ずつ加算(※最低でも1は増減する)
		int diff = m_stoneCount - m_drawStoneCount;
		int add = static_cast<int>(diff * 0.05f);
		m_drawStoneCount += abs(add) > 0 ? add : (diff > 0) - (diff < 0);
	}
}

void UiStoneCount::Draw()
{
	Vector2 dest = m_transform.position;
	dest.y += FontMargin;
	int count = m_drawStoneCount;
	int digit = 2;
	do
	{
		int value = count % 10; //1の位の値を取り出す

		DrawRectGraph(
			static_cast<int>(dest.x - FontSize.x * digit), static_cast<int>(dest.y),
			static_cast<int>(FontSize.x) * value, 0,
			static_cast<int>(FontSize.x), static_cast<int>(FontSize.y),
			m_fontTextureId,
			true
		);

		count /= 10;	//スコアの桁下げ
		digit++;
	} while (count > 0);
}

//スコアの更新
void UiStoneCount::SetStoneCount(int count)
{
	m_stoneCount = count;
}