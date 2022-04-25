#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "Util.h"

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	obj.model = Model::CreateFromOBJ("monkey", false);

	vProj.Initialize();

	obj.wld.Initialize();

	float boxsize = 2;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			floor[i][j] = Obj3D(WorldTransform(), &vProj, 0, nullptr);
			floor[i][j].model = Model::Create();
			floor[i][j].tex = TextureManager::Load("mario.jpg");
			floor[i][j].wld.Initialize();
			floor[i][j].wld.translation_ = XMFLOAT3(-boxsize + i * boxsize, -3, -boxsize + j * boxsize);
			floor[i][j].wld.UpdateMatrix();
		}
	}
}

void GameScene::Update() {

	obj.wld.rotation_ = obj.wld.rotation_ + XMFLOAT3(0, XM_PI / 72 * (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)), 0);
	
	XMMATRIX rotmat = XMMatrixIdentity();
	rotmat *= XMMatrixRotationY(XM_PI / 72 * (input_->PushKey(DIK_RIGHT) - input_->PushKey(DIK_LEFT)));
	
	obj.front.CalcWithMatLH(rotmat);

	Vec3 move = obj.front.SetLength(obj.speed) * (input_->PushKey(DIK_UP) - input_->PushKey(DIK_DOWN));
	obj.wld.translation_ = obj.wld.translation_ + (move.GetXMFloat());
	obj.wld.UpdateMatrix();

	float cameraDistance = 5.0f;

	Vec3 back = obj.front * -1;

	back.SetLength(cameraDistance);

	vProj.target = obj.wld.translation_;
	vProj.eye = obj.wld.translation_ + back.GetXMFloat();
	vProj.UpdateMatrix();
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
	obj.Draw();
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			floor[i][j].Draw();
		}
	}
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
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
