//******************************************************************************
// �v���C���[�̏��� [player.h]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "model.h"
#include "joystick.h"
#include "block.h"
#include "stone_block.h"
#include "frame.h"
#include "collision.h"
#include "3d_obj.h"
#include "player.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define UNDER_BODY			("data/MODEL/PLAYER/00_UnderBody.x")		// �����g
#define BODY				("data/MODEL/PLAYER/01_Body.x")				// �㔼�g
#define HEAD				("data/MODEL/PLAYER/02_Head.x")				// ��
#define SHOULDER_R			("data/MODEL/PLAYER/03_shoulder_R.x")		// �E��
#define UP_ARM_R			("data/MODEL/PLAYER/04_up_arm_R.x")			// �E��r
#define DOWN_ARM_R			("data/MODEL/PLAYER/05_down_arm_R.x")		// �E�O�r	
#define SHOULDER_L			("data/MODEL/PLAYER/06_shoulder_L.x")		// ����
#define UP_ARM_L			("data/MODEL/PLAYER/07_up_arm_L.x")			// ����r
#define DOWN_ARM_L			("data/MODEL/PLAYER/08_down_arm_L.x")		// ���O�r
#define THIGTS_R			("data/MODEL/PLAYER/09_Thigts_R.x")			// �E������
#define KNEE_R				("data/MODEL/PLAYER/10_Knee_R.x")			// �E�G
#define FOOT_R				("data/MODEL/PLAYER/11_foot_R.x")			// �E��
#define THIGTS_L			("data/MODEL/PLAYER/12_Thigts_L.x")			// ��������
#define KNEE_L				("data/MODEL/PLAYER/13_Knee_L.x")			// ���G
#define FOOT_L				("data/MODEL/PLAYER/14_foot_L.x")			// ����
#define MOTION_PLAYER_TEXT	("data/MODEL/PLAYER/Motion/motion.txt")		// ���[�V�����̃e�L�X�g
#define LOAD_PLAYER_TEXT	("data/MODEL/PLAYER/Motion/player.txt")		// �e���f���p�[�c�̏����l
#define BLOCK_POS			(D3DXVECTOR3(m_pos.x,m_pos.y + 80,m_pos.z))	// �������ʒu
#define BLOCK_ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))				// ���̌���
#define BLOCK_SIZE			(D3DXVECTOR3(30.0f,30.0f,30.0f))			// ���̃T�C�Y
#define MOVE_VALUE			(D3DXVECTOR3(2.0f,2.0f,2.0f))				// �ړ���
#define RIGHT_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))// ����
#define LEFT_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))// ����
#define MIN_BLOCK_NUM		(0)											// �u���b�N�̍ŏ���
#define ARRAY_FIRST_NUM		(0)											// �z��̐擪
#define ARRAY_MOVE_NUMBER	(1)											// �z��̈ړ�
#define ARRAY_SUB_VALUE		(1)											// �z��ɍ��킹�邽�߂̒l
#define DEVIDE_VALUE		(2.0f)										// ���鐔
#define PARENT_NUMBER		(-1)										// �e�̐��l
#define ROT_MOVE			(0.2f)										// �����̈ړ�
#define POW_VALUE			(2.0f)										// ���
#define MIN_MOVE_VALUE		(0.0f)										// �ړ��ʂ̍ŏ��l
#define GRAVITY_VALUE		(-1.5f)										// �d��
#define JUMP_VALUE			(21.5f)										// �W�����v��
#define JUMP_VALUE_2		(0.1f)										// �W�����v��
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH CPlayer::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[PARTS_MAX] = {};
DWORD CPlayer::m_nNumMat[PARTS_MAX] = {};
D3DXMATRIX CPlayer::m_mtxWorld[PARTS_MAX] = {};
int CPlayer::m_nldxModelParent[PARTS_MAX] = {};
char* CPlayer::m_apFileName[PARTS_MAX] = {
	UNDER_BODY,
	BODY,
	HEAD,
	SHOULDER_R,
	UP_ARM_R,
	DOWN_ARM_R,
	SHOULDER_L,
	UP_ARM_L,
	DOWN_ARM_L,
	THIGTS_R,
	KNEE_R,
	FOOT_R,
	THIGTS_L,
	KNEE_L,
	FOOT_L,
};
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_pos					= INIT_D3DXVECTOR3;		
	m_posOld				= INIT_D3DXVECTOR3;		
	m_rot					= INIT_D3DXVECTOR3;		
	m_size					= INIT_D3DXVECTOR3;		
	m_move					= INIT_D3DXVECTOR3;		
	m_bAllMotion			= false;				
	m_pMotion				= NULL;					
	m_pBlock				= NULL;	
	m_pStoneBlock			= NULL;
	m_Blcok_Active			= BLOCK_ACTIVE_NONE;	
	m_nBlockNum				= INIT_INT;				
	m_nBlock_Select_Num		= INIT_INT;				
	m_bStick				= false;				
	m_Rot_State				= ROT_STATE_RIGHT;		
	m_bJump					= false;				
	m_bJumpValue			= false;
	memset(m_pModel, NULL, sizeof(m_pModel));		
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPlayer::~CPlayer()
{

}

