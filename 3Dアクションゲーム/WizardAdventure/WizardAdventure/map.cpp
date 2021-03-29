//******************************************************************************
// マップ[map.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "floor.h"
#include "floor_block.h"
#include "needle_block.h"
#include "button.h"
#include "map.h"
#include "gate.h"
#include "gate_roof.h"
//******************************************************************************
//	マクロ定義
//******************************************************************************
#define FLOOR_TEXT		("data/Map/Text/Floor.csv")																							// マップ
#define BLOCK_TEXT		("data/Map/Text/Block.csv")																							// 床
#define FLOOR_SIZE		(D3DXVECTOR3(200.0f,200.0f,200.0f))																					// 床のサイズ
#define FLOOR_POS		(D3DXVECTOR3(nCountCol * -FLOOR_SIZE.x + 1000.0f,0.0f,nCountRow * -FLOOR_SIZE.z))									// 床の位置
#define FLOOR_ROT		(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0f))																		// 床の向き
#define FLOOR_COL		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))																					// 色
#define BLOCK_SIZE		(D3DXVECTOR3(30.0f,30.0f,30.0f))																					// ブロックのサイズ
#define BLOCK_POS		(D3DXVECTOR3(nCountCol * BLOCK_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + 150.0f ,-200.0f))						// ブロックの位置
#define BLOCK_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))																						// ブロックの向き
#define NEEDLE_SIZE		(D3DXVECTOR3(30.0f,15.0f,30.0f))																					// 針のサイズ
#define NEEDLE_POS		(D3DXVECTOR3(nCountCol * NEEDLE_SIZE.x - 290.0f,nCountRow * -NEEDLE_SIZE.y * 2 + 150.0f ,-200.0f))					// ブロックの位置
#define BUTTON_SIZE		(D3DXVECTOR3(30.0f,10.0f,30.0f))																					// ボタンサイズ
#define BUTTON_POS		(D3DXVECTOR3(nCountCol * BUTTON_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + BUTTON_SIZE.y * 1.5f + 150.0f ,-200.0f))// ボタンの位置
#define BUTTON_ROT		(D3DXVECTOR3(0.0f,0.0f,0.0f))																						// 向き
#define GATE_SIZE		(D3DXVECTOR3(30.0f,37.0f,10.0f))																					// 扉サイズ
#define GATE_POS		(D3DXVECTOR3(nCountCol * GATE_SIZE.x - GATE_SIZE.x / 2 - 290.0f,nCountRow * -BLOCK_SIZE.y + GATE_SIZE.y + 150.0f ,-200.0f))			// 扉の位置
#define GATE_ROT		(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))																		// 扉向き
#define GATE_ROOF_SIZE	(D3DXVECTOR3(30.0f,37.0f,20.0f))																					// 扉の屋根のサイズ
#define GATE_ROOF_POS	(D3DXVECTOR3(nCountCol * GATE_ROOF_SIZE.x - 290.0f,nCountRow * -BLOCK_SIZE.y + GATE_ROOF_SIZE.y + 150.0f ,-200.0f))			// 扉の屋根の位置
#define GATE_ROOF_ROT	(D3DXVECTOR3(0.0f,D3DXToRadian(270.0f),0.0f))																		// 扉の屋根
#define BYTE_NUM		(1024)																												// 最大バイト数
//******************************************************************************
// コンストラクタ
//******************************************************************************
CMap::CMap(int nPriority)
{
	m_apFloorIndex	= NULL;		// 行列
	m_apBlockIndex	= NULL;		// 行列
	m_nRow			= INIT_INT;	// 縦
	m_nCol			= INIT_INT;	// 横
}
//******************************************************************************
// デストラクタ
//******************************************************************************
CMap::~CMap()
{
}
//******************************************************************************
// 生成関数
//******************************************************************************
CMap * CMap::Create(void)
{
	// CMapのポインタ
	CMap *pMap = NULL;

	// NULLの場合
	if (pMap == NULL)
	{
		// メモリ確保
		pMap = new CMap;

		// NULLでない場合
		if (pMap != NULL)
		{
			// 初期化
			pMap->Init();
		}
	}
	// ポインタを返す
	return pMap;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CMap::Init(void)
{
	// マップ生成
	MapCreate();

	return S_OK;
}
//******************************************************************************
// 終了関数
//******************************************************************************
void CMap::Uninit(void)
{
	// 破棄
	Release();
}
//******************************************************************************
// 更新関数
//******************************************************************************
void CMap::Update(void)
{
}
//******************************************************************************
// 描画関数
//******************************************************************************
void CMap::Draw(void)
{
}
//******************************************************************************
// マップ生成
//******************************************************************************
void CMap::MapCreate(void)
{
	// 床生成
	FloorCreate();

	// ブロック生成
	BlockCreate();
}
//******************************************************************************
// 床の生成
//******************************************************************************
void CMap::FloorCreate(void)
{
	// 床のテキストの行列の数読み込み
	SetRowCol(LOAD_TYPE_FLOOR);

	// 床の情報読み込み
	FloorLoad();

	// NULLでない場合
	if (m_apFloorIndex != NULL)
	{
		// 行分回す
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// 列分回す
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apFloorIndex[nCountRow][nCountCol])
				{
					// 床
				case FLOOR_TYPE_GLASS:
					// 床生成
					CFloor::Create(FLOOR_POS, FLOOR_ROT, FLOOR_SIZE, FLOOR_COL);
					break;

				default:
					break;
				}
			}
		}
		// 行分回す
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// メモリ破棄
			delete[] m_apFloorIndex[nCntRow];
		}
		// メモリ破棄
		delete[] m_apFloorIndex;
	}
}
//******************************************************************************
// 床の読み込み
//******************************************************************************
void CMap::FloorLoad()
{
	// ファイル読み込み
	FILE * pfile = fopen(FLOOR_TEXT, "r");

	// csv読み取り処理
	char str[BYTE_NUM];

	// 行
	int nRowIndex = INIT_INT;

	// 列
	int nColIndex = INIT_INT;

	// NULLでない場合
	if (pfile != NULL)
	{
		if (m_apFloorIndex == NULL)
		{
			// メモリ確保
			m_apFloorIndex = new FLOOR_TYPE*[m_nRow];

			// NULLでない場合
			if (m_apFloorIndex != NULL)
			{
				// 行分回す
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// 列分回す
					m_apFloorIndex[nCnt] = new FLOOR_TYPE[m_nCol];
				}
				// 一行取得
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #が含まれていれば抜かす
					char cSearchStr = '#';

					// 対象文字
					strchr(cTokStr, cSearchStr);

					// NULLになるまで
					while (cTokStr != NULL)
					{
						// #が含まれていれば抜かす
						char cSearchStr = '#';

						// 対象文字
						strchr(cTokStr, cSearchStr);

						// 含まれていなかったら出力
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// 行列にブロックのタイプを格納
							m_apFloorIndex[nRowIndex][nColIndex] = (FLOOR_TYPE)atoi(cTokStr);

							// 次の列へ
							nColIndex++;
						}
						// NULLを入れる
						cTokStr = strtok(NULL, ",");
					}
					// インクリメント
					nRowIndex++;

					// 0に
					nColIndex = INIT_INT;
				}
			}
		}
		// ファイルを閉じる
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// ブロック生成
//******************************************************************************
void CMap::BlockCreate(void)
{
	// 床のテキストの行列の数読み込み
	SetRowCol(LOAD_TYPE_BLOCK);

	// 床の情報読み込み
	BlockLoad();

	// NULLでない場合
	if (m_apBlockIndex != NULL)
	{
		// 行分回す
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// 列分回す
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apBlockIndex[nCountRow][nCountCol])
				{
					// 無し
				case OBJ_TYPE_NONE:
					break;

					// 床
				case OBJ_TYPE_NORMAL_BLOCK:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);
					break;

					// 針
				case OBJ_TYPE_NEEDLE:
					// 針生成
					CNeedle_Block::Create(NEEDLE_POS, BLOCK_ROT, NEEDLE_SIZE);
					break;

					// ボタン
				case OBJ_TYPE_BUTTON:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);
					// ボタン生成
					CButton::Create(BUTTON_POS, BUTTON_ROT, BUTTON_SIZE);
					break;

					// ボタン
				case OBJ_TYPE_GATE:
					// 床生成
					CFloor_Block::Create(BLOCK_POS, BLOCK_ROT, BLOCK_SIZE);
					// 扉生成
					CGate::Create(GATE_POS, GATE_ROT, GATE_SIZE);
					// 扉生成
					CGate_Roof::Create(GATE_ROOF_POS, GATE_ROOF_ROT, GATE_ROOF_SIZE);
					break;

				default:
					break;
				}
			}
		}
		// 行分回す
		for (int nCntRow = INIT_INT; nCntRow < m_nRow; nCntRow++)
		{
			// メモリ破棄
			delete[] m_apBlockIndex[nCntRow];
		}
		// メモリ破棄
		delete[] m_apBlockIndex;
	}
}
//******************************************************************************
// ブロック読み込み
//******************************************************************************
void CMap::BlockLoad(void)
{
	// ファイル読み込み
	FILE * pfile = fopen(BLOCK_TEXT, "r");

	// csv読み取り処理
	char str[BYTE_NUM];

	// 行
	int nRowIndex = INIT_INT;

	// 列
	int nColIndex = INIT_INT;

	// NULLでない場合
	if (pfile != NULL)
	{
		if (m_apBlockIndex == NULL)
		{
			// メモリ確保
			m_apBlockIndex = new OBJ_TYPE*[m_nRow];

			// NULLでない場合
			if (m_apBlockIndex != NULL)
			{
				// 行分回す
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// 列分回す
					m_apBlockIndex[nCnt] = new OBJ_TYPE[m_nCol];
				}
				// 一行取得
				while (fgets(str, BYTE_NUM, pfile) != NULL)
				{
					char * cTokStr;

					cTokStr = strtok(str, ",");

					// #が含まれていれば抜かす
					char cSearchStr = '#';

					// 対象文字
					strchr(cTokStr, cSearchStr);

					// NULLになるまで
					while (cTokStr != NULL)
					{
						// #が含まれていれば抜かす
						char cSearchStr = '#';

						// 対象文字
						strchr(cTokStr, cSearchStr);

						// 含まれていなかったら出力
						if (strchr(cTokStr, cSearchStr) == NULL)
						{
							// 行列にブロックのタイプを格納
							m_apBlockIndex[nRowIndex][nColIndex] = (OBJ_TYPE)atoi(cTokStr);

							// 次の列へ
							nColIndex++;
						}
						// NULLを入れる
						cTokStr = strtok(NULL, ",");
					}
					// インクリメント
					nRowIndex++;

					// 0に
					nColIndex = INIT_INT;
				}
			}
		}
		// ファイルを閉じる
		fclose(pfile);
	}
	else
	{
		return;
	}
}
//******************************************************************************
// 行と列設定
//******************************************************************************
void CMap::SetRowCol(LOAD_TYPE load_type)
{
	FILE * pfile = NULL;

	// NULLの場合
	if (pfile == NULL)
	{
		// LOAD_TYPE_FLOORの場合
		if (load_type == LOAD_TYPE_FLOOR)
		{
			pfile = fopen(FLOOR_TEXT, "r");
		}
		// LOAD_TYPE_BLOCKの場合
		if (load_type == LOAD_TYPE_BLOCK)
		{
			pfile = fopen(BLOCK_TEXT, "r");
		}

		// 行初期化
		m_nRow = INIT_INT;

		// 列初期化
		m_nCol = INIT_INT;

		// csv読み取り処理
		char str[BYTE_NUM];

		// 行
		int nRowIndex = INIT_INT;

		// 列
		int nColIndex = INIT_INT;

		// NULLでない場合
		if (pfile != NULL)
		{
			// 一行取得
			while (fgets(str, BYTE_NUM, pfile) != NULL)
			{
				char * cTokStr;

				cTokStr = strtok(str, ",");

				// NULLになるまで
				while (cTokStr != NULL)
				{
					// #が含まれていれば抜かす
					char cSearchStr = '#';

					// 対象文字
					strchr(cTokStr, cSearchStr);

					// 含まれていなかったら出力
					if (strchr(cTokStr, cSearchStr) == NULL)
					{
						// 次の列へ
						nColIndex++;
					}

					// NULLを入れる
					cTokStr = strtok(NULL, ",");
				}
				// 列保存
				m_nCol = nColIndex;

				// 0に
				nColIndex = INIT_INT;

				// インクリメント
				nRowIndex++;

				// 行保存
				m_nRow = nRowIndex;
			}
			// ファイルを閉じる
			fclose(pfile);
		}
		else
		{
			return;
		}
	}
}