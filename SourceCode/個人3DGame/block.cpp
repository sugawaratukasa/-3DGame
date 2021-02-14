//******************************************************************************
// ブロック[block.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "block.h"
#include "model.h"

//******************************************************************************
//静的メンバ変数
//******************************************************************************
LPD3DXMESH CBlock::m_pMesh = NULL;
LPD3DXBUFFER CBlock::m_pBuffMat = NULL;
DWORD CBlock::m_nNumMat = NULL;
char* CBlock::m_apFileName = { "data/Model/Object/box.x" };// 箱
LPDIRECT3DTEXTURE9 CBlock::m_pTexture[MAX_MATERIAL] = {};

//******************************************************************************
//インクリメント
//******************************************************************************
CBlock::CBlock(int nPriority) :CScene(nPriority)
{
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_size = INIT_D3DXVECTOR3;
	m_pModel = NULL;
	m_mtxWorld = {};
}
//******************************************************************************
//デクリメント
//******************************************************************************
CBlock::~CBlock()
{

}
//******************************************************************************
//生成処理
//******************************************************************************
CBlock * CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CBlockのポインタ
	CBlock *pBlock;

	// メモリ確保
	pBlock = new CBlock;

	// 初期化
	pBlock->Init();

	// 情報設定
	pBlock->SetBlock(pos, rot, size);

	// ポインタを返す
	return pBlock;
}

//******************************************************************************
//モデルの読み込み
//******************************************************************************
HRESULT CBlock::Load(void)
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
	return S_OK;
}
//******************************************************************************
//モデルの破棄
//******************************************************************************
void CBlock::Unload(void)
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
HRESULT CBlock::Init(void)
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
void CBlock::Uninit(void)
{
	// モデルクラスの終了処理
	m_pModel->Uninit();
	m_pModel = NULL;
}

//******************************************************************************
//更新処理
//******************************************************************************
void CBlock::Update(void)
{
	// 設定
	SetBlock(m_pos, m_rot, m_size);
	CScene *pScene = NULL;
}

//******************************************************************************
//描画処理
//******************************************************************************
void CBlock::Draw(void)
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
// 情報設定
//******************************************************************************
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
}