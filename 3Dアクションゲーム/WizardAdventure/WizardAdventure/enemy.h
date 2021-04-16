//******************************************************************************
// 敵 [enemy.h]
// Author : 管原　司
//******************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
#include "model.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_MATERIAL	(50)
//******************************************************************************
// 前方宣言
//******************************************************************************
class CModel;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CEnemy :public CScene
{
public:

	CEnemy(int nPriority = OBJTYPE_ENEMY);
	~CEnemy();

	static HRESULT Load(void);
	static void Unload(void);
	static HRESULT LoadTexture(void);
	static void UnloadTexture(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//***************************************
	// セッター
	//***************************************
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);

	//***************************************
	// ゲッター
	//***************************************
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

private:
	static LPD3DXMESH m_pMesh;									// メッシュ情報のポインタ
	static LPD3DXBUFFER m_pBuffMat;								// マテリアル情報のポインタ
	static DWORD m_nNumMat;										// マテリアル情報の数
	D3DXMATRIX m_mtxWorld;										// 行列計算用
	static char* m_apFileName;									// ファイルの名前
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_MATERIAL];		// マテリアルの最大数
	D3DXVECTOR3 m_pos;											// 位置
	D3DXVECTOR3 m_rot;											// 角度
	D3DXVECTOR3 m_size;											// 大きさ
	CModel *m_pModel;											// モデルクラスのポインタ
	bool m_bDraw;												// 描画判定
};

#endif