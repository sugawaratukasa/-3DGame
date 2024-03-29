//******************************************************************************
// 扉 [gate.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "model.h"
#include "3d_obj.h"
#include "player.h"
#include "collision.h"
#include "button.h"
#include "sound.h"
#include "gate.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE		(D3DXVECTOR3(0.0f,2.0f,0.0f))	// 移動量
#define SIZE_DEVIDE	(3.0f)							// サイズをわる量
#define SIZE_MUT	(1.1f)							// サイズに掛ける値
//******************************************************************************
//静的メンバ変数
//******************************************************************************

//******************************************************************************
// コンストラクタ
//******************************************************************************
CGate::CGate(int nPriority) : C3D_Obj(nPriority)
{
	m_SavePos	= INIT_D3DXVECTOR3;
	m_bOpen		= false;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CGate::~CGate()
{

}
//******************************************************************************
// 生成関数
//******************************************************************************
CGate * CGate::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CGateのポインタ
	CGate *pGate = NULL;

	// NULLの場合
	if (pGate == NULL)
	{
		// メモリ確保
		pGate = new CGate;

		// NULLでない場合
		if (pGate != NULL)
		{
			// 情報設定
			pGate->SetModel(pos, rot, size, C3D_Obj::TYPE_GATE);

			// 位置保存
			pGate->m_SavePos = pos;

			// 初期化
			pGate->Init();
		}
	}
	// ポインタを返す
	return pGate;
}
//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CGate::Init(void)
{
	// 初期化
	C3D_Obj::Init();

	return S_OK;
}
//******************************************************************************
// 終了処理
//******************************************************************************
void CGate::Uninit(void)
{
	// 終了
	C3D_Obj::Uninit();
}
//******************************************************************************
// 更新処理
//******************************************************************************
void CGate::Update(void)
{
	// サウンド取得
	CSound *pSound = CManager::GetSound();

	// 更新
	C3D_Obj::Update();

	// 押されているか取得
	bool bPush = GetPush();

	// trueの場合
	if (bPush == true)
	{
		// falseの場合
		if (m_bOpen == false)
		{
			// 開く音再生
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_GATE_OPEN);

			// trueに
			m_bOpen = true;
		}
		// 移動処理
		UpMove();
	}
	// falseの場合
	if (bPush == false)
	{
		// falseの場合
		if (m_bOpen == true)
		{
			// 開く音再生
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_GATE_OPEN);

			// trueに
			m_bOpen = false;
		}
		// 移動処理
		UnderMove();
	}
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CGate::Draw(void)
{
	// 描画
	C3D_Obj::Draw();
}
//******************************************************************************
// 上移動処理
//******************************************************************************
void CGate::UpMove(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置が設置した位置以下の場合
	if (pos.y <= m_SavePos.y + size.y * SIZE_MUT)
	{
		// 移動
		pos.y += MOVE.y;
	}

	// 位置設定
	SetPos(pos);
}
//******************************************************************************
// ボタンが押されているか取得
//******************************************************************************
bool CGate::GetPush(void)
{
	// シーンのポインタ
	CScene *pScene = NULL;

	// 押されたか
	bool bPush = false;

	// プレイヤーとの当たり判定
	do
	{
		// リスト構造の先頭取得
		pScene = GetScene(OBJTYPE_BUTTON);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE Objtype = pScene->GetObjType();

			// オブジェクトタイプがプレイヤーの場合
			if (Objtype == OBJTYPE_BUTTON)
			{
				// 取得
				bPush = ((CButton*)pScene)->GetbPush();
			}
		}
		// NULLになるまで
	} while (pScene != NULL);

	// 押されているか返す
	return bPush;
}
//******************************************************************************
// 下移動処理
//******************************************************************************
void CGate::UnderMove(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置が設置した位置以上の場合
	if (pos.y >= m_SavePos.y)
	{
		// 移動
		pos.y += -MOVE.y;
	}

	// 位置設定
	SetPos(pos);
}