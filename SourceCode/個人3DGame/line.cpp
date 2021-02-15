//******************************************************************************
// 3D [scene3d.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
//�C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "line.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define NOR				(D3DXVECTOR3(0, 1, 0))	// �@��
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CLine::CLine(int nPriority) :CScene(nPriority)
{
	m_pVtxBuff	= NULL;
	m_pos		= INIT_D3DXVECTOR3;
	m_Start_pos = INIT_D3DXVECTOR3;
	m_End_pos	= INIT_D3DXVECTOR3;
	m_rot		= INIT_D3DXVECTOR3;
	m_col		= INIT_COLOR;
	memset(m_mtxWorld, NULL, sizeof(m_mtxWorld));
}

//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CLine::~CLine()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CLine * CLine::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos, D3DXCOLOR col)
{
	// CLine�̃|�C���^
	CLine *pLine;

	// �������m��
	pLine = new CLine;

	// ���ݒ�
	pLine->SetLine(pos,rot,startpos,endpos,col);

	// ������
	pLine->Init();

	// �|�C���^��Ԃ�
	return pLine;
}

//******************************************************************************
// ����������
//******************************************************************************
HRESULT CLine::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_POLYGON,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,																	// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_POINT,																	// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,																	// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,																		// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))																				// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	// ���_����ݒ�
	VERTEX_POINT *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(NULL, NULL, (void**)&pVtx, NULL);

	// �ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Start_pos.x, m_Start_pos.y, m_Start_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_End_pos.x, m_End_pos.y, m_End_pos.z);

	// �J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//******************************************************************************
// �I������
//******************************************************************************
void CLine::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �j��
	Release();
}

//******************************************************************************
// �X�V����
//******************************************************************************
void CLine::Update(void)
{
	// ���_����ݒ�
	VERTEX_POINT *pVtx = NULL;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(NULL, NULL, (void**)&pVtx, NULL);

	// �ꏊ�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Start_pos.x, m_Start_pos.y, m_Start_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_End_pos.x, m_End_pos.y, m_End_pos.z);

	// �J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void CLine::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;

	// �}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);

	// ����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ� 
	pDevice->SetStreamSource(NULL, m_pVtxBuff, NULL, sizeof(VERTEX_POINT));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_POINT);

	// ���C���̕`��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);
}
//******************************************************************************
// ���ݒ�
//******************************************************************************
void CLine::SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos, D3DXCOLOR col)
{
	// �ʒu
	m_pos = pos;

	// ����
	m_rot = rot;

	// �n�_
	m_Start_pos = startpos;

	// �I�_
	m_End_pos = endpos;

	// �F
	m_col = col;
}