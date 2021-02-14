//******************************************************************************
// �J���� [camera.cpp]
// Author : �ǌ��i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "keyboard.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define VECU_VALUE		(D3DXVECTOR3(0.0f,1.0f,0.0f))	// vecu�l
#define ROT_VALUE		(D3DXToRadian(1.0f))			// �J�����̋��ʍ��W�̈ړ�
#define PHI_VALUE		(1.0f)							// phi�l
#define THETA_VALUE		(1.7f)							// theta�l
#define DISTANCE_VALUE	(40.0f)							// ����
#define FOV_VALUE		(D3DXToRadian(90))				// ����p
#define DRAW_DISTANCE	(10000)							// �`�拗��
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CCamera::CCamera()
{
	posV		= INIT_D3DXVECTOR3;
	posR		= INIT_D3DXVECTOR3;
	vecU		= INIT_D3DXVECTOR3;
	m_fPhi		= INIT_FLOAT;
	m_fTheta	= INIT_FLOAT;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
}

//******************************************************************************
// �f�N�������g
//******************************************************************************
CCamera::~CCamera()
{

}

//******************************************************************************
// ����������
//******************************************************************************
void CCamera::Init(void)
{
	posV		= INIT_D3DXVECTOR3;
	posR		= INIT_D3DXVECTOR3;
	vecU		= VECU_VALUE;
	m_fPhi		= PHI_VALUE;
	m_fTheta	= THETA_VALUE;
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
}

//******************************************************************************
// �I������
//******************************************************************************
void CCamera::Uninit(void)
{

}

//******************************************************************************
// �X�V����
//******************************************************************************
void CCamera::Update(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pKeyborad = CSceneManager::GetInputKeyboard();		

	// �E��]
	if (pKeyborad->GetKeyPress(DIK_D))
	{
		m_fPhi -= ROT_VALUE;
	}
	//����]
	if (pKeyborad->GetKeyPress(DIK_A))
	{
		m_fPhi += ROT_VALUE;
	}
	//���]
	if (pKeyborad->GetKeyPress(DIK_W))
	{
		m_fTheta -= ROT_VALUE;
	}
	//����]
	if (pKeyborad->GetKeyPress(DIK_S))
	{
		m_fTheta += ROT_VALUE;
	}

	// �����_
	posR.x = (sinf(m_fTheta)*cosf(m_fPhi));
	posR.y = cosf(m_fTheta);
	posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	
	// ����
	m_fDistance = DISTANCE_VALUE;

	// ���_	
	posV.x = m_fDistance*(sinf(m_fTheta)*cosf(m_fPhi));
	posV.y = m_fDistance*cosf(m_fTheta);
	posV.z = m_fDistance*(sinf(m_fTheta)*sinf(m_fPhi));

	//======================================
	//�J�����`��
	//======================================
	D3DXMatrixIdentity(&mtxView);
	D3DXMatrixLookAtLH(&mtxView, &posV, &posR, &vecU);
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
	D3DXMatrixIdentity(&mtxProjection);
	D3DXMatrixPerspectiveFovLH(&mtxProjection, FOV_VALUE, SCREEN_WIDTH / SCREEN_HEIGHT, 10, DRAW_DISTANCE);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}