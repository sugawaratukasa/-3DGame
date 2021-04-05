//******************************************************************************
// プレイヤーの処理 [player.h]
// Author : 管原　司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "manager.h"
#include "renderer.h"
#include "motion.h"
#include "model.h"
#include "joystick.h"
#include "block.h"
#include "stone_block.h"
#include "frame.h"
#include "collision.h"
#include "3d_obj.h"
#include "player.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define UNDER_BODY			("data/MODEL/PLAYER/00_UnderBody.x")		// 下半身
#define BODY				("data/MODEL/PLAYER/01_Body.x")				// 上半身
#define HEAD				("data/MODEL/PLAYER/02_Head.x")				// 頭
#define SHOULDER_R			("data/MODEL/PLAYER/03_shoulder_R.x")		// 右肩
#define UP_ARM_R			("data/MODEL/PLAYER/04_up_arm_R.x")			// 右上腕
#define DOWN_ARM_R			("data/MODEL/PLAYER/05_down_arm_R.x")		// 右前腕	
#define SHOULDER_L			("data/MODEL/PLAYER/06_shoulder_L.x")		// 左肩
#define UP_ARM_L			("data/MODEL/PLAYER/07_up_arm_L.x")			// 左上腕
#define DOWN_ARM_L			("data/MODEL/PLAYER/08_down_arm_L.x")		// 左前腕
#define THIGTS_R			("data/MODEL/PLAYER/09_Thigts_R.x")			// 右太もも
#define KNEE_R				("data/MODEL/PLAYER/10_Knee_R.x")			// 右膝
#define FOOT_R				("data/MODEL/PLAYER/11_foot_R.x")			// 右足
#define THIGTS_L			("data/MODEL/PLAYER/12_Thigts_L.x")			// 左太もも
#define KNEE_L				("data/MODEL/PLAYER/13_Knee_L.x")			// 左膝
#define FOOT_L				("data/MODEL/PLAYER/14_foot_L.x")			// 左足
#define MOTION_PLAYER_TEXT	("data/MODEL/PLAYER/Motion/motion.txt")		// モーションのテキスト
#define LOAD_PLAYER_TEXT	("data/MODEL/PLAYER/Motion/player.txt")		// 各モデルパーツの初期値
#define BLOCK_POS			(D3DXVECTOR3(m_pos.x,m_pos.y + 80,m_pos.z))	// 箱生成位置
#define BLOCK_ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))				// 箱の向き
#define BLOCK_SIZE			(D3DXVECTOR3(30.0f,30.0f,30.0f))			// 箱のサイズ
#define MOVE_VALUE			(D3DXVECTOR3(2.0f,2.0f,2.0f))				// 移動量
#define RIGHT_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))// 向き
#define LEFT_ROT			(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))// 向き
#define MIN_BLOCK_NUM		(0)											// ブロックの最小数
#define ARRAY_FIRST_NUM		(0)											// 配列の先頭
#define ARRAY_MOVE_NUMBER	(1)											// 配列の移動
#define ARRAY_SUB_VALUE		(1)											// 配列に合わせるための値
#define DEVIDE_VALUE		(2.0f)										// 割る数
#define PARENT_NUMBER		(-1)										// 親の数値
#define ROT_MOVE			(0.2f)										// 向きの移動
#define POW_VALUE			(2.0f)										// 二乗
#define MIN_MOVE_VALUE		(0.0f)										// 移動量の最小値
#define GRAVITY_VALUE		(-1.5f)										// 重力
#define JUMP_VALUE			(21.5f)										// ジャンプ量
#define JUMP_VALUE_2		(0.1f)										// ジャンプ量
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPD3DXMESH CPlayer::m_pMesh[PARTS_MAX] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[PARTS_MAX] = {};
DWORD CPlayer::m_nNumMat[PARTS_MAX] = {};
D3DXMATRIX CPlayer::m_mtxWorld[PARTS_MAX] = {};
int CPlayer::m_nldxModelParent[PARTS_MAX] = {};
char* CPlayer::m_apFileName[PARTS_MAX] = {
	UNDER_BODY,
	BODY,
	HEAD,
	SHOULDER_R,
	UP_ARM_R,
	DOWN_ARM_R,
	SHOULDER_L,
	UP_ARM_L,
	DOWN_ARM_L,
	THIGTS_R,
	KNEE_R,
	FOOT_R,
	THIGTS_L,
	KNEE_L,
	FOOT_L,
};
//******************************************************************************
// コンストラクタ
//******************************************************************************
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_pos					= INIT_D3DXVECTOR3;		
	m_posOld				= INIT_D3DXVECTOR3;		
	m_rot					= INIT_D3DXVECTOR3;		
	m_size					= INIT_D3DXVECTOR3;		
	m_move					= INIT_D3DXVECTOR3;		
	m_bAllMotion			= false;				
	m_pMotion				= NULL;					
	m_pBlock				= NULL;	
	m_pStoneBlock			= NULL;
	m_Blcok_Active			= BLOCK_ACTIVE_NONE;	
	m_nBlockNum				= INIT_INT;				
	m_nBlock_Select_Num		= INIT_INT;				
	m_bStick				= false;				
	m_Rot_State				= ROT_STATE_RIGHT;		
	m_bJump					= false;				
	m_bJumpValue			= false;
	memset(m_pModel, NULL, sizeof(m_pModel));		
}

