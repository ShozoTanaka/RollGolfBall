#pragma once
#ifndef GRAPH_SCENE_DEFINED
#define GRAPH_SCENE_DEFINED
#include "DeviceResources.h"
#include "ArcBall.h"
#include "Game.h"
#include "GolfBall.h"

class Game;

class GraphScene
{
public:
	// 開始位置
	const DirectX::SimpleMath::Vector2 START_POSITION = DirectX::SimpleMath::Vector2(-80.0f, 0.0f);

public:
	// コンストラクタ
	GraphScene(Game* game);
	// デストラクタ
	~GraphScene();
	// 初期化する
	void Initialize();
	// 更新する
	void Update(const DX::StepTimer& timer);
	// 描画する
	void Render();
	// 後処理を行う
	void Finalize();
	// アークボールのウィンドウサイズを設定する
	void SetWindow(const int& width, const int& height);

private:
	// 情報を表示する
	void DrawInfo();
	// ボールを描画する
	void DrawBall();
	// 蹴る方向ベクトルを描画する
	void DrawRollDirection();

	// アークボールを使用してカメラをコントロールする
	void ControlCamera(const DX::StepTimer& timer);
	// グリッドを描画する
	void DrawGrid(
		const DirectX::FXMVECTOR& xAxis, 
		const DirectX::FXMVECTOR& yAxis, 
		const DirectX::FXMVECTOR& origin, 
		const size_t& xdivs, 
		const size_t& ydivs, 
		const DirectX::GXMVECTOR& m_color
	);
	// プロジェクションを生成する
	void CreateProjection();

private:
	// Gameクラスのインスタンスへのポインタ
	Game* m_game;
	// DirectX Graphicsクラスのインスタンスへのポインタ
	Graphics* m_graphics;
	// Deviceクラスのインスタンスへのポインタ
	ID3D11Device* m_device;
	// DeviceContextクラスのインスタンスへのポインタ
	ID3D11DeviceContext* m_context;
	// マウスカーソル位置
	DirectX::SimpleMath::Vector2 m_mouseCursorPosition;
	// キーボードステート
	DirectX::Keyboard::State m_keyboardState;
	// マウスステート
	DirectX::Mouse::Mouse::State m_mouseState;
	// マウスステートトラッカー
	DirectX::Mouse::ButtonStateTracker m_mouseStateTracker;

	// ワールド
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ビュー
	DirectX::SimpleMath::Matrix m_viewMatrix;
	// プロジェクション
	DirectX::SimpleMath::Matrix m_projectionMatrix;
	// カメラ回転
	DirectX::SimpleMath::Quaternion m_cameraRotation;
	// カメラ位置
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	// カメラフォーカス
	DirectX::SimpleMath::Vector3 m_cameraFocus;
	// 角度
	float m_rotaionAngle;
	// 注視点から視点までの距離
	float m_distance;
	// ズーム
	float m_zoom;
	// フィールドオブビュー
	float m_fov;
	// ニアクリップ
	float m_nearPlane;
	// ファークリップ
	float m_farPlane;
	// スケール
	float m_scale;
	// アークボール
	ArcBall	 m_ballCamera;
	// 角度
	float m_angle;

	// ゴルフボールのモデル
	std::unique_ptr<DirectX::Model> m_golfBallModel;
	// ゴルフボール
	std::unique_ptr<GolfBall> m_golfBall;

	// ロールアングル
	float m_rollAngle;
	// ロールパワー
	float m_rollPower;
};

#endif		// GRAPH_SCENE_DEFINED
