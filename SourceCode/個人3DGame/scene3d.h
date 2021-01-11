#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "scene.h"

class CScene3d :public CScene
{
public:
	CScene3d(int nPriority);//インクリメント
	~CScene3d();//デクリメント
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);


private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;	// 位置座標
	D3DXVECTOR3 m_size;	// サイズ
	D3DXVECTOR3 m_rot;	// 向き
	D3DXMATRIX m_mtxWorld;	// ワールド座標
};
#endif //_SCENE3D_H_