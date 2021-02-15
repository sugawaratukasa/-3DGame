//******************************************************************************
// 線[line.h]
// Author : 管原司
//******************************************************************************
#ifndef _LINE_H_
#define _LINE_H_
//******************************************************************************
// マクロ定義
//******************************************************************************
#define FVF_VERTEX_POINT (D3DFVF_XYZ | D3DFVF_DIFFUSE)
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// クラス
//******************************************************************************
class CLine : public CScene
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
	}VERTEX_POINT;

	CLine(int nPriority = OBJTYPE_POLYGON);
	~CLine();
	static CLine *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos,D3DXCOLOR col);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLine(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 startpos, D3DXVECTOR3 endpos, D3DXCOLOR col);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;						// 位置座標
	D3DXVECTOR3 m_Start_pos;				// 始点
	D3DXVECTOR3 m_End_pos;					// 終点
	D3DXVECTOR3 m_rot;						// 向き
	D3DXCOLOR m_col;						// 色
	D3DXMATRIX m_mtxWorld;					// ワールド座標
};
#endif