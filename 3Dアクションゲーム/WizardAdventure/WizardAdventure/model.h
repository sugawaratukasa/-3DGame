//******************************************************************************
// モデルの階層構造の処理 [model.h]
// Author : 管原司
//******************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

//******************************************************************************
// マクロ定義
//******************************************************************************
#define MAX_MATERIAL (50)
//******************************************************************************
// クラス
//******************************************************************************
class CModel
{
public:
	CModel();
	~CModel();

	static CModel*Create();

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void BindModel(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD nNumMat,int nldxModelParent);
	void BindTexture(LPDIRECT3DTEXTURE9 Texture, int nCount);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetParent(CModel *cmodel);
	void SetWorldMatrix(D3DXMATRIX mtxWorld);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXMATRIX GetMtxWorld(void) { return m_mtxWorld; }
private:
	LPD3DXMESH m_pMesh;								// メッシュ情報のポインタ
	LPD3DXBUFFER m_pBuffMat;						// マテリアル情報のポインタ
	DWORD m_nNumMat;								// マテリアル情報の数
	D3DXMATRIX m_mtxWorld;							// 行列計算用
	int m_nldxModelParent;							// 親モデルのインデックス
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_MATERIAL];	// テクスチャの情報
	D3DXVECTOR3 m_pos;								// 位置
	D3DXVECTOR3 m_rot;								// 角度
	D3DXVECTOR3 m_size;								// サイズ
	CModel *m_pParent;								// 親
};

#endif