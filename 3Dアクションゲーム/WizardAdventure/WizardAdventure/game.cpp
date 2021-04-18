//******************************************************************************
// ツール [game.cpp]
// Author : 管原　
//******************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "renderer.h"
#include "time.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "game.h"
#include "debug_proc.h"
#include "sphere_particle_emitter.h"
#include "player.h"
#include "block.h"
#include "wood_block.h"
#include "frame.h"
#include "map.h"
#include "floor_block.h"
#include "particle_emitter.h"
#include "particle_effect.h"
#include "bg.h"
#include "ghost.h"
#include "life_gage.h"
#include "pause.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_POS		(D3DXVECTOR3(100.0f, 0.0f, -200.0f))
#define PLAYER_ROT		(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))
#define PLAYER_SIZE		(D3DXVECTOR3(30.0f,15.0f,30.0f))
#define ENEMY_POS		(D3DXVECTOR3(-100.0f,-45.0f,-200.0f))
#define ENEMY_POS2		(D3DXVECTOR3(0.0f,-45.0f,-200.0f))
#define TEST_POS		(D3DXVECTOR3(-150.0f, -70.0f, -200.0f))
#define TEST_ROT		(D3DXVECTOR3(0.0f,0.0,0.0))
#define TEST_SIZE		(D3DXVECTOR3(30.0f,30.0f, 30.0f))
#define TEST_COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TEST_POS2		(D3DXVECTOR3(-50.0f, -50.0f, -200.0f))
#define TEST_ROT2		(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE2		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_POS3		(D3DXVECTOR3(-100.0f, -50.0f, -200.0f))
#define TEST_ROT3		(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE3		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_COLOR2		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define POS				(D3DXVECTOR3(-30.0f, 0.0f, -200.0f))
#define ROT				(D3DXVECTOR3(0.0f,90.0f,0.0f))
#define SIZE			(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define COLOR			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define CREATE_COUNT	(60)
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CGame::CGame()
{
	m_nCount = INIT_INT;
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

	// マップ生成
	CMap::Create();

	// プレイヤー生成
	CPlayer::Create(PLAYER_POS, PLAYER_ROT, PLAYER_SIZE);

	// プレイヤー生成
	CGhost::Create(ENEMY_POS, PLAYER_SIZE, CGhost::TYPE_FIRE);

	// プレイヤー生成
	CGhost::Create(ENEMY_POS2, PLAYER_SIZE, CGhost::TYPE_ICE);

	// 背景生成
	CBg::Create();

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
	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();
	// NULLでない場合
	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// NULLでない場合
	if (g_lpDIDevice != NULL)
	{
		// STARTボタンを押した場合
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
		{
			// ポーズ生成
			CPause::Create();
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CGame::Draw(void)
{

}