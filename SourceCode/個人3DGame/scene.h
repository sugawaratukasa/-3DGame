//*******************************************************************
// オブジェクト処理 [scene.h]
// Author : 管原司
//*******************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_
//*******************************************************************
// インクルードファイル
//*******************************************************************
#include "main.h"
//*******************************************************************
// マクロ定義
//*******************************************************************
#define NUM_VERTEX			(4)
#define NUM_POLYGON			(2)
#define MAX_POLYGON			(2048)
#define	FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_3D		(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define RHW_VALUE			(1.0f)													// rhw値
//********************************************************************
// 構造体定義
//*******************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

typedef struct {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;
//*******************************************************************
// オブジェクトクラス
//*******************************************************************
class CScene
{
public:
	// オブジェクトタイプ
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ITEM,
		OBJTYPE_DEFAULT,
		OBJTYPE_PARTICLE,
		OBJTYPE_BLOCK,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_POLYGON,
		OBJTYPE_TEST,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_DEFAULT);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	//純粋仮想関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void DesignationReleaseAll(OBJTYPE type);
	static void SetUpdateStop(bool bUpdateStop);

	static bool GetUpdateStop(void) { return m_bUpdateStop; }

protected:
	void Release(void);

private:
	OBJTYPE m_objType;					// オブジェクトの種類
	static CScene *m_pTop[OBJTYPE_MAX];	// 先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];	// 現在のオブジェクトへのポインタ
	CScene *m_pPrev;					// 前のオブジェクトへのポインタ
	CScene *m_pNext;					// 次のオブジェクトへのポインタ
	int m_nPriority;
	int m_nID;
	static int m_nNext;
	static bool m_bRelease;
	bool m_bDeath;
	static bool m_bUpdateStop;
};
#endif // !_RENDERER_H_