//******************************************************************************
// デストラクタ
//******************************************************************************
CPlayer::~CPlayer()
{

}

//******************************************************************************
// 生成関数
//******************************************************************************
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size)
{
	// CPlayerのポインタ
	CPlayer *pPlayer;

	// メモリ確保
	pPlayer = new CPlayer;

	// 情報設定
	pPlayer->SetPlayer(pos, rot, size);

	// 初期化
	pPlayer->Init();

	// ポインタを返す
	return pPlayer;
}

//******************************************************************************
// 読み込み関数
//******************************************************************************
HRESULT CPlayer::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_apFileName[nCount],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCount],
			NULL,
			&m_nNumMat[nCount],
			&m_pMesh[nCount]
		);
	}
	
	return S_OK;
}

//******************************************************************************
// 読み込み破棄関数
//******************************************************************************
void CPlayer::Unload(void)
{
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// メッシュの破棄
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}

		// マテリアルの破棄
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}

		if (m_nNumMat[nCount] != NULL)
		{
			m_nNumMat[nCount] = NULL;
		}
	}
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CPlayer::Init(void)
{
	// モーションの生成
	m_pMotion = CMotion::Create();

	// モーションの読み込み
	m_pMotion->Load(LOAD_PLAYER_TEXT);
	m_pMotion->LoadMotion(MOTION_PLAYER_TEXT);

	// モーションの初期設定
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// モデルの生成
		m_pModel[nCount] = CModel::Create();

		// ペアレントの受け取り
		m_nldxModelParent[nCount] = m_pMotion->GetParents(nCount);

		// モデルのバインド
		m_pModel[nCount]->BindModel(m_pMesh[nCount], m_pBuffMat[nCount], m_nNumMat[nCount], m_nldxModelParent[nCount]);

		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// 座標、回転、サイズのセット
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// 終了関数
//******************************************************************************
void CPlayer::Uninit(void)
{
	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		if (m_pModel[nCount] != NULL)
		{
			// モデルクラスの終了処理
			m_pModel[nCount]->Uninit();
			m_pModel[nCount] = NULL;
		}
	}
	// NULLチェック
	if (m_pMotion != NULL)
	{
		// モーションクラスの終了処理
		m_pMotion->Uninit();
		m_pMotion = NULL;
	}

	// リリース
	Release();
}

