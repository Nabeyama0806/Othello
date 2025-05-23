#include "Time.h"
#include "Input.h"
#include "DxLib.h"

//コンストラクタ
Time::Time() :
	m_prevTime(GetNowCount()),
	m_deltaTime(0)
{
}

//更新
void Time::Update()
{
	int nowTime = GetNowCount();

	//前フレームの時刻と現在時刻から経過時間を求める
	//単位をミリ秒から秒に変換
	m_deltaTime = (nowTime - m_prevTime) / 1000.0f;

	//現在時刻を覚えておく
	m_prevTime = nowTime;
}