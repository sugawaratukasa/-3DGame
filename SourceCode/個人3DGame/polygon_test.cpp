//******************************************************************************
// ポリゴンテスト[polygon_test.cpp]
// Author : 管原司
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "scene.h"
#include "scene3d.h"
#include "polygon_test.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
//******************************************************************************
// 静的メンバ変数初期化
//******************************************************************************
LPDIRECT3DTEXTURE9 CPolygon_Test::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPolygon_Test::CPolygon_Test(int nPriority) : CScene3d(nPriority)
{
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPolygon_Test::~CPolygon_Test()
{
}
//******************************************************************************
// テクスチャ読み込み関数
//******************************************************************************
HRESULT CPolygon_Test::Load(void)
{
	// レンダラー取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/circle.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// テクスチャ破棄関数
//******************************************************************************
void CPolygon_Test::Unload(void)
{
	// NULLチェック
	if (m_pTexture != NULL)
	{
		// 破棄
		m_pTexture->Release();

		// NULL
		m_pTexture = NULL;
	}
}
//******************************************************************************
// 生成関数
//******************************************************************************
CPolygon_Test * CPolygon_Test::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	// CPolygonのポインタ
	CPolygon_Test *pPolygon;

	// メモリ確保
	pPolygon = new CPolygon_Test;

	// 情報設定
	pPolygon->SetPolygon(pos, rot, size, col);

	// テクスチャ受け渡し
	pPolygon->BindTexture(m_pTexture);

	// オブジェクトタイプ設定
	pPolygon->SetObjType(OBJTYPE_TEST);

	// 初期化
	pPolygon->Init();

	// ポインタを返す
	return pPolygon;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPolygon_Test::Init(void)
{
	// 初期化
	CScene3d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPolygon_Test::Uninit(void)
{
	// 終了
	CScene3d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPolygon_Test::Update(void)
{
	// 更新
	CScene3d::Update();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置更新
	SetPosition(pos);
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPolygon_Test::Draw(void)
{
	// 描画
	CScene3d::Draw();
}