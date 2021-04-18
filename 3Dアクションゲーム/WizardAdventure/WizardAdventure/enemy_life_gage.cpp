//******************************************************************************
// �G�̃��C�t�Q�[�W [enemy_life_gage.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "ui_texture.h"
#include "enemy.h"
#include "enemy_life_gage.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POS			(D3DXVECTOR3(EnemyPos.x,EnemyPos.y + 40.0f, EnemyPos.z - 10.0f))	// �ʒu
#define SIZE		(D3DXVECTOR3(30.0f,2.5f,0.0f))										// �T�C�Y
#define ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))										// ����
#define COL			(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))									// �F
#define MIN_LIFE	(0)																	// ���C�t�̍ŏ��l
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CEnemy_Life_Gage::CEnemy_Life_Gage()
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CEnemy_Life_Gage::~CEnemy_Life_Gage()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CEnemy_Life_Gage * CEnemy_Life_Gage::Create(D3DXVECTOR3 pos, CEnemy *pEnemy)
{
	// CLife_Gage�̃|�C���^
	CEnemy_Life_Gage *pEnemy_Life_Gage = NULL;

	// NULL�̏ꍇ
	if (pEnemy_Life_Gage == NULL)
	{
		// �������m��
		pEnemy_Life_Gage = new CEnemy_Life_Gage;

		// NULL�łȂ��ꍇ
		if (pEnemy_Life_Gage != NULL)
		{
			// ���
			pEnemy_Life_Gage->m_pEnemy = pEnemy;

			// ���C�t
			int nLife = pEnemy_Life_Gage->m_pEnemy->GetLife();

			// ���ݒ�
			pEnemy_Life_Gage->SetGage(pos, ROT, SIZE, COL, nLife);

			// �e�N�X�`���󂯓n��
			//pEnemy_Life_Gage->BindTexture(CManager::GetUI_Texture()->GetTexture(CUI_Texture::TEX_TYPE_LIFE_GAGE));

			// ������
			pEnemy_Life_Gage->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pEnemy_Life_Gage;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CEnemy_Life_Gage::Init(void)
{
	// ������
	C3D_Gage::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CEnemy_Life_Gage::Uninit(void)
{
	// �I��
	C3D_Gage::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CEnemy_Life_Gage::Update(void)
{
	// �X�V
	C3D_Gage::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �G�̈ʒu�擾
	D3DXVECTOR3 EnemyPos = m_pEnemy->GetPos();

	// ���C�t�擾
	int nLife = m_pEnemy->GetLife();

	// ���C�t�ݒ�
	SetGageNum(nLife);

	// �ʒu���
	pos = POS;

	// �ʒu�ݒ�
	SetPosition(pos);

	// ���C�t��0�ȉ��ɂȂ����ꍇ
	if (nLife <= MIN_LIFE)
	{
		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CEnemy_Life_Gage::Draw(void)
{
	// �`��
	C3D_Gage::Draw();
}