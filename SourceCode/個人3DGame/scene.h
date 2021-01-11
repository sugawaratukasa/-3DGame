#ifndef _SCENE_H_
#define _SCENE_H_
#include "main.h"
//オブジェクトクラス
class CScene
{
public:
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,
		OBJTYPE_ITEM,
		OBJTYPE_PARTICLE,
		OBJTYPE_UI,
		OBJTYPE_FADE,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = 2);
	virtual ~CScene();

	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void) { return m_objType; }
	static CScene *GetScene(int nPriority);

	//純粋仮想関数
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void DesignationReleaseAll(OBJTYPE type);
	static void SetUpdateStop(bool bUpdateStop);

	static bool GetUpdateStop(void) { return m_bUpdateStop; }

protected:
	void Release(void);

private:
	OBJTYPE m_objType;					//オブジェクトの種類
	static CScene *m_pTop[OBJTYPE_MAX];	//先頭のオブジェクトへのポインタ
	static CScene *m_pCur[OBJTYPE_MAX];	//現在のオブジェクトへのポインタ
	CScene *m_pPrev;					//前のオブジェクトへのポインタ
	CScene *m_pNext;					//次のオブジェクトへのポインタ
	int m_nPriority;
	int m_nID;
	static int m_nNext;
	static bool m_bRelease;
	bool m_bDeath;
	static bool m_bUpdateStop;
};
#endif // !_RENDERER_H_