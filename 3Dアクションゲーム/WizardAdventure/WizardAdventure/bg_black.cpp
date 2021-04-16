//******************************************************************************
// ��[bg_black.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "joystick.h"
#include "player.h"
#include "bg_black.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define COL	(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
//******************************************************************************
// �ÓI�����o�ϐ�������
//******************************************************************************

//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CBg_Black::CBg_Black(int nPriority)
{
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CBg_Black::~CBg_Black()
{
}
//******************************************************************************
// �����֐�
//******************************************************************************
CBg_Black * CBg_Black::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// CBg_Black�̃|�C���^
	CBg_Black *pBg_Black = NULL;

	// NULL�̏ꍇ
	if (pBg_Black == NULL)
	{
		// �������m��
		pBg_Black = new CBg_Black;

		// NULL�łȂ��ꍇ
		if (pBg_Black != NULL)
		{
			// ���ݒ�
			pBg_Black->SetPolygon(pos, size, C3D_Polygon::TEX_TYPE_SKY);

			// ������
			pBg_Black->Init();
		}
	}

	// �|�C���^��Ԃ�
	return pBg_Black;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CBg_Black::Init(void)
{
	// ������
	C3D_Polygon::Init();

	// �F�ݒ�
	SetColor(COL);

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CBg_Black::Uninit(void)
{
	// �I��
	C3D_Polygon::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CBg_Black::Update(void)
{
	// �X�V
	C3D_Polygon::Update();
	// �R���g���[���[�擾
	DIJOYSTATE js;
	js.lY = INIT_INT;
	js.lX = INIT_INT;
	CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = CInputJoystick::GetDevice();

	if (g_lpDIDevice != NULL)
	{
		g_lpDIDevice->Poll();
		g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
	}

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;

	// CScene�N���X�̃|�C���^
	CScene *pScene = NULL;
	do
	{
		// �V�[���擾
		pScene = GetScene(OBJTYPE_PLAYER);
		// NULL�łȂ��ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = GetObjType();

			// �I�u�W�F�^�C�v�v���C���[�̏ꍇ
			if (objtype = OBJTYPE_PLAYER)
			{
				// �v���C���[�̈ʒu�擾
				PlayerPos = ((CPlayer*)pScene)->GetPos();
			}
		}
		// NULL�ɂȂ�܂�
	} while (pScene != NULL);

	// �ʒu���
	pos.x = PlayerPos.x;

	// �ʒu�ݒ�
	SetPosition(pos);
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CBg_Black::Draw(void)
{
	// �`��
	C3D_Polygon::Draw();
}