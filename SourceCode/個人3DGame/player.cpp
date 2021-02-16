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
#define BLOCK_SIZE			(D3DXVECTOR3(50.0f,50.0f,50.0f))			// 箱のサイズ
#define MOVE_VALUE			(D3DXVECTOR3(2.0f,2.0f,2.0f))				// 移動量
#define LINE_ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))				// 線の向き
#define LINE_ROT1			(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0f))// 線の向き
#define LINE_ROT2			(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))// 線の向き
#define LINE_ROT3			(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))// 線の向き
#define LINE_COLOR			(D3DXCOLOR(0.0f,0.8f,1.0f,1.0f))			// 色
#define POLYGON_SIZE		(D3DXVECTOR3(30.0f,30.0f,30.0f))			// サイズ
#define POLYGON_SIZE2		(D3DXVECTOR3(30.0f,30.0f,-30.0f))			// サイズ
#define PARENT_NUMBER		(-1)										// 親の数値
//******************************************************************************
// 静的メンバ変数
//******************************************************************************
LPD3DXMESH CPlayer::m_pMesh[MAX_PLAYER_PARTS] = {};
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PLAYER_PARTS] = {};
DWORD CPlayer::m_nNumMat[MAX_PLAYER_PARTS] = {};
D3DXMATRIX CPlayer::m_mtxWorld[MAX_PLAYER_PARTS] = {};
int CPlayer::m_nldxModelParent[MAX_PLAYER_PARTS] = {};
char* CPlayer::m_apFileName[MAX_PLAYER_PARTS] = {
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
CPlayer::CPlayer(int nPriority)
{
	m_pos			= INIT_D3DXVECTOR3;			// 場所
	m_rot			= INIT_D3DXVECTOR3;			// 角度
	m_size			= INIT_D3DXVECTOR3;			// 大きさ
	m_bAllMotion	= false;					// 全モーションの判定
	m_pMotion		= NULL;						// モーションクラスのポインタ
	m_pBlock		= NULL;						// 箱のポインタ
	memset(m_pModel, NULL, sizeof(m_pModel));	// モデルクラスのポインタ
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
	pPlayer->SetPlayer(pos, rot);

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
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);

	return S_OK;
}

//******************************************************************************
// 終了関数
//******************************************************************************
void CPlayer::Uninit(void)
{
	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
	// モーションの更新処理
	m_pMotion->UpdateMotion();

	// ニュートラルモーション
	m_pMotion->SetMotion(CMotion::MOTION_IDLE);

	// 移動処理
	Move();

	// 箱の処理
	Block();

	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
	{
		// モデルのパーツごとの座標と回転を受け取る
		m_pModel[nCount]->SetModel(m_pMotion->GetPos(nCount), m_pMotion->GetRot(nCount), m_size);
	}
	// 座標、回転、サイズのセット
	m_pModel[0]->SetModel(m_pMotion->GetPos(0) + m_pos, m_pMotion->GetRot(0) + m_rot, m_size);
}

//******************************************************************************
// 描画関数
//******************************************************************************
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;

	// パーツ数分繰り返す
	for (int nCount = INIT_INT; nCount < MAX_PLAYER_PARTS; nCount++)
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
void CPlayer::SetPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;
	m_rot = rot;
}
//******************************************************************************
// ブロック処理関数
//******************************************************************************
void CPlayer::Block(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}
	// NULLの場合
	if (m_pBlock == NULL)
	{
		// Xボタンを押し場合
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_X))
		{
			// 箱生成
			m_pBlock = CStone_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE, CBlock::TYPE_STONE);
		}
	}
	// NULLでない場合
	if (m_pBlock != NULL)
	{
		// Bボタンを押した場合
		if (pInputJoystick->GetJoystickTrigger(CInputJoystick::JS_B))
		{
			// 箱破棄
			m_pBlock->ReleaseBlock();

			// NULLに
			m_pBlock = NULL;
		}
		// RTを押した場合
		if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_RT))
		{
			// 移動
			m_pBlock->Move();
		}
		// LTを押して場合
		if (pInputJoystick->GetJoystickPress(CInputJoystick::JS_LT))
		{
			bool bP = true;
			// 終点
			D3DXVECTOR3 Pos = m_pBlock->GetPos();
			if (bP == true)
			{
				CFrame::FrameCreate(Pos, POLYGON_SIZE, LINE_COLOR, m_pBlock);
				bP = false;
			}
		}
	}
}
//******************************************************************************
// 移動処理関数
//******************************************************************************
void CPlayer::Move(void)
{
	// コントローラー取得
	DIJOYSTATE js;
	CInputJoystick * pInputJoystick = CSceneManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// 移動
	D3DXVECTOR3 move = INIT_D3DXVECTOR3;

	if (g_lpDIDevice != NULL)
	{
		// 上
		if (js.lY <= -STICK_REACTION)
		{
			move.y = MOVE_VALUE.y;
		}
		// 下
		if (js.lY >= STICK_REACTION)
		{
			move.y = -MOVE_VALUE.y;
		}
		// 左
		if (js.lX <= -STICK_REACTION)
		{
			move.x = MOVE_VALUE.x;
		}
		// 右
		if (js.lX >= STICK_REACTION)
		{
			move.x = -MOVE_VALUE.x;
		}
	}
	// 移動
	m_pos.x += move.x;
	m_pos.y += move.y;
}