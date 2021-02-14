//******************************************************************************
// 球のパーティクルエミッター [sphere_particle.cpp]
// Author : 管原　司
//******************************************************************************
//******************************************************************************
//	インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sphere_particle.h"
//******************************************************************************
//	マクロ定義
//******************************************************************************
#define SUB_SCALE_VALUE (0.005f)		// 拡大率減算値
#define SUB_COLOR_VALUE (0.005f)		// 色減算値
#define MIN_SCALE_VALUE	(0.0f)			// 拡大率最小値
#define MIN_COLOR_VALUE	(0.0f)			// 色の最小値
//******************************************************************************
//	コンストラクタ
//******************************************************************************
CSphere_Particle::CSphere_Particle(int nPrirority)
{
	m_move		= INIT_D3DXVECTOR3;
	m_fMinScale = INIT_FLOAT;
	m_fMinColor = INIT_FLOAT;
}
//******************************************************************************
//	デストラクタ
//******************************************************************************
CSphere_Particle::~CSphere_Particle()
{
}
//******************************************************************************
//	生成関数
//******************************************************************************
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
//******************************************************************************
//	初期化
//******************************************************************************
HRESULT CSphere_Particle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// 初期化
	CParticle::Init(pos, size, rot, col, TexType);

	// 移動量
	m_move = move;

	// 拡大率減算値
	m_fMinScale = SUB_SCALE_VALUE;

	// カラー減算値
	m_fMinColor = SUB_COLOR_VALUE;

	return S_OK;

}
//******************************************************************************
//	終了関数
//******************************************************************************
void CSphere_Particle::Uninit(void)
{
	// 終了
	CParticle::Uninit();
}
//******************************************************************************
//	更新関数
//******************************************************************************
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
	col.a -= m_fMinColor;

	// aの値が0以下の場合
	if (col.a <= MIN_COLOR_VALUE)
	{
		col.a = MIN_COLOR_VALUE;
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
	if (fScale <= MIN_SCALE_VALUE)
	{
		// 終了
		Uninit();
		return;
	}
	// αが0.0f以下の場合
	if (col.a <= MIN_COLOR_VALUE)
	{
		// 終了
		Uninit();
		return;
	}
}
//******************************************************************************
//	描画関数
//******************************************************************************
void CSphere_Particle::Draw(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// 加算合成の設定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画
	CParticle::Draw();

	// 元に戻す
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}