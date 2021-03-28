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
#include "player.h"
#include "block.h"
#include "wood_block.h"
#include "frame.h"
#include "map.h"
#include "floor_block.h"
#include "particle_emitter.h"
#include "particle_effect.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_POS	(D3DXVECTOR3(100.0f, -50.0f, -200.0f))
#define PLAYER_ROT	(D3DXVECTOR3(0.0f,D3DXToRadian(90.0f),0.0f))
#define PLAYER_SIZE	(D3DXVECTOR3(20.0f,20.0f,20.0f))
#define TEST_POS	(D3DXVECTOR3(-150.0f, -70.0f, -200.0f))
#define TEST_ROT	(D3DXVECTOR3(0.0f,0.0,0.0))
#define TEST_SIZE	(D3DXVECTOR3(30.0f,30.0f, 30.0f))
#define TEST_COLOR	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define TEST_POS2	(D3DXVECTOR3(-50.0f, -50.0f, -200.0f))
#define TEST_ROT2	(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE2	(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_POS3	(D3DXVECTOR3(-100.0f, -50.0f, -200.0f))
#define TEST_ROT3	(D3DXVECTOR3(0.0f,0.0,0.0f))
#define TEST_SIZE3	(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define TEST_COLOR2	(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))
#define POS			(D3DXVECTOR3(-30.0f, 0.0f, -200.0f))
#define ROT			(D3DXVECTOR3(0.0f,90.0f,0.0f))
#define SIZE		(D3DXVECTOR3(30.0f, 30.0f, 30.0f))
#define COLOR		(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))
#define CREATE_COUNT	(60)
//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//*****************************************************************************
//�R���X�g���N�^
//*****************************************************************************
CGame::CGame()
{
	m_nCount = INIT_INT;
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
	CManager::CreateCamera();

	// ���C�g
	CManager::CreateLight();

	// �f�o�b�O�v���V�[�W��
	CDebugProc::Print("%s%d", "���W:", 500);

	// ���̃p�[�e�B�N������
	//CSphere_Particle_Emitter::Create(D3DXVECTOR3(-90.0f, 0.0f, -150.0f));

	// �}�b�v����
	CMap::Create();

	// �v���C���[����
	CPlayer::Create(PLAYER_POS, PLAYER_ROT, PLAYER_SIZE);

	// �u���b�N
	CWood_Block::Create(TEST_POS2, TEST_ROT, TEST_SIZE);

	// �u���b�N
	CWood_Block::Create(TEST_POS3, TEST_ROT, TEST_SIZE);

	// �u���b�N
	CWood_Block::Create(TEST_POS, TEST_ROT, TEST_SIZE);

	// �p�[�e�B�N������
	//CParticle_Emitter::Create(PLAYER_POS);

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
	// �C���N�������g
	m_nCount++;

	// 60�ɂȂ�����
	if (m_nCount == CREATE_COUNT)
	{
		// ����
		//CParticle_Effect::Create(PLAYER_POS);

		m_nCount = INIT_INT;
	}
}

//*****************************************************************************
//�`�揈��
//*****************************************************************************
void CGame::Draw(void)
{

}