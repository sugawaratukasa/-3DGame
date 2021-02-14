//******************************************************************************
// 球のパーティクルエミッター [sphere_particle_emitter.cpp]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "sphere_particle_emitter.h"
#include "sphere_particle.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define SPHERE_PARTICLE_SIZE	(D3DXVECTOR3(10.0f,10.0f,0.0f))		// サイズ
#define SPHERE_PARTICLE_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))		// 向き
#define PARTICLE_COLOR			(D3DCOLOR_RGBA(255,255,255,255))	// 色(白)
#define PARTICLE_COLOR2			(D3DCOLOR_RGBA(255,0,255,255))		// 色(紫)
#define DEVIDE_VALUE			(2)									// 割る数
#define PARTICLE_NUMBER			(2)									// 生成する数
#define RANDUM_DEVIDE			(10.0f)								// ランダムを割る数
#define RANDUM_ANGLE			(360 - 180)							// 弧度ランダム
#define RANDUM_POS				(300 - 150)							// 位置をランダム
#define SPEED_RANDUM			(15 + 10)							// 移動量ランダム
// 移動の処理
#define PARTICLE_MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle2))*fFireSpeed, sinf(D3DXToRadian(fAngle2))*fFireSpeed, sinf(D3DXToRadian(fAngle2))*fFireSpeed))

//******************************************************************************
// コンストラクタ
//******************************************************************************
CSphere_Particle_Emitter::CSphere_Particle_Emitter()
{
	m_nCount = 0;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CSphere_Particle_Emitter::~CSphere_Particle_Emitter()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
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
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CSphere_Particle_Emitter::Init(void)
{
	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CSphere_Particle_Emitter::Uninit(void)
{
	// 終了
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CSphere_Particle_Emitter::Update(void)
{
	// カウントインクリメント
	m_nCount++;

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// カウントが2あまり0の時
	if (m_nCount % DEVIDE_VALUE == INIT_INT)
	{
		// 2回繰り返す
		for (int nCnt = INIT_INT; nCnt < PARTICLE_NUMBER; nCnt++)
		{
			// 位置ランダム
			float fPosX = float(rand() % RANDUM_POS);
			fPosX = fPosX / RANDUM_DEVIDE;

			// 弧度ランダム
			float fAngle2 = float(rand() % RANDUM_ANGLE);

			// 移動量ランダム
			float fFireSpeed = float(rand() % SPEED_RANDUM);
			fFireSpeed = fFireSpeed / RANDUM_DEVIDE;

			// 球のパーティクル生成
			CSphere_Particle::Create(D3DXVECTOR3(pos.x + fPosX, pos.y, pos.z),
				SPHERE_PARTICLE_SIZE,
				SPHERE_PARTICLE_ROT,
				PARTICLE_COLOR,
				PARTICLE_MOVE,
				CParticle::TEX_TYPE_1
			);

			// 球のパーティクル生成
			CSphere_Particle::Create(D3DXVECTOR3(pos.x + fPosX, pos.y, pos.z),
				SPHERE_PARTICLE_SIZE,
				SPHERE_PARTICLE_ROT,
				PARTICLE_COLOR2,
				PARTICLE_MOVE,
				CParticle::TEX_TYPE_1
			);
		}
	}
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CSphere_Particle_Emitter::Draw(void)
{
}