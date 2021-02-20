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
		MOTION_IDLE = 0,// �ҋ@���[�V����
		MOTION_RUN,		// �������[�V����
		MOTION_MAX		// �ő吔
	}MOTIONSTATE;

	// �u���b�N��p���Ă̍s���̎��
	typedef enum
	{
		BLOCK_ACTIVE_NONE = 0,// �u���b�N��p���čs�������Ă��Ȃ�
		BLOCK_ACTIVE_MOVE,	  // �u���b�N���ړ������Ă���
		BLOCK_ACTIVE_SELECT,  // �u���b�N��I�����Ă���
		BLOCK_ACTIVE_MAX	  // �ő吔
	}BLOCK_ACTIVE;

	// �v���C���[�̌���
	typedef enum
	{
		ROT_STATE_RIGHT = 0,// �E�������Ă�����
		ROT_STATE_LEFT,		// ���������Ă�����
		ROT_STATE_MAX		// �ő吔
	}ROT_STATE;

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
	void RightSelectBlock(void);
	void RightBlock(void);
	void RightSelectionBlock(void);
	void SelectionBlockNum(void);
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
	CBlock *m_pAllBlock[MAX_BLOCK];						// ���̑���
	CBlock *m_pBlock;									// ���̃|�C���^
	BLOCK_ACTIVE m_Blcok_Active;						// ����p���Ă̈ړ�
	ROT_STATE m_Rot_State;								// �����̏��
	int m_nBlockNum;									// ���̐�
	int m_nBlock_Select_Num;							// ���̑I������
	int m_nSelect_Save_Num;								// ���̐���ۑ�����
	bool m_bStick;										// �X�e�B�b�N����
	bool m_bRot;										// ����
};

#endif