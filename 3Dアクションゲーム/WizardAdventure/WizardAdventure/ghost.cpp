//******************************************************************************
// 幽霊[ghost.cpp]
// Author : 管原 司
//******************************************************************************

//******************************************************************************
//インクルードファイル
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene3d.h"
#include "model.h"
#include "player.h"
#include "particle_emitter.h"
#include "magic.h"
#include "enemy_life_gage.h"
#include "ghost.h"
//******************************************************************************
// マクロ定義
//******************************************************************************
#define POS			(D3DXVECTOR3(pos.x,pos.y + 15.0f,pos.z - 8.0f))						// 位置
#define ATTACK_POS	(D3DXVECTOR3(pos.x,pos.y + 15.0f,pos.z))							// 位置
#define ROT			(D3DXVECTOR3(0.0f,0.0f,0.0f))										// 向き
#define MAGIC_MOVE	(D3DXVECTOR3(cosf(fAngle) * 2.0f, sinf(fAngle) * 2.0f, 0.0f))		// 魔法の移動
#define ATTACKCOUNT	(200)																// 攻撃カウント
#define REMAINDER	(0)																	// 余り
#define MAX_LIFE	(100)																// ライフの最大数
//******************************************************************************
//静的メンバ変数
//******************************************************************************

//******************************************************************************
// コンストラクタ
//******************************************************************************
CGhost::CGhost(int nPriority) : CEnemy(nPriority)
{
	m_pParticleEmitter	= NULL;
	m_Type				= TYPE_NONE;
	m_nAttackCount		= INIT_INT;
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CGhost::~CGhost()
{

}
//******************************************************************************
// 生成関数
//******************************************************************************
CGhost * CGhost::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// CGhostのポインタ
	CGhost *pGhost = NULL;

	// NULLの場合
	if (pGhost == NULL)
	{
		// メモリ確保
		pGhost = new CGhost;

		// NULLでない場合
		if (pGhost != NULL)
		{
			// 情報設定
			pGhost->SetEnemy(pos, ROT, size, MAX_LIFE);

			// 種類代入
			pGhost->m_Type = type;

			// オブジェクトタイプ設定
			pGhost->SetObjType(OBJTYPE_ENEMY);

			// 初期化
			pGhost->Init();

			// 生成
			CEnemy_Life_Gage::Create(pos, pGhost);
		}
	}
	// ポインタを返す
	return pGhost;
}
//******************************************************************************
// 初期化処理
//******************************************************************************
HRESULT CGhost::Init(void)
{
	// 初期化
	CEnemy::Init();

	// 位置
	D3DXVECTOR3 pos = GetPos();

	// FIREの場合
	if (m_Type == TYPE_FIRE)
	{
		// 放射体生成
		m_pParticleEmitter = CParticle_Emitter::Create(POS, CParticle_Emitter::TYPE_FIRE_GHOST);
	}
	// ICEの場合
	if (m_Type == TYPE_ICE)
	{
		// 放射体生成
		m_pParticleEmitter = CParticle_Emitter::Create(POS, CParticle_Emitter::TYPE_ICE_GHOST);
	}

	return S_OK;
}
//******************************************************************************
// 終了処理
//******************************************************************************
void CGhost::Uninit(void)
{
	// 終了
	CEnemy::Uninit();
}
//******************************************************************************
// 更新処理
//******************************************************************************
void CGhost::Update(void)
{
	// 更新
	CEnemy::Update();

	// 状態取得
	int nState = CEnemy::GetState();

	// 死亡状態の場合
	if (nState == STATE_DEAD)
	{
		// 破棄
		m_pParticleEmitter->Uninit();
	}

	// インクリメント
	m_nAttackCount++;

	// 200カウント毎に
	if (m_nAttackCount % ATTACKCOUNT == REMAINDER)
	{
		// 攻撃
		Attack();
	}
	// 位置種痘
	D3DXVECTOR3 pos = GetPos();

	// 位置設定
	m_pParticleEmitter->SetPos(POS);

	// 位置設定
	SetPos(pos);
}

//******************************************************************************
// 描画処理
//******************************************************************************
void CGhost::Draw(void)
{
	// 描画
	CEnemy::Draw();
}
//******************************************************************************
// 攻撃処理
//******************************************************************************
void CGhost::Attack(void)
{
	// 位置取得
	D3DXVECTOR3 pos = GetPos();

	// CSceneのポインタ
	CScene *pScene = NULL;

	// プレイヤーの位置
	D3DXVECTOR3 PlayerPos;
	// プレイヤー取得
	do
	{
		// プレイヤーのポインタ取得
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULLでない場合
		if (pScene != NULL)
		{
			// オブジェクトタイプ取得
			OBJTYPE objtype = pScene->GetObjType();

			// オブジェクトタイププレイヤーの場合
			if (objtype == OBJTYPE_PLAYER)
			{
				// 位置取得
				PlayerPos.x = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._41;
				PlayerPos.y = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._42;
				PlayerPos.z = ((CPlayer*)pScene)->GetMtxWorld(CPlayer::PARTS_UNDER_BODY)._43;
			}
		}
		// NULLになるまで繰り返す
	} while (pScene != NULL);

	// 角度算出
	float fAngle = atan2f(PlayerPos.y - pos.y, PlayerPos.x - pos.x);

	// FIREの場合
	if (m_Type == TYPE_FIRE)
	{
		// 攻撃生成
		CMagic::Create(ATTACK_POS, MAGIC_MOVE, CMagic::TYPE_ENEMY_FIRE_BALL);
	}
	// ICEの場合
	if (m_Type == TYPE_ICE)
	{
		// 攻撃生成
		CMagic::Create(ATTACK_POS, MAGIC_MOVE, CMagic::TYPE_ENEMY_ICE_BALL);
	}
}