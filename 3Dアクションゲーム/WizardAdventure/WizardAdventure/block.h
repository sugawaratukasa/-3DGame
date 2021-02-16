//******************************************************************************
// �u���b�N [block.h]
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
// �}�N����`
//******************************************************************************

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
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_WOOD,
		TYPE_STONE,
		TYPE_MAX
	}TYPE;
	CBlock(int nPriority = 5);//�R���X�g���N�^
	~CBlock();//�f�X�g���N�^

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(void);

	void ReleaseBlock(void);
	void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; };
private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];							// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX];						// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[TYPE_MAX];								// �}�e���A�����̐�
	D3DXMATRIX m_mtxWorld;											// �s��v�Z�p
	static char* m_apFileName[TYPE_MAX];							// �t�@�C���̖��O
	D3DXVECTOR3 m_pos;												// �ꏊ
	D3DXVECTOR3 m_rot;												// �p�x
	D3DXVECTOR3 m_size;												// �傫��
	CModel *m_pModel;												// ���f���N���X�̃|�C���^
	TYPE m_Type;													// ���
};

#endif