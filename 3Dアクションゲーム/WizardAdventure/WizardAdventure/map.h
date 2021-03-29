//******************************************************************************
// �}�b�v[map.h]
// Author : �ǌ��i
//******************************************************************************
#ifndef _MAP_H_
#define _MAP_H_
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "scene.h"
//******************************************************************************
// �O���錾
//******************************************************************************

//******************************************************************************
// �N���X
//******************************************************************************
class CMap : public CScene
{
public:
	//�ǂݍ��ގ��
	typedef enum
	{
		LOAD_TYPE_FLOOR = -1,
		LOAD_TYPE_BLOCK,
		LOAD_TYPE_MAX
	}LOAD_TYPE;
	// ���
	typedef enum
	{
		FLOOR_TYPE_NONE = -1,	// �ŏ�
		FLOOR_TYPE_GLASS,		// ���u���b�N
		FLOOR_TYPE_MAX			// �ő�
	}FLOOR_TYPE;

	// ���
	typedef enum
	{
		OBJ_TYPE_NONE = 0,		// ����
		OBJ_TYPE_NORMAL_BLOCK,	// ���u���b�N
		OBJ_TYPE_NEEDLE,		// �j�u���b�N
		OBJ_TYPE_BUTTON,		// �{�^��
		OBJ_TYPE_GATE,			// ��
		OBJ_TYPE_MAX			// �ő�
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

	FLOOR_TYPE **m_apFloorIndex;	// �s��
	OBJ_TYPE **m_apBlockIndex;	// �s��
	int m_nRow;						// �s
	int m_nCol;						// ��
};
#endif