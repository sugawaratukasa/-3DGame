//=============================================================================
//
// ツール [tool.cpp]
// Author : 管原　司
//
//=============================================================================

//*****************************************************************************
//インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "time.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "game.h"
#include "debug_proc.h"
#include "sphere_particle_emitter.h"

//*****************************************************************************
//静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame()
{

}

//*****************************************************************************
//デストラクタ
//*****************************************************************************
CGame::~CGame()
{
}

//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CGame::Init(void)
{
	// カメラ
	CManager::CreateCamera();

	// ライト
	CManager::CreateLight();

	// デバッグプロシージャ
	CDebugProc::Print("%s%d", "座標:", 500);

	// 球のパーティクル生成
	CSphere_Particle_Emitter::Create(D3DXVECTOR3(-90.0f, 0.0f, -150.0f));
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CGame::Uninit(void)
{

}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CGame::Update(void)
{

}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CGame::Draw(void)
{

}