//******************************************************************************
// �����֐�
//******************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CPlayer�̃|�C���^
	CPlayer *pPlayer;

	// �������m��
	pPlayer = new CPlayer;

	// ���ݒ�
	pPlayer->SetPlayer(pos, rot, size);

	// ������
	pPlayer->Init();

	// �|�C���^��Ԃ�
	return pPlayer;
}

//******************************************************************************
// �ǂݍ��݊֐�
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFileName[nCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCount],
			NULL,
			&m_nNumMat[nCount],
			&m_pMesh[nCount]
		);
	}
	
	return S_OK;
}

//******************************************************************************
// �ǂݍ��ݔj���֐�
//******************************************************************************
void CPlayer::Unload(void)
{
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// ���b�V���̔j��
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}

		// �}�e���A���̔j��
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}

		if (m_nNumMat[nCount] != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPlayer::Init(void)
{
	// ���[�V�����̐���
	m_pMotion = CMotion::Create();

	// ���[�V�����̓ǂݍ���
	m_pMotion->Load(LOAD_PLAYER_TEXT);
	m_pMotion->LoadMotion(MOTION_PLAYER_TEXT);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// ���f���̐���
		m_pModel[nCount] = CModel::Create();

		// �y�A�����g�̎󂯎��
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// ���f���̃o�C���h
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount]);

		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer::Uninit(void)
{
	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		if (m_pModel[nCount] != NULL)
		{
			// ���f���N���X�̏I������
			m_pModel[nCount]->Uninit();
			m_pModel[nCount] = NULL;
		}
	}
	// NULL�`�F�b�N
	if (m_pMotion != NULL)
	{
		// ���[�V�����N���X�̏I������
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	// �����[�X
	Release();
}

