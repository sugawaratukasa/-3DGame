//-----------------------------------------------------------
// �}�l�[�W���[[mamnager.h]
// Author : �ǌ��@�i
//-----------------------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//-----------------------------------------------------------
//�O���錾
//-----------------------------------------------------------
class CRenderer;
class CCamera;
class CLight;
class CInputKeyboard;
class CDebugProc;
class CMode;
//-----------------------------------------------------------
//�N���X
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
	static CRenderer *m_pRenderer;			//�����_���[
	static CCamera *m_pCamera;				//�J����
	static CLight *m_pLight;				//���C�g
	static CInputKeyboard *m_pKeyboard;		// �L�[�{�[�h
	static CDebugProc *m_pDebugProc;		// �f�o�b�O�v���V�[�W��
	static CMode *m_pMode;					// ���[�h
	int m_nCountFPS;						// FPS�̒l
	MODE m_Mode;							// ���[�h
};
#endif // !_MANAGER_H_
