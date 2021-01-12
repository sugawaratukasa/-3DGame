//=============================================================================
//
// 球のパーティクルエミッター [sphere_particle_emitter.cpp]
// Author : 管原　司
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "sphere_particle_emitter.h"
#include "sphere_particle.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SPHERE_PARTICLE_SIZE_X (10)
#define SPHERE_PARTICLE_SIZE_Y (10)
//=============================================================================
// コンストラクタ
//=============================================================================
CSphere_Particle_Emitter::CSphere_Particle_Emitter()
{
	m_nCount = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CSphere_Particle_Emitter::~CSphere_Particle_Emitter()
{
}
//=============================================================================
// 生成関数
//=============================================================================
CSphere_Particle_Emitter * CSphere_Particle_Emitter::Create(D3DXVECTOR3 pos)
{
	// CParticle_Fireクラスのポインタ
	CSphere_Particle_Emitter *pSphere_Particle_Emitter;

	// メモリ確保
	pSphere_Particle_Emitter = new CSphere_Particle_Emitter;

	// 位置座標設定
	pSphere_Particle_Emitter->SetPosition(pos);

	// 初期化
	pSphere_Particle_Emitter->Init();

	// ポインタを返す
	return pSphere_Particle_Emitter;
}
//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CSphere_Particle_Emitter::Init(void)
{
	return S_OK;
}
//=============================================================================
// 終了関数
//=============================================================================
void CSphere_Particle_Emitter::Uninit(void)
{
	// 終了
	Release();
}
//=============================================================================
// 更新関数
//=============================================================================
void CSphere_Particle_Emitter::Update(void)
{
	// カウントインクリメント
	m_nCount++;

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// カウントが2あまり0の時
	if (m_nCount % 2 == 0)
	{
		// 2回繰り返す
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			float fPosX = float(rand() % 300 - 150);
			fPosX = fPosX / 10.0f;
			float fAngle = float(rand() % 150 + 30);
			float fAngle2 = float(rand() % 360 - 180);
			float fRot = float(rand() % 360 - 180);
			float fFireSpeed = float(rand() % 15 + 10);
			fFireSpeed = fFireSpeed / 10.0f;

			// 球のパーティクル生成
			CSphere_Particle::Create(D3DXVECTOR3(pos.x + fPosX, pos.y, pos.z),
				D3DXVECTOR3(SPHERE_PARTICLE_SIZE_X, SPHERE_PARTICLE_SIZE_Y, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DCOLOR_RGBA(255, 255, 255, 255),
				D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fFireSpeed, sinf(D3DXToRadian(fAngle))*fFireSpeed, sinf(D3DXToRadian(fAngle2))*fFireSpeed),
				CParticle::TEX_TYPE_1
			);

			// 球のパーティクル生成
			CSphere_Particle::Create(D3DXVECTOR3(pos.x + fPosX, pos.y, pos.z),
				D3DXVECTOR3(SPHERE_PARTICLE_SIZE_X, SPHERE_PARTICLE_SIZE_Y, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DCOLOR_RGBA(255, 0, 255, 255),
				D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fFireSpeed, sinf(D3DXToRadian(fAngle))*fFireSpeed, sinf(D3DXToRadian(fAngle2))*fFireSpeed),
				CParticle::TEX_TYPE_1
			);
		}
	}
}
//=============================================================================
// 描画関数
//=============================================================================
void CSphere_Particle_Emitter::Draw(void)
{
}