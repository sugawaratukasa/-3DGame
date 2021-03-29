//******************************************************************************
// マップ[map.h]
// Author : 管原司
//******************************************************************************
#ifndef _MAP_H_
#define _MAP_H_
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "scene.h"
//******************************************************************************
// 前方宣言
//******************************************************************************

//******************************************************************************
// クラス
//******************************************************************************
class CMap : public CScene
{
public:
	//読み込む種類
	typedef enum
	{
		LOAD_TYPE_FLOOR = -1,
		LOAD_TYPE_BLOCK,
		LOAD_TYPE_MAX
	}LOAD_TYPE;
	// 種類
	typedef enum
	{
		FLOOR_TYPE_NONE = -1,	// 最小
		FLOOR_TYPE_GLASS,		// 床ブロック
		FLOOR_TYPE_MAX			// 最大
	}FLOOR_TYPE;

	// 種類
	typedef enum
	{
		OBJ_TYPE_NONE = 0,		// 無し
		OBJ_TYPE_NORMAL_BLOCK,	// 床ブロック
		OBJ_TYPE_NEEDLE,		// 針ブロック
		OBJ_TYPE_BUTTON,		// ボタン
		OBJ_TYPE_GATE,			// 扉
		OBJ_TYPE_MAX			// 最大
	}OBJ_TYPE;

	CMap(int nPriority = OBJTYPE_FLOOR);
	~CMap();
	static CMap *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
		
	void MapCreate(void);
private:
	void FloorCreate(void);
	void FloorLoad(void);
	void BlockCreate(void);
	void BlockLoad(void);
	void SetRowCol(LOAD_TYPE load_type);

	FLOOR_TYPE **m_apFloorIndex;	// 行列
	OBJ_TYPE **m_apBlockIndex;	// 行列
	int m_nRow;						// 行
	int m_nCol;						// 列
};
#endif