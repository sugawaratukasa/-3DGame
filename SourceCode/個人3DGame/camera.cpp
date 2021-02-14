//******************************************************************************
// カメラ [camera.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "keyboard.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define VECU_VALUE		(D3DXVECTOR3(0.0f,1.0f,0.0f))	// vecu値
#define ROT_VALUE		(D3DXToRadian(1.0f))			// カメラの球面座標の移動
#define PHI_VALUE		(1.0f)							// phi値
#define THETA_VALUE		(1.7f)							// theta値
#define DISTANCE_VALUE	(40.0f)							// 距離
#define FOV_VALUE		(D3DXToRadian(90))				// 視野角
#define DRAW_DISTANCE	(10000)							// 描画距離
//******************************************************************************
// コンストラクタ
//******************************************************************************
CCamera::CCamera()
{
	posV		= INIT_D3DXVECTOR3;
	posR		= INIT_D3DXVECTOR3;
	vecU		= INIT_D3DXVECTOR3;
	m_fPhi		= INIT_FLOAT;
	m_fTheta	= INIT_FLOAT;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
}

//******************************************************************************
// デクリメント
//******************************************************************************
CCamera::~CCamera()
{

}

//******************************************************************************
// 初期化処理
//******************************************************************************
void CCamera::Init(void)
{
	posV		= INIT_D3DXVECTOR3;
	posR		= INIT_D3DXVECTOR3;
	vecU		= VECU_VALUE;
	m_fPhi		= PHI_VALUE;
	m_fTheta	= THETA_VALUE;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
}

//******************************************************************************
// 終了処理
//******************************************************************************
void CCamera::Uninit(void)
{

}

//******************************************************************************
// 更新処理
//******************************************************************************
void CCamera::Update(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//キーボードの取得
	CInputKeyboard *pKeyborad = CSceneManager::GetInputKeyboard();		

	// 右回転
	if (pKeyborad->GetKeyPress(DIK_D))
	{
		m_fPhi -= ROT_VALUE;
	}
	//左回転
	if (pKeyborad->GetKeyPress(DIK_A))
	{
		m_fPhi += ROT_VALUE;
	}
	//上回転
	if (pKeyborad->GetKeyPress(DIK_W))
	{
		m_fTheta -= ROT_VALUE;
	}
	//下回転
	if (pKeyborad->GetKeyPress(DIK_S))
	{
		m_fTheta += ROT_VALUE;
	}

	// 注視点
	posR.x = (sinf(m_fTheta)*cosf(m_fPhi));
	posR.y = cosf(m_fTheta);
	posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	
	// 距離
	m_fDistance = DISTANCE_VALUE;

	// 視点	
	posV.x = m_fDistance*(sinf(m_fTheta)*cosf(m_fPhi));
	posV.y = m_fDistance*cosf(m_fTheta);
	posV.z = m_fDistance*(sinf(m_fTheta)*sinf(m_fPhi));

	//======================================
	//カメラ描画
	//======================================
	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, FOV_VALUE, SCREEN_WIDTH / SCREEN_HEIGHT, 10, DRAW_DISTANCE);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}