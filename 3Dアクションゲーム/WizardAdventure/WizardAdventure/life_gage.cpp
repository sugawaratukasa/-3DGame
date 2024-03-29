//******************************************************************************
// ライフゲージ [life_gage.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "ui_texture.h"
#include "player.h"
#include "gage_back.h"
#include "life_gage.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SIZE		(D3DXVECTOR3(500.0f, 30.0f, 0.0f))					// サイズ
#define SIZE_BACK	(D3DXVECTOR3(500.0f * 1.01f, 30.0f * 1.15f, 0.0f))	// ゲージの背景サイズ
#define COL			(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))					// 色
//******************************************************************************
// コンストラクタ
//******************************************************************************
CLife_Gage::CLife_Gage()
{
	m_pPlayer		= NULL;
	m_nGageNum		= INIT_INT;
	m_pGage_Back	= NULL;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CLife_Gage::~CLife_Gage()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CLife_Gage * CLife_Gage::Create(D3DXVECTOR3 pos, CPlayer *pPlayer)
{
	// CLife_Gageのポインタ
	CLife_Gage *pLife_Gage = NULL;

	// NULLの場合
	if (pLife_Gage == NULL)
	{
		// メモリ確保
		pLife_Gage = new CLife_Gage;

		// NULLでない場合
		if (pLife_Gage != NULL)
		{
			// CPlayerのポインタ代入
			pLife_Gage->m_pPlayer = pPlayer;

			// ライフ取得
			pLife_Gage->m_nGageNum = pLife_Gage->m_pPlayer->GetLife();

			// 初期化
			pLife_Gage->SetGage(pos, SIZE, COL, pLife_Gage->m_nGageNum);

			// 初期化
			pLife_Gage->Init();
		}
	}
	// ポインタを返す
	return pLife_Gage;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CLife_Gage::Init(void)
{
	// 初期化
	CGage::Init();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();
	
	m_pGage_Back = CGage_Back::Create(pos, SIZE_BACK);

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CLife_Gage::Uninit(void)
{
	// 終了
	CGage::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CLife_Gage::Update(void)
{
	// 更新
	CGage::Update();

	// ライフ取得
	int nLife = m_pPlayer->GetLife();

	// ライフ設定
	SetGageNum(nLife);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CLife_Gage::Draw(void)
{
	// 描画
	CGage::Draw();
}