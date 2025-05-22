#pragma once
#include "Node.h"
#include "Transform.h"

class UiStoneCount : public Node
{
private:
	static constexpr Vector2 FontSize = Vector2(20, 35);	//数字1文字の幅・高さ
	static constexpr int FontMargin = 5;					//数字と数字の間の余白

	int m_fontTextureId;		//数字フォント
	Transform m_transform;		//姿勢
	int m_stoneCount;			//スコアの値
	int m_drawStoneCount;		//描画用のスコア
	int m_se;					//スコア上昇時のSE

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	//コンストラクタ
	UiStoneCount(Vector2 drawPos);

	//石の数を計算
	void SetStoneCount(int count);

	//石の数を取得
	int GetStoneCount() const
	{
		return m_stoneCount;
	}
};