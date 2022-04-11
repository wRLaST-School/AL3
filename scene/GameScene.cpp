#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	texHandle = TextureManager::Load("mario.jpg");

	spr = unique_ptr<Sprite>(Sprite::Create(texHandle, { 100, 50 }));

	model = unique_ptr<Model>(Model::Create());

	wTrans.Initialize();
	vProj.Initialize();

	sndHandle = audio_->LoadWave("se_sad03.wav");

	audio_->PlayWave(sndHandle, true);
}

void GameScene::Update() {
	XMFLOAT2 pos = spr->GetPosition();

	pos.x += 2.0;
	pos.y += 1.0;

	spr->SetPosition(pos);

	if (input_->TriggerKey(DIK_SPACE)) audio_->StopWave(sndHandle);
	debugText_->Print("Kaizokuou ni oreha naru.", 50, 50, 1.0f);
}

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
	model->Draw(wTrans, vProj, texHandle);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	spr->Draw();
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
