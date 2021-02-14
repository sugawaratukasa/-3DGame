//******************************************************************************
// 球のパーティクル [sphere_particle.h]
// Author : 管原　司
//******************************************************************************
#ifndef _SPHERE_PARTICLE_H_
#define _SPHERE_PARTICLE_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "particle.h"
//******************************************************************************
// クラス
//******************************************************************************
class CSphere_Particle: public CParticle
{
public:
	CSphere_Particle(int nPrirority = 5);
	~CSphere_Particle();
	static CSphere_Particle *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	D3DXVECTOR3	m_move;		//	移動量
	float m_fMinColor;		//	色の減算値
	float m_fMinScale;		//　拡大率の減算値
};
#endif