//******************************************************************************
// 更新関数
//******************************************************************************
void CPlayer::Update(void)
{
	// 位置代入
	m_posOld = m_pModel[PARTS_UNDER_BODY]->GetPos();

	// コントローラー取得
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
	}

	// モーションの更新処理
	m_pMotion->UpdateMotion();

	// NULLでない場合
	if (m_pBlock != NULL)
	{
		// 右向きの場合
		if (m_Rot_State == ROT_STATE_RIGHT)
		{
			// LTを押した場合
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
			{

				// 0に
				m_nBlock_Select_Num = MIN_BLOCK_NUM;

				// 選択中の状態に
				m_Blcok_Active = BLOCK_ACTIVE_SELECT;
			}
			// 選択中の状態の場合
			if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
			{
				// 箱の選択処理
				RightSelectionBlock();
			}
			// ブロックで何もしていない状態
			if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
			{
				// 右向きの時ブロックを最も近いブロックを選択中にする処理
				RightSelectBlock();
			}
			// 箱の処理
			RightBlock();
		}
		// 左向きの場合
		if (m_Rot_State == ROT_STATE_LEFT)
		{
			// LTを押した場合
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_LT))
			{
				// 0に
				m_nBlock_Select_Num = MIN_BLOCK_NUM;

				// 選択中の状態に
				m_Blcok_Active = BLOCK_ACTIVE_SELECT;
			}
			// 選択中の状態の場合
			if (m_Blcok_Active == BLOCK_ACTIVE_SELECT)
			{
				// 箱の選択処理
				LeftSelectionBlock();
			}
			// ブロックで何もしていない状態
			if (m_Blcok_Active == BLOCK_ACTIVE_NONE)
			{
				// 左向きの時ブロックを最も近いブロックを選択中にする処理
				LeftSelectBlock();
			}
			// 箱の処理
			LeftBlock();
		}
	}
	// Xボタンが押された場合
	if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_X))
	{
		// ブロック生成
		Block_Crate();
	}
	// ブロック選択中でない場合
	if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
	{
		// 移動処理
		Move();
	}

	// パーツ数分回す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}

	// 座標、回転、サイズのセット
	m_pModel[PARTS_UNDER_BODY]->SetModel(m_pMotion->GetPos(PARTS_UNDER_BODY) + m_pos, m_pMotion->GetRot(PARTS_UNDER_BODY) + m_rot, m_size);

	// 当たり判定
	Collision();
}

