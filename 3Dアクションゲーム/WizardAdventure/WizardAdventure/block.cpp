//******************************************************************************
// ブロック[block.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "input.h"
#include "joystick.h"
#include "model.h"
#include "frame.h"
#include "collision.h"
#include "block.h"
#include "3d_obj.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define MOVE_VALUE		(D3DXVECTOR3(2.0f,2.0f,0.0f))						// 移動量
#define FRAME_COLOR1	(D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))					// 枠の色
#define FRAME_COLOR2	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// 枠の色
#define FRAME_COLOR3	(D3DXCOLOR(0.0f,0.8f,1.0f,1.0f))					// 枠の色
#define FRAME_ROT1		(D3DXVECTOR3(0.0f,D3DXToRadian(180.0f),0.0f))		// 枠の向き
#define MIN_MOVE_VALUE	(0)													// 移動量の最小値
#define DEVIDE_VALUE	(2.0f)													// 割る数
//******************************************************************************
// コンストラクタ
//******************************************************************************
CBlock::CBlock(int nPriority) :C3D_Obj(nPriority)
{
	m_posOld	= INIT_D3DXVECTOR3;
	m_move		= INIT_D3DXVECTOR3;
	m_pBlock	= NULL;
	m_pFrame	= NULL;
}

//******************************************************************************
// デストラクタ
//******************************************************************************
CBlock::~CBlock()
{

}

//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CBlock::Init(void)
{
	// 初期化
	C3D_Obj::Init();

	// 枠を生成
	SetFrame();

	return S_OK;
}

//******************************************************************************
// 終了処理
//******************************************************************************
void CBlock::Uninit(void)
{
	// 終了
	C3D_Obj::Uninit();
}

//******************************************************************************
// 更新処理
//******************************************************************************
void CBlock::Update(void)
{
	// 1フレーム前の
	D3DXVECTOR3 posOld = GetPos();

	// 更新
	C3D_Obj::Update();

	// サイズ取得
	D3DXVECTOR3 size = GetSize();

	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// 位置設定
	SetPos(pos);

	// 当たり判定
	Collision(pos, posOld, size);
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CBlock::Draw(void)
{
	// 描画
	C3D_Obj::Draw();
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CBlock::Move(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	js.lZ = NULL;
	js.lRz = NULL;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	// 位置
	D3DXVECTOR3 pos = GetPos();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	if (g_lpDIDevice != NULL)
	{
		// スティックの範囲外の場合
		if (js.lZ > -STICK_REACTION && js.lZ < STICK_REACTION)
		{
			// 移動量0
			m_move.y = MIN_MOVE_VALUE;
		}
		if (js.lRz > -STICK_REACTION && js.lRz < STICK_REACTION)
		{
			// 移動量0
			m_move.x = MIN_MOVE_VALUE;
		}
		// 右スティックを左に倒す
		if (js.lZ <= -STICK_REACTION)
		{
			m_move.x = -MOVE_VALUE.x;
		}
		// 右スティックを右に倒す
		if (js.lZ >= STICK_REACTION)
		{
			m_move.x = MOVE_VALUE.x;
		}
		// 右スティックを上に倒す
		if (js.lRz <= -STICK_REACTION)
		{
			m_move.y = MOVE_VALUE.y;
		}
		// 右スティックを下に倒す
		if (js.lRz >= STICK_REACTION)
		{
			m_move.y = -MOVE_VALUE.y;
		}
	}

	// 移動
	pos.x += m_move.x;
	pos.y += m_move.y;

	// 位置設定
	SetPos(pos);
}
//******************************************************************************
// 破棄関数
//******************************************************************************
void CBlock::ReleaseBlock(void)
{
	// 破棄
	Uninit();

	return;
}
//******************************************************************************
// フレーム生成
//******************************************************************************
void CBlock::SetFrame(void)
{
	// 位置
	D3DXVECTOR3 pos	= GetPos();
	D3DXVECTOR3 size = GetSize();

	// フレーム生成
	m_pFrame = CFrame::Create(pos, FRAME_ROT1, size, FRAME_COLOR1, m_pBlock);
}
//******************************************************************************
// 選択されている場合
//******************************************************************************
void CBlock::Selecting(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR3);
}
//******************************************************************************
// 未選択の場合
//******************************************************************************
void CBlock::UnSelected(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR1);
}
//******************************************************************************
// プレイヤーが選択中の場合
//******************************************************************************
void CBlock::PlayerSelection(void)
{
	m_pFrame->SetSelectingColor(FRAME_COLOR2);
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CBlock::SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, TYPE type, CBlock *pBlock)
{
	SetModel(pos, rot, size, type);
	m_pBlock = pBlock;

	// オブジェタイプをブロックに設定
	SetObjType(OBJTYPE_BLOCK);
}
//******************************************************************************
// 当たり判定
//******************************************************************************
void CBlock::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 size)
{
	// ブロックとの当たり判定
	CScene *pScene = NULL;
	do
	{
		// オブジェタイプがブロックの場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプが敵
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();
				D3DXVECTOR3 BlockSize = ((CBlock*)pScene)->GetSize();

				// どこの面に当たったか
				//下
				if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_DOWN)
				{

					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					pos.y = (-size.y / DEVIDE_VALUE) + (BlockPos.y - BlockSize.y / DEVIDE_VALUE);

				}
				// 上
				if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					pos.y = (size.y / DEVIDE_VALUE) + (BlockPos.y + BlockSize.y / DEVIDE_VALUE);

				}
				// 右
				if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					pos.x = (size.x / DEVIDE_VALUE) + (BlockPos.x + BlockSize.x / DEVIDE_VALUE);

				}
				// 左
				if (CCollision::RectangleCollisionMove(pos, posOld, size, BlockPos, BlockSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					pos.x = (-size.x / DEVIDE_VALUE) + (BlockPos.x - BlockSize.x / DEVIDE_VALUE);
				}
			}
		}
	} while (pScene != NULL);

	// マップオブジェクトの当たり判定
	do
	{
		// オブジェタイプがブロックの場合
		pScene = GetScene(OBJTYPE_MAP_OBJ);

		// NULLチェック
		if (pScene != NULL)
		{
			// オブジェタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプが敵
			if (objType == OBJTYPE_MAP_OBJ)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 ObjPos = ((C3D_Obj*)pScene)->GetPos();
				D3DXVECTOR3 ObjSize = ((C3D_Obj*)pScene)->GetSize();

				// どこの面に当たったか
				//下
				if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					pos.y = (-size.y / DEVIDE_VALUE) + (ObjPos.y - ObjSize.y / DEVIDE_VALUE);
				}
				// 上
				if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					pos.y = (size.y / DEVIDE_VALUE) + (ObjPos.y + ObjSize.y / DEVIDE_VALUE);
				}
				// 右
				if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					pos.x = (size.x / DEVIDE_VALUE) + (ObjPos.x + ObjSize.x / DEVIDE_VALUE);

				}
				// 左
				if (CCollision::RectangleCollisionMove(pos, posOld, size, ObjPos, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					pos.x = (-size.x / DEVIDE_VALUE) + (ObjPos.x - ObjSize.x / DEVIDE_VALUE);
				}
			}
		}
	} while (pScene != NULL);

	// 位置設定
	SetPos(pos);
}