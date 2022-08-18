#pragma once
#ifndef GOLF_BALL_DEFINED
#define GOLF_BALL_DEFINED

#include "StepTimer.h"

class GolfBall
{
public:
	// 位置を取得する
	DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }
	// 位置を設定する
	void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
	// 速度を取得する
	DirectX::SimpleMath::Vector2 GetVelocity() const { return m_velocity; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector2& velocity) { m_velocity = velocity; }

public:
	// コンストラクタ
	GolfBall(DirectX::Model* model);
	// デストラクタ
	~GolfBall();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const float& elapsedTime);
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();

	// ゴルフボールを転がす
	void Roll(const DirectX::SimpleMath::Vector2& direction, const float& force);

public:
	// 摩擦係数
	static const float FRICTION;
	// 最大移動速度
	static const float MAX_SPEED;
private:
	// DirectXグラフィックス
	Graphics* m_graphics;

	// ゴルフボールモデル
	DirectX::Model* m_model;
	// ゴルフボールの回転クォータニオン
	DirectX::SimpleMath::Quaternion m_quaternion;
	// ゴルフボールの位置
	DirectX::SimpleMath::Vector2 m_position;
	// ゴルフボールの速度
	DirectX::SimpleMath::Vector2 m_velocity;
	// ゴルフボールの方向
	DirectX::SimpleMath::Vector2 m_heading;
	// ゴルフボールの質量
	float m_mass;
	// ゴルフボールの半径
	float m_radius;
};

#endif		// GOLF_BALL_DEFINED
