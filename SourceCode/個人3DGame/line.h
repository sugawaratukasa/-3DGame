//******************************************************************************
// ��[line.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _LINE_H_
#define _LINE_H_
//******************************************************************************
// �}�N����`
//******************************************************************************
#define FVF_VERTEX_POINT (D3DFVF_XYZ | D3DFVF_DIFFUSE)
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �N���X
//******************************************************************************
class CLine : public CScene
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
	}VERTEX_POINT;

	CLine(int nPriority = OBJTYPE_POLYGON);
	~CLine();
	static CLine *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos,D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos, D3DXCOLOR col);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;						// �ʒu���W
	D3DXVECTOR3 m_Start_pos;				// �n�_
	D3DXVECTOR3 m_End_pos;					// �I�_
	D3DXVECTOR3 m_rot;						// ����
	D3DXCOLOR m_col;						// �F
	D3DXMATRIX m_mtxWorld;					// ���[���h���W
};
#endif