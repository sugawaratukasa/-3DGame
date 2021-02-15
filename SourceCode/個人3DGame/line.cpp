//******************************************************************************
// 3D [scene3d.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "line.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define NOR				(D3DXVECTOR3(0, 1, 0))	// 法線
//******************************************************************************
// コンストラクタ
//******************************************************************************
CLine::CLine(int nPriority) :CScene(nPriority)
{
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_Start_pos = INIT_D3DXVECTOR3;
	m_End_pos	= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_col		= INIT_COLOR;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// デストラクタ
//******************************************************************************
CLine::~CLine()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CLine * CLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos, D3DXCOLOR col)
{
	// CLineのポインタ
	CLine *pLine;

	// メモリ確保
	pLine = new CLine;

	// 情報設定
	pLine->SetLine(pos,rot,startpos,endpos,col);

	// 初期化
	pLine->Init();

	// ポインタを返す
	return pLine;
}

//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CLine::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,																	// 頂点バッファの使用法　
		FVF_VERTEX_POINT,																	// 使用する頂点フォーマット
		D3DPOOL_MANAGED,																	// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,																		// 頂点バッファへのポインタ
		NULL)))																				// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_POINT *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(NULL, NULL, (void**)&pVtx, NULL);

	// 場所の設定
	pVtx[0].pos = D3DXVECTOR3(m_Start_pos.x, m_Start_pos.y, m_Start_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_End_pos.x, m_End_pos.y, m_End_pos.z);

	// カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//******************************************************************************
// 終了処理
//******************************************************************************
void CLine::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// 破棄
	Release();
}

//******************************************************************************
// 更新処理
//******************************************************************************
void CLine::Update(void)
{
	// 頂点情報を設定
	VERTEX_POINT *pVtx = NULL;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(NULL, NULL, (void**)&pVtx, NULL);

	// 場所の設定
	pVtx[0].pos = D3DXVECTOR3(m_Start_pos.x, m_Start_pos.y, m_Start_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_End_pos.x, m_End_pos.y, m_End_pos.z);

	// カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CLine::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	// マトリックス初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向き
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定 
	pDevice->SetStreamSource(NULL, m_pVtxBuff, NULL, sizeof(VERTEX_POINT));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_POINT);

	// ラインの描画
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CLine::SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos, D3DXCOLOR col)
{
	// 位置
	m_pos = pos;

	// 向き
	m_rot = rot;

	// 始点
	m_Start_pos = startpos;

	// 終点
	m_End_pos = endpos;

	// 色
	m_col = col;
}