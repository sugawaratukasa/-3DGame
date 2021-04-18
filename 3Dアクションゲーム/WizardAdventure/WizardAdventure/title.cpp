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
#include "joystick.h"
#include "2d_polygon.h"
#include "fade.h"
#include "title.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))	// 位置
#define BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f))			// サイズ
#define TITLE_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 0.0f))	// 位置
#define TITLE_SIZE			(D3DXVECTOR3(1500.0f, 750.0f, 0.0f))						// サイズ
#define PRESS_START_POS		(D3DXVECTOR3(SCREEN_WIDTH / 2, 700.0f, 0.0f))				// 位置
#define PRESS_START_SIZE	(D3DXVECTOR3(750.0f, 300.0f, 0.0f))							// サイズ
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//*****************************************************************************
//コンストラクタ
//*****************************************************************************
CTitle::CTitle()
{
}
//*****************************************************************************
//デストラクタ
//*****************************************************************************
CTitle::~CTitle()
{
}
//*****************************************************************************
//初期化処理
//*****************************************************************************
HRESULT CTitle::Init(void)
{
	// タイトルの背景
	C2D_Polygon::Create(BG_POS, BG_SIZE, C2D_Polygon::TYPE_TITLE_BG);

	// タイトル生成
	C2D_Polygon::Create(TITLE_POS, TITLE_SIZE, C2D_Polygon::TYPE_TITLE);

	// PRESS_START
	C2D_Polygon::Create(PRESS_START_POS, PRESS_START_SIZE, C2D_Polygon::TYPE_PRESS_START);
	return S_OK;
}

//*****************************************************************************
//終了処理
//*****************************************************************************
void CTitle::Uninit(void)
{
	// フェード以外破棄
	CScene::DesignationReleaseAll(CScene::OBJTYPE_FADE);
}

//*****************************************************************************
//更新処理
//*****************************************************************************
void CTitle::Update(void)
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
			// ゲームに遷移
			CFade::Create(CManager::MODE_GAME);
		}
	}
}

//*****************************************************************************
//描画処理
//*****************************************************************************
void CTitle::Draw(void)
{

}