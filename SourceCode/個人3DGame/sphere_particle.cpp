//******************************************************************************
// ���̃p�[�e�B�N���G�~�b�^�[ [sphere_particle.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
//	�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "sphere_particle.h"
//******************************************************************************
//	�}�N����`
//******************************************************************************
#define SUB_SCALE_VALUE (0.005f)		// �g�嗦���Z�l
#define SUB_COLOR_VALUE (0.005f)		// �F���Z�l
#define MIN_SCALE_VALUE	(0.0f)			// �g�嗦�ŏ��l
#define MIN_COLOR_VALUE	(0.0f)			// �F�̍ŏ��l
//******************************************************************************
//	�R���X�g���N�^
//******************************************************************************
CSphere_Particle::CSphere_Particle(int nPrirority)
{
	m_move		= INIT_D3DXVECTOR3;
	m_fMinScale = INIT_FLOAT;
	m_fMinColor = INIT_FLOAT;
}
//******************************************************************************
//	�f�X�g���N�^
//******************************************************************************
CSphere_Particle::~CSphere_Particle()
{
}
//******************************************************************************
//	�����֐�
//******************************************************************************
CSphere_Particle * CSphere_Particle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// CParticle_Fire�N���X�̃|�C���^
	CSphere_Particle *pSphere_Particle;

	// �������m��
	pSphere_Particle = new CSphere_Particle;

	// ������
	pSphere_Particle->Init(pos, size, rot, col, move, TexType);

	// �|�C���^��Ԃ�
	return pSphere_Particle;
}
//******************************************************************************
//	������
//******************************************************************************
HRESULT CSphere_Particle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 move, CParticle::TEX_TYPE TexType)
{
	// ������
	CParticle::Init(pos, size, rot, col, TexType);

	// �ړ���
	m_move = move;

	// �g�嗦���Z�l
	m_fMinScale = SUB_SCALE_VALUE;

	// �J���[���Z�l
	m_fMinColor = SUB_COLOR_VALUE;

	return S_OK;

}
//******************************************************************************
//	�I���֐�
//******************************************************************************
void CSphere_Particle::Uninit(void)
{
	// �I��
	CParticle::Uninit();
}
//******************************************************************************
//	�X�V�֐�
//******************************************************************************
void CSphere_Particle::Update(void)
{
	// �X�V
	CParticle::Update();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �F�擾
	D3DXCOLOR col = GetColor();

	// �g�嗦�擾
	float fScale = GetScale();

	// �J���[���Z
	col.a -= m_fMinColor;

	// a�̒l��0�ȉ��̏ꍇ
	if (col.a <= MIN_COLOR_VALUE)
	{
		col.a = MIN_COLOR_VALUE;
	}

	// �T�C�Y���Z
	fScale -= m_fMinScale;

	// �T�C�Y�ݒ�
	SetScale(fScale);

	// �F�ݒ�
	SetColor(col);

	// �ʒu�X�V
	pos += m_move;

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �g�嗦��0.0f�ȉ��̏ꍇ
	if (fScale <= MIN_SCALE_VALUE)
	{
		// �I��
		Uninit();
		return;
	}
	// ����0.0f�ȉ��̏ꍇ
	if (col.a <= MIN_COLOR_VALUE)
	{
		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
//	�`��֐�
//******************************************************************************
void CSphere_Particle::Draw(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CParticle::Draw();

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}