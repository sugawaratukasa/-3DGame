//******************************************************************************
// �c�[�� [game.cpp]
// Author : �ǌ��@
//******************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "manager.h"
#include "keyboard.h"
#include "renderer.h"
#include "time.h"
#include "mode.h"
#include "camera.h"
#include "light.h"
#include "scene.h"
#include "game.h"
#include "debug_proc.h"
#include "sphere_particle_emitter.h"
#include "test_model.h"
#include "player.h"
#include "polygon.h"
#include "polygon_test.h"
#include "frame.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_POS	(D3DXVECTOR3(-30.0f, -50.0f, -50.0f))
#define TEST_POS	(D3DXVECTOR3(-30.0f, 200.0f, -50.0f))
#define TEST_ROT	(D3DXVECTOR3(D3DXToRadian(90.0f),0.0f,0.0))
#define TEST_SIZE	(D3DXVECTOR3(500.0f,500.0f, 500.0f))
#define TEST_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TEST_POS2	(D3DXVECTOR3(50.0f, 0.0f, -50.0f))
#define TEST_ROT2	(D3DXVECTOR3(0.0f,0.0f,0.0f))
#define TEST_SIZE2	(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_COLOR2	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define POS			(D3DXVECTOR3(-30.0f, 0.0f, -50.0f))
#define ROT			(D3DXVECTOR3(0.0f,90.0f,0.0f))
#define SIZE		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define COLOR		(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{

}
//*****************************************************************************
//�f�X�g���N�^
//*****************************************************************************
CGame::~CGame()
{
}
//*****************************************************************************
//����������
//*****************************************************************************
HRESULT CGame::Init(void)
{
	// �J����
	CSceneManager::CreateCamera();

	// ���C�g
	CSceneManager::CreateLight();

	// �f�o�b�O�v���V�[�W��
	CDebugProc::Print("%s%d", "���W:", 500);

	// ���̃p�[�e�B�N������
	//CSphere_Particle_Emitter::Create(D3DXVECTOR3(-90.0f, 0.0f, -150.0f));

	// �v���C���[����
	CPlayer::Create(PLAYER_POS, D3DXVECTOR3(0.0f, D3DXToRadian(90.0f), 0.0f), D3DXVECTOR3(BOX_SIZE, BOX_SIZE, BOX_SIZE));

	// �|���S������
	CPolygon_Test::Create(TEST_POS, TEST_ROT, TEST_SIZE, TEST_COLOR);

	//���f��
	//CTestModel::Create(POS, ROT, SIZE);

	// �|���S������
	//CPolygon_Test::Create(TEST_POS2, TEST_ROT2, TEST_SIZE2, TEST_COLOR2);

	// �|���S������
	//CPolygon::Create(POS, ROT, SIZE, COLOR);

	return S_OK;
}

//*****************************************************************************
//�I������
//*****************************************************************************
void CGame::Uninit(void)
{

}

//*****************************************************************************
//�X�V����
//*****************************************************************************
void CGame::Update(void)
{

}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CGame::Draw(void)
{

}