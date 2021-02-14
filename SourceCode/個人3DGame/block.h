//******************************************************************************
// �u���b�N���f���̃e�X�g [block.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _BLOCK_H_
#define _BLOCK_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
#include "model.h"
//******************************************************************************
// �O���錾
//******************************************************************************
class CModel;
//******************************************************************************
// �v���C���[�N���X
//******************************************************************************
class CBlock :public CScene
{
public:
	CBlock(int nPriority = OBJTYPE_BLOCK);//�R���X�g���N�^
	~CBlock();//�f�X�g���N�^

	static CBlock *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; };
	LPD3DXMESH GetMesh(void) { return m_pMesh; }
private:
	static LPD3DXMESH m_pMesh;								// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;							// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat;									// �}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;									// �s��v�Z�p
	static char* m_apFileName;								// �t�@�C���̖��O
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_MATERIAL];		// �}�e���A��
	D3DXVECTOR3 m_pos;										// �ꏊ
	D3DXVECTOR3 m_rot;										// �p�x
	D3DXVECTOR3 m_size;										// �傫��
	CModel *m_pModel;										// ���f���N���X�̃|�C���^
};
#endif