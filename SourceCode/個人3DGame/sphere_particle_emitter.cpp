//=============================================================================
//
// ���̃p�[�e�B�N���G�~�b�^�[ [sphere_particle_emitter.cpp]
// Author : �ǌ��@�i
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "sphere_particle_emitter.h"
#include "sphere_particle.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SPHERE_PARTICLE_SIZE_X (10)
#define SPHERE_PARTICLE_SIZE_Y (10)
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSphere_Particle_Emitter::CSphere_Particle_Emitter()
{
	m_nCount = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSphere_Particle_Emitter::~CSphere_Particle_Emitter()
{
}
//=============================================================================
// �����֐�
//=============================================================================
CSphere_Particle_Emitter * CSphere_Particle_Emitter::Create(D3DXVECTOR3 pos)
{
	// CParticle_Fire�N���X�̃|�C���^
	CSphere_Particle_Emitter *pSphere_Particle_Emitter;

	// �������m��
	pSphere_Particle_Emitter = new CSphere_Particle_Emitter;

	// �ʒu���W�ݒ�
	pSphere_Particle_Emitter->SetPosition(pos);

	// ������
	pSphere_Particle_Emitter->Init();

	// �|�C���^��Ԃ�
	return pSphere_Particle_Emitter;
}
//=============================================================================
// �������֐�
//=============================================================================
HRESULT CSphere_Particle_Emitter::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I���֐�
//=============================================================================
void CSphere_Particle_Emitter::Uninit(void)
{
	// �I��
	Release();
}
//=============================================================================
// �X�V�֐�
//=============================================================================
void CSphere_Particle_Emitter::Update(void)
{
	// �J�E���g�C���N�������g
	m_nCount++;

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �J�E���g��2���܂�0�̎�
	if (m_nCount % 2 == 0)
	{
		// 2��J��Ԃ�
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			float fPosX = float(rand() % 300 - 150);
			fPosX = fPosX / 10.0f;
			float fAngle = float(rand() % 150 + 30);
			float fAngle2 = float(rand() % 360 - 180);
			float fRot = float(rand() % 360 - 180);
			float fFireSpeed = float(rand() % 15 + 10);
			fFireSpeed = fFireSpeed / 10.0f;

			// ���̃p�[�e�B�N������
			CSphere_Particle::Create(D3DXVECTOR3(pos.x + fPosX, pos.y, pos.z),
				D3DXVECTOR3(SPHERE_PARTICLE_SIZE_X, SPHERE_PARTICLE_SIZE_Y, 0.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DCOLOR_RGBA(255, 255, 255, 255),
				D3DXVECTOR3(cosf(D3DXToRadian(fAngle))*fFireSpeed, sinf(D3DXToRadian(fAngle))*fFireSpeed, sinf(D3DXToRadian(fAngle2))*fFireSpeed),
				CParticle::TEX_TYPE_1
			);

			// ���̃p�[�e�B�N������
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
// �`��֐�
//=============================================================================
void CSphere_Particle_Emitter::Draw(void)
{
}