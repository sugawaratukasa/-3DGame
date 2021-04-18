//******************************************************************************
// �X�ʂ�UI[iceball_ui.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "player.h"
#include "iceball_ui.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define POS				(D3DXVECTOR3(PlayerPos.x,PlayerPos.y + 55.0f,PlayerPos.z - 10.0f))	// �ʒu
#define SIZE			(D3DXVECTOR3(10.0f,10.0f,0.0f))										// �T�C�Y
#define COL				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))									// �F
#define SUBCOLOR		(-0.05f)															// ���l���Z
#define MIN_COLOR		(0.0f)																// �F�̍ŏ��l
#define PLAYER_POS_Y	(15.0f)																// y���W
#define PLAYER_POS_Z	(-15.0f)															// z���W
#define ROT				(D3DXVECTOR3(0.0f,0.0f,D3DXToRadian(330.0f)))						// ����
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CIceBall_UI::CIceBall_UI(int nPriority) : CBillboard_UI(nPriority)
{
}
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CIceBall_UI::~CIceBall_UI()
{
}
//******************************************************************************                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
// �����֐�
//******************************************************************************
CIceBall_UI * CIceBall_UI::Create(D3DXVECTOR3 pos)
{
	// CIceBall_UI�̃|�C���^
	CIceBall_UI *pIceBall_UI = NULL;

	// NULL�̏ꍇ
	if (pIceBall_UI == NULL)
	{
		// �������m��
		pIceBall_UI = new CIceBall_UI;

		// NULL�łȂ��ꍇ
		if (pIceBall_UI != NULL)
		{
			// ���ݒ�
			pIceBall_UI->SetBillboard(pos, ROT, SIZE, COL, CBillboard_UI::TEX_TYPE_ICEBALL);

			// ������
			pIceBall_UI->Init();
		}
	}
	// �|�C���^��Ԃ�
	return pIceBall_UI;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CIceBall_UI::Init(void)
{
	// ������
	CBillboard_UI::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CIceBall_UI::Uninit(void)
{
	// �I��
	CBillboard_UI::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CIceBall_UI::Update(void)
{
	// �X�V
	CBillboard_UI::Update();

	// �ʒu�擾
	D3DXVECTOR3 pos = GetPosition();

	// �F�擾
	D3DXCOLOR col = GetColor();

	// �F���Z
	col.a += SUBCOLOR;

	// CScene�̃|�C���^
	CScene *pScene = NULL;

	// �v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;

	// �v���C���[�̈ʒu�擾
	do
	{
		// �v���C���[�擾
		pScene = GetScene(OBJTYPE_PLAYER);

		// NULL�̏ꍇ
		if (pScene != NULL)
		{
			// �I�u�W�F�N�g�^�C�v�擾
			OBJTYPE objtype = pScene->GetObjType();

			// �I�u�W�F�N�g�^�C�v���v���C���[�̏ꍇ
			if (objtype == OBJTYPE_PLAYER)
			{
				// �ʒu�擾
				PlayerPos = ((CPlayer*)pScene)->GetPos();

				// ���
				pos = POS;

				// �ʒu�ݒ�
				SetPosition(pos);
			}
		}
		// NULL�ɂȂ�܂ŌJ��Ԃ�
	} while (pScene != NULL);

	// �F�ݒ�
	SetColor(col);


	// 0.0f�ȉ��̏ꍇ
	if (col.a <= MIN_COLOR)
	{
		// �I��
		Uninit();
		return;
	}
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CIceBall_UI::Draw(void)
{
	// �`��
	CBillboard_UI::Draw();
}