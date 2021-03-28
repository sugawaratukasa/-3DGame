//******************************************************************************
// プレイヤーの処理 [player.h]
// Author : 管原　司
//******************************************************************************
#ifndef _PLAYER_H_
#define _PLAYER_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_PLAYER_PARTS	(15)							// プレイヤーのモデルのパーツの最大数
#define MAX_MATERIAL		(50)							// マテリアルの最大
#define MAX_BLOCK			(3)								// ブロック数の最大数
//******************************************************************************
// 前方宣言
//******************************************************************************
class CMotion;
class CModel;
class CBlock;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CPlayer :public CScene
{
public:
	// プレイヤーパーツ
	typedef enum
	{
		PARTS_UNDER_BODY = 0,
		PARTS_BODY,
		PARTS_HEAD,
		PARTS_SHOULDER_R,
		PARTS_UP_ARM_R,
		PARTS_DOWN_ARM_R,
		PARTS_SHOULDER_L,
		PARTS_UP_ARM_L,
		PARTS_DOWN_ARM_L,
		PARTS_THIGTS_R,
		PARTS_KNEE_R,
		PARTS_FOOT_R,
		PARTS_THIGTS_L,
		PARTS_KNEE_L,
		PARTS_FOOT_L,
		PARTS_MAX
	}PLAYER_PARTS;

	// モーション
	typedef enum {
		MOTION_IDLE = 0,// 待機モーション
		MOTION_RUN,		// 歩きモーション
		MOTION_JUMP,	// ジャンプモーション
		MOTION_LANDING,	// 着地モーション
		MOTION_MAX		// 最大数
	}MOTIONSTATE;

	// ブロックを用いての行動の種類
	typedef enum
	{
		BLOCK_ACTIVE_NONE = 0,	// ブロックを用いて行動をしていない状態
		BLOCK_ACTIVE_MOVE,		// ブロックを移動させている状態
		BLOCK_ACTIVE_SELECT,	// ブロックを選択している状態
		BLOCK_ACTIVE_SELECTED,	// ブロックを選択した状態
		BLOCK_ACTIVE_MAX		// 最大数
	}BLOCK_ACTIVE;

	// プレイヤーの向き
	typedef enum
	{
		ROT_STATE_RIGHT = 0,// 右を向いている状態
		ROT_STATE_LEFT,		// 左を向いている状態
		ROT_STATE_MAX		// 最大数
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
	void SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);

	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
private:
	void RightSelectBlock(void);
	void RightBlock(void);
	void RightSelectionBlock(void);

	void LeftSelectBlock(void);
	void LeftBlock(void);
	void LeftSelectionBlock(void);

	void Collision(void);
	void Move(void);

	static LPD3DXMESH m_pMesh[PARTS_MAX];				// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[PARTS_MAX];			// マテリアル情報のポインタ
	static DWORD m_nNumMat[PARTS_MAX];					// マテリアル情報の数
	static D3DXMATRIX m_mtxWorld[PARTS_MAX];			// 行列計算用
	static int m_nldxModelParent[PARTS_MAX];			// 親モデルのインデックス
	static char* m_apFileName[PARTS_MAX];				// ファイルの名前
	static char* m_apTextureFileName[PARTS_MAX];		// テクスチャのファイルの名前
	D3DXVECTOR3 m_pos;									// 位置
	D3DXVECTOR3 m_posOld;								// 古い位置
	D3DXVECTOR3 m_rot;									// 角度
	D3DXVECTOR3 m_size;									// 大きさ
	D3DXVECTOR3 m_move;									// 移動量
	bool m_bAllMotion;									// 全モーションの判定
	CMotion *m_pMotion;									// モーションクラスのポインタ
	CModel *m_pModel[PARTS_MAX];						// モデルクラスのポインタ
	CBlock *m_pBlock;									// 箱のポインタ
	BLOCK_ACTIVE m_Blcok_Active;						// 箱を用いての移動
	ROT_STATE m_Rot_State;								// 向きの状態
	int m_nBlockNum;									// 箱の数
	int m_nBlock_Select_Num;							// 箱の選択する
	int m_nSelect_Save_Num;								// 箱の数を保存する
	bool m_bStick;										// スティック判定
	bool m_bRot;										// 向き
};

#endif