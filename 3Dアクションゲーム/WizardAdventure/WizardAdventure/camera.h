//******************************************************************************
// �J���� [camera.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Move(float fMove);
	D3DXVECTOR3 GetPos(void) { return m_posV; }
private:
	D3DXVECTOR3 m_posV;		// �ʒu
	D3DXVECTOR3 m_posR;		// �����_
	D3DXVECTOR3 m_vecU;	
	D3DXMATRIX	m_mtxProjection;
	D3DXMATRIX	m_mtxView;
	float AddPosV;			// �ʒu���Z
	float m_fDistance;		// ����
	float m_fPhi;			// �t�@�C
	float m_fTheta;			// �V�[�^
};

#endif