//******************************************************************************
// �����蔻�� [collision.cpp]
// Author : �ǌ��@�i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "collision.h"
//******************************************************************************
// �����̂̓����蔻��
//******************************************************************************
bool CCollision::RectangleCollision(D3DXVECTOR3 pPos1, D3DXVECTOR3 size1, D3DXVECTOR3 pPos2, D3DXVECTOR3 size2)
{
	bool bHit = false;

	D3DXVECTOR3 box1Max = D3DXVECTOR3(size1.x / 2, size1.y, size1.z / 2) + pPos1;          //�Ԃ��鑤�̍ő�l
	D3DXVECTOR3 box1Min = D3DXVECTOR3(-size1.x / 2, -size1.y, -size1.z / 2) + pPos1;       //�Ԃ��鑤�̍ŏ��l
	D3DXVECTOR3 box2Max = D3DXVECTOR3(size2.x / 2, size2.y / 2, size2.z / 2) + pPos2;      //�Ԃ����鑤�̍ő�l
	D3DXVECTOR3 box2Min = D3DXVECTOR3(-size2.x / 2, -size2.y / 2, -size2.z / 2) + pPos2;   //�Ԃ����鑤�̍ŏ��l

	if (box1Max.y > box2Min.y&&
		box1Min.y < box2Max.y&&
		box1Max.x > box2Min.x&&
		box1Min.x < box2Max.x&&
		box1Max.z > box2Min.z&&
		box1Min.z < box2Max.z)
	{
		bHit = true;
	}

	// �����������ǂ�����Ԃ�
	return bHit;
}
//******************************************************************************
// �~�`�̓����蔻��
//******************************************************************************
bool CCollision::SphereCollision(D3DXVECTOR3 pos1, float size1, D3DXVECTOR3 pos2, float size2)
{
	// �ʒu
	float distance = powf(pos1.x - pos2.x, 2.0f) + powf(pos1.y - pos2.y, 2.0f) + powf(pos1.z - pos2.z, 2.0f); 

	// ���a
	float radius = powf(size1 + size2, 2.0f); 

	// �߂荞��ł��邩
	return (distance < radius);
}
