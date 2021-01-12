//-----------------------------------------------------------
// マネージャー[mamnager.h]
// Author : 管原　司
//-----------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//-----------------------------------------------------------
//前方宣言
//-----------------------------------------------------------
class CRenderer;
class CCamera;
class CLight;
class CInputKeyboard;
class CDebugProc;
class CMode;
//-----------------------------------------------------------
//クラス
//-----------------------------------------------------------
class CManager
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_GAME,
		MODE_MAX
	}MODE;
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadAll(void);
	void UnloadAll(void);
	static void CreateCamera(void);
	static void CreateLight(void);
	void SetNumFPS(int nCountFPS) { m_nCountFPS = nCountFPS; }
	void SetMode(MODE mode);

	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
	static CInputKeyboard *GetInputKeyboard(void) { return m_pKeyboard; }
private:
	static CRenderer *m_pRenderer;			//レンダラー
	static CCamera *m_pCamera;				//カメラ
	static CLight *m_pLight;				//ライト
	static CInputKeyboard *m_pKeyboard;		// キーボード
	static CDebugProc *m_pDebugProc;		// デバッグプロシージャ
	static CMode *m_pMode;					// モード
	int m_nCountFPS;						// FPSの値
	MODE m_Mode;							// モード
};
#endif // !_MANAGER_H_
