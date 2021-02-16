//******************************************************************************
// �u���b�N[block.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "input.h"
#include "joystick.h"
#include "model.h"
#include "block.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(2.0f,2.0f,0.0f))	// �ړ���
#define BLOCK_WOOD	("data/Model/Object/box.x")		// �ؔ�
#define BLOCK_STOON	("data/Model/Object/box_2.x")	// �΂̔�
//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH CBlock::m_pMesh[TYPE_MAX] = {};
LPD3DXBUFFER CBlock::m_pBuffMat[TYPE_MAX] = {};
DWORD CBlock::m_nNumMat[TYPE_MAX] = {};
char* CBlock::m_apFileName[TYPE_MAX] = { BLOCK_WOOD, BLOCK_STOON };// ��

//******************************************************************************
//�C���N�������g
//******************************************************************************
CBlock::CBlock(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	m_Type		= TYPE_NONE;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
//�f�N�������g
//******************************************************************************
CBlock::~CBlock()
{

}

//******************************************************************************
//���f���̓ǂݍ���
//******************************************************************************
HRESULT CBlock::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_nNumMat[nCnt],
			&m_pMesh[nCnt]
		);
	}
	return S_OK;
}
//******************************************************************************
//���f���̔j��
//******************************************************************************
void CBlock::Unload(void)
{
	for (int nCnt = INIT_INT; nCnt < TYPE_MAX; nCnt++)
	{
		// ���b�V���̔j��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// �}�e���A���̔j��
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}
		if (m_nNumMat[nCnt] != NULL)
		{
			m_nNumMat[nCnt] = NULL;
		}
	}
}

//******************************************************************************
//����������
//******************************************************************************
HRESULT CBlock::Init(void)
{
	// ���f���̐���
	m_pModel = CModel::Create();

	// ���f���̃o�C���h
	m_pModel->BindModel(m_pMesh[m_Type], m_pBuffMat[m_Type], m_nNumMat[m_Type], -1);

	return S_OK;
}

//******************************************************************************
//�I������
//******************************************************************************
void CBlock::Uninit(void)
{
	if (m_pModel != NULL)
	{
		// ���f���N���X�̏I������
		m_pModel->Uninit();

		m_pModel = NULL;
	}
	// �j��
	Release();
}

//******************************************************************************
//�X�V����
//******************************************************************************
void CBlock::Update(void)
{
	m_pModel->SetModel(m_pos, m_rot, m_size);
}

//******************************************************************************
//�`�揈��
//******************************************************************************
void CBlock::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	m_pModel->SetWorldMatrix(m_mtxWorld);

	// ���f���N���X�̕`�揈��
	m_pModel->Draw();
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CBlock::Move(void)
{
	// �R���g���[���[�擾
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	D3DXVECTOR3 move = INIT_D3DXVECTOR3;

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (g_lpDIDevice != NULL)
	{
		// �E�X�e�B�b�N�����ɓ|��
		if (js.lZ <= -STICK_REACTION)
		{
			move.x = MOVE_VALUE.x;
		}
		// �E�X�e�B�b�N���E�ɓ|��
		if (js.lZ >= STICK_REACTION)
		{
			move.x = -MOVE_VALUE.x;
		}
		// �E�X�e�B�b�N����ɓ|��
		if (js.lRz <= -STICK_REACTION)
		{
			move.y = MOVE_VALUE.y;
		}
		// �E�X�e�B�b�N�����ɓ|��
		if (js.lRz >= STICK_REACTION)
		{
			move.y = -MOVE_VALUE.y;
		}
	}
	// �ړ�
	m_pos.x += move.x;
	m_pos.y += move.y;
}
//******************************************************************************
// �j���֐�
//******************************************************************************
void CBlock::ReleaseBlock(void)
{
	// �j��
	Uninit();

	return;
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;
	m_Type = type;
}