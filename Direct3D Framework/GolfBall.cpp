#include "pch.h"
#include "GolfBall.h"
#include "Common.h"

// ���C�W��
const float GolfBall::FRICTION = -0.02f;
// �ő�ړ����x
const float GolfBall::MAX_SPEED = 3.0f;

// �R���X�g���N�^
GolfBall::GolfBall(DirectX::Model* model)
	:
	m_model(model),																	// ���f��
	m_quaternion{},																		// �N�H�[�^�j�I��
	m_position(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),			// �ʒu
	m_velocity(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),			// ���x
	m_heading(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),			// ����
	m_mass(0.45f),																		// ����
	m_radius(2.13f)																		// ���a
{
	// DirectX�O���t�B�b�N�X���擾����
	m_graphics = Graphics::GetInstance();
}

// �f�X�g���N�^
GolfBall::~GolfBall()
{
}

// ����������
void GolfBall::Initialize()
{
}

// �X�V����
void GolfBall::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);

	// ���C�ɂ�錸���̑傫����葬�x��������Ό���������
	if (m_velocity.Length() > GolfBall::FRICTION)
	{
		// ������ݒ肷��
		m_heading = m_velocity;
		// ���C�ɂ�茸������
		m_velocity += m_heading * GolfBall::FRICTION;
		// �ʒu���X�V����
		m_position += m_velocity;
		// �S���t�{�[���̉�]����ݒ肷��
		Vector3 axis = Vector3(m_heading.y, 0.0f, -m_heading.x);
		// �S���t�{�[�����ړ����Ă���ꍇ
		if (m_velocity.Length())
		{
			// �N�H�[�^�j�I���𐶐�����
			m_quaternion *= Quaternion::CreateFromAxisAngle(axis, m_velocity.Length() / m_radius);
		}
	}
}

// �`�悷��
void GolfBall::Render()
{
	using namespace DirectX::SimpleMath;

	// �X�P�[���s��𐶐�����
	Matrix scaleMatrix = Matrix::CreateScale(1.0f, 1.0f, 1.0f);
	// �ړ��s��𐶐�����
	Matrix translationMatrix = Matrix::CreateTranslation(m_position.x, m_radius, m_position.y);
	// ��]�N�H�[�^�j�I�������]�s��𐶐�����
	Matrix rotationMatrix = Matrix::CreateFromQuaternion(m_quaternion);
	// ���[���h�s����v�Z����
	Matrix worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// �S���t�{�[����`�悷��
	m_graphics->DrawModel(m_model, worldMatrix);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �㏈�����s��
void GolfBall::Finalize()
{
}

// �����̃S���t�{�[���̈ʒu��`�悷��
void GolfBall::DrawFuturePosition(const float& time)
{
	// �v���~�e�B�u�`����J�n����
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// 10�b��̈ʒu��\������
	m_graphics->DrawCircle(PredictFuturePosition(time), 2.0f);
	// �v���~�e�B�u�`����I������
	m_graphics->DrawPrimitiveEnd();
}

// �S���t�{�[����]����
void GolfBall::Roll(const DirectX::SimpleMath::Vector2& direction, const float& force)
{
	using namespace DirectX::SimpleMath;
	// �S���t�{�[�����]��������x�N�g���𐳋K������
	Vector2 kickDirection = Normalize(direction);
	// �^�����������瑬�x���v�Z����
	m_velocity = kickDirection * force / m_mass;
}

// �����̃S���t�{�[���̈ʒu��\������
// �������x�����^���̌����F distance = (velocity * time) + (1/2 * acceralation * time^2)
DirectX::SimpleMath::Vector2 GolfBall::PredictFuturePosition(const float& time) const
{
	using namespace DirectX::SimpleMath;
	
	// �����̈ړ��x�N�g�����v�Z����
	Vector2 initialVelocity = m_velocity * time;
	// ���x�𐳋K������
	Vector2 velocity = Normalize(m_velocity);
	// �����������̈ړ��������v�Z����
	float distance = 0.5f * GolfBall::FRICTION * time * time;
	// �ʒu��Ԃ�
	return m_position + initialVelocity + velocity * distance;
}

// �S���t�{�[���̈ړ��Ɋ|���鎞�Ԃ��v�Z����
	// �^��������: F(force) = M(mass) * A(accelaration)
float GolfBall::CalculateTimeToMoveDistance(const DirectX::SimpleMath::Vector2& from, const DirectX::SimpleMath::Vector2& to, const float& force) const
{
	// �������v�Z����
	float initialVelocity = force / m_mass;
	// �S���t�{�[���܂ł̋������v�Z����
	float distanceToGolfBall = (from - to).Length();
 	// �S���t�{�[���̈ʒu�ɓ��B�������̑��x���v�Z����
	float velocity = sqrtf(initialVelocity * initialVelocity + 2.0f * distanceToGolfBall * GolfBall::FRICTION);
	// �S���t�{�[���܂ł̓��B���Ԃ�Ԃ�
	return (velocity - initialVelocity) / GolfBall::FRICTION;
}
