#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "scene.h"

class CScene3d :public CScene
{
public:
	CScene3d(int nPriority);//�C���N�������g
	~CScene3d();//�f�N�������g
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);


private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;	// �ʒu���W
	D3DXVECTOR3 m_size;	// �T�C�Y
	D3DXVECTOR3 m_rot;	// ����
	D3DXMATRIX m_mtxWorld;	// ���[���h���W
};
#endif //_SCENE3D_H_