//******************************************************************************
// 描画関数
//******************************************************************************
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < PARTS_MAX; nCount++)
	{
		//ワールドマトリクスの初期化
		D3DXMatrixIdentity(&m_mtxWorld[nCount]);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld[nCount], &m_mtxWorld[nCount], &mtxTrans);

		// 親のモデルパーツ以外のペアレントをセット
		if (m_nldxModelParent[nCount] != PARENT_NUMBER)
		{
			m_pModel[nCount]->SetParent(m_pModel[m_nldxModelParent[nCount]]);
		}

		// モデルクラスの描画処理
		m_pModel[nCount]->Draw();
	}
}
//******************************************************************************
// 情報設定
//******************************************************************************
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot ,D3DXVECTOR3 size)
{
	m_pos = pos;
	m_rot = rot;
	m_size = size;

	// オブジェクトタイプ設定
	SetObjType(OBJTYPE_PLAYER);
}
//******************************************************************************
// 位置設定
//******************************************************************************
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//******************************************************************************
// 箱の選択
//******************************************************************************
void CPlayer::RightSelectBlock(void)
{
	// CSceneのポインタ
	CScene *pScene = NULL;

	// 箱
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();
			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// プレイヤーが正面を向いていて箱の位置が前にある場合
				if (m_pos.x > BlockPos.x)
				{
					// インクリメント
					m_nBlockNum++;
				}
				// プレイヤーが正面を向いていて箱の位置が前後ろにある場合
				if (m_pos.x < BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);
					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// プレイヤーが右を向いていて箱の位置が前にある場合
							if (m_pos.x > BlockPos.x)
							{
								// ポインタ代入
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// インクリメント
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// floatのポインタ
				float *anLength = NULL;

				// NULLの場合
				if (anLength == NULL)
				{
					// メモリ確保
					anLength = new float[m_nBlockNum];
					// NULLでない場合
					if (anLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();
							// プレイヤーとの距離
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]anLength;

					// NULLに
					anLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->UnSelected();
				}

				// 配列の先頭を代入
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}
	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// ブロック処理関数
//******************************************************************************
void CPlayer::RightBlock(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULLでない場合
	if (m_pBlock != NULL)
	{
		// 箱の位置取得
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// プレイヤーが右を向いていて箱の位置が後ろにある場合
		if (m_pos.x < BlockPos.x)
		{
			// 選択外に
			m_pBlock->UnSelected();

			// ブロックを移動状態に
			m_Blcok_Active = BLOCK_ACTIVE_NONE;
		}
		// プレイヤーが右を向いていて箱の位置が前にある場合
		if (m_pos.x > BlockPos.x)
		{
			// 選択中の場合
			m_pBlock->Selecting();

			// 選択状態以外の場合
			if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
			{
				// RTを押した場合
				if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
				{
					// 移動状態に
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// ブロックの移動
					m_pBlock->Move();
				}
			}
		}
	}
}
//******************************************************************************
// 動かすブロックを選択中
//******************************************************************************
void CPlayer::RightSelectionBlock(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// CSceneのポインタ
	CScene *pScene = NULL;

	// 箱
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// プレイヤーが正面を向いていて箱の位置が前にある場合
				if (m_pos.x > BlockPos.x)
				{
					// インクリメント
					m_nBlockNum++;
				}
				// プレイヤーが正面を向いていて箱の位置が前後ろにある場合
				if (m_pos.x < BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	// 0より多い場合
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// プレイヤーが右を向いていて箱の位置が前にある場合
							if (m_pos.x > BlockPos.x)
							{
								// ポインタ代入
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// インクリメント
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// floatのポインタ
				float *anLength = NULL;

				// NULLの場合
				if (anLength == NULL)
				{
					// メモリ確保
					anLength = new float[m_nBlockNum];

					// NULLでない場合
					if (anLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// プレイヤーとの距離
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (anLength[nCnt] > anLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							anLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]anLength;

					// NULLに
					anLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->PlayerSelection();
				}
				// 選択終了状態でない場合
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0番目以外未選択状態に
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// 選択終了の色に
						apBlock[nCnt]->UnSelected();
					}

					// 選択した状態
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// 色選択中の色に
				apBlock[m_nBlock_Select_Num]->Selecting();

				// 選択しているブロックの配列を代入
				m_pBlock = apBlock[m_nBlock_Select_Num];
			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}

	// 数保存
	m_nSelect_Save_Num = m_nBlockNum;

	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// falseの場合
		if (m_bStick == false)
		{
			// 右スティックを左に倒す
			if (js.lZ >= STICK_REACTION)
			{
				// 0番目の場合
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// デクリメント
					m_nBlock_Select_Num--;
				}
				// 0番目の場合
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// ブロックの最大値にする
					//m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;

					// ブロックの最大値にする
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}

				// trueに
				m_bStick = true;
			}
			// 右スティックを右に倒す
			if (js.lZ <= -STICK_REACTION)
			{
				// 最大値の場合
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// インクリメント
					m_nBlock_Select_Num++;
				}
				// 最大値の場合
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0番目に設定
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}

				// trueに
				m_bStick = true;
			}
		}
		// trueの場合
		if (m_bStick == true)
		{
			// -500より大きく0より小さい場合
			if (js.lZ > -STICK_REACTION && js.lZ <= INIT_INT)
			{
				m_bStick = false;
			}
			// 500より小さく0より大きい場合
			if (js.lZ < STICK_REACTION && js.lZ >= INIT_INT)
			{
				m_bStick = false;
			}
		}
		// 0より低い場合
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0に設定
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// 箱の数より大きい場合
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// 箱の数と同じにする
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// 左箱の選択
//******************************************************************************
void CPlayer::LeftSelectBlock(void)
{
	// CSceneのポインタ
	CScene *pScene = NULL;

	// 箱
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();
			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// プレイヤーが左を向いていて箱の位置が前にある場合
				if (m_pos.x < BlockPos.x)
				{
					// インクリメント
					m_nBlockNum++;
				}
				// プレイヤーが左を向いていて箱の位置が前後ろにある場合
				if (m_pos.x > BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);
					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// プレイヤーが右を向いていて箱の位置が前にある場合
							if (m_pos.x < BlockPos.x)
							{
								// ポインタ代入
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// インクリメント
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// floatのポインタ
				float *anLength = NULL;

				// NULLの場合
				if (anLength == NULL)
				{
					// メモリ確保
					anLength = new float[m_nBlockNum];
					// NULLでない場合
					if (anLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();
							// プレイヤーとの距離
							anLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum - ARRAY_MOVE_NUMBER; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (anLength[nCnt] < anLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = anLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							anLength[nFirst_Array] = anLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							anLength[nMin_Length] = fArray_Move;
							apBlock[nMin_Length] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]anLength;

					// NULLに
					anLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->UnSelected();
				}

				// 配列の先頭を代入
				m_pBlock = apBlock[ARRAY_FIRST_NUM];

			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}
	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;
}
//******************************************************************************
// ブロック処理関数
//******************************************************************************
void CPlayer::LeftBlock(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// NULLでない場合
	if (m_pBlock != NULL)
	{
		// 箱の位置取得
		D3DXVECTOR3 BlockPos = m_pBlock->GetPos();

		// プレイヤーが左を向いていて箱の位置が後ろにある場合
		if (m_pos.x > BlockPos.x)
		{
			// 選択外に
			m_pBlock->UnSelected();

			// ブロックを移動状態に
			m_Blcok_Active = BLOCK_ACTIVE_NONE;
		}
		// プレイヤーが左を向いていて箱の位置が前にある場合
		if (m_pos.x < BlockPos.x)
		{
			// 選択中の場合
			m_pBlock->Selecting();

			// 選択状態以外の場合
			if (m_Blcok_Active != BLOCK_ACTIVE_SELECT)
			{
				// RTを押した場合
				if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
				{
					// 移動状態に
					m_Blcok_Active = BLOCK_ACTIVE_MOVE;

					// ブロックの移動
					m_pBlock->Move();
				}
			}
		}
	}
}
//******************************************************************************
// 動かすブロックを選択中
//******************************************************************************
void CPlayer::LeftSelectionBlock(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// CSceneのポインタ
	CScene *pScene = NULL;

	// 箱
	do
	{
		// オブジェタイプが敵の場合
		pScene = GetScene(OBJTYPE_BLOCK);

		// NULLの場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objType = pScene->GetObjType();

			// オブジェクトタイプがBLOCKの場合
			if (objType == OBJTYPE_BLOCK)
			{
				// 座標とサイズ取得
				D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

				// プレイヤーが正面を向いていて箱の位置が前にある場合
				if (m_pos.x < BlockPos.x)
				{
					// インクリメント
					m_nBlockNum++;
				}
				// プレイヤーが正面を向いていて箱の位置が前後ろにある場合
				if (m_pos.x > BlockPos.x)
				{
					((CBlock*)pScene)->UnSelected();
				}
			}
		}
	} while (pScene != NULL);

	// 0より多い場合
	if (m_nBlockNum > MIN_BLOCK_NUM)
	{
		// NULLに
		CBlock **apBlock = NULL;

		// NULLの場合
		if (apBlock == NULL)
		{
			// メモリ確保
			apBlock = new CBlock*[m_nBlockNum];

			// 最小数に
			m_nBlockNum = MIN_BLOCK_NUM;

			// NULLでない場合
			if (apBlock != NULL)
			{
				do
				{
					// オブジェタイプが敵の場合
					pScene = GetScene(OBJTYPE_BLOCK);

					// NULLでない場合
					if (pScene != NULL)
					{
						// オブジェクトタイプ取得
						OBJTYPE objType = pScene->GetObjType();

						// オブジェクトタイプがBLOCKの場合
						if (objType == OBJTYPE_BLOCK)
						{
							// 座標とサイズ取得
							D3DXVECTOR3 BlockPos = ((CBlock*)pScene)->GetPos();

							// プレイヤーが左を向いていて箱の位置が前にある場合
							if (m_pos.x < BlockPos.x)
							{
								// ポインタ代入
								apBlock[m_nBlockNum] = (CBlock*)pScene;

								// インクリメント
								m_nBlockNum++;
							}
						}
					}
				} while (pScene != NULL);

				// floatのポインタ
				float *afLength = NULL;

				// NULLの場合
				if (afLength == NULL)
				{
					// メモリ確保
					afLength = new float[m_nBlockNum];

					// NULLでない場合
					if (afLength != NULL)
					{
						// ブロック数分回す
						for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
						{
							// 位置座標
							D3DXVECTOR3 BlockPos = apBlock[nCnt]->GetPos();

							// プレイヤーとの距離
							afLength[nCnt] = sqrtf(powf(m_pos.x - BlockPos.x, POW_VALUE) + powf(m_pos.y - BlockPos.y, POW_VALUE));
						}

						// 配列の先頭
						int nFirst_Array;

						// 最小値
						int nMin_Length;

						// 一時保存
						float fArray_Move;

						// 一時保存
						CBlock *pBlock_Save;

						// ブロック数分回す
						for (nFirst_Array = INIT_INT; nFirst_Array < m_nBlockNum; nFirst_Array++)
						{
							// 配列の先頭を最小値に
							nMin_Length = nFirst_Array;

							// 比較
							for (int nCnt = nFirst_Array + ARRAY_MOVE_NUMBER; nCnt < m_nBlockNum; nCnt++)
							{
								// 距離が最小値より近い場合
								if (afLength[nCnt] > afLength[nMin_Length])
								{
									// 代入
									nMin_Length = nCnt;
								}
							}
							// 先頭の配列の値をを保存
							fArray_Move = afLength[nFirst_Array];
							pBlock_Save = apBlock[nFirst_Array];

							// 先頭の配列に最小値代入
							afLength[nFirst_Array] = afLength[nMin_Length];
							apBlock[nFirst_Array] = apBlock[nMin_Length];

							// 最小値に元の先頭の値を代入
							afLength[nMin_Length] = fArray_Move;
							apBlock[nFirst_Array] = pBlock_Save;
						}
					}
					// メモリ破棄
					delete[]afLength;

					// NULLに
					afLength = NULL;
				}
				// 0番目以外未選択状態に
				for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
				{
					// 未選択状態に
					apBlock[nCnt]->PlayerSelection();
				}
				// 選択終了状態でない場合
				if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickRelease(CInputJoystick::JS_LT))
				{
					// 0番目以外未選択状態に
					for (int nCnt = INIT_INT; nCnt < m_nBlockNum; nCnt++)
					{
						// 選択終了の色に
						apBlock[nCnt]->UnSelected();
					}

					// 選択した状態
					m_Blcok_Active = BLOCK_ACTIVE_SELECTED;
				}
				// 色選択中の色に
				apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num]->Selecting();

				// 選択しているブロックの配列を代入
				m_pBlock = apBlock[m_nBlockNum - ARRAY_SUB_VALUE - m_nBlock_Select_Num];
			}
			// メモリ破棄
			delete[]apBlock;

			// NULLに
			apBlock = NULL;
		}
	}

	// 数保存
	m_nSelect_Save_Num = m_nBlockNum;

	// 最小数に
	m_nBlockNum = MIN_BLOCK_NUM;

	if (g_lpDIDevice != NULL)
	{
		// falseの場合
		if (m_bStick == false)
		{
			// 右スティックを左に倒す
			if (js.lZ >= STICK_REACTION)
			{
				// 最大値の場合
				if (m_nBlock_Select_Num < m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// インクリメント
					m_nBlock_Select_Num++;
				}
				// 最大値の場合
				if (m_nBlock_Select_Num >= m_nSelect_Save_Num - ARRAY_SUB_VALUE)
				{
					// 0番目に設定
					m_nBlock_Select_Num = m_nSelect_Save_Num - ARRAY_SUB_VALUE;
				}
				// trueに
				m_bStick = true;
			}
			// 右スティックを右に倒す
			if (js.lZ <= -STICK_REACTION)
			{
				// 0番目の場合
				if (m_nBlock_Select_Num > MIN_BLOCK_NUM)
				{
					// デクリメント
					m_nBlock_Select_Num--;
				}
				// 0番目の場合
				if (m_nBlock_Select_Num == MIN_BLOCK_NUM)
				{
					// ブロックの最大値にする
					m_nBlock_Select_Num = MIN_BLOCK_NUM;
				}
				// trueに
				m_bStick = true;
			}
		}
		// trueの場合
		if (m_bStick == true)
		{
			// -500より大きく0より小さい場合
			if (js.lZ > -STICK_REACTION && js.lZ <= 0)
			{
				m_bStick = false;
			}
			// 500より小さく0より大きい場合
			if (js.lZ < STICK_REACTION && js.lZ >= 0)
			{
				m_bStick = false;
			}
		}
		// 0より引く場合
		if (m_nBlock_Select_Num < MIN_BLOCK_NUM)
		{
			// 0に設定
			m_nBlock_Select_Num = MIN_BLOCK_NUM;
		}
		// 箱の数より大きい場合
		if (m_nBlock_Select_Num > m_nSelect_Save_Num)
		{
			// 箱の数と同じにする
			m_nBlock_Select_Num = m_nSelect_Save_Num;
		}
	}
}
//******************************************************************************
// ブロック生成関数
//******************************************************************************
void CPlayer::Block_Crate(void)
{
	// NULLの場合
	if (m_pStoneBlock == NULL)
	{
		// 生成
		m_pStoneBlock = CStone_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);

		// 代入
		m_pBlock = m_pStoneBlock;
	}
	// NULLでない場合
	if (m_pStoneBlock != NULL)
	{
		// 破棄
		m_pStoneBlock->ReleaseBlock();

		// 生成
		m_pStoneBlock = CStone_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);

		// 代入
		m_pBlock = m_pStoneBlock;
	}
}												   
//******************************************************************************
// 当たり判定処理関数
//******************************************************************************
void CPlayer::Collision(void)
{
	// 位置
	D3DXVECTOR3 pos = m_pModel[PARTS_UNDER_BODY]->GetPos();

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

				 //どこの面に当たったか取得
				 //下
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (m_size.y / DEVIDE_VALUE) - (BlockPos.y + BlockSize.y / DEVIDE_VALUE);
				}
				// 上
				else if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (-m_size.y / DEVIDE_VALUE) + (BlockPos.y + BlockSize.y / DEVIDE_VALUE);

					// trueの場合
					if (m_bJump == true)
					{
						// falseに
						m_bJump = false;
					}
				}
				// 左
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (-m_size.x / DEVIDE_VALUE) + (BlockPos.x - BlockSize.x / DEVIDE_VALUE);
				}
				// 右
				else if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, BlockPos, BlockSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (m_size.x / DEVIDE_VALUE) + (BlockPos.x + BlockSize.x / DEVIDE_VALUE);

				}
			}
		}
	} while (pScene != NULL);

	// 3Dオブジェクトとの当たり判定
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
				//どこの面に当たったか取得
				//下
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_DOWN)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (m_size.y / DEVIDE_VALUE) - (ObjPos.y + ObjSize.y / DEVIDE_VALUE);

				}
				// 上
				if (CCollision::RectangleCollisionMove(m_pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_UP)
				{
					// 移動量0
					m_move.y = MIN_MOVE_VALUE;

					// 位置
					m_pos.y = (-m_size.y / DEVIDE_VALUE) + (ObjPos.y + ObjSize.y / DEVIDE_VALUE);

					// trueの場合
					if (m_bJump == true)
					{
						// falseに
						m_bJump = false;

						// falseに
						m_bJumpValue = false;
					}
				}
				// 左
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_LEFT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (-m_size.x / DEVIDE_VALUE) + (ObjPos.x - ObjSize.x / DEVIDE_VALUE);
				}
				// 右
				if (CCollision::RectangleCollisionMove(pos, m_posOld, m_size, ObjPos, ObjSize) == CCollision::SURFACE_RIGHT)
				{
					// 移動量0
					m_move.x = MIN_MOVE_VALUE;

					// 位置
					m_pos.x = (m_size.x / DEVIDE_VALUE) + (ObjPos.x + ObjSize.x / DEVIDE_VALUE);

				}
			}
		}
		// pSceneがNULLの場合
	} while (pScene != NULL);
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CPlayer::Move(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// 目的の向き
	D3DXVECTOR3 RotDest = m_rot;

	if (g_lpDIDevice != NULL)
	{
		// 左
		if (js.lX <= -STICK_REACTION)
		{
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				if (m_pBlock != NULL)
				{
					if (m_Rot_State == ROT_STATE_RIGHT)
					{
						// 移動モーション
						m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

						// 後ろ
						m_move.x = -MOVE_VALUE.x;

						// 向き
						RotDest.y = RIGHT_ROT.y;
					}
					if (m_Rot_State == ROT_STATE_LEFT)
					{
						// 移動モーション
						m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

						// 後ろ
						m_move.x = MOVE_VALUE.x / DEVIDE_VALUE;

						// 向き
						RotDest.y = RIGHT_ROT.y;
					}
				}
			}
			else
			{
				// 移動モーション
				m_pMotion->SetMotion(CMotion::MOTION_RUN);

				// 後ろ
				m_move.x = -MOVE_VALUE.x;

				// 向き
				RotDest.y = RIGHT_ROT.y;

				// 左向きの状態
				m_Rot_State = ROT_STATE_RIGHT;
			}
		}
		// 右
		if (js.lX >= STICK_REACTION)
		{
			if (g_lpDIDevice != NULL && pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
			{
				if (m_pBlock != NULL)
				{
					if (m_Rot_State == ROT_STATE_LEFT)
					{
						// 移動モーション
						m_pMotion->SetMotion(CMotion::MOTION_BLOCK_RUN);

						// 後ろ
						m_move.x = MOVE_VALUE.x;

						// 向き
						RotDest.y = LEFT_ROT.y;
					}
					if (m_Rot_State == ROT_STATE_RIGHT)
					{
						// 移動モーション
						m_pMotion->SetMotion(CMotion::MOTION_BACKRUN);

						// 後ろ
						m_move.x = -MOVE_VALUE.x / DEVIDE_VALUE;

						// 向き
						RotDest.y = LEFT_ROT.y;
					}
				}
			}
			else
			{
				// 移動モーション
				m_pMotion->SetMotion(CMotion::MOTION_RUN);

				// 前に進む
				m_move.x = MOVE_VALUE.x;

				// 向き
				RotDest.y = LEFT_ROT.y;

				// 右向きの状態
				m_Rot_State = ROT_STATE_LEFT;
			}
		}
		// スティックの範囲外の場合
		if (js.lX > -STICK_REACTION && js.lX < STICK_REACTION)
		{
			// 移動量0
			m_move.x = MIN_MOVE_VALUE;

			// ニュートラルモーション
			m_pMotion->SetMotion(CMotion::MOTION_IDLE);
		}
		// ジャンプ
		if (m_bJump == false)
		{
			// Aボタンを押した場合
			if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_A))
			{
				// falseの場合
				if (m_bJumpValue == false)
				{
					// 移動
					m_move.y += JUMP_VALUE;

					m_bJumpValue = true;
				}
				// trueの場合
				if (m_bJumpValue == true)
				{
					// 移動
					m_move.y += JUMP_VALUE_2;
				}

				// trueに
				m_bJump = true;
			}
		}
	}

	// 向き
	m_rot += (RotDest - m_rot) * ROT_MOVE;

	// 重力
	m_move.y += GRAVITY_VALUE;

	// 移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
}