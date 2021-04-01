//******************************************************************************
// ポリゴン[polygon.cpp]
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
#include "collision.h"
#include "polygon.h"
#include "polygon_test.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(2.0f, 2.0f, 0.0f))
#define RADIUS		(15.0f)
//******************************************************************************
// 静的メンバ変数初期化
//******************************************************************************
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = NULL;
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPolygon::CPolygon(int nPriority) : CScene3d(nPriority)
{
	m_posOld = INIT_D3DXVECTOR3;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CPolygon::~CPolygon()
{
}
//******************************************************************************
// テクスチャ読み込み関数
//******************************************************************************
HRESULT CPolygon::Load(void)
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
void CPolygon::Unload(void)
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
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	// CPolygonのポインタ
	CPolygon *pPolygon;

	// メモリ確保
	pPolygon = new CPolygon;

	// 情報設定
	pPolygon->SetPolygon(pos, rot, size, col);

	// テクスチャ
	pPolygon->BindTexture(m_pTexture);

	// 初期化
	pPolygon->Init();

	// ポインタを返す
	return pPolygon;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPolygon::Init(void)
{
	// 初期化
	CScene3d::Init();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CPolygon::Uninit(void)
{
	// 終了
	CScene3d::Uninit();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CPolygon::Update(void)
{
	// 更新
	CScene3d::Update();

	// 位置座標取得
	m_posOld = GetPosition();

	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();
	// 移動
	D3DXVECTOR3 move = INIT_D3DXVECTOR3;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//キーボードの取得
	CInputKeyboard *pKeyborad = CSceneManager::GetInputKeyboard();

	// 右移動
	if (pKeyborad->GetKeyPress(DIK_RIGHT))
	{
		// 移動
		move.x = -MOVE_VALUE.x;
	}
	// 左移動
	if (pKeyborad->GetKeyPress(DIK_LEFT))
	{
		// 移動
		move.x = MOVE_VALUE.x;
	}
	// 上移動
	if (pKeyborad->GetKeyPress(DIK_UP))
	{
		// 移動
		move.y = MOVE_VALUE.y;
	}
	// 下移動
	if (pKeyborad->GetKeyPress(DIK_DOWN))
	{
		// 移動
		move.y = -MOVE_VALUE.y;
	}
	

	// 移動
	pos.x += move.x;
	pos.y += move.y;

	// 位置更新
	SetPosition(pos);

	// 当たり判定処理
	//Collision();

	DotCollision();
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CPolygon::Draw(void)
{
	// 描画
	CScene3d::Draw();

}
//******************************************************************************
// 内積の当たり判定
//******************************************************************************
void CPolygon::DotCollision(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// CScene型のポインタ
	CScene *pScene = NULL;

	// 敵の当たり判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_TEST);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_TEST)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 Test_Pos = ((CPolygon_Test*)pScene)->GetPosition();

				// 位置
				float fDistance = powf(pos.x - Test_Pos.x, 2.0f) + powf(pos.y - Test_Pos.y, 2.0f) + powf(pos.z - Test_Pos.z, 2.0f);

				// 半径
				float fRadius = powf(RADIUS + RADIUS, 2.0f);

				// めり込んでいるか
				if (fDistance < fRadius)
				{
					// 移動量
					D3DXVECTOR3 move = MOVE_VALUE;

					float fAngle = MOVE_VALUE.x - fDistance * MOVE_VALUE.x / powf(fDistance, 2.0f) * fDistance;

					D3DXVECTOR3 movePos = (D3DXVECTOR3(cosf(D3DXToRadian(fAngle)),
						sinf(D3DXToRadian(fAngle)),
						0.0f));

					pos += movePos * 3.5f;

					// 位置設定
					SetPosition(pos);
				
				}
			}
		}
	} while (pScene != NULL);
}
//******************************************************************************
// 当たり判定処理関数
//******************************************************************************
void CPolygon::Collision(void)
{
	// 位置座標取得
	D3DXVECTOR3 pos = GetPosition();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// CScene型のポインタ
	CScene *pScene = NULL;

	// 敵の当たり判定
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_TEST);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_TEST)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 Test_Pos = ((CPolygon_Test*)pScene)->GetPosition();
				D3DXVECTOR3 Test_Size = ((CPolygon_Test*)pScene)->GetSize();

				if(CCollision::SphereCollision(pos, RADIUS, Test_Pos, RADIUS) == true)
				{
					// 位置座標設定
					SetPosition(m_posOld);

				}

			}
		}
	} while (pScene != NULL);
}