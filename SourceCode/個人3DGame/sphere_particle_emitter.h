//******************************************************************************
// ���̃p�[�e�B�N���G�~�b�^�[ [sphere_particle_emitter.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _SPHERE_PARTICLE_EMITTER_H_
#define _SPHERE_PARTICLE_EMITTER_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle_emitter.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CSphere_Particle_Emitter : public CParticle_Emitter
{
public:
	CSphere_Particle_Emitter();
	~CSphere_Particle_Emitter();
	static CSphere_Particle_Emitter *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	int m_nCount;
};
#endif
