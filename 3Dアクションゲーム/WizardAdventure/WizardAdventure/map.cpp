//******************************************************************************
// マップ[map.cpp]
// Author : 管原司
//******************************************************************************

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "floor.h"
#include "map.h"
//******************************************************************************
//	マクロ定義
//******************************************************************************
#define MAP_TEXT	("data/Map/Text/map.csv")																// マップ
#define FLOOR_SIZE	(D3DXVECTOR3(200.0f,200.0f,200.0f))														// 床のサイズ
#define FLOOR_POS	(D3DXVECTOR3(nCountCol * -FLOOR_SIZE.x + 800.0f,0.0f,nCountRow * -FLOOR_SIZE.z + 0))	// 床の位置
#define FLOOR_ROT	(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0f))											// 床の向き
#define FLOOR_COL	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))														// 色
#define BYTE_NUM	(1024)																					// 最大バイト数
//******************************************************************************
// コンストラクタ
//******************************************************************************
CMap::CMap(int nPriority)
{
	m_apMapIndex	= NULL;
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

		if (pMap != NULL)
		{
			// 行列設定
			pMap->SetRowCol();

			// マップ読み込み
			pMap->MapLoad();

			// 初期化
			pMap->Init();
		}
	}
	return pMap;
}
//******************************************************************************
// 初期化関数
//******************************************************************************
HRESULT CMap::Init(void)
{
	// NULLでない場合
	if (m_apMapIndex != NULL)
	{
		// 行分回す
		for (int nCountRow = INIT_INT; nCountRow < m_nRow; nCountRow++)
		{
			// 列分回す
			for (int nCountCol = INIT_INT; nCountCol < m_nCol; nCountCol++)
			{
				switch (m_apMapIndex[nCountRow][nCountCol])
				{
					// 床
				case TYPE_FLOOR:
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
			delete[] m_apMapIndex[nCntRow];
		}
		// メモリ破棄
		delete[] m_apMapIndex;
	}
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
// マップ読み込み
//******************************************************************************
void CMap::MapLoad(void)
{
	// ファイル読み込み
	FILE * pfile = fopen(MAP_TEXT, "r");

	// csv読み取り処理
	char str[BYTE_NUM];

	// 行
	int nRowIndex = INIT_INT;

	// 列
	int nColIndex = INIT_INT;

	// NULLでない場合
	if (pfile != NULL)
	{
		if (m_apMapIndex == NULL)
		{
			// メモリ確保
			m_apMapIndex = new TYPE*[m_nRow];

			// NULLでない場合
			if (m_apMapIndex != NULL)
			{
				// 行分回す
				for (int nCnt = INIT_INT; nCnt < m_nRow; nCnt++)
				{
					// 列分回す
					m_apMapIndex[nCnt] = new TYPE[m_nCol];
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
							m_apMapIndex[nRowIndex][nColIndex] = (TYPE)atoi(cTokStr);

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
void CMap::SetRowCol(void)
{
	FILE * pfile = fopen(MAP_TEXT, "r");

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