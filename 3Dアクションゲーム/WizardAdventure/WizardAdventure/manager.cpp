//******************************************************************************
// �}�l�[�W���[���� [manager.cpp]
// Author : �ǌ��@�i
//******************************************************************************

//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "debug_proc.h"
#include "mode.h"
#include "game.h"
#include "particle.h"
#include "player.h"
#include "block.h"
#include "frame.h"
#include "floor.h"
//******************************************************************************
// �ÓI�����o�ϐ�
//******************************************************************************
CRenderer *CSceneManager::m_pRenderer = NULL;
CCamera *CSceneManager::m_pCamera = NULL;
CLight *CSceneManager::m_pLight = NULL;
CInputKeyboard *CSceneManager::m_pKeyboard = NULL;
CInputJoystick *CSceneManager::m_pJoystick = NULL;
CDebugProc *CSceneManager::m_pDebugProc = NULL;
CMode *CSceneManager::m_pMode = NULL;

//******************************************************************************
//�R���X�g���N�^
//******************************************************************************
CSceneManager::CSceneManager()
{

}

//******************************************************************************
//�f�X�g���N�^
//******************************************************************************
CSceneManager::~CSceneManager()
{

}

//******************************************************************************
//����������
//******************************************************************************
HRESULT CSceneManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindouw)
{

	//�N���X�����Ə�����	
	//�����_���[
	if (m_pRenderer == NULL)
	{
		// �������m��
		m_pRenderer = new CRenderer;
		if (m_pRenderer != NULL)
		{
			// ������
			m_pRenderer->Init(hWnd, TRUE);
		}
	}
	// �L�[�{�[�h
	if (m_pKeyboard == NULL)
	{
		// �������m��
		m_pKeyboard = new CInputKeyboard;
		if (m_pKeyboard != NULL)
		{
			// ������
			m_pKeyboard->Init(hInstance, hWnd);
		}
	}
	// �R���g���[���[
	if (m_pJoystick == NULL)
	{
		// �������m��
		m_pJoystick = new CInputJoystick;
		if (m_pJoystick != NULL)
		{
			// ������
			m_pJoystick->Init(hInstance, hWnd);
		}
	}
	// �f�o�b�O
	if (m_pDebugProc == NULL)
	{
		m_pDebugProc = new CDebugProc;
		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}
	//�e�N�X�`���̓ǂݍ���
	LoadAll();

	// ���[�h�ݒ�
	SetMode(MODE_GAME);
	return S_OK;
}

//******************************************************************************
//�I������
//******************************************************************************
void CSceneManager::Uninit(void)
{
	CScene::ReleaseAll();
	//�e�N�X�`���̔j��
	UnloadAll();
	// ���[�h�̏I��
	if (m_pMode != NULL)
	{
		//���̎��̃��[�h�I��
		m_pMode->Uninit();
	}
	// �f�o�b�O
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}
	//�R���g���[���[�̔j��
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Uninit();
		delete m_pJoystick;
		m_pJoystick = NULL;
	}
	//���C�g�̏I��
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}
	//�J�����̏I��
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//�����_���[�̏I��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//******************************************************************************
// �X�V����
//******************************************************************************
void CSceneManager::Update(void)
{
	if (m_pRenderer != NULL)
	{
		//�����_���[�̍X�V����
		m_pRenderer->Update();
	}
	if (m_pCamera != NULL)
	{
		//�J�����̂̍X�V����
		m_pCamera->Update();
	}
	if (m_pMode != NULL)
	{
		// ���̎��̃��[�h�̕`�揈��
		m_pMode->Update();
	}
	//�L�[�{�[�h�̍X�V
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Update();
	}
	//�L�[�{�[�h�̍X�V
	if (m_pJoystick != NULL)
	{
		m_pJoystick->Update();
	}
}

//******************************************************************************
// �`�揈��
//******************************************************************************
void CSceneManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		//�`�揈��
		m_pRenderer->Draw();
	}

	if (m_pMode != NULL)
	{
		// ���̎��̃��[�h�̕`�揈��
		m_pMode->Draw();
	}
}

//******************************************************************************
// �e�N�X�`���̓ǂݍ��݂܂Ƃ�
//******************************************************************************
void CSceneManager::LoadAll(void)
{
	// �e�N�X�`���ǂݍ���
	CParticle::Load();

	// �v���C���[���f���ǂݍ���
	CPlayer::Load();

	// �t���[��
	CFrame::Load();

	// �u���b�N
	CBlock::Load();

	// ��
	CFloor::Load();
}

//******************************************************************************
// �e�N�X�`���̔j���܂Ƃ�
//******************************************************************************
void CSceneManager::UnloadAll(void)
{
	// ��
	CFloor::Unload();

	// �u���b�N
	CBlock::Unload();

	// �t���[��
	CFrame::Unload();

	// �v���C���[���f���j��
	CPlayer::Unload();

	// �e�N�X�`���j��
	CParticle::Unload();
}

//******************************************************************************
// �J�����̐���
//******************************************************************************
void CSceneManager::CreateCamera(void)
{
	if (m_pCamera == NULL)
	{
		// �|�C���^�̓��I�m��
		m_pCamera = new CCamera;
		if (m_pCamera != NULL)
		{
			// ������
			m_pCamera->Init();
		}
	}
}

//******************************************************************************
// ���C�g�̐���
//******************************************************************************
void CSceneManager::CreateLight(void)
{
	if (m_pLight == NULL)
	{
		// �|�C���^�̓��I�m��
		m_pLight = new CLight;
		if (m_pLight != NULL)
		{
			// ������
			m_pLight->Init();
		}
	}
}
//******************************************************************************
// ���[�h�̐ݒ�
//******************************************************************************
void CSceneManager::SetMode(MODE mode)
{
	if (m_pMode != NULL)
	{
		// ���̎��̃��[�h�̏I������
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = NULL;
	}

	if (m_pMode == NULL)
	{
		// ���
		m_Mode = mode;

		switch (m_Mode)
		{
		case MODE_GAME:
			// �c�[���̐���
			m_pMode = new CGame;

			// �c�[���̏���������
			m_pMode->Init();

			break;

		default:
			return;
			break;
		}
	}
}