//******************************************************************************
// 2D [scene2d.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"

//******************************************************************************
//コンストラクタ
//******************************************************************************
CScene2D::CScene2D(int nPriority) :CScene(nPriority)
{
	m_pTexture		= NULL;
	m_pVtxBuff		= NULL;
	m_pos			= INIT_D3DXVECTOR3;
	m_size			= INIT_D3DXVECTOR3;
	m_rot			= INIT_D3DXVECTOR3;
	m_color			= INIT_COLOR;
	m_fAngle		= INIT_FLOAT;
	m_fLength		= INIT_FLOAT;
}

//******************************************************************************
//デストラクタ
//******************************************************************************
CScene2D::~CScene2D()
{

}

//******************************************************************************
//初期化処理
//******************************************************************************
HRESULT CScene2D::Init(void)
{
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * MAX_POLYGON,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_2D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&m_pVtxBuff,				// 頂点バッファへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	// 頂点情報を設定
	VERTEX_2D *pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;
	//頂点カラーの設定 ※いつものやつ

	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//******************************************************************************
// ポリゴンの終了処理
//******************************************************************************
void CScene2D::Uninit(void)
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
// ポリゴンの更新処理
//******************************************************************************
void CScene2D::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	//角度取得
	m_fAngle = atan2f((m_size.y / 2), (m_size.x / 2));

	//半径取得
	m_fLength = sqrtf((float)(((m_size.x / 2) * (m_size.x / 2)) + ((m_size.y / 2) * (m_size.y / 2))));

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos.x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw
	pVtx[0].rhw = RHW_VALUE;
	pVtx[1].rhw = RHW_VALUE;
	pVtx[2].rhw = RHW_VALUE;
	pVtx[3].rhw = RHW_VALUE;

	//頂点カラーの設定 
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	//テクスチャ
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
	//位置座標設定
	SetPosition(m_pos);
}

//******************************************************************************
// ポリゴンの描画処理
//******************************************************************************
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CSceneManager::GetRenderer()->GetDevice();

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//アルファテスト基準値の設定
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	//アルファテストの比較方法の設定（GREATERは基準値より大きい場合)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//******************************************************************************
//テクスチャの設定
//******************************************************************************
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//******************************************************************************
//アルファ値の設定
//******************************************************************************
void CScene2D::SetColor(D3DXCOLOR color)
{
	m_color = color;
}

//******************************************************************************
//向き設定
//******************************************************************************
void CScene2D::SetRotation(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//******************************************************************************
// 位置座標設定
//******************************************************************************
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// サイズ設定
//******************************************************************************
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}