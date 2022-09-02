#include "pch.h"
#include "GolfBall.h"
#include "Common.h"

// 摩擦係数
const float GolfBall::FRICTION = -0.02f;
// 最大移動速度
const float GolfBall::MAX_SPEED = 3.0f;

// コンストラクタ
GolfBall::GolfBall(DirectX::Model* model)
	:
	m_model(model),																	// モデル
	m_quaternion{},																		// クォータニオン
	m_position(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),			// 位置
	m_velocity(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),			// 速度
	m_heading(DirectX::SimpleMath::Vector2(0.0f, 0.0f)),			// 向き
	m_mass(0.45f),																		// 質量
	m_radius(2.13f)																		// 半径
{
	// DirectXグラフィックスを取得する
	m_graphics = Graphics::GetInstance();
}

// デストラクタ
GolfBall::~GolfBall()
{
}

// 初期化する
void GolfBall::Initialize()
{
}

// 更新する
void GolfBall::Update(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsedTime);

	// 摩擦による減速の大きさより速度が速ければ減速させる
	if (m_velocity.Length() > GolfBall::FRICTION)
	{
		// 向きを設定する
		m_heading = m_velocity;
		// 摩擦により減速する
		m_velocity += m_heading * GolfBall::FRICTION;
		// 位置を更新する
		m_position += m_velocity;
		// ゴルフボールの回転軸を設定する
		Vector3 axis = Vector3(m_heading.y, 0.0f, -m_heading.x);
		// ゴルフボールが移動している場合
		if (m_velocity.Length())
		{
			// クォータニオンを生成する
			m_quaternion *= Quaternion::CreateFromAxisAngle(axis, m_velocity.Length() / m_radius);
		}
	}
}

// 描画する
void GolfBall::Render()
{
	using namespace DirectX::SimpleMath;

	// スケール行列を生成する
	Matrix scaleMatrix = Matrix::CreateScale(1.0f, 1.0f, 1.0f);
	// 移動行列を生成する
	Matrix translationMatrix = Matrix::CreateTranslation(m_position.x, m_radius, m_position.y);
	// 回転クォータニオンから回転行列を生成する
	Matrix rotationMatrix = Matrix::CreateFromQuaternion(m_quaternion);
	// ワールド行列を計算する
	Matrix worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	// プリミティブ描画を開始する
	m_graphics->DrawPrimitiveBegin(m_graphics->GetViewMatrix(), m_graphics->GetProjectionMatrix());
	// ゴルフボールを描画する
	m_graphics->DrawModel(m_model, worldMatrix);
	// プリミティブ描画を終了する
	m_graphics->DrawPrimitiveEnd();
}

// 後処理を行う
void GolfBall::Finalize()
{
}

// ゴルフボールを転がす
void GolfBall::Roll(const DirectX::SimpleMath::Vector2& direction, const float& force)
{
	using namespace DirectX::SimpleMath;
	// ゴルフボールが転がる方向ベクトルを正規化する
	Vector2 rollDirection = Normalize(direction);
	// 運動方程式から速度を計算する
	m_velocity = rollDirection * force / m_mass;
}
