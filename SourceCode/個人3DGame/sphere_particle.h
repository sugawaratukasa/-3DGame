//******************************************************************************
// ���̃p�[�e�B�N�� [sphere_particle.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SPHERE_PARTICLE_H_
#define _SPHERE_PARTICLE_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
//******************************************************************************
// �N���X
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
	D3DXVECTOR3	m_move;		//	�ړ���
	float m_fMinColor;		//	�F�̌��Z�l
	float m_fMinScale;		//�@�g�嗦�̌��Z�l
};
#endif