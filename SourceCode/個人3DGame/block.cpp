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
#include "block.h"
#include "model.h"

//******************************************************************************
//�ÓI�����o�ϐ�
//******************************************************************************
LPD3DXMESH CBlock::m_pMesh = NULL;
LPD3DXBUFFER CBlock::m_pBuffMat = NULL;
DWORD CBlock::m_nNumMat = NULL;
char* CBlock::m_apFileName = { "data/Model/Object/box.x" };// ��
LPDIRECT3DTEXTURE9 CBlock::m_pTexture[MAX_MATERIAL] = {};

//******************************************************************************
//�C���N�������g
//******************************************************************************
CBlock::CBlock(int nPriority) :CScene(nPriority)
{
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
	m_size = INIT_D3DXVECTOR3;
	m_pModel = NULL;
	m_mtxWorld = {};
}
//******************************************************************************
//�f�N�������g
//******************************************************************************
CBlock::~CBlock()
{

}
//******************************************************************************
//��������
//******************************************************************************
CBlock * CBlock::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CBlock�̃|�C���^
	CBlock *pBlock;

	// �������m��
	pBlock = new CBlock;

	// ������
	pBlock->Init();

	// ���ݒ�
	pBlock->SetBlock(pos, rot, size);

	// �|�C���^��Ԃ�
	return pBlock;
}

//******************************************************************************
//���f���̓ǂݍ���
//******************************************************************************
HRESULT CBlock::Load(void)
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
	return S_OK;
}
//******************************************************************************
//���f���̔j��
//******************************************************************************
void CBlock::Unload(void)
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
HRESULT CBlock::Init(void)
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
void CBlock::Uninit(void)
{
	// ���f���N���X�̏I������
	m_pModel->Uninit();
	m_pModel = NULL;
}

//******************************************************************************
//�X�V����
//******************************************************************************
void CBlock::Update(void)
{
	// �ݒ�
	SetBlock(m_pos, m_rot, m_size);
	CScene *pScene = NULL;
}

//******************************************************************************
//�`�揈��
//******************************************************************************
void CBlock::Draw(void)
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
// ���ݒ�
//******************************************************************************
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	m_pos = pos; m_rot = rot; m_size = size;
	m_pModel->SetModel(m_pos, m_rot, m_size);
}