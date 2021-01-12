//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 管原　司
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "keyboard.h"
#include "debug_proc.h"
#include "mode.h"
#include "game.h"
#include "particle.h"

//=============================================================================
//スタティック変数初期化
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CInputKeyboard *CManager::m_pKeyboard = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CMode *CManager::m_pMode = NULL;

//=============================================================================
//コンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
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

//=============================================================================
//終了処理
//=============================================================================
void CManager::Uninit(void)
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

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{

	if (m_pRenderer != NULL)
	{
#ifdef _DEBUG
		// FPSのセット
		m_pRenderer->SetNumFPS(m_nCountFPS);
#endif
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
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
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

//=============================================================================
// テクスチャの読み込みまとめ
//=============================================================================
void CManager::LoadAll(void)
{
	// テクスチャ読み込み
	CParticle::Load();
}

//=============================================================================
// テクスチャの破棄まとめ
//=============================================================================
void CManager::UnloadAll(void)
{
	// テクスチャ破棄
	CParticle::Unload();
}

//=============================================================================
// カメラの生成
//=============================================================================
void CManager::CreateCamera(void)
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

//=============================================================================
// ライトの生成
//=============================================================================
void CManager::CreateLight(void)
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
//---------------------------------------------------------------
// モードの設定
//---------------------------------------------------------------
void CManager::SetMode(MODE mode)
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