//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPlayer::Update(void)
{
	// �ʒu���
	m_posOld = m_pModel[PARTS_UNDER_BODY]->GetPos();

	// �R���g���[���[�擾
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
	}

	// ���[�V�����̍X�V����
	m_pMotion->UpdateMotion();

	// NULL�łȂ��ꍇ
	if (m_pBlock != NULL)
	{
		// �E�����̏ꍇ
		if (m_Rot_State == ROT_STATE_RIGHT)
		{
			// LT���������ꍇ
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
			{

				// 0��
				m_nBlock_Select_Num = MIN_BLOCK_NUM;

				// �I�𒆂̏�Ԃ�
				m_Blcok_Active = BLOCK_ACTIVE_SELECT;
			}
			// �I�𒆂̏�Ԃ̏ꍇ
			if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
			{
				// ���̑I������
				RightSelectionBlock();
			}
			// �u���b�N�ŉ������Ă��Ȃ����
			if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
			{
				// �E�����̎��u���b�N���ł��߂��u���b�N��I�𒆂ɂ��鏈��
				RightSelectBlock();
			}
			// ���̏���
			RightBlock();
		}
		// �������̏ꍇ
		if (m_Rot_State == ROT_STATE_LEFT)
		{
			// LT���������ꍇ
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
			{
				// 0��
				m_nBlock_Select_Num = MIN_BLOCK_NUM;

				// �I�𒆂̏�Ԃ�
				m_Blcok_Active = BLOCK_ACTIVE_SELECT;
			}
			// �I�𒆂̏�Ԃ̏ꍇ
			if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
			{
				// ���̑I������
				LeftSelectionBlock();
			}
			// �u���b�N�ŉ������Ă��Ȃ����
			if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
			{
				// �������̎��u���b�N���ł��߂��u���b�N��I�𒆂ɂ��鏈��
				LeftSelectBlock();
			}
			// ���̏���
			LeftBlock();
		}
	}
	// X�{�^���������ꂽ�ꍇ
	if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_X))
	{
		// �u���b�N����
		Block_Crate();
	}
	// �u���b�N�I�𒆂łȂ��ꍇ
	if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
	{
		// �ړ�����
		Move();
	}

	// �p�[�c������
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	// �����蔻��
	Collision();
}

