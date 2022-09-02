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

// �S���t�{�[����]����
void GolfBall::Roll(const DirectX::SimpleMath::Vector2& direction, const float& force)
{
	using namespace DirectX::SimpleMath;
	// �S���t�{�[�����]��������x�N�g���𐳋K������
	Vector2 rollDirection = Normalize(direction);
	// �^�����������瑬�x���v�Z����
	m_velocity = rollDirection * force / m_mass;
}
