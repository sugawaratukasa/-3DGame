//******************************************************************************
// �}�b�v[map.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "floor.h"
#include "floor_block.h"
#include "needle_block.h"
#include "map.h"
//******************************************************************************
//	�}�N����`
//******************************************************************************
#define FLOOR_TEXT	("data/Map/Text/Floor.csv")																		// �}�b�v
#define BLOCK_TEXT	("data/Map/Text/Block.csv")																		// ��
#define FLOOR_SIZE	(D3DXVECTOR3(200.0f,200.0f,200.0f))																// ���̃T�C�Y
#define FLOOR_POS	(D3DXVECTOR3(nCountCol * -FLOOR_SIZE.x + 1000.0f,0.0f,nCountRow * -FLOOR_SIZE.z))				// ���̈ʒu
#define FLOOR_ROT	(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0f))													// ���̌���
#define FLOOR_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))																// �F
#define BLOCK_SIZE	(D3DXVECTOR3(30.0f,30.0f,30.0f))																// �u���b�N�̃T�C�Y
#define BLOCK_POS	(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + 150.0f ,-200.0f))	// �u���b�N�̈ʒu
#define BLOCK_ROT	(D3DXVECTOR3(0.0f,0.0f,0.0f))																	// �u���b�N�̌���
#define NEEDLE_SIZE	(D3DXVECTOR3(30.0f,15.0f,30.0f))																// �j�̃T�C�Y
#define NEEDLE_POS	(D3DXVECTOR3(nCountCol * NEEDLE_SIZE.x - 290.0f,nCountRow * -NEEDLE_SIZE.y * 2 + 150.0f ,-200.0f))	// �u���b�N�̈ʒu
#define BYTE_NUM	(1024)																							// �ő�o�C�g��
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CMap::CMap(int nPriority)
{
	m_apFloorIndex	= NULL;		// �s��
	m_apBlockIndex	= NULL;		// �s��
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

		// NULL�łȂ��ꍇ
		if (pMap != NULL)
		{
			// ������
			pMap->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pMap;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CMap::Init(void)
{
	// �}�b�v����
	MapCreate();

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
// �}�b�v����
//******************************************************************************
void CMap::MapCreate(void)
{
	// ������
	FloorCreate();

	// �u���b�N����
	BlockCreate();
}
//******************************************************************************
// ���̐���
//******************************************************************************
void CMap::FloorCreate(void)
{
	// ���̃e�L�X�g�̍s��̐��ǂݍ���
	SetRowCol(LOAD_TYPE_FLOOR);

	// ���̏��ǂݍ���
	FloorLoad();

	// NULL�łȂ��ꍇ
	if (m_apFloorIndex != NULL)
	{
		// �s����
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// �񕪉�
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apFloorIndex[nCountRow][nCountCol])
				{
					// ��
				case FLOOR_TYPE_GLASS:
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
			delete[] m_apFloorIndex[nCntRow];
		}
		// �������j��
		delete[] m_apFloorIndex;
	}
}
//******************************************************************************
// ���̓ǂݍ���
//******************************************************************************
void CMap::FloorLoad()
{
	// �t�@�C���ǂݍ���
	FILE * pfile = fopen(FLOOR_TEXT, "r");

	// csv�ǂݎ�菈��
	char str[BYTE_NUM];

	// �s
	int nRowIndex = INIT_INT;

	// ��
	int nColIndex = INIT_INT;

	// NULL�łȂ��ꍇ
	if (pfile != NULL)
	{
		if (m_apFloorIndex == NULL)
		{
			// �������m��
			m_apFloorIndex = new FLOOR_TYPE*[m_nRow];

			// NULL�łȂ��ꍇ
			if (m_apFloorIndex != NULL)
			{
				// �s����
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// �񕪉�
					m_apFloorIndex[nCnt] = new FLOOR_TYPE[m_nCol];
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
							m_apFloorIndex[nRowIndex][nColIndex] = (FLOOR_TYPE)atoi(cTokStr);

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
// �u���b�N����
//******************************************************************************
void CMap::BlockCreate(void)
{
	// ���̃e�L�X�g�̍s��̐��ǂݍ���
	SetRowCol(LOAD_TYPE_BLOCK);

	// ���̏��ǂݍ���
	BlockLoad();

	// NULL�łȂ��ꍇ
	if (m_apBlockIndex != NULL)
	{
		// �s����
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// �񕪉�
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apBlockIndex[nCountRow][nCountCol])
				{
					// ��
				case BLOCK_TYPE_NONE:
					break;

					// ��
				case BLOCK_TYPE_NORMAL:
					// ������
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);
					break;

					// �j
				case BLOCK_TYPE_NEEDLE:
					// �j����
					CNeedle_Block::Create(NEEDLE_POS, BLOCK_ROT, NEEDLE_SIZE);
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
			delete[] m_apBlockIndex[nCntRow];
		}
		// �������j��
		delete[] m_apBlockIndex;
	}
}
//******************************************************************************
// �u���b�N�ǂݍ���
//******************************************************************************
void CMap::BlockLoad(void)
{
	// �t�@�C���ǂݍ���
	FILE * pfile = fopen(BLOCK_TEXT, "r");

	// csv�ǂݎ�菈��
	char str[BYTE_NUM];

	// �s
	int nRowIndex = INIT_INT;

	// ��
	int nColIndex = INIT_INT;

	// NULL�łȂ��ꍇ
	if (pfile != NULL)
	{
		if (m_apBlockIndex == NULL)
		{
			// �������m��
			m_apBlockIndex = new BLOCK_TYPE*[m_nRow];

			// NULL�łȂ��ꍇ
			if (m_apBlockIndex != NULL)
			{
				// �s����
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// �񕪉�
					m_apBlockIndex[nCnt] = new BLOCK_TYPE[m_nCol];
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
							m_apBlockIndex[nRowIndex][nColIndex] = (BLOCK_TYPE)atoi(cTokStr);

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
void CMap::SetRowCol(LOAD_TYPE load_type)
{
	FILE * pfile = NULL;

	// NULL�̏ꍇ
	if (pfile == NULL)
	{
		// LOAD_TYPE_FLOOR�̏ꍇ
		if (load_type == LOAD_TYPE_FLOOR)
		{
			pfile = fopen(FLOOR_TEXT, "r");
		}
		// LOAD_TYPE_BLOCK�̏ꍇ
		if (load_type == LOAD_TYPE_BLOCK)
		{
			pfile = fopen(BLOCK_TEXT, "r");
		}

		// �s������
		m_nRow = INIT_INT;

		// �񏉊���
		m_nCol = INIT_INT;

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
}