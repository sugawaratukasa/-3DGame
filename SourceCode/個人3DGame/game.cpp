//******************************************************************************
// ツール [game.cpp]
// Author : 管原　
//******************************************************************************

//*****************************************************************************
// インクルードファイル
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
#include "test_model.h"
#include "player.h"
#include "polygon.h"
#include "polygon_test.h"
#include "frame.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_POS	(D3DXVECTOR3(-30.0f, -50.0f, -50.0f))
#define TEST_POS	(D3DXVECTOR3(-30.0f, 200.0f, -50.0f))
#define TEST_ROT	(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0))
#define TEST_SIZE	(D3DXVECTOR3(500.0f,500.0f, 500.0f))
#define TEST_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TEST_POS2	(D3DXVECTOR3(50.0f, 0.0f, -50.0f))
#define TEST_ROT2	(D3DXVECTOR3(0.0f,0.0f,0.0f))
#define TEST_SIZE2	(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_COLOR2	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define POS			(D3DXVECTOR3(-30.0f, 0.0f, -50.0f))
#define ROT			(D3DXVECTOR3(0.0f,90.0f,0.0f))
#define SIZE		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define COLOR		(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
//*****************************************************************************
// 静的メンバ変数
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
	CSceneManager::CreateCamera();

	// ライト
	CSceneManager::CreateLight();

	// デバッグプロシージャ
	CDebugProc::Print("%s%d", "座標:", 500);

	// 球のパーティクル生成
	//CSphere_Particle_Emitter::Create(D3DXVECTOR3(-90.0f, 0.0f, -150.0f));

	// プレイヤー生成
	CPlayer::Create(PLAYER_POS, D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE));

	// ポリゴン生成
	CPolygon_Test::Create(TEST_POS, TEST_ROT, TEST_SIZE, TEST_COLOR);

	//モデル
	//CTestModel::Create(POS, ROT, SIZE);

	// ポリゴン生成
	//CPolygon_Test::Create(TEST_POS2, TEST_ROT2, TEST_SIZE2, TEST_COLOR2);

	// ポリゴン生成
	//CPolygon::Create(POS, ROT, SIZE, COLOR);

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