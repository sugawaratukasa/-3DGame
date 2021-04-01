//******************************************************************************
// �|���S��[polygon.cpp]
// Author : �ǌ��i
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "keyboard.h"
#include "scene.h"
#include "scene3d.h"
#include "collision.h"
#include "polygon.h"
#include "polygon_test.h"
//******************************************************************************
// �}�N����`
//******************************************************************************
#define MOVE_VALUE	(D3DXVECTOR3(2.0f, 2.0f, 0.0f))
#define RADIUS		(15.0f)
//******************************************************************************
// �ÓI�����o�ϐ�������
//******************************************************************************
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = NULL;
//******************************************************************************
// �R���X�g���N�^
//******************************************************************************
CPolygon::CPolygon(int nPriority) : CScene3d(nPriority)
{
	m_posOld = INIT_D3DXVECTOR3;
}
//******************************************************************************
// �f�X�g���N�^
//******************************************************************************
CPolygon::~CPolygon()
{
}
//******************************************************************************
// �e�N�X�`���ǂݍ��݊֐�
//******************************************************************************
HRESULT CPolygon::Load(void)
{
	// �����_���[�擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/Texture/circle.png", &m_pTexture);
	return S_OK;
}
//******************************************************************************
// �e�N�X�`���j���֐�
//******************************************************************************
void CPolygon::Unload(void)
{
	// NULL�`�F�b�N
	if (m_pTexture != NULL)
	{
		// �j��
		m_pTexture->Release();

		// NULL
		m_pTexture = NULL;
	}
}
//******************************************************************************
// �����֐�
//******************************************************************************
CPolygon * CPolygon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col)
{
	// CPolygon�̃|�C���^
	CPolygon *pPolygon;

	// �������m��
	pPolygon = new CPolygon;

	// ���ݒ�
	pPolygon->SetPolygon(pos, rot, size, col);

	// �e�N�X�`��
	pPolygon->BindTexture(m_pTexture);

	// ������
	pPolygon->Init();

	// �|�C���^��Ԃ�
	return pPolygon;
}
//******************************************************************************
// �������֐�
//******************************************************************************
HRESULT CPolygon::Init(void)
{
	// ������
	CScene3d::Init();

	return S_OK;
}
//******************************************************************************
// �I���֐�
//******************************************************************************
void CPolygon::Uninit(void)
{
	// �I��
	CScene3d::Uninit();
}
//******************************************************************************
// �X�V�֐�
//******************************************************************************
void CPolygon::Update(void)
{
	// �X�V
	CScene3d::Update();

	// �ʒu���W�擾
	m_posOld = GetPosition();

	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();
	// �ړ�
	D3DXVECTOR3 move = INIT_D3DXVECTOR3;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CSceneManager::GetRenderer()->GetDevice();
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pKeyborad = CSceneManager::GetInputKeyboard();

	// �E�ړ�
	if (pKeyborad->GetKeyPress(DIK_RIGHT))
	{
		// �ړ�
		move.x = -MOVE_VALUE.x;
	}
	// ���ړ�
	if (pKeyborad->GetKeyPress(DIK_LEFT))
	{
		// �ړ�
		move.x = MOVE_VALUE.x;
	}
	// ��ړ�
	if (pKeyborad->GetKeyPress(DIK_UP))
	{
		// �ړ�
		move.y = MOVE_VALUE.y;
	}
	// ���ړ�
	if (pKeyborad->GetKeyPress(DIK_DOWN))
	{
		// �ړ�
		move.y = -MOVE_VALUE.y;
	}
	

	// �ړ�
	pos.x += move.x;
	pos.y += move.y;

	// �ʒu�X�V
	SetPosition(pos);

	// �����蔻�菈��
	//Collision();

	DotCollision();
}
//******************************************************************************
// �`��֐�
//******************************************************************************
void CPolygon::Draw(void)
{
	// �`��
	CScene3d::Draw();

}
//******************************************************************************
// ���ς̓����蔻��
//******************************************************************************
void CPolygon::DotCollision(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;

	// �G�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_TEST);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_TEST)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 Test_Pos = ((CPolygon_Test*)pScene)->GetPosition();

				// �ʒu
				float fDistance = powf(pos.x - Test_Pos.x, 2.0f) + powf(pos.y - Test_Pos.y, 2.0f) + powf(pos.z - Test_Pos.z, 2.0f);

				// ���a
				float fRadius = powf(RADIUS + RADIUS, 2.0f);

				// �߂荞��ł��邩
				if (fDistance < fRadius)
				{
					// �ړ���
					D3DXVECTOR3 move = MOVE_VALUE;

					float fAngle = MOVE_VALUE.x - fDistance * MOVE_VALUE.x / powf(fDistance, 2.0f) * fDistance;

					D3DXVECTOR3 movePos = (D3DXVECTOR3(cosf(D3DXToRadian(fAngle)),
						sinf(D3DXToRadian(fAngle)),
						0.0f));

					pos += movePos * 3.5f;

					// �ʒu�ݒ�
					SetPosition(pos);
				
				}
			}
		}
	} while (pScene != NULL);
}
//******************************************************************************
// �����蔻�菈���֐�
//******************************************************************************
void CPolygon::Collision(void)
{
	// �ʒu���W�擾
	D3DXVECTOR3 pos = GetPosition();

	// �T�C�Y�擾
	D3DXVECTOR3 size = GetSize();

	// CScene�^�̃|�C���^
	CScene *pScene = NULL;

	// �G�̓����蔻��
	do
	{
		// �I�u�W�F�^�C�v���G�̏ꍇ
		pScene = GetScene(OBJTYPE_TEST);
		if (pScene != NULL)
		{
			OBJTYPE objType = pScene->GetObjType();
			if (objType == OBJTYPE_TEST)
			{
				// ���W�ƃT�C�Y�擾
				D3DXVECTOR3 Test_Pos = ((CPolygon_Test*)pScene)->GetPosition();
				D3DXVECTOR3 Test_Size = ((CPolygon_Test*)pScene)->GetSize();

				if(CCollision::SphereCollision(pos, RADIUS, Test_Pos, RADIUS) == true)
				{
					// �ʒu���W�ݒ�
					SetPosition(m_posOld);

				}

			}
		}
	} while (pScene != NULL);
}