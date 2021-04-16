//******************************************************************************
// 木 [tree.h]
// Author : 管原　司
//******************************************************************************
#ifndef _OBJ_TREE_H_
#define _OBJ_TREE_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "3d_obj.h"
//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// 前方宣言
//******************************************************************************
class CModel;
//******************************************************************************
// プレイヤークラス
//******************************************************************************
class CTree :public C3D_Obj
{
public:
	CTree(int nPriority = OBJTYPE_BACK_OBJ);
	~CTree();
	static CTree *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
};
#endif