//=============================================================================
//
// モード処理 [mode.h]
// Author : 管原　司
//
//=============================================================================
#ifndef _MODE_H_
#define _MODE_H_

//*****************************************************************************
//ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//*****************************************************************************
//クラス定義
//*****************************************************************************
class CMode
{
public:
	CMode();
	virtual ~CMode();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
};

#endif