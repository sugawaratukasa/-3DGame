//******************************************************************************
// �e�X�g���f��[test_model.cpp]
// Author : �ǌ� �i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "test_model.h"
#include "input.h"
#include "joystick.h"
#include "model.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(2.0f,2.0f,0.0f))	// �ړ���
//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH CTestModel::m_pMesh = NULL;
LPD3DXBUFFER CTestModel::m_pBuffMat = NULL;
DWORD CTestModel::m_nNumMat = NULL;
char* CTestModel::m_apFileName = { "data/Model/Object/box.x" };// ��
LPDIRECT3DTEXTURE9 CTestModel::m_pTexture[MAX_MATERIAL] = {};

//******************************************************************************
//�C���N�������g
//******************************************************************************
CTestModel::CTestModel(int nPriority) :CScene(nPriority)
{
	m_pos		= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_size		= INIT_D3DXVECTOR3;
	m_pModel	= NULL;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
//�f�N�������g
//******************************************************************************
CTestModel::~CTestModel()
{

}

//******************************************************************************
//��������
//******************************************************************************
CTestModel * CTestModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	CTestModel *pTest_Model;
	pTest_Model = new CTestModel;
	pTest_Model->Init();
	pTest_Model->SetBox(pos, rot, size);

	return pTest_Model;
}

//******************************************************************************
//���f���̓ǂݍ���
//******************************************************************************
HRESULT CTestModel::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_apFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat,
			NULL,
			&m_nNumMat,
			&m_pMesh
		);
	LoadTexture();
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���̓ǂݍ���
//******************************************************************************
HRESULT CTestModel::LoadTexture(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

		// �}�e���A���������o��
		D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
		for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
		{
			// �g�p���Ă���e�N�X�`��������Γǂݍ���
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_pTexture[nCntMat])))
				{
					return E_FAIL;
				}
			}
		}

	return S_OK;
}
//******************************************************************************
//���f���̔j��
//******************************************************************************
void CTestModel::Unload(void)
{
		// ���b�V���̔j��
		if (m_pMesh != NULL)
		{
			m_pMesh->Release();
			m_pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (m_pBuffMat != NULL)
		{
			m_pBuffMat->Release();
			m_pBuffMat = NULL;
		}

		if (m_nNumMat != NULL)
		{
			m_nNumMat = NULL;
		}
}

//******************************************************************************
//����������
//******************************************************************************
HRESULT CTestModel::Init(void)
{
	// ���f���̐���
	m_pModel = CModel::Create();

	// ���f���̃o�C���h
	m_pModel->BindModel(m_pMesh, m_pBuffMat, m_nNumMat, -1);

	for (int nCntMat = INIT_INT; nCntMat < (signed)m_nNumMat; nCntMat++)
	{
		// �e�N�X�`���̃o�C���h
		m_pModel->BindTexture(m_pTexture[nCntMat], nCntMat);
	}

	return S_OK;
}

//******************************************************************************
//�I������
//******************************************************************************
void CTestModel::Uninit(void)
{
	// ���f���N���X�̏I������
	m_pModel->Uninit();

	m_pModel = NULL;

	// �j��
	Release();
}

//******************************************************************************
//�X�V����
//******************************************************************************
void CTestModel::Update(void)
{
	// �ݒ�
	SetBox(m_pos, m_rot, m_size);
}

//******************************************************************************
//�`�揈��
//******************************************************************************
void CTestModel::Draw(void)
{
	//�����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�̌��ʂ𖳌���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
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

	// ���C�g�̌��ʂ𖳌���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//******************************************************************************
// �ړ������֐�
//******************************************************************************
void CTestModel::Move(void)
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
void CTestModel::ReleaseBox(void)
{
	// �j��
	Uninit();

	return;
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CTestModel::SetBox(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
}