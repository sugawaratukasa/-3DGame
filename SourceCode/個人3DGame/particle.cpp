//******************************************************************************
// particle.cpp
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "billboard.h"
#include "particle.h"

//******************************************************************************
//�ÓI�����o�ϐ��錾
//******************************************************************************
LPDIRECT3DTEXTURE9 CParticle::m_pTexture[TEX_TYPE_MAX] = {};

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle::CParticle()
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle::~CParticle()
{
}
//******************************************************************************
// �e�N�X�`���̓ǂݍ���
//******************************************************************************
HRESULT CParticle::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle001.png", &m_pTexture[TEX_TYPE_1]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/fire002.png", &m_pTexture[TEX_TYPE_2]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/particle004.png", &m_pTexture[TEX_TYPE_3]);
	D3DXCreateTextureFromFile(pDevice, "data/Texture/snow.png", &m_pTexture[TEX_TYPE_4]);
	return S_OK;
}

//******************************************************************************
// �e�N�X�`���̔j��
//******************************************************************************
void CParticle::Unload(void)
{
	// 3��J��Ԃ�
	for (int nCnt = INIT_INT; nCnt < TEX_TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			// �e�N�X�`��Release
			m_pTexture[nCnt]->Release();

			// m_pTexture��NULL��
			m_pTexture[nCnt] = NULL;
		}
	}
}

//******************************************************************************
// ������
//******************************************************************************
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, D3DXCOLOR col, TEX_TYPE TexType)
{

	// �e�N�X�`���^�C�v
	m_TexType = TexType;

	// ������
	CBillboard::Init();

	// �ʒu���W�ݒ�
	SetPosition(pos);

	// �T�C�Y�ݒ�
	SetSize(size);

	// �����ݒ�
	SetRotation(rot);

	// �J���[�ݒ�
	SetColor(col);

	// �e�N�X�`���󂯓n��
	BindTexture(m_pTexture[m_TexType]);

	// �e�N�X�`���ݒ�
	SetTexture(0.0f, 0.0f, 1.0f, 1.0f);

	return S_OK;
}

//******************************************************************************
// �I��
//******************************************************************************
void CParticle::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//******************************************************************************
// �X�V
//******************************************************************************
void CParticle::Update(void)
{
	// �X�V
	CBillboard::Update();
}

//******************************************************************************
// �`��
//******************************************************************************
void CParticle::Draw(void)
{
	// �`��
	CBillboard::Draw();
}