//******************************************************************************
// 箱ポリゴン[polygon.h]
// Author : 管原司
//******************************************************************************
#ifndef _BLOCK_POLYGON_H_
#define _BLOCK_POLYGON_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// クラス
//******************************************************************************
class CBlock_Polygon : public CScene3d
{
public:
	CBlock_Polygon(int nPriority = OBJTYPE_POLYGON);
	~CBlock_Polygon();
	static CBlock_Polygon *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};
#endif