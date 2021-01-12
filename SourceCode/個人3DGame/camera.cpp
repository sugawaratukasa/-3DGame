//======================================
//	camera.cpp
//	Author : �ǌ��i
//======================================

//======================================
//�C���N���[�h�t�@�C��
//======================================
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "keyboard.h"
//======================================
//�R���X�g���N�^
//======================================
CCamera::CCamera()
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_fPhi = 0.0f;
	m_fTheta = 0.0f;
}

//======================================
//�f�N�������g
//======================================
CCamera::~CCamera()
{

}

//======================================
//����������
//======================================
void CCamera::Init(void)
{
	posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	memset(mtxProjection, NULL, sizeof(mtxProjection));
	memset(mtxView, NULL, sizeof(mtxView));
	m_fPhi = 1;
	m_fTheta = 1.7f;
}

//======================================
//�I������
//======================================
void CCamera::Uninit(void)
{

}

//======================================
//�X�V����
//======================================
void CCamera::Update(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pKeyborad = CManager::GetInputKeyboard();

	//======================================
	//�ړ�
	//======================================		

	// �E��]
	if (pKeyborad->GetKeyPress(DIK_D))
	{
		m_fPhi += D3DXToRadian(1);
	}
	//����]
	if (pKeyborad->GetKeyPress(DIK_A))
	{
		m_fPhi -= D3DXToRadian(1);
	}
	//���]
	if (pKeyborad->GetKeyPress(DIK_W))
	{
		m_fTheta -= D3DXToRadian(1);
	}
	//����]
	if (pKeyborad->GetKeyPress(DIK_S))
	{
		m_fTheta += D3DXToRadian(1);
	}

	//�����_
	//����
	posR.x = (sinf(m_fTheta)*cosf(m_fPhi));
	posR.y = cosf(m_fTheta);
	posR.z = (sinf(m_fTheta)*sinf(m_fPhi));

	//���_	
	//����
	m_fDistance = 40;
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
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(90), SCREEN_WIDTH / SCREEN_HEIGHT, 10, 10000);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}