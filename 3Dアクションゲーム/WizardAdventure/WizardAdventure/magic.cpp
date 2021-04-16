//******************************************************************************
// 魔法 [magic.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
#include "magic.h"

//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_TEXT		(1024)									// テキストの最大数
#define FIRE_BALL_TEXT	("data/Effect/FireBall_Data.txt")		// テキスト
#define ICE_BALL_TEXT	("data/Effect/IceBall_Data.txt")		// テキスト
#define REMAINDER		(0)										// 余り0
#define MAX_LIFE		(150)									// ライフの最大数
#define MIN_LIFE		(0)										// ライフの最小数
#define MOVE_VALUE		(2.5f)									// 移動量
//******************************************************************************
// コンストラクタ
//******************************************************************************
CMagic::CMagic()
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nCount		= INIT_INT;
	m_nCreateCount	= INIT_INT;
	m_nLife			= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CMagic::~CMagic()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CMagic * CMagic::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	// CMagicのポインタ
	CMagic *pMagic;

	// メモリ確保
	pMagic = new CMagic;

	// 位置代入
	pMagic->m_pos = pos;

	// 移動量代入
	pMagic->m_move = move;

	// 位置代入
	pMagic->m_Type = type;

	// 初期化
	pMagic->Init();

	// ポインタを返す
	return pMagic;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CMagic::Init(void)
{
	// ライフ設定
	m_nLife = MAX_LIFE;

	// タイプ
	switch (m_Type)
	{
		// 火玉
	case TYPE_FIRE_BALL:
		// テキストファイル読み込み
		sprintf(m_cText, FIRE_BALL_TEXT);
		break;
		// 氷玉
	case TYPE_ICE_BALL:
		// テキストファイル読み込み
		sprintf(m_cText, ICE_BALL_TEXT);
		break;

	}

	// 読み込み
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CMagic::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CMagic::Update(void)
{
	// インクリメント
	m_nCount++;

	// デクリメント
	m_nLife--;

	// 余りが0の場合
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		CParticle::Create(m_pos, m_cText);
	}
	// ライフが0以下になったら
	if (m_nLife <= MIN_LIFE)
	{
		// 終了
		Uninit();
		return;
	}

	// 移動
	m_pos += m_move;
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CMagic::Draw(void)
{
}
//******************************************************************************
// 読み込み関数
//******************************************************************************
void CMagic::Load(const char * cText)
{
	// 読み込み用
	char cReedText[MAX_TEXT];

	// 文字の判別用
	char cHeadText[MAX_TEXT];

	// 使わない文字
	char cDie[MAX_TEXT];

	// ファイルポインタ
	FILE *pFile = NULL;

	// NULLの場合
	if (pFile == NULL)
	{
		//ファイルを開く
		pFile = fopen(cText, "r");

		// NULLでない場合
		if (pFile != NULL)
		{
			// SCRIPTの文字が見つかるまで
			while (strcmp(cHeadText, "SCRIPT") != INIT_INT)
			{
				// テキストからcReedText分文字を読み込む
				fgets(cReedText, sizeof(cReedText), pFile);

				// 読み込んだ文字ををcHeadTextに格納
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadTextがSCRIPTだったら
			if (strcmp(cHeadText, "SCRIPT") == INIT_INT)
			{
				// END_SCRIPTの文字が見つかるまで
				while (strcmp(cHeadText, "END_SCRIPT") != INIT_INT)
				{
					// テキストからcReedText分文字を読み込む
					fgets(cReedText, sizeof(cReedText), pFile);

					// 読み込んだ文字ををcHeadTextに格納
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadTextがMOTIONSETだったら
					if (strcmp(cHeadText, "SETTINGS") == INIT_INT)
					{
						// END_MOTIONSETの文字が見つかるまで
						while (strcmp(cHeadText, "END_SETTINGS") != INIT_INT)
						{
							// テキストからcReedText分文字を読み込む
							fgets(cReedText, sizeof(cReedText), pFile);

							// 読み込んだ文字ををcHeadTextに格納
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadTextがALPHA_BLENDの場合
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// 情報をm_bAlpha_Blendに格納
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
						}
					}
				}
				// ファイルを閉じる
				fclose(pFile);
			}
			// 開けなかったら
			else
			{
				printf("ファイルを開く事が出来ませんでした。\n");
			}
		}
	}
}