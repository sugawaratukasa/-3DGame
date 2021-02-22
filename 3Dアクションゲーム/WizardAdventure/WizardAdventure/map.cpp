//******************************************************************************
// �}�b�v[map.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "floor.h"
#include "map.h"
//******************************************************************************
//	�}�N����`
//******************************************************************************
#define MAP_TEXT	("data/Map/Text/map.csv")																// �}�b�v
#define FLOOR_SIZE	(D3DXVECTOR3(200.0f,200.0f,200.0f))														// ���̃T�C�Y
#define FLOOR_POS	(D3DXVECTOR3(nCountCol * -FLOOR_SIZE.x + 800.0f,0.0f,nCountRow * -FLOOR_SIZE.z + 0))	// ���̈ʒu
#define FLOOR_ROT	(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0f))											// ���̌���
#define FLOOR_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))														// �F
#define BYTE_NUM	(1024)																					// �ő�o�C�g��
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CMap::CMap(int nPriority)
{
	m_apMapIndex	= NULL;
	m_nRow			= INIT_INT;	// �c
	m_nCol			= INIT_INT;	// ��
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CMap::~CMap()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CMap * CMap::Create(void)
{
	// CMap�̃|�C���^
	CMap *pMap = NULL;

	// NULL�̏ꍇ
	if (pMap == NULL)
	{
		// �������m��
		pMap = new CMap;

		if (pMap != NULL)
		{
			// �s��ݒ�
			pMap->SetRowCol();

			// �}�b�v�ǂݍ���
			pMap->MapLoad();

			// ������
			pMap->Init();
		}
	}
	return pMap;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CMap::Init(void)
{
	// NULL�łȂ��ꍇ
	if (m_apMapIndex != NULL)
	{
		// �s����
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// �񕪉�
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apMapIndex[nCountRow][nCountCol])
				{
					// ��
				case TYPE_FLOOR:
					// ������
					CFloor::Create(FLOOR_POS, FLOOR_ROT, FLOOR_SIZE, FLOOR_COL);
					break;

				default:
					break;
				}
			}
		}
		// �s����
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// �������j��
			delete[] m_apMapIndex[nCntRow];
		}
		// �������j��
		delete[] m_apMapIndex;
	}
	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CMap::Uninit(void)
{
	// �j��
	Release();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CMap::Update(void)
{
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CMap::Draw(void)
{
}
//******************************************************************************
// �}�b�v�ǂݍ���
//******************************************************************************
void CMap::MapLoad(void)
{
	// �t�@�C���ǂݍ���
	FILE * pfile = fopen(MAP_TEXT, "r");

	// csv�ǂݎ�菈��
	char str[BYTE_NUM];

	// �s
	int nRowIndex = INIT_INT;

	// ��
	int nColIndex = INIT_INT;

	// NULL�łȂ��ꍇ
	if (pfile != NULL)
	{
		if (m_apMapIndex == NULL)
		{
			// �������m��
			m_apMapIndex = new TYPE*[m_nRow];

			// NULL�łȂ��ꍇ
			if (m_apMapIndex != NULL)
			{
				// �s����
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// �񕪉�
					m_apMapIndex[nCnt] = new TYPE[m_nCol];
				}
				// ��s�擾
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #���܂܂�Ă���Δ�����
					char cSearchStr = '#';

					// �Ώە���
					strchr(cTokStr, cSearchStr);

					// NULL�ɂȂ�܂�
					while (cTokStr != NULL)
					{
						// #���܂܂�Ă���Δ�����
						char cSearchStr = '#';

						// �Ώە���
						strchr(cTokStr, cSearchStr);

						// �܂܂�Ă��Ȃ�������o��
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// �s��Ƀu���b�N�̃^�C�v���i�[
							m_apMapIndex[nRowIndex][nColIndex] = (TYPE)atoi(cTokStr);

							// ���̗��
							nColIndex++;
						}
						// NULL������
						cTokStr = strtok(NULL, ",");
					}
					// �C���N�������g
					nRowIndex++;

					// 0��
					nColIndex = INIT_INT;
				}
			}
		}
		// �t�@�C�������
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// �s�Ɨ�ݒ�
//******************************************************************************
void CMap::SetRowCol(void)
{
	FILE * pfile = fopen(MAP_TEXT, "r");

	// csv�ǂݎ�菈��
	char str[BYTE_NUM];

	// �s
	int nRowIndex = INIT_INT;

	// ��
	int nColIndex = INIT_INT;

	// NULL�łȂ��ꍇ
	if (pfile != NULL)
	{
		// ��s�擾
		while (fgets(str, BYTE_NUM, pfile) != NULL)
		{
			char * cTokStr;

			cTokStr = strtok(str, ",");

			// NULL�ɂȂ�܂�
			while (cTokStr != NULL)
			{
				// #���܂܂�Ă���Δ�����
				char cSearchStr = '#';

				// �Ώە���
				strchr(cTokStr, cSearchStr);

				// �܂܂�Ă��Ȃ�������o��
				if (strchr(cTokStr, cSearchStr) == NULL)
				{
					// ���̗��
					nColIndex++;
				}

				// NULL������
				cTokStr = strtok(NULL, ",");
			}
			// ��ۑ�
			m_nCol = nColIndex;

			// 0��
			nColIndex = INIT_INT;

			// �C���N�������g
			nRowIndex++;

			// �s�ۑ�
			m_nRow = nRowIndex;
		}
		// �t�@�C�������
		fclose(pfile);
	}
	else
	{
		return;
	}
}