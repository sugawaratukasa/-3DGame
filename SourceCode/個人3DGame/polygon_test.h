//******************************************************************************
// ポリゴンテスト[polygon_test.h]
// Author : 管原司
//******************************************************************************
#ifndef _POLYGON_TEST_H_
#define _POLYGON_TEST_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// クラス
//******************************************************************************
class CPolygon_Test : public CScene3d
{
public:
	CPolygon_Test(int nPriority = OBJTYPE_TEST);
	~CPolygon_Test();
	static HRESULT Load(void);
	static void Unload(void);
	static CPolygon_Test *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
};
#endif