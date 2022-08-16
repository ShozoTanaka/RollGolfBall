#pragma once
#ifndef GOLF_BALL_DEFINED
#define GOLF_BALL_DEFINED

#include "StepTimer.h"

class GolfBall
{
public:
	// ���C�W��
	static const float FRICTION;
	// �ő�ړ����x(1�b�ԕӂ�̃h�b�g��)
	static const float MAX_SPEED;

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
	// �S���t�{�[���̈ʒu��\������
	DirectX::SimpleMath::Vector2 PredictFuturePosition(const float& time) const;
	// �S���t�{�[���̈ړ��ɂ����鎞�Ԃ�Ԃ�
	float TimeToMoveDistance(const DirectX::SimpleMath::Vector2& from, const DirectX::SimpleMath::Vector2& to, const float& force) const;
	// �`�悷��
	void Render();
	// �����̈ʒu��`�悷��
	void GolfBall::DrawFuturePosition(const float& time);
	// �S���t�{�[����]����
	void Roll(const DirectX::SimpleMath::Vector2& direction, const float& force);
	// �㏈��
	void Finalize();

private:
	// DirectX�O���t�B�b�N�X
	Graphics* m_graphics;

	// �{�[�����f��
	DirectX::Model* m_model;
	// �{�[���̉�]�������N�H�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_quaternion;
	// �ʒu
	DirectX::SimpleMath::Vector2 m_position;
	// ���x
	DirectX::SimpleMath::Vector2 m_velocity;
	// �����x�N�g��
	DirectX::SimpleMath::Vector2 m_heading;
	// ����
	float m_mass;
	// ���a
	float m_radius;
};

#endif		// GOLF_BALL_DEFINED
