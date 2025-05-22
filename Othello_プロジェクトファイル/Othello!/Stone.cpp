#include "Stone.h"
#include "Screen.h"
#include "Stage.h"

const char* Stone::Texture[static_cast<int>(Color::Length)] =
{
	"stone_black2.png",
	"stone_white2.png"
};

const char* Stone::ColorName[static_cast<int>(Color::Length)] =
{
	"Black",
	"White"
};

//コンストラクタ
Stone::Stone(const Vector2& boardPos, Color color) :
	Actor("Stone",
		nullptr,
		Stage::BoardToScreen(boardPos)
	),
	m_se(0),
	m_color(color),
	m_boardPos(boardPos)
{
	//画像の登録
	m_sprite = new Sprite();
	m_transform.scale = SizeOffset;
	m_sprite->Register("Black", Animation(Texture[static_cast<int>(Color::Black)]));
	m_sprite->Register("White", Animation(Texture[static_cast<int>(Color::White)]));
	m_sprite->Play(ColorName[static_cast<int>(m_color)]);

	//BGM
	m_se = LoadSoundMem("Resource/sound/se_stone.mp3");
	ChangeVolumeSoundMem(170, m_se);
}

void Stone::Release()
{
	//リソースの解放
	Actor::Release();

	//サウンドの削除
	DeleteSoundMem(m_se);
}

//色を反転させる
void Stone::Flip()
{
	m_color = m_color == Color::White ?
		Color::Black :
		Color::White;

	m_sprite->Play(ColorName[static_cast<int>(m_color)]);

	PlaySoundMem(m_se, DX_PLAYTYPE_BACK);
}