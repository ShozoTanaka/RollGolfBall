#pragma once
#ifndef GOLF_BALL_DEFINED
#define GOLF_BALL_DEFINED

#include "StepTimer.h"

class GolfBall
{
public:
	// �ʒu���擾����
	DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }
	// �ʒu��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
	// ���x���擾����
	DirectX::SimpleMath::Vector2 GetVelocity() const { return m_velocity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector2& velocity) { m_velocity = velocity; }

public:
	// �R���X�g���N�^
	GolfBall(DirectX::Model* model);
	// �f�X�g���N�^
	~GolfBall();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �`�悷��
	void Render();
	// �㏈�����s��
	void Finalize();

	// �S���t�{�[����]����
	void Roll(const DirectX::SimpleMath::Vector2& direction, const float& force);

public:
	// ���C�W��
	static const float FRICTION;
	// �ő�ړ����x
	static const float MAX_SPEED;
private:
	// DirectX�O���t�B�b�N�X
	Graphics* m_graphics;

	// �S���t�{�[�����f��
	DirectX::Model* m_model;
	// �S���t�{�[���̉�]�N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_quaternion;
	// �S���t�{�[���̈ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// �S���t�{�[���̑��x
	DirectX::SimpleMath::Vector2 m_velocity;
	// �S���t�{�[���̕���
	DirectX::SimpleMath::Vector2 m_heading;
	// �S���t�{�[���̎���
	float m_mass;
	// �S���t�{�[���̔��a
	float m_radius;
};

#endif		// GOLF_BALL_DEFINED
