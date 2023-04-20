#include "GameScene.h"


/// <summary>
	/// コンストクラタ
	/// </summary>
GameScene::GameScene() {
}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {
	delete spriteCommon;
	delete camera;
	delete player_;
	delete enemyManager_;

	delete UI;
	delete buttomPng1;
	delete buttomPng2;
	delete hpGauge;
	delete unionGauge;
	delete titlePic;
	delete selectPic;
	delete clearPic;
	delete gameoverPic;
	delete floor;
	delete skydome;
	delete sordUI;
	delete sord2UI;
	delete srr;
	delete srl;
	delete sru;
	delete srd;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//スプライト共通部分の初期化
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// カメラ生成
	camera = new Camera(WinApp::window_width, WinApp::window_height);

	camWtf.Initialize();
	camWtf.position = { 0.0f, 3.0f, -8.0f };

	targetWtf.Initialize();
	targetWtf.position = { 0.0f,0.0f,targetDistance };

	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	floorMD = Model::LoadFromOBJ("floor");
	floor = Object3d::Create();
	floor->SetModel(floorMD);
	floor->wtf.position = (Vector3{ 0, -10, 0 });

	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });


	//プレイヤー
	player_ = new Player();
	player_->Initialize(input);

	//エネミー
	enemyManager_ = new EnemyManager();
	enemyManager_->Initialize();
	enemyManager_->SetPlayer(player_);

	//UI
	UI = new Sprite();
	UI->Initialize(spriteCommon);
	UI->SetPozition({ 0,0 });
	UI->SetSize({1280.0f, 720.0f});

	buttomPng1 = new Sprite();
	buttomPng1->Initialize(spriteCommon);
	buttomPng1->SetPozition({ 0,0 });
	buttomPng1->SetSize({ 1280.0f, 720.0f });

	buttomPng2 = new Sprite();
	buttomPng2->Initialize(spriteCommon);
	buttomPng2->SetPozition({ 0,0 });
	buttomPng2->SetSize({ 1280.0f, 720.0f });

	hpGauge = new Sprite();
	hpGauge->Initialize(spriteCommon);
	hpPosition = hpGauge->GetPosition();
	hpGauge->SetPozition(hpPosition);
	hpGauge->SetSize({ 1280.0f, 720.0f });

	unionGauge = new Sprite();
	unionGauge->Initialize(spriteCommon);
	unionGauge->SetPozition({ 0,0 });
	unionScale = unionGauge->GetPosition();
	unionScale.x = 1280.0f;
	unionScale.y = 720.0f;
	unionGauge->SetSize(unionScale);

	//ゲームフロー
	scene = Scene::Title;
	stage = 0;

	titlePic = new Sprite();
	titlePic->Initialize(spriteCommon);
	titlePic->SetPozition({ 0,0 });
	titlePic->SetSize({ 1280,720 });

	selectPic = new Sprite();
	selectPic->Initialize(spriteCommon);
	selectPic->SetPozition({ 0,0 });
	selectPic->SetSize({ 1280,720 });

	clearPic = new Sprite();
	clearPic->Initialize(spriteCommon);
	clearPic->SetPozition({ 0,0 });
	clearPic->SetSize({ 1280,720 });

	gameoverPic = new Sprite();
	gameoverPic->Initialize(spriteCommon);
	gameoverPic->SetPozition({ 0,0 });
	gameoverPic->SetSize({ 1280,720 });

	sordUI = new Sprite();
	sordUI->Initialize(spriteCommon);
	sordUI->SetPozition({ 0,0 });
	sordUI->SetSize({ 1280,720 });

	sord2UI = new Sprite();
	sord2UI->Initialize(spriteCommon);
	sord2UI->SetPozition({ 0,0 });
	sord2UI->SetSize({ 1280,720 });

	srr = new Sprite();
	srr->Initialize(spriteCommon);
	srrPosition = srr->GetPosition();
	srr->SetPozition(srrPosition);
	srr->SetSize({ 1280.0f, 720.0f });

	srl = new Sprite();
	srl->Initialize(spriteCommon);
	srlPosition = srl->GetPosition();
	srl->SetPozition(srlPosition);
	srl->SetSize({ 1280.0f, 720.0f });

	sru = new Sprite();
	sru->Initialize(spriteCommon);
	sruPosition = sru->GetPosition();
	sru->SetPozition(sruPosition);
	sru->SetSize({ 1280.0f, 720.0f });

	srd = new Sprite();
	srd->Initialize(spriteCommon);
	srdPosition = srd->GetPosition();
	srd->SetPozition(srdPosition);
	srd->SetSize({ 1280.0f, 720.0f });

	spriteCommon->LoadTexture(0, "UI.png");
	UI->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "buttom1.png");
	buttomPng1->SetTextureIndex(1);
	spriteCommon->LoadTexture(2, "buttom2.png");
	buttomPng2->SetTextureIndex(2);
	spriteCommon->LoadTexture(3, "hpGauge.png");
	hpGauge->SetTextureIndex(3);
	spriteCommon->LoadTexture(4, "unionGauge.png");
	unionGauge->SetTextureIndex(4);
	spriteCommon->LoadTexture(5, "title.png");
	titlePic->SetTextureIndex(5);
	spriteCommon->LoadTexture(6, "select.png");
	selectPic->SetTextureIndex(6);
	spriteCommon->LoadTexture(7, "clear.png");
	clearPic->SetTextureIndex(7);
	spriteCommon->LoadTexture(8, "gameover.png");
	gameoverPic->SetTextureIndex(8);
	spriteCommon->LoadTexture(9, "migi.png");
	sordUI->SetTextureIndex(9);
	spriteCommon->LoadTexture(10, "migi2.png");
	sord2UI->SetTextureIndex(10);
	spriteCommon->LoadTexture(11, "srr.png");
	srr->SetTextureIndex(11);
	spriteCommon->LoadTexture(12, "srl.png");
	srl->SetTextureIndex(12);
	spriteCommon->LoadTexture(13, "sru.png");
	sru->SetTextureIndex(13);
	spriteCommon->LoadTexture(14, "srd.png");
	srd->SetTextureIndex(14);

	audio = new Audio();
	audio->Initialize();

	audio->LoadWave("kako.wav");





	Reset();
}

