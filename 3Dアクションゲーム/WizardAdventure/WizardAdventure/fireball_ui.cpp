//******************************************************************************
// 火玉のUI[fireball_ui.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "player.h"
#include "fireball_ui.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define POS				(D3DXVECTOR3(PlayerPos.x,PlayerPos.y + 55.0f,PlayerPos.z - 10.0f))
#define SIZE			(D3DXVECTOR3(10.0f,10.0f,0.0f))				// サイズ
#define COL				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))			// 色
#define SUBCOLOR		(-0.05f)									// α値減算
#define MIN_COLOR		(0.0f)										// 色の最小値
#define PLAYER_POS_Y	(15.0f)										// y座標
#define PLAYER_POS_Z	(-15.0f)									// z座標
#define ROT				(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(330.0f)))// 向き
//******************************************************************************
// コンストラクタ
//******************************************************************************
CFireBall_UI::CFireBall_UI(int nPriority) : CBillboard_UI(nPriority)
{
}
//******************************************************************************
// コンストラクタ
//******************************************************************************
CFireBall_UI::~CFireBall_UI()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CFireBall_UI * CFireBall_UI::Create(D3DXVECTOR3 pos)
{
	// CFireBall_UIのポインタ
	CFireBall_UI *pFireBall_UI = NULL;

	// NULLの場合
	if (pFireBall_UI == NULL)
	{
		// メモリ確保
		pFireBall_UI = new CFireBall_UI;

		// NULLでない場合
		if (pFireBall_UI != NULL)
		{
			// 情報設定
			pFireBall_UI->SetBillboard(pos, ROT, SIZE, COL, CBillboard_UI::TEX_TYPE_FIREBALL);

			// 初期化
			pFireBall_UI->Init();
		}
	}
	// ポインタを返す
	return pFireBall_UI;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CFireBall_UI::Init(void)
{
	// 初期化
	CBillboard_UI::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CFireBall_UI::Uninit(void)
{
	// 終了
	CBillboard_UI::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CFireBall_UI::Update(void)
{
	// 更新
	CBillboard_UI::Update();

	// 位置取得
	D3DXVECTOR3 pos = GetPosition();

	// 色取得
	D3DXCOLOR col = GetColor();

	// 色減算
	col.a += SUBCOLOR;

	// CSceneのポインタ
	CScene *pScene = NULL;

	// プレイヤーの位置
	D3DXVECTOR3 PlayerPos;

	// プレイヤーの位置取得
	do 
	{
		// プレイヤー取得
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = pScene->GetObjType();

			// オブジェクトタイプがプレイヤーの場合
			if (objtype == OBJTYPE_PLAYER)
			{
				// 位置取得
				PlayerPos = ((CPlayer*)pScene)->GetPos();

				// 代入
				pos = POS;

				// 位置設定
				SetPosition(pos);
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);

	// 色設定
	SetColor(col);

	

	// 0.0f以下の場合
	if (col.a <= MIN_COLOR)
	{
		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CFireBall_UI::Draw(void)
{
	// 描画
	CBillboard_UI::Draw();
}