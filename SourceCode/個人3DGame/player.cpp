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
#include "player.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define UNDER_BODY			("data/MODEL/PLAYER/00_UnderBody.x")	// �����g
#define BODY				("data/MODEL/PLAYER/01_Body.x")			// �㔼�g
#define HEAD				("data/MODEL/PLAYER/02_Head.x")			// ��
#define SHOULDER_R			("data/MODEL/PLAYER/03_shoulder_R.x")	// �E��
#define UP_ARM_R			("data/MODEL/PLAYER/04_up_arm_R.x")		// �E��r
#define DOWN_ARM_R			("data/MODEL/PLAYER/05_down_arm_R.x")	// �E�O�r	
#define SHOULDER_L			("data/MODEL/PLAYER/06_shoulder_L.x")	// ����
#define UP_ARM_L			("data/MODEL/PLAYER/07_up_arm_L.x")		// ����r
#define DOWN_ARM_L			("data/MODEL/PLAYER/08_down_arm_L.x")	// ���O�r
#define THIGTS_R			("data/MODEL/PLAYER/09_Thigts_R.x")		// �E������
#define KNEE_R				("data/MODEL/PLAYER/10_Knee_R.x")		// �E�G
#define FOOT_R				("data/MODEL/PLAYER/11_foot_R.x")		// �E��
#define THIGTS_L			("data/MODEL/PLAYER/12_Thigts_L.x")		// ��������
#define KNEE_L				("data/MODEL/PLAYER/13_Knee_L.x")		// ���G
#define FOOT_L				("data/MODEL/PLAYER/14_foot_L.x")		// ����
#define MOTION_PLAYER_TEXT	("data/MODEL/PLAYER/Motion/motion.txt") // ���[�V�����̃e�L�X�g
#define LOAD_PLAYER_TEXT	("data/MODEL/PLAYER/Motion/player.txt") // �e���f���p�[�c�̏����l
#define PARENT_NUMBER		(-1)									// �e�̐��l
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH CPlayer::m_pMesh[MAX_PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PLAYER_PARTS] = {};
DWORD CPlayer::m_nNumMat[MAX_PLAYER_PARTS] = {};
D3DXMATRIX CPlayer::m_mtxWorld[MAX_PLAYER_PARTS] = {};
int CPlayer::m_nldxModelParent[MAX_PLAYER_PARTS] = {};
char* CPlayer::m_apFileName[MAX_PLAYER_PARTS] = {
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
CPlayer::CPlayer(int nPriority)
{
	m_pos			= INIT_D3DXVECTOR3;							// �ꏊ
	m_rot			= INIT_D3DXVECTOR3;							// �p�x
	m_size			= INIT_D3DXVECTOR3;							// �傫��
	m_bAllMotion	= false;									// �S���[�V�����̔���
	m_pMotion		= NULL;										// ���[�V�����N���X�̃|�C���^
	memset(m_pModel, NULL, sizeof(m_pModel));					// ���f���N���X�̃|�C���^
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
	pPlayer->SetPlayer(pos, rot);

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
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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

	return E_NOTIMPL;
}

//******************************************************************************
// �ǂݍ��ݔj���֐�
//******************************************************************************
void CPlayer::Unload(void)
{
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// �I���֐�
//******************************************************************************
void CPlayer::Uninit(void)
{
	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
	// ���[�V�����̍X�V����
	m_pMotion->UpdateMotion();

	// �j���[�g�������[�V����
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);


	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// ���f���̃p�[�c���Ƃ̍��W�Ɖ�]���󂯎��
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}
	// ���W�A��]�A�T�C�Y�̃Z�b�g
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

}

//******************************************************************************
// �`��֐�
//******************************************************************************
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// �p�[�c�����J��Ԃ�
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}