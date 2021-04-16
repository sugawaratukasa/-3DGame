//******************************************************************************
// 雲[bg_cloud.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "bg_cloud.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define TEX_X_1		(0.0f)		// UV値
#define TEX_X_2		(1.0f)		// UV値
#define TEX_Y_1		(0.0f)		// UV値
#define TEX_Y_2		(1.0f)		// UV値
#define MAX_TEX_1	(-1.0f)		// UV最大値
#define MAX_TEX_2	(-2.0f)		// UV最大値
#define ADDTEX		(-0.0005f)	// UV加算値
#define COL	(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
//******************************************************************************
// 静的メンバ変数初期化
//******************************************************************************

//******************************************************************************
// コンストラクタ
//******************************************************************************
CBg_Cloud::CBg_Cloud(int nPriority)
{
	m_fTex_1	= INIT_FLOAT;
	m_fTex_2	= INIT_FLOAT;
	m_fAddTex	= INIT_FLOAT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CBg_Cloud::~CBg_Cloud()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CBg_Cloud * CBg_Cloud::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBg_Cloudのポインタ
	CBg_Cloud *pCloud = NULL;

	// NULLの場合
	if (pCloud == NULL)
	{
		// メモリ確保
		pCloud = new CBg_Cloud;

		// NULLでない場合
		if (pCloud != NULL)
		{
			// 情報設定
			pCloud->SetPolygon(pos, size, C3D_Polygon::TEX_TYPE_CLOUD);

			// 初期化
			pCloud->Init();
		}
	}

	// ポインタを返す
	return pCloud;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CBg_Cloud::Init(void)
{
	// テクスチャ値
	m_fTex_1 = TEX_X_1;
	m_fTex_2 = TEX_X_2;

	// 加算値
	m_fAddTex = ADDTEX;

	// 初期化
	C3D_Polygon::Init();

	// 色設定
	SetColor(COL);
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CBg_Cloud::Uninit(void)
{
	// 終了
	C3D_Polygon::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CBg_Cloud::Update(void)
{
	// 更新
	C3D_Polygon::Update();

	// テクスチャスクロール
	// UV加算
	m_fTex_1 += m_fAddTex;
	m_fTex_2 += m_fAddTex;

	// テクスチャ設定
	SetTexture(m_fTex_1, m_fTex_2, TEX_Y_1, TEX_Y_2);

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// プレイヤーの位置
	D3DXVECTOR3 PlayerPos;

	// CSceneクラスのポインタ
	CScene *pScene = NULL;

	do
	{
		// シーン取得
		pScene = GetScene(OBJTYPE_PLAYER);
		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = GetObjType();

			// オブジェタイププレイヤーの場合
			if (objtype = OBJTYPE_PLAYER)
			{
				// プレイヤーの位置取得
				PlayerPos = ((CPlayer*)pScene)->GetPos();
			}
		}
		// NULLになるまで
	} while (pScene != NULL);

	// 位置代入
	pos.x = PlayerPos.x;

	// 位置設定
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CBg_Cloud::Draw(void)
{
	// 描画
	C3D_Polygon::Draw();
}