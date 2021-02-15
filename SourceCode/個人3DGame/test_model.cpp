//******************************************************************************
// テストモデル[test_model.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "test_model.h"
#include "input.h"
#include "joystick.h"
#include "model.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(2.0f,2.0f,0.0f))	// 移動量
//******************************************************************************
//静的メンバ変数
//******************************************************************************
LPD3DXMESH CTestModel::m_pMesh = NULL;
LPD3DXBUFFER CTestModel::m_pBuffMat = NULL;
DWORD CTestModel::m_nNumMat = NULL;
char* CTestModel::m_apFileName = { "data/Model/Object/box.x" };// 箱
LPDIRECT3DTEXTURE9 CTestModel::m_pTexture[MAX_MATERIAL] = {};

//******************************************************************************
//インクリメント
//******************************************************************************
CTestModel::CTestModel(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
//デクリメント
//******************************************************************************
CTestModel::~CTestModel()
{

}

//******************************************************************************
//生成処理
//******************************************************************************
CTestModel * CTestModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CTestModel *pTest_Model;
	pTest_Model = new CTestModel;
	pTest_Model->Init();
	pTest_Model->SetBox(pos, rot, size);

	return pTest_Model;
}

//******************************************************************************
//モデルの読み込み
//******************************************************************************
HRESULT CTestModel::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);
	LoadTexture();
	return S_OK;
}
//******************************************************************************
// テクスチャの読み込み
//******************************************************************************
HRESULT CTestModel::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

		// マテリアル情報を取り出す
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
		{
			// 使用しているテクスチャがあれば読み込む
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャ読み込み
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_pTexture[nCntMat])))
				{
					return E_FAIL;
				}
			}
		}

	return S_OK;
}
//******************************************************************************
//モデルの破棄
//******************************************************************************
void CTestModel::Unload(void)
{
		// メッシュの破棄
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}

		// マテリアルの破棄
		if (m_pBuffMat != NULL)
		{
			m_pBuffMat->Release();
			m_pBuffMat = NULL;
		}

		if (m_nNumMat != NULL)
		{
			m_nNumMat = NULL;
		}
}

//******************************************************************************
//初期化処理
//******************************************************************************
HRESULT CTestModel::Init(void)
{
	// モデルの生成
	m_pModel = CModel::Create();

	// モデルのバインド
	m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, -1);

	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// テクスチャのバインド
		m_pModel->BindTexture(m_pTexture[nCntMat], nCntMat);
	}

	return S_OK;
}

//******************************************************************************
//終了処理
//******************************************************************************
void CTestModel::Uninit(void)
{
	// モデルクラスの終了処理
	m_pModel->Uninit();

	m_pModel = NULL;

	// 破棄
	Release();
}

//******************************************************************************
//更新処理
//******************************************************************************
void CTestModel::Update(void)
{
	// 設定
	SetBox(m_pos, m_rot, m_size);
}

//******************************************************************************
//描画処理
//******************************************************************************
void CTestModel::Draw(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトの効果を無効に
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//ワールドマトリクスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	m_pModel->SetWorldMatrix(m_mtxWorld);

	// モデルクラスの描画処理
	m_pModel->Draw();

	// ライトの効果を無効に
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CTestModel::Move(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	D3DXVECTOR3 move = INIT_D3DXVECTOR3;

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (g_lpDIDevice != NULL)
	{
		// 右スティックを左に倒す
		if (js.lZ <= -STICK_REACTION)
		{
			move.x = MOVE_VALUE.x;
		}
		// 右スティックを右に倒す
		if (js.lZ >= STICK_REACTION)
		{
			move.x = -MOVE_VALUE.x;
		}
		// 右スティックを上に倒す
		if (js.lRz <= -STICK_REACTION)
		{
			move.y = MOVE_VALUE.y;
		}
		// 右スティックを下に倒す
		if (js.lRz >= STICK_REACTION)
		{
			move.y = -MOVE_VALUE.y;
		}
	}
	// 移動
	m_pos.x += move.x;
	m_pos.y += move.y;
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void CTestModel::ReleaseBox(void)
{
	// 破棄
	Uninit();

	return;
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CTestModel::SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
}