//******************************************************************************
// ���̃p�[�e�B�N���G�~�b�^�[ [sphere_particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "sphere_particle_emitter.h"
#include "sphere_particle.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define SPHERE_PARTICLE_SIZE	(D3DXVECTOR3(10.0f,10.0f,0.0f))		// �T�C�Y
#define SPHERE_PARTICLE_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))		// ����
#define PARTICLE_COLOR			(D3DCOLOR_RGBA(255,255,255,255))	// �F(��)
#define PARTICLE_COLOR2			(D3DCOLOR_RGBA(255,0,255,255))		// �F(��)
#define DEVIDE_VALUE			(2)									// ���鐔
#define PARTICLE_NUMBER			(2)									// �������鐔
#define RANDUM_DEVIDE			(10.0f)								// �����_�������鐔
#define RANDUM_ANGLE			(360 - 180)							// �ʓx�����_��
#define RANDUM_POS				(300 - 150)							// �ʒu�������_��
#define SPEED_RANDUM			(15 + 10)							// �ړ��ʃ����_��
// �ړ��̏���
#define PARTICLE_MOVE			(D3DXVECTOR3(cosf(D3DXToRadian(fAngle2))*fFireSpeed, sinf(D3DXToRadian(fAngle2))*fFireSpeed, sinf(D3DXToRadian(fAngle2))*fFireSpeed))

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CSphere_Particle_Emitter::CSphere_Particle_Emitter()
{
	m_nCount = 0;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CSphere_Particle_Emitter::~CSphere_Particle_Emitter()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
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
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CSphere_Particle_Emitter::Init(void)
{
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CSphere_Particle_Emitter::Uninit(void)
{
	// �I��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CSphere_Particle_Emitter::Update(void)
{
	// �J�E���g�C���N�������g
	m_nCount++;

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �J�E���g��2���܂�0�̎�
	if (m_nCount % DEVIDE_VALUE == INIT_INT)
	{
		// 2��J��Ԃ�
		for (int nCnt = INIT_INT; nCnt < PARTICLE_NUMBER; nCnt++)
		{
			// �ʒu�����_��
			float fPosX = float(rand() % RANDUM_POS);
			fPosX = fPosX / RANDUM_DEVIDE;

			// �ʓx�����_��
			float fAngle2 = float(rand() % RANDUM_ANGLE);

			// �ړ��ʃ����_��
			float fFireSpeed = float(rand() % SPEED_RANDUM);
			fFireSpeed = fFireSpeed / RANDUM_DEVIDE;

			// ���̃p�[�e�B�N������
			CSphere_Particle::Create(D3DXVECTOR3(pos.x + fPosX, pos.y, pos.z),
				SPHERE_PARTICLE_SIZE,
				SPHERE_PARTICLE_ROT,
				PARTICLE_COLOR,
				PARTICLE_MOVE,
				CParticle::TEX_TYPE_1
			);

			// ���̃p�[�e�B�N������
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
// �`��֐�
//******************************************************************************
void CSphere_Particle_Emitter::Draw(void)
{
}