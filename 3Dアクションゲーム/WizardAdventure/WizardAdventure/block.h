//******************************************************************************
// ブロック [block.h]
// Author : 管原　司
//******************************************************************************
#ifndef _BLOCK_H_
#define _BLOCK_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
#include "model.h"
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 前方宣言
//******************************************************************************
class CModel;
class CFrame;
//******************************************************************************
// プレイヤークラス
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
	CBlock(int nPriority = OBJTYPE_BLOCK);//コンストラクタ
	~CBlock();//デストラクタ

	static HRESULT Load(void);
	static void Unload(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(void);

	void ReleaseBlock(void);
	void SetFrame(void);
	void Selecting(void);
	void UnSelected(void);
	void PlayerSelection(void);
	void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CBlock *pBlock, TYPE type);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; };
private:
	static LPD3DXMESH m_pMesh[TYPE_MAX];							// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat[TYPE_MAX];						// マテリアル情報のポインタ
	static DWORD m_nNumMat[TYPE_MAX];								// マテリアル情報の数
	D3DXMATRIX m_mtxWorld;											// 行列計算用
	static char* m_apFileName[TYPE_MAX];							// ファイルの名前
	D3DXVECTOR3 m_pos;												// 場所
	D3DXVECTOR3 m_rot;												// 角度
	D3DXVECTOR3 m_size;												// 大きさ
	CModel *m_pModel;												// モデルクラスのポインタ
	CBlock *m_pBlock;												// ポインタ
	CFrame *m_pFrame;												// 枠のポインタ
	TYPE m_Type;													// 種類
};

#endif