void GameScene::Reset() {
	camWtf.Initialize();
	camWtf.position = { 0.0f, 3.0f, -8.0f };

	targetWtf.Initialize();
	targetWtf.position = { 0.0f,0.0f,targetDistance };

	player_->Reset();
}

/// <summary>
/// 毎フレーム処理
/// </summary>
void GameScene::Update() {
	switch (scene)
	{
	case Scene::Title:
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Select;
		}


		//音声再生
		if (soundCheckFlag == 0) {
			//音声再生
			pSourceVoice[0] = audio->PlayWave("kako.wav");
			soundCheckFlag = 1;
		}

		sruPosition.x = 0.0f;
		sruPosition.y = 0.0f;
		sru->SetPozition(sruPosition);

		srdPosition.x = 0.0f;
		srdPosition.y = 0.0f;
		srd->SetPozition(srdPosition);
		
		srrPosition.x = 0.0f;
		srr->SetPozition(srrPosition);

		srlPosition.x = 0.0f;
		srl->SetPozition(srlPosition);


		break;
	case Scene::Select:
		sruPosition.x -= 50.0f;
		sruPosition.y -= 10.0f;
		sru->SetPozition(sruPosition);

		srdPosition.x += 50.0f;
		srdPosition.y += 10.0f;
		srd->SetPozition(srdPosition);
		//ステージの選択
		if(input->LeftStickInput()) {
			if (input->PStickTrigger(L_LEFT)) {
				stage = 0;
			}else if (input->PStickTrigger(L_RIGHT)){
				stage = 1;
			}
		}

		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			enemyManager_->creatEnemy(stage);
			Reset();
			scene = Scene::Play;
		}

		break;
	case Scene::Play:
		CamUpdate();

		srrPosition.x -= 30.0f;
		srr->SetPozition(srrPosition);
		
		srlPosition.x += 30.0f;
		srl->SetPozition(srlPosition);


		enemyManager_->Update();
		
		player_->Update(&camWtf);


		if (enemyManager_->isHitStop) {
			hitStopTimer--;
			if (hitStopTimer < 0) {
				enemyManager_->isHitStop = false;
			}
		}else{
			hitStopTimer = hitStopLimit;
			enemyManager_->Update();
			player_->Update(&camWtf);
		}

		hpGauge->SetPozition({ -400.0f + player_->GetHp() * 4 ,0 });
    

		floor->Update();
		skydome->Update();

		//シーン切り替え
		if (player_->GetHp() < 0) {
			scene = Scene::Gameover;
		}else if (enemyManager_->IsAllEnemyDead()) {
			scene = Scene::Clear;
		}

		break;
	case Scene::Clear:
		pSourceVoice[0]->Stop();
		soundCheckFlag = 0;
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Title;
		}

		break;
	case Scene::Gameover:
		pSourceVoice[0]->Stop();
		soundCheckFlag = 0;
		//シーン切り替え
		if (input->PButtonTrigger(B)) {
			scene = Scene::Title;
		}

		break;
	}
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	/// <summary>
	/// 3Dオブジェクトの描画
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// <summary>
	//3Dオブジェクト描画前処理
	Object3d::PreDraw(dxCommon->GetCommandList());
	//// 3Dオブクジェクトの描画
	switch (scene)
	{
	case Scene::Title:




		break;
	case Scene::Play:
		
		player_->Draw();
		enemyManager_->Draw();
		
    
    floor->Draw();
    skydome->Draw();
		break;
	case Scene::Clear:


		break;
	case Scene::Gameover:


		break;
	}
	//3Dオブジェクト描画後処理
	Object3d::PostDraw();


	//// パーティクルの描画
	switch (scene)
	{
	case Scene::Title:
		titlePic->Draw();

		break;
	case Scene::Select:
		selectPic->Draw();
		
		//ステージ選択わかりやすく
		if (stage == 0) {sordUI->Draw();}
		else if (stage == 1) { sord2UI->Draw(); }

		sru->Draw();
		srd->Draw();
		break;
	case Scene::Play:
		
		// パーティクル描画前処理
	/*	ParticleManager::PreDraw(dxCommon->GetCommandList());*/
		player_->EffDraw();
		enemyManager_->EffDraw();
		//// パーティクル描画後処理
		//ParticleManager::PostDraw();
		
		UI->Draw();
		if (input->ButtonInput(LT)) {
			buttomPng2->Draw();
		}
		else {
			buttomPng1->Draw();
		}
		hpGauge->Draw();
		unionGauge->Draw();

		srr->Draw();
		srl->Draw();

		break;
	case Scene::Clear:
		clearPic->Draw();

		break;
	case Scene::Gameover:
		gameoverPic->Draw();

		break;
	}
}


