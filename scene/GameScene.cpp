#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	obj.tex = TextureManager::Load("mario.jpg");
	obj.model = Model::Create();

	vProj.Initialize();

	obj.wld.scale_ = { 5.0f, 5.0f, 5.0f };
	obj.wld.translation_ = {10, 10, 10 };
	obj.wld.rotation_ = { 0.785398, 0.785398, 0 };

	obj.wld.Initialize();

}

void GameScene::Update() {}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	obj.Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->SetPos(32, 32);
	debugText_->Printf("translation (%f %f %f) rotation (%f %f %f) scale (%f %f %f)",
		obj.wld.translation_.x,
		obj.wld.translation_.y,
		obj.wld.translation_.z,

		obj.wld.rotation_.x,
		obj.wld.rotation_.y,
		obj.wld.rotation_.z,

		obj.wld.scale_.x,
		obj.wld.scale_.y,
		obj.wld.scale_.z
		);
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
