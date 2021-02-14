//******************************************************************************
// �|���S��[polygon.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _POLYGON_H_
#define _POLYGON_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CPolygon : public CScene3d
{
public:
	CPolygon(int nPriority = OBJTYPE_POLYGON);
	~CPolygon();
	static HRESULT Load(void);
	static void Unload(void);
	static CPolygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	void DotCollision(void);
	void Collision(void);
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_posOld;						// 1�t���[���O�̈ʒu

};
#endif