void GameScene::CamMove() {
	if (input->LeftStickInput()) {
		//カメラの移動
		Vector3 eyeVelocity = { 0,0,0 };

		//通常移動
		if (player_->isAction == 0) {
			//入力
			Vector2 stickVec = input->GetLeftStickVec();

			eyeVelocity.x = stickVec.x;
			eyeVelocity.z = stickVec.y;

			eyeVelocity = eyeVelocity.nomalize();

			eyeVelocity *= camMoveSpeed;
		}
		//回避時移動
		else if (player_->isAction == 3) {
			eyeVelocity = player_->GetDodgeMoveVec();

		}
		
		//移動ベクトルを向いてる方向に合わせる
		eyeVelocity = bVelocity(eyeVelocity, camWtf);

		//更新
		camWtf.position += eyeVelocity;
	}

}

void GameScene::CamRota() {
	//視点移動

	//左右
	Vector3 theta;
	if (input->StickInput(R_LEFT)) {
		theta.y = -camRotaSpeed;
	}else if (input->StickInput(R_RIGHT)) {
		theta.y = camRotaSpeed;
	}
	camWtf.rotation += theta;

	//上下
	if (input->StickInput(R_UP)) {
		targetTheta += camRotaSpeed;
	}else if (input->StickInput(R_DOWN)) {
		targetTheta += -camRotaSpeed;
	}
	
	//角度制限
	if (targetTheta < -PI / 5 * 2) {//下の制限
		targetTheta = -PI / 5 * 2;
	}else if (targetTheta > PI / 3) { //上の制限
		targetTheta = PI / 3;
	}
	
	//視点は一定の距離
	targetWtf.position.z = cos(targetTheta) * targetDistance;
	targetWtf.position.y = sin(targetTheta) * targetDistance;
}

void GameScene::CamUpdate() {
	CamMove();
	CamRota();

	camWtf.UpdateMat();

	camera->SetEye(camWtf.position);

	targetWtf.UpdateMat();
	targetWtf.matWorld *= camWtf.matWorld;
	//y方向の制限
	if (targetWtf.matWorld.m[3][1] < 0) {
		targetWtf.matWorld.m[3][1] = 0;
	}
	camera->SetTarget({ targetWtf.matWorld.m[3][0],targetWtf.matWorld.m[3][1] ,targetWtf.matWorld.m[3][2] });

	camera->Update();
}

Vector3 GameScene::bVelocity(Vector3& velocity, Transform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//内積
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}