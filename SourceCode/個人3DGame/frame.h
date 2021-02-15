//******************************************************************************
// フレーム[frame.h]
// Author : 管原司
//******************************************************************************
#ifndef _FRAME_H_
#define _FRAME_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene3d.h"
//******************************************************************************
// 前方宣言
//******************************************************************************
class CTestModel;
//******************************************************************************
// クラス
//******************************************************************************
class CFrame : public CScene3d
{
public:
	CFrame(int nPriority = OBJTYPE_POLYGON);
	~CFrame();
	static HRESULT Load(void);
	static void Unload(void);
	static CFrame *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, CTestModel *pBlock);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void FrameCreate(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col, CTestModel *pBlock);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// テクスチャへのポインタ
	CTestModel *m_pBlock;						// 箱
};
#endif