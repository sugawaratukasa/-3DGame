//******************************************************************************
// ブロックモデルのテスト [block.h]
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
// 前方宣言
//******************************************************************************
class CModel;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CBlock :public CScene
{
public:
	CBlock(int nPriority = OBJTYPE_BLOCK);//コンストラクタ
	~CBlock();//デストラクタ

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
	static LPD3DXMESH m_pMesh;								// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat;							// マテリアル情報のポインタ
	static DWORD m_nNumMat;									// マテリアル情報の数
	D3DXMATRIX m_mtxWorld;									// 行列計算用
	static char* m_apFileName;								// ファイルの名前
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_MATERIAL];		// マテリアル
	D3DXVECTOR3 m_pos;										// 場所
	D3DXVECTOR3 m_rot;										// 角度
	D3DXVECTOR3 m_size;										// 大きさ
	CModel *m_pModel;										// モデルクラスのポインタ
};
#endif