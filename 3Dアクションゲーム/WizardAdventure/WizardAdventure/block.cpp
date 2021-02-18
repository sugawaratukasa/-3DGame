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
#include "input.h"
#include "joystick.h"
#include "model.h"
#include "frame.h"
#include "block.h"
#include "block_manager.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE_VALUE		(D3DXVECTOR3(2.0f,2.0f,0.0f))		// 移動量
#define FRAME_COLOR1	(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))	// 枠の色
#define FRAME_COLOR2	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 枠の色
#define FRAME_COLOR3	(D3DXCOLOR(0.0f,0.8f,1.0f,1.0f))	// 枠の色
#define BLOCK_WOOD		("data/Model/Object/box.x")			// 木箱
#define BLOCK_STOON		("data/Model/Object/box_2.x")		// 石の箱
//******************************************************************************
//静的メンバ変数
//******************************************************************************
LPD3DXMESH CBlock::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CBlock::m_pBuffMat[TYPE_MAX] = {};
DWORD CBlock::m_nNumMat[TYPE_MAX] = {};
char* CBlock::m_apFileName[TYPE_MAX] = { BLOCK_WOOD, BLOCK_STOON };// 箱

//******************************************************************************
// コンストラクタ
//******************************************************************************
CBlock::CBlock(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	m_pBlock	= NULL;
	m_pFrame	= NULL;
	m_Type		= TYPE_NONE;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// デストラクタ
//******************************************************************************
CBlock::~CBlock()
{

}

//******************************************************************************
// モデルの読み込み
//******************************************************************************
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_nNumMat[nCnt],
			&m_pMesh[nCnt]
		);
	}
	return S_OK;
}
//******************************************************************************
// モデルの破棄
//******************************************************************************
void CBlock::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// メッシュの破棄
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// マテリアルの破棄
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
		if (m_nNumMat[nCnt] != NULL)
		{
			m_nNumMat[nCnt] = NULL;
		}
	}
}

//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CBlock::Init(void)
{
	// モデルの生成
	m_pModel = CModel::Create();

	// モデルのバインド
	m_pModel->BindModel(m_pMesh[m_Type], m_pBuffMat[m_Type], m_nNumMat[m_Type], -1);

	// 情報設定
	m_pModel->SetModel(m_pos, m_rot, m_size);

	// 枠を生成
	SetFrame();

	return S_OK;
}

//******************************************************************************
// 終了処理
//******************************************************************************
void CBlock::Uninit(void)
{
	if (m_pModel != NULL)
	{
		// モデルクラスの終了処理
		m_pModel->Uninit();

		m_pModel = NULL;
	}

	// 破棄
	Release();
}

//******************************************************************************
// 更新処理
//******************************************************************************
void CBlock::Update(void)
{
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CBlock::Draw(void)
{
	//レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

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
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CBlock::Move(void)
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

		// 位置更新
		m_pModel->SetModel(m_pos, m_rot, m_size);
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void CBlock::ReleaseBlock(void)
{
	// 破棄
	Uninit();

	return;
}
//******************************************************************************
// フレーム生成
//******************************************************************************
void CBlock::SetFrame(void)
{
	m_pFrame = CFrame::Create(m_pos, m_rot, m_size, FRAME_COLOR1, m_pBlock);
}
//******************************************************************************
// 選択されている場合
//******************************************************************************
void CBlock::Selecting(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR3);
}
//******************************************************************************
// 未選択の場合
//******************************************************************************
void CBlock::UnSelected(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR1);
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CBlock *pBlock,TYPE type)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
	m_pBlock = pBlock;
	m_Type = type;

	// オブジェタイプをブロックに設定
	SetObjType(OBJTYPE_BLOCK);
}