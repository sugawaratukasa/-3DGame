//******************************************************************************
// ���@ [magic.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "particle.h"
#include "magic.h"

//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_TEXT		(1024)									// �e�L�X�g�̍ő吔
#define FIRE_BALL_TEXT	("data/Effect/FireBall_Data.txt")		// �e�L�X�g
#define ICE_BALL_TEXT	("data/Effect/IceBall_Data.txt")		// �e�L�X�g
#define REMAINDER		(0)										// �]��0
#define MAX_LIFE		(150)									// ���C�t�̍ő吔
#define MIN_LIFE		(0)										// ���C�t�̍ŏ���
#define MOVE_VALUE		(2.5f)									// �ړ���
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CMagic::CMagic()
{
	m_pos			= INIT_D3DXVECTOR3;
	m_nCount		= INIT_INT;
	m_nCreateCount	= INIT_INT;
	m_nLife			= INIT_INT;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CMagic::~CMagic()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CMagic * CMagic::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, TYPE type)
{
	// CMagic�̃|�C���^
	CMagic *pMagic;

	// �������m��
	pMagic = new CMagic;

	// �ʒu���
	pMagic->m_pos = pos;

	// �ړ��ʑ��
	pMagic->m_move = move;

	// �ʒu���
	pMagic->m_Type = type;

	// ������
	pMagic->Init();

	// �|�C���^��Ԃ�
	return pMagic;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CMagic::Init(void)
{
	// ���C�t�ݒ�
	m_nLife = MAX_LIFE;

	// �^�C�v
	switch (m_Type)
	{
		// �΋�
	case TYPE_FIRE_BALL:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, FIRE_BALL_TEXT);
		break;
		// �X��
	case TYPE_ICE_BALL:
		// �e�L�X�g�t�@�C���ǂݍ���
		sprintf(m_cText, ICE_BALL_TEXT);
		break;

	}

	// �ǂݍ���
	Load(m_cText);
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CMagic::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CMagic::Update(void)
{
	// �C���N�������g
	m_nCount++;

	// �f�N�������g
	m_nLife--;

	// �]�肪0�̏ꍇ
	if (m_nCount % m_nCreateCount == REMAINDER)
	{
		CParticle::Create(m_pos, m_cText);
	}
	// ���C�t��0�ȉ��ɂȂ�����
	if (m_nLife <= MIN_LIFE)
	{
		// �I��
		Uninit();
		return;
	}

	// �ړ�
	m_pos += m_move;
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CMagic::Draw(void)
{
}
//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
void CMagic::Load(const char * cText)
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