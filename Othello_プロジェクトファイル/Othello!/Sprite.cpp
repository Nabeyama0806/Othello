#include "Sprite.h"
#include "Time.h"
#include "ImageLoader.h"
#include "Dxlib.h"

//デストラクタ
Sprite::~Sprite()
{
	Release();
}

//リソースの読み込み
void Sprite::Load()
{
	//最初の画像を覚えておくための変数
	int firstTexutre = 0;

	for (auto& pair : m_animationList)
	{
		//アニメーションデータから画像パスを取り出して読み込み
		pair.second.textureId = ImageLoader::GetInstance()->Load(pair.second.textureName);

		if (!firstTexutre)
		{
			firstTexutre = pair.second.textureId;
		}
	}

	//グリッドサイズを指定しなかった場合は、画像からサイズを取得する
	if (gridSize.IsZero())
	{
		int w, h;
		GetGraphSize(firstTexutre, &w, &h);
		gridSize = Vector2(w, h);
	}
}

//リソースの解放
void Sprite::Release()
{
	for (auto& pair : m_animationList)
	{
		ImageLoader::GetInstance()->Delete(pair.second.textureName);
	}
	m_animationList.clear();
	m_runningAnime = nullptr;
}

//更新
void Sprite::Update()
{
	//アニメーションが終了していないか
	if (IsFinishAnime()) return;

	//経過時間の加算
	m_elapsedTime += Time::GetInstance()->GetDeltaTime();

	//経過時間が総アニメーション時間を超えたらループ処理
	if (IsFinishAnime() && m_runningAnime->loopFlag)
	{
		//最初のコマに戻る
		m_elapsedTime = 0;
	}
}

//描画
void Sprite::Draw(const Transform& transform)
{
	//再生するアニメが無ければ何もしない
	if (!m_runningAnime) return;

	//描画するコマを計算
	int gridIndex;

	if (IsFinishAnime())
	{
		//アニメーションが終了していたら最後のコマ番号

		gridIndex = m_runningAnime->gridAmount - 1;
	}
	else
	{
		//経過時間に応じたコマ
		gridIndex = static_cast<int>(m_elapsedTime / GetFrameTime());
	}

	//描画(※画像の起点は中央)
	DrawRectRotaGraph(
		static_cast<int>(transform.position.x), static_cast<int>(transform.position.y),
		static_cast<int>(gridSize.x) * gridIndex, 0,	//0は高さ
		static_cast<int>(gridSize.x), static_cast<int>(gridSize.y),
		transform.scale,
		transform.angle,
		m_runningAnime->textureId,
		true,
		flipX, flipY
	);

#ifdef _DEBUG

	//グリッド枠の表示
	DrawBox(
		static_cast<int>(transform.position.x - gridSize.x * transform.scale / 2),
		static_cast<int>(transform.position.y - gridSize.y * transform.scale / 2),
		static_cast<int>(transform.position.x + gridSize.x * transform.scale / 2),
		static_cast<int>(transform.position.y + gridSize.y * transform.scale / 2),
		GetColor(255, 0, 0), false//(矩形の中を塗るかどうか)
	);
#endif 
}

//アニメーション登録
void Sprite::Register(const char* textureName)
{
	Register("-", Animation(textureName, 1, 0, false));
}

void Sprite::Register(const char* animeName, const Animation& animation)
{
	//リストに登録
	m_animationList.emplace(animeName, animation);

	//最初に登録されたアニメーションを再生中アニメーションとする
	if (!m_runningAnime)
	{
		m_runningAnime = &m_animationList.begin()->second;
	}
}

//アニメーションの再生
void Sprite::Play(const char* animeName)
{
	//指定されたアニメーションをリストから取得
	const auto& pair = m_animationList.find(animeName);

	//未登録のアニメーション名
	if (pair == m_animationList.end()) return;

	//現在再生中のアニメーションと同じ
	if (m_runningAnime == &pair->second) return;

	//アニメーションの切り替え
	m_runningAnime = &pair->second;
	m_elapsedTime = 0;
}