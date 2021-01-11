#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class CCamera
{
public:
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);

private:
	D3DXVECTOR3 posV;		// �ʒu
	D3DXVECTOR3 posR;		// �����_
	D3DXVECTOR3 vecU;
	D3DXMATRIX	mtxProjection;
	D3DXMATRIX	mtxView;
	float m_fDistance;		// ����
	float m_fPhi;			// �t�@�C
	float m_fTheta;			// �V�[�^
};

#endif