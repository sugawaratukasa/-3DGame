//******************************************************************************
// �v���C���[�̏��� [player.h]
// Author : �ǌ��@�i
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MAX_PLAYER_PARTS	(15)							// �v���C���[�̃��f���̃p�[�c�̍ő吔
#define MAX_MATERIAL		(50)							// �}�e���A���̍ő�
#define MAX_BLOCK			(3)								// �u���b�N���̍ő吔
//******************************************************************************
// �O���錾
//******************************************************************************
class CMotion;
class CModel;
class CBlock;
//******************************************************************************
// �v���C���[�N���X
//******************************************************************************
class CPlayer :public CScene
{
public:
	// ���[�V����
	typedef enum {
		MOTION_IDLE = 0,	 // �ҋ@���[�V����
		MOTION_RUN,			 // �������[�V����
		MOTION_MAX
	}MOTIONSTATE;

	CPlayer(int nPriority = CScene::OBJTYPE_PLAYER);
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	void SelectBlock(void);
	void Block(void);
	void Move(void);

	static LPD3DXMESH m_pMesh[MAX_PLAYER_PARTS];		// ���b�V�����̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[MAX_PLAYER_PARTS];	// �}�e���A�����̃|�C���^
	static DWORD m_nNumMat[MAX_PLAYER_PARTS];			// �}�e���A�����̐�
	static D3DXMATRIX m_mtxWorld[MAX_PLAYER_PARTS];		// �s��v�Z�p
	static int m_nldxModelParent[MAX_PLAYER_PARTS];		// �e���f���̃C���f�b�N�X
	static char* m_apFileName[MAX_PLAYER_PARTS];		// �t�@�C���̖��O
	static char* m_apTextureFileName[MAX_PLAYER_PARTS];	// �e�N�X�`���̃t�@�C���̖��O
	D3DXVECTOR3 m_pos;									// �ꏊ
	D3DXVECTOR3 m_rot;									// �p�x
	D3DXVECTOR3 m_size;									// �傫��
	bool m_bAllMotion;									// �S���[�V�����̔���
	CMotion *m_pMotion;									// ���[�V�����N���X�̃|�C���^
	CModel *m_pModel[MAX_PLAYER_PARTS];					// ���f���N���X�̃|�C���^
	int m_nBlockNum;									// ���̐�
	CBlock *m_pAllBlock[MAX_BLOCK];						// ���̑���
	CBlock *m_pBlock;									// ���̃|�C���^
};

#endif