//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		//���[���h�}�g���N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld[nCount]);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxTrans);

		// �e�̃��f���p�[�c�ȊO�̃y�A�����g���Z�b�g
		if (m_nldxModelParent[nCount] != PARENT_NUMBER)
		{
			m_pModel[nCount]->SetParent(m_pModel[m_nldxModelParent[nCount]]);
		}

		// ���f���N���X�̕`�揈��
		m_pModel[nCount]->Draw();
	}
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot ,D3DXVECTOR3 size)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	// �I�u�W�F�N�g�^�C�v�ݒ�
	SetObjType(OBJTYPE_PLAYER);
}
//******************************************************************************
// �ʒu�ݒ�
//******************************************************************************
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// ���̑I��
//******************************************************************************
void CPlayer::RightSelectBlock(void)
{
	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
				if (m_pos.x > BlockPos.x)
				{
					// �C���N�������g
					m_nBlockNum++;
				}
				// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
				if (m_pos.x < BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);
					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �v���C���[���E�������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
							if (m_pos.x > BlockPos.x)
							{
								// �|�C���^���
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// �C���N�������g
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// float�̃|�C���^
				float *anLength = NULL;

				// NULL�̏ꍇ
				if (anLength == NULL)
				{
					// �������m��
					anLength = new float[m_nBlockNum];
					// NULL�łȂ��ꍇ
					if (anLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();
							// �v���C���[�Ƃ̋���
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// �������j��
					delete[]anLength;

					// NULL��
					anLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->UnSelected();
				}

				// �z��̐擪����
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}
	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// �u���b�N�����֐�
//******************************************************************************
void CPlayer::RightBlock(void)
{
	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULL�łȂ��ꍇ
	if (m_pBlock != NULL)
	{
		// ���̈ʒu�擾
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// �v���C���[���E�������Ă��Ĕ��̈ʒu�����ɂ���ꍇ
		if (m_pos.x < BlockPos.x)
		{
			// �I���O��
			m_pBlock->UnSelected();

			// �u���b�N���ړ���Ԃ�
			m_Blcok_Active = BLOCK_ACTIVE_NONE;
		}
		// �v���C���[���E�������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
		if (m_pos.x > BlockPos.x)
		{
			// �I�𒆂̏ꍇ
			m_pBlock->Selecting();

			// �I����ԈȊO�̏ꍇ
			if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
			{
				// RT���������ꍇ
				if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
				{
					// �ړ���Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// �u���b�N�̈ړ�
					m_pBlock->Move();
				}
			}
		}
	}
}
//******************************************************************************
// �������u���b�N��I��
//******************************************************************************
void CPlayer::RightSelectionBlock(void)
{
	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
				if (m_pos.x > BlockPos.x)
				{
					// �C���N�������g
					m_nBlockNum++;
				}
				// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
				if (m_pos.x < BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	// 0��葽���ꍇ
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �v���C���[���E�������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
							if (m_pos.x > BlockPos.x)
							{
								// �|�C���^���
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// �C���N�������g
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// float�̃|�C���^
				float *anLength = NULL;

				// NULL�̏ꍇ
				if (anLength == NULL)
				{
					// �������m��
					anLength = new float[m_nBlockNum];

					// NULL�łȂ��ꍇ
					if (anLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// �v���C���[�Ƃ̋���
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (anLength[nCnt] > anLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							anLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// �������j��
					delete[]anLength;

					// NULL��
					anLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->PlayerSelection();
				}
				// �I���I����ԂłȂ��ꍇ
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0�ԖڈȊO���I����Ԃ�
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// �I���I���̐F��
						apBlock[nCnt]->UnSelected();
					}

					// �I���������
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// �F�I�𒆂̐F��
				apBlock[m_nBlock_Select_Num]->Selecting();

				// �I�����Ă���u���b�N�̔z�����
				m_pBlock = apBlock[m_nBlock_Select_Num];
			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}

	// ���ۑ�
	m_nSelect_Save_Num = m_nBlockNum;

	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// false�̏ꍇ
		if (m_bStick == false)
		{
			// �E�X�e�B�b�N�����ɓ|��
			if (js.lZ >= STICK_REACTION)
			{
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// �f�N�������g
					m_nBlock_Select_Num--;
				}
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// �u���b�N�̍ő�l�ɂ���
					//m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;

					// �u���b�N�̍ő�l�ɂ���
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}

				// true��
				m_bStick = true;
			}
			// �E�X�e�B�b�N���E�ɓ|��
			if (js.lZ <= -STICK_REACTION)
			{
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// �C���N�������g
					m_nBlock_Select_Num++;
				}
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0�Ԗڂɐݒ�
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}

				// true��
				m_bStick = true;
			}
		}
		// true�̏ꍇ
		if (m_bStick == true)
		{
			// -500���傫��0��菬�����ꍇ
			if (js.lZ > -STICK_REACTION && js.lZ <= INIT_INT)
			{
				m_bStick = false;
			}
			// 500��菬����0���傫���ꍇ
			if (js.lZ < STICK_REACTION && js.lZ >= INIT_INT)
			{
				m_bStick = false;
			}
		}
		// 0���Ⴂ�ꍇ
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0�ɐݒ�
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// ���̐����傫���ꍇ
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// ���̐��Ɠ����ɂ���
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// �����̑I��
//******************************************************************************
void CPlayer::LeftSelectBlock(void)
{
	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();
			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �v���C���[�����������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
				if (m_pos.x < BlockPos.x)
				{
					// �C���N�������g
					m_nBlockNum++;
				}
				// �v���C���[�����������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
				if (m_pos.x > BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);
					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �v���C���[���E�������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
							if (m_pos.x < BlockPos.x)
							{
								// �|�C���^���
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// �C���N�������g
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// float�̃|�C���^
				float *anLength = NULL;

				// NULL�̏ꍇ
				if (anLength == NULL)
				{
					// �������m��
					anLength = new float[m_nBlockNum];
					// NULL�łȂ��ꍇ
					if (anLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();
							// �v���C���[�Ƃ̋���
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// �������j��
					delete[]anLength;

					// NULL��
					anLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->UnSelected();
				}

				// �z��̐擪����
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}
	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// �u���b�N�����֐�
//******************************************************************************
void CPlayer::LeftBlock(void)
{
	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULL�łȂ��ꍇ
	if (m_pBlock != NULL)
	{
		// ���̈ʒu�擾
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// �v���C���[�����������Ă��Ĕ��̈ʒu�����ɂ���ꍇ
		if (m_pos.x > BlockPos.x)
		{
			// �I���O��
			m_pBlock->UnSelected();

			// �u���b�N���ړ���Ԃ�
			m_Blcok_Active = BLOCK_ACTIVE_NONE;
		}
		// �v���C���[�����������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
		if (m_pos.x < BlockPos.x)
		{
			// �I�𒆂̏ꍇ
			m_pBlock->Selecting();

			// �I����ԈȊO�̏ꍇ
			if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
			{
				// RT���������ꍇ
				if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
				{
					// �ړ���Ԃ�
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// �u���b�N�̈ړ�
					m_pBlock->Move();
				}
			}
		}
	}
}
//******************************************************************************
// �������u���b�N��I��
//******************************************************************************
void CPlayer::LeftSelectionBlock(void)
{
	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// ��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
				if (m_pos.x < BlockPos.x)
				{
					// �C���N�������g
					m_nBlockNum++;
				}
				// �v���C���[�����ʂ������Ă��Ĕ��̈ʒu���O���ɂ���ꍇ
				if (m_pos.x > BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	// 0��葽���ꍇ
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULL��
		CBlock **apBlock = NULL;

		// NULL�̏ꍇ
		if (apBlock == NULL)
		{
			// �������m��
			apBlock = new CBlock*[m_nBlockNum];

			// �ŏ�����
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULL�łȂ��ꍇ
			if (apBlock != NULL)
			{
				do
				{
					// �I�u�W�F�^�C�v���G�̏ꍇ
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULL�łȂ��ꍇ
					if (pScene != NULL)
					{
						// �I�u�W�F�N�g�^�C�v�擾
						OBJTYPE objType = pScene->GetObjType();

						// �I�u�W�F�N�g�^�C�v��BLOCK�̏ꍇ
						if (objType == OBJTYPE_BLOCK)
						{
							// ���W�ƃT�C�Y�擾
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// �v���C���[�����������Ă��Ĕ��̈ʒu���O�ɂ���ꍇ
							if (m_pos.x < BlockPos.x)
							{
								// �|�C���^���
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// �C���N�������g
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// float�̃|�C���^
				float *afLength = NULL;

				// NULL�̏ꍇ
				if (afLength == NULL)
				{
					// �������m��
					afLength = new float[m_nBlockNum];

					// NULL�łȂ��ꍇ
					if (afLength != NULL)
					{
						// �u���b�N������
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// �ʒu���W
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// �v���C���[�Ƃ̋���
							afLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// �z��̐擪
						int nFirst_Array;

						// �ŏ��l
						int nMin_Length;

						// �ꎞ�ۑ�
						float fArray_Move;

						// �ꎞ�ۑ�
						CBlock *pBlock_Save;

						// �u���b�N������
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum; nFirst_Array++)
						{
							// �z��̐擪���ŏ��l��
							nMin_Length = nFirst_Array;

							// ��r
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// �������ŏ��l���߂��ꍇ
								if (afLength[nCnt] > afLength[nMin_Length])
								{
									// ���
									nMin_Length = nCnt;
								}
							}
							// �擪�̔z��̒l����ۑ�
							fArray_Move = afLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// �擪�̔z��ɍŏ��l���
							afLength[nFirst_Array] = afLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// �ŏ��l�Ɍ��̐擪�̒l����
							afLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// �������j��
					delete[]afLength;

					// NULL��
					afLength = NULL;
				}
				// 0�ԖڈȊO���I����Ԃ�
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// ���I����Ԃ�
					apBlock[nCnt]->PlayerSelection();
				}
				// �I���I����ԂłȂ��ꍇ
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0�ԖڈȊO���I����Ԃ�
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// �I���I���̐F��
						apBlock[nCnt]->UnSelected();
					}

					// �I���������
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// �F�I�𒆂̐F��
				apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num]->Selecting();

				// �I�����Ă���u���b�N�̔z�����
				m_pBlock = apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num];
			}
			// �������j��
			delete[]apBlock;

			// NULL��
			apBlock = NULL;
		}
	}

	// ���ۑ�
	m_nSelect_Save_Num = m_nBlockNum;

	// �ŏ�����
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// false�̏ꍇ
		if (m_bStick == false)
		{
			// �E�X�e�B�b�N�����ɓ|��
			if (js.lZ >= STICK_REACTION)
			{
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// �C���N�������g
					m_nBlock_Select_Num++;
				}
				// �ő�l�̏ꍇ
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0�Ԗڂɐݒ�
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}
				// true��
				m_bStick = true;
			}
			// �E�X�e�B�b�N���E�ɓ|��
			if (js.lZ <= -STICK_REACTION)
			{
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// �f�N�������g
					m_nBlock_Select_Num--;
				}
				// 0�Ԗڂ̏ꍇ
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// �u���b�N�̍ő�l�ɂ���
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}
				// true��
				m_bStick = true;
			}
		}
		// true�̏ꍇ
		if (m_bStick == true)
		{
			// -500���傫��0��菬�����ꍇ
			if (js.lZ > -STICK_REACTION && js.lZ <= 0)
			{
				m_bStick = false;
			}
			// 500��菬����0���傫���ꍇ
			if (js.lZ < STICK_REACTION && js.lZ >= 0)
			{
				m_bStick = false;
			}
		}
		// 0�������ꍇ
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0�ɐݒ�
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// ���̐����傫���ꍇ
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// ���̐��Ɠ����ɂ���
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// �u���b�N�����֐�
//******************************************************************************
void CPlayer::Block_Crate(void)
{
	// NULL�̏ꍇ
	if (m_pStoneBlock == NULL)
	{
		// ����
		m_pStoneBlock = CStone_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);

		// ���
		m_pBlock = m_pStoneBlock;
	}
	// NULL�łȂ��ꍇ
	if (m_pStoneBlock != NULL)
	{
		// �j��
		m_pStoneBlock->ReleaseBlock();

		// ����
		m_pStoneBlock = CStone_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);

		// ���
		m_pBlock = m_pStoneBlock;
	}
}												   
//******************************************************************************
// �����蔻�菈���֐�
//******************************************************************************
void CPlayer::Collision(void)
{
	// �ʒu
	D3DXVECTOR3 pos = m_pModel[PARTS_UNDER_BODY]->GetPos();

	// �u���b�N�Ƃ̓����蔻��
	CScene *pScene = NULL;
	do
	{
		// �I�u�W�F�^�C�v���u���b�N�̏ꍇ
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_BLOCK)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				 //�ǂ��̖ʂɓ����������擾
				 //��
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (m_size.y / DEVIDE_VALUE) - (BlockPos.y + BlockSize.y / DEVIDE_VALUE);
				}
				// ��
				else if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (-m_size.y / DEVIDE_VALUE) + (BlockPos.y + BlockSize.y / DEVIDE_VALUE);

					// true�̏ꍇ
					if (m_bJump == true)
					{
						// false��
						m_bJump = false;
					}
				}
				// ��
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (-m_size.x / DEVIDE_VALUE) + (BlockPos.x - BlockSize.x / DEVIDE_VALUE);
				}
				// �E
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (m_size.x / DEVIDE_VALUE) + (BlockPos.x + BlockSize.x / DEVIDE_VALUE);

				}
			}
		}
	} while (pScene != NULL);

	// 3D�I�u�W�F�N�g�Ƃ̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���u���b�N�̏ꍇ
		pScene = GetScene(OBJTYPE_MAP_OBJ);

		// NULL�`�F�b�N
		if (pScene != NULL)
		{
			// �I�u�W�F�^�C�v�擾
			OBJTYPE objType = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���G
			if (objType == OBJTYPE_MAP_OBJ)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 ObjPos = ((C3D_Obj*)pScene)->GetPos();
				D3DXVECTOR3 ObjSize = ((C3D_Obj*)pScene)->GetSize();
				//�ǂ��̖ʂɓ����������擾
				//��
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (m_size.y / DEVIDE_VALUE) - (ObjPos.y + ObjSize.y / DEVIDE_VALUE);

				}
				// ��
				if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_UP)
				{
					// �ړ���0
					m_move.y = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.y = (-m_size.y / DEVIDE_VALUE) + (ObjPos.y + ObjSize.y / DEVIDE_VALUE);

					// true�̏ꍇ
					if (m_bJump == true)
					{
						// false��
						m_bJump = false;

						// false��
						m_bJumpValue = false;
					}
				}
				// ��
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (-m_size.x / DEVIDE_VALUE) + (ObjPos.x - ObjSize.x / DEVIDE_VALUE);
				}
				// �E
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// �ړ���0
					m_move.x = MIN_MOVE_VALUE;

					// �ʒu
					m_pos.x = (m_size.x / DEVIDE_VALUE) + (ObjPos.x + ObjSize.x / DEVIDE_VALUE);

				}
			}
		}
		// pScene��NULL�̏ꍇ
	} while (pScene != NULL);
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CPlayer::Move(void)
{
	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// �ړI�̌���
	D3DXVECTOR3 RotDest = m_rot;

	if (g_lpDIDevice != NULL)
	{
		// ��
		if (js.lX <= -STICK_REACTION)
		{
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				if (m_pBlock != NULL)
				{
					if (m_Rot_State == ROT_STATE_RIGHT)
					{
						// �ړ����[�V����
						m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

						// ���
						m_move.x = -MOVE_VALUE.x;

						// ����
						RotDest.y = RIGHT_ROT.y;
					}
					if (m_Rot_State == ROT_STATE_LEFT)
					{
						// �ړ����[�V����
						m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

						// ���
						m_move.x = MOVE_VALUE.x / DEVIDE_VALUE;

						// ����
						RotDest.y = RIGHT_ROT.y;
					}
				}
			}
			else
			{
				// �ړ����[�V����
				m_pMotion->SetMotion(CMotion::MOTION_RUN);

				// ���
				m_move.x = -MOVE_VALUE.x;

				// ����
				RotDest.y = RIGHT_ROT.y;

				// �������̏��
				m_Rot_State = ROT_STATE_RIGHT;
			}
		}
		// �E
		if (js.lX >= STICK_REACTION)
		{
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				if (m_pBlock != NULL)
				{
					if (m_Rot_State == ROT_STATE_LEFT)
					{
						// �ړ����[�V����
						m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

						// ���
						m_move.x = MOVE_VALUE.x;

						// ����
						RotDest.y = LEFT_ROT.y;
					}
					if (m_Rot_State == ROT_STATE_RIGHT)
					{
						// �ړ����[�V����
						m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

						// ���
						m_move.x = -MOVE_VALUE.x / DEVIDE_VALUE;

						// ����
						RotDest.y = LEFT_ROT.y;
					}
				}
			}
			else
			{
				// �ړ����[�V����
				m_pMotion->SetMotion(CMotion::MOTION_RUN);

				// �O�ɐi��
				m_move.x = MOVE_VALUE.x;

				// ����
				RotDest.y = LEFT_ROT.y;

				// �E�����̏��
				m_Rot_State = ROT_STATE_LEFT;
			}
		}
		// �X�e�B�b�N�͈̔͊O�̏ꍇ
		if (js.lX > -STICK_REACTION && js.lX < STICK_REACTION)
		{
			// �ړ���0
			m_move.x = MIN_MOVE_VALUE;

			// �j���[�g�������[�V����
			m_pMotion->SetMotion(CMotion::MOTION_IDLE);
		}
		// �W�����v
		if (m_bJump == false)
		{
			// A�{�^�����������ꍇ
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
			{
				// false�̏ꍇ
				if (m_bJumpValue == false)
				{
					// �ړ�
					m_move.y += JUMP_VALUE;

					m_bJumpValue = true;
				}
				// true�̏ꍇ
				if (m_bJumpValue == true)
				{
					// �ړ�
					m_move.y += JUMP_VALUE_2;
				}

				// true��
				m_bJump = true;
			}
		}
	}

	// ����
	m_rot += (RotDest - m_rot) * ROT_MOVE;

	// �d��
	m_move.y += GRAVITY_VALUE;

	// �ړ�
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
}