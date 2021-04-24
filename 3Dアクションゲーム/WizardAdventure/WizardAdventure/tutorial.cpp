//******************************************************************************
// チュートリアル [tutorial.cpp]
// Author : 管原司
//******************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "joystick.h"
#include "scene.h"
#include "renderer.h"
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "2d_particle_emitter.h"
#include "map.h"
#include "player.h"
#include "bg.h"
#include "tutorial_pause.h"
#include "tutorial.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_POS		(D3DXVECTOR3(200.0f, -50.0f, -200.0f))
#define PLAYER_ROT		(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))
#define PLAYER_SIZE		(D3DXVECTOR3(30.0f,15.0f,30.0f))
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTutorial::CTutorial()
{
	m_bPause = false;
}
//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTutorial::~CTutorial()
{
}
//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTutorial::Init(void)
{
	// カメラ
	CManager::CreateCamera();

	// ライト
	CManager::CreateLight();

	// マップ生成
	CMap::Create(CMap::TYPE_TUTORIAL);

	// プレイヤー生成
	CPlayer::Create(PLAYER_POS, PLAYER_ROT, PLAYER_SIZE);

	// 背景生成
	CBg::Create();
	
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTutorial::Uninit(void)
{
	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTutorial::Update(void)
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
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START) || pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
		{
			// falseの場合
			if (m_bPause == false)
			{
				// STARTボタンを押した場合
				if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_START))
				{
					// ポーズ生成
					CTutorial_Pause::Create();

					// trueに
					m_bPause = true;
				}
			}
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CTutorial::Draw(void)
{

}