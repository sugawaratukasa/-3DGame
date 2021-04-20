//******************************************************************************
// �p�[�e�B�N���G�~�b�^�[ [particle_emitter.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "player.h"
#include "scene.h"
#include "particle.h"
#include "particle_emitter.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define STAR_EMITTER_TEXT	("data/Effect/StarEmitter01_Data.txt")		// �e�L�X�g�̃p�X
#define FIRE_EMITTER_TEXT	("data/Effect/FireEmitter_Data.txt")		// �e�L�X�g�̃p�X
#define ICE_EMITTER_TEXT	("data/Effect/IceEmitter_Data.txt")			// �e�L�X�g�̃p�X
#define FIREGHOST_TEXT		("data/Effect/FireGhostEmitter_Data.txt")	// �e�L�X�g�̃p�X
#define ICEGHOST_TEXT		("data/Effect/IceGhostEmitter_Data.txt")	// �e�L�X�g�̃p�X
#define REMAINDER			(0)											// �]��0
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CParticle_Emitter::CParticle_Emitter()
{
	m_pos				= INIT_D3DXVECTOR3;
	m_nCount			= INIT_INT;
	m_nCreateCount		= INIT_INT;
	memset(m_cText, NULL, sizeof(m_cText));
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CParticle_Emitter::~CParticle_Emitter()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CParticle_Emitter * CParticle_Emitter::Create(D3DXVECTOR3 pos, TYPE type)
{
	// CParticle_Emitter�̃|�C���^
	CParticle_Emitter *pParticle_Emitter;

	// �������m��
	pParticle_Emitter = new CParticle_Emitter;

	// �ʒu���
	pParticle_Emitter->m_pos = pos;

	// �ʒu���
	pParticle_Emitter->m_Type = type;

	// ������
	pParticle_Emitter->Init();

	// �|�C���^��Ԃ�
	return pParticle_Emitter;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CParticle_Emitter::Init(void)
{
	// �^�C�v
	switch (m_Type)
	{
	case TYPE_STAR_RIGHT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, STAR_EMITTER_TEXT);
		break;
	case TYPE_STAR_LEFT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, STAR_EMITTER_TEXT);
		break;
	case TYPE_FIRE_RIGHT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
	case TYPE_FIRE_LEFT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIRE_EMITTER_TEXT);
		break;
	case TYPE_ICE_RIGHT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
	case TYPE_ICE_LEFT:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICE_EMITTER_TEXT);
		break;
	case TYPE_FIRE_GHOST:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIREGHOST_TEXT);
		break;
	case TYPE_ICE_GHOST:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICEGHOST_TEXT);
		break;
	}

	// �ǂݍ���
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CParticle_Emitter::Uninit(void)
{
	// �j��
	CScene::Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CParticle_Emitter::Update(void)
{
	// ��������
	CreateParticle();

	// �^�C�v���E�̏ꍇ
	if (m_Type == TYPE_STAR_RIGHT || m_Type == TYPE_FIRE_RIGHT || m_Type == TYPE_ICE_RIGHT)
	{
		// ���̏���
		Right_Arm();
	}
	// �^�C�v�����̏ꍇ
	if (m_Type == TYPE_STAR_LEFT || m_Type == TYPE_FIRE_LEFT || m_Type == TYPE_ICE_LEFT)
	{
		// ���̏���
		Left_Arm();
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CParticle_Emitter::Draw(void)
{
}
//******************************************************************************
// �j���֐�
//******************************************************************************
void CParticle_Emitter::Release(void)
{
	// �I��
	Uninit();
	return;
}
//******************************************************************************
// �ʒu�ݒ�֐�
//******************************************************************************
void CParticle_Emitter::SetPos(D3DXVECTOR3 pos)
{
	// �ʒu���
	m_pos = pos;
}
//******************************************************************************
// �p�[�e�B�N�����������֐�
//******************************************************************************
void CParticle_Emitter::CreateParticle(void)
{
	// �C���N�������g
	m_nCount++;

	// �]�肪0�̏ꍇ
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		CParticle::Create(m_pos, m_cText);
	}
}
//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
void CParticle_Emitter::Load(const char * cText)
{
	// �ǂݍ��ݗp
	char cReedText[MAX_TEXT];

	// �����̔��ʗp
	char cHeadText[MAX_TEXT];

	// �g��Ȃ�����
	char cDie[MAX_TEXT];

	// �t�@�C���|�C���^
	FILE *pFile = NULL;

	// NULL�̏ꍇ
	if (pFile == NULL)
	{
		//�t�@�C�����J��
		pFile = fopen(cText, "r");

		// NULL�łȂ��ꍇ
		if (pFile != NULL)
		{
			// SCRIPT�̕�����������܂�
			while (strcmp(cHeadText, "SCRIPT") != INIT_INT)
			{
				// �e�L�X�g����cReedText��������ǂݍ���
				fgets(cReedText, sizeof(cReedText), pFile);

				// �ǂݍ��񂾕�������cHeadText�Ɋi�[
				sscanf(cReedText, "%s", &cHeadText);
			}
			// cHeadText��SCRIPT��������
			if (strcmp(cHeadText, "SCRIPT") == INIT_INT)
			{
				// END_SCRIPT�̕�����������܂�
				while (strcmp(cHeadText, "END_SCRIPT") != INIT_INT)
				{
					// �e�L�X�g����cReedText��������ǂݍ���
					fgets(cReedText, sizeof(cReedText), pFile);

					// �ǂݍ��񂾕�������cHeadText�Ɋi�[
					sscanf(cReedText, "%s", &cHeadText);

					// cHeadText��MOTIONSET��������
					if (strcmp(cHeadText, "SETTINGS") == INIT_INT)
					{
						// END_MOTIONSET�̕�����������܂�
						while (strcmp(cHeadText, "END_SETTINGS") != INIT_INT)
						{
							// �e�L�X�g����cReedText��������ǂݍ���
							fgets(cReedText, sizeof(cReedText), pFile);

							// �ǂݍ��񂾕�������cHeadText�Ɋi�[
							sscanf(cReedText, "%s", &cHeadText);

							// cHeadText��ALPHA_BLEND�̏ꍇ
							if (strcmp(cHeadText, "CREATE_COUNT") == INIT_INT)
							{
								// ����m_bAlpha_Blend�Ɋi�[
								sscanf(cReedText, "%s %s %d", &cDie, &cDie, &m_nCreateCount);
							}
						}
					}
				}
				// �t�@�C�������
				fclose(pFile);
			}
			// �J���Ȃ�������
			else
			{
				printf("�t�@�C�����J�������o���܂���ł����B\n");
			}
		}
	}
}
//******************************************************************************
// �E��̏����֐�
//******************************************************************************
void CParticle_Emitter::Right_Arm(void)
{
	// �ʒu
	D3DXVECTOR3 pos;

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�擾
	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v�v���C���[
			if (objtype == OBJTYPE_PLAYER)
			{
				// �ʒu�擾
				pos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._41;
				pos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._42;
				pos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_R)._43;

				// �ʒu���
				m_pos = pos;
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);
}
//******************************************************************************
// ����̏����֐�
//******************************************************************************
void CParticle_Emitter::Left_Arm(void)
{
	// �ʒu
	D3DXVECTOR3 pos;

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�擾
	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v�v���C���[
			if (objtype == OBJTYPE_PLAYER)
			{
				// �ʒu�擾
				pos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._41;
				pos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._42;
				pos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_DOWN_ARM_L)._43;

				// �ʒu���
				m_pos = pos;
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);
}