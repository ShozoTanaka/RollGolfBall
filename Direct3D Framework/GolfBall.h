#pragma once
#ifndef GOLF_BALL_DEFINED
#define GOLF_BALL_DEFINED

#include "StepTimer.h"

class GolfBall
{
public:
	// 摩擦係数
	static const float FRICTION;
	// 最大移動速度(1秒間辺りのドット数)
	static const float MAX_SPEED;

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
	// ゴルフボールの位置を予測する
	DirectX::SimpleMath::Vector2 PredictFuturePosition(const float& time) const;
	// ゴルフボールの移動にかかる時間を返す
	float TimeToMoveDistance(const DirectX::SimpleMath::Vector2& from, const DirectX::SimpleMath::Vector2& to, const float& force) const;
	// 描画する
	void Render();
	// 将来の位置を描画する
	void GolfBall::DrawFuturePosition(const float& time);
	// ゴルフボールを転がす
	void Roll(const DirectX::SimpleMath::Vector2& direction, const float& force);
	// 後処理
	void Finalize();

private:
	// DirectXグラフィックス
	Graphics* m_graphics;

	// ボールモデル
	DirectX::Model* m_model;
	// ボールの回転を示すクォータニオン
	DirectX::SimpleMath::Quaternion m_quaternion;
	// 位置
	DirectX::SimpleMath::Vector2 m_position;
	// 速度
	DirectX::SimpleMath::Vector2 m_velocity;
	// 方向ベクトル
	DirectX::SimpleMath::Vector2 m_heading;
	// 質量
	float m_mass;
	// 半径
	float m_radius;
};

#endif		// GOLF_BALL_DEFINED
