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
	// モーション
	typedef enum {
		MOTION_IDLE = 0,	 // 待機モーション
		MOTION_RUN,			 // 歩きモーション
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

	static LPD3DXMESH m_pMesh[MAX_PLAYER_PARTS];		// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[MAX_PLAYER_PARTS];	// マテリアル情報のポインタ
	static DWORD m_nNumMat[MAX_PLAYER_PARTS];			// マテリアル情報の数
	static D3DXMATRIX m_mtxWorld[MAX_PLAYER_PARTS];		// 行列計算用
	static int m_nldxModelParent[MAX_PLAYER_PARTS];		// 親モデルのインデックス
	static char* m_apFileName[MAX_PLAYER_PARTS];		// ファイルの名前
	static char* m_apTextureFileName[MAX_PLAYER_PARTS];	// テクスチャのファイルの名前
	D3DXVECTOR3 m_pos;									// 場所
	D3DXVECTOR3 m_rot;									// 角度
	D3DXVECTOR3 m_size;									// 大きさ
	bool m_bAllMotion;									// 全モーションの判定
	CMotion *m_pMotion;									// モーションクラスのポインタ
	CModel *m_pModel[MAX_PLAYER_PARTS];					// モデルクラスのポインタ
	int m_nBlockNum;									// 箱の数
	CBlock *m_pAllBlock[MAX_BLOCK];						// 箱の総数
	CBlock *m_pBlock;									// 箱のポインタ
};

#endif