//=============================================================================
//
// 球のパーティクルエミッター [sphere_particle.cpp]
// Author : 管原　司
//
//=============================================================================
//============================================================================
//	インクルードファイル
//============================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sphere_particle.h"
//============================================================================
//	コンストラクタ
//============================================================================
CSphere_Particle::CSphere_Particle(int nPrirority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMinScale = 0.0f;
	m_fMinColor = 0.0f;
}
//============================================================================
//	デストラクタ
//============================================================================
CSphere_Particle::~CSphere_Particle()
{
}
//============================================================================
//	生成関数
//============================================================================
CSphere_Particle * CSphere_Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Fireクラスのポインタ
	CSphere_Particle *pSphere_Particle;

	// メモリ確保
	pSphere_Particle = new CSphere_Particle;

	// 初期化
	pSphere_Particle->Init(pos, size, rot, col, move, TexType);

	// ポインタを返す
	return pSphere_Particle;
}
//============================================================================
//	初期化
//============================================================================
HRESULT CSphere_Particle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// 初期化
	CParticle::Init(pos, size, rot, col, TexType);

	// 移動量
	m_move = move;

	// 拡大率減算値
	m_fMinScale = 0.005f;

	// カラー減算値
	m_fMinColor = 0.005f;

	return S_OK;

}
//============================================================================
//	終了関数
//============================================================================
void CSphere_Particle::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//============================================================================
//	更新関数
//============================================================================
void CSphere_Particle::Update(void)
{
	// 更新
	CParticle::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// 色取得
	D3DXCOLOR col = GetColor();

	// 拡大率取得
	float fScale = GetScale();

	// カラー減算
	//col.r -= m_fMinColor;
	//col.g -= m_fMinColor;
	col.a -= m_fMinColor;

	// rの値が0以下の場合
	if (col.r <= 0.0f)
	{
		col.r = 0.0f;
	}

	// gの値が0以下の場合
	if (col.g <= 0.0f)
	{
		col.g = 0.0f;
	}

	// aの値が0以下の場合
	if (col.a <= 0.0f)
	{
		col.a = 0.0f;
	}

	// サイズ減算
	fScale -= m_fMinScale;

	// サイズ設定
	SetScale(fScale);

	// 色設定
	SetColor(col);

	// 位置更新
	pos += m_move;

	// 位置座標設定
	SetPosition(pos);

	// 拡大率が0.0f以下の場合
	if (fScale <= 0.0f)
	{
		// 終了
		Uninit();
		return;
	}
	// αが0.0f以下の場合
	if (col.a <= 0.0f)
	{
		// 終了
		Uninit();
		return;
	}
}
//============================================================================
//	描画関数
//============================================================================
void CSphere_Particle::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CParticle::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}