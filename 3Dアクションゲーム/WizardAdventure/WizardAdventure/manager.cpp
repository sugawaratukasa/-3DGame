//******************************************************************************
// マネージャー処理 [manager.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "debug_proc.h"
#include "mode.h"
#include "game.h"
#include "particle.h"
#include "player.h"
#include "block.h"
#include "frame.h"
#include "floor.h"
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
CRenderer *CSceneManager::m_pRenderer = NULL;
CCamera *CSceneManager::m_pCamera = NULL;
CLight *CSceneManager::m_pLight = NULL;
CInputKeyboard *CSceneManager::m_pKeyboard = NULL;
CInputJoystick *CSceneManager::m_pJoystick = NULL;
CDebugProc *CSceneManager::m_pDebugProc = NULL;
CMode *CSceneManager::m_pMode = NULL;

//******************************************************************************
//コンストラクタ
//******************************************************************************
CSceneManager::CSceneManager()
{

}

//******************************************************************************
//デストラクタ
//******************************************************************************
CSceneManager::~CSceneManager()
{

}

//******************************************************************************
//初期化処理
//******************************************************************************
HRESULT CSceneManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{

	//クラス生成と初期化	
	//レンダラー
	if (m_pRenderer == NULL)
	{
		// メモリ確保
		m_pRenderer = new CRenderer;
		if (m_pRenderer != NULL)
		{
			// 初期化
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	// キーボード
	if (m_pKeyboard == NULL)
	{
		// メモリ確保
		m_pKeyboard = new CInputKeyboard;
		if (m_pKeyboard != NULL)
		{
			// 初期化
			m_pKeyboard->Init(hInstance, hWnd);
		}
	}
	// コントローラー
	if (m_pJoystick == NULL)
	{
		// メモリ確保
		m_pJoystick = new CInputJoystick;
		if (m_pJoystick != NULL)
		{
			// 初期化
			m_pJoystick->Init(hInstance, hWnd);
		}
	}
	// デバッグ
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = new CDebugProc;
		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}
	//テクスチャの読み込み
	LoadAll();

	// モード設定
	SetMode(MODE_GAME);
	return S_OK;
}

//******************************************************************************
//終了処理
//******************************************************************************
void CSceneManager::Uninit(void)
{
	CScene::ReleaseAll();
	//テクスチャの破棄
	UnloadAll();
	// モードの終了
	if (m_pMode != NULL)
	{
		//その時のモード終了
		m_pMode->Uninit();
	}
	// デバッグ
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
	//キーボードの破棄
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	//コントローラーの破棄
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = NULL;
	}
	//ライトの終了
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	//カメラの終了
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//レンダラーの終了
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//******************************************************************************
// 更新処理
//******************************************************************************
void CSceneManager::Update(void)
{
	if (m_pRenderer != NULL)
	{
		//レンダラーの更新処理
		m_pRenderer->Update();
	}
	if (m_pCamera != NULL)
	{
		//カメラのの更新処理
		m_pCamera->Update();
	}
	if (m_pMode != NULL)
	{
		// その時のモードの描画処理
		m_pMode->Update();
	}
	//キーボードの更新
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	//キーボードの更新
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Update();
	}
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CSceneManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//描画処理
		m_pRenderer->Draw();
	}

	if (m_pMode != NULL)
	{
		// その時のモードの描画処理
		m_pMode->Draw();
	}
}

//******************************************************************************
// テクスチャの読み込みまとめ
//******************************************************************************
void CSceneManager::LoadAll(void)
{
	// テクスチャ読み込み
	CParticle::Load();

	// プレイヤーモデル読み込み
	CPlayer::Load();

	// フレーム
	CFrame::Load();

	// ブロック
	CBlock::Load();

	// 床
	CFloor::Load();
}

//******************************************************************************
// テクスチャの破棄まとめ
//******************************************************************************
void CSceneManager::UnloadAll(void)
{
	// 床
	CFloor::Unload();

	// ブロック
	CBlock::Unload();

	// フレーム
	CFrame::Unload();

	// プレイヤーモデル破棄
	CPlayer::Unload();

	// テクスチャ破棄
	CParticle::Unload();
}

//******************************************************************************
// カメラの生成
//******************************************************************************
void CSceneManager::CreateCamera(void)
{
	if (m_pCamera == NULL)
	{
		// ポインタの動的確保
		m_pCamera = new CCamera;
		if (m_pCamera != NULL)
		{
			// 初期化
			m_pCamera->Init();
		}
	}
}

//******************************************************************************
// ライトの生成
//******************************************************************************
void CSceneManager::CreateLight(void)
{
	if (m_pLight == NULL)
	{
		// ポインタの動的確保
		m_pLight = new CLight;
		if (m_pLight != NULL)
		{
			// 初期化
			m_pLight->Init();
		}
	}
}
//******************************************************************************
// モードの設定
//******************************************************************************
void CSceneManager::SetMode(MODE mode)
{
	if (m_pMode != NULL)
	{
		// その時のモードの終了処理
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	if (m_pMode == NULL)
	{
		// 代入
		m_Mode = mode;

		switch (m_Mode)
		{
		case MODE_GAME:
			// ツールの生成
			m_pMode = new CGame;

			// ツールの初期化処理
			m_pMode->Init();

			break;

		default:
			return;
			break;
		}
	}
}