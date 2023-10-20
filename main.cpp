#include "MyMath.h"
#include <Novice.h>

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	struct Object {
		Vector2 pos = {0};
		Vector2 speed = {0};
		Vector2 radius = {0};
		int degree = 0;
	};

	int texHandle = Novice::LoadTexture("./daihuku1.png");

	const float kPlayerSpeed = 5.0f;

	Object player;
	player.pos = {300.0f, 300.0f};
	player.speed = {
	    cosf(ToRadian(player.degree)) * kPlayerSpeed, sinf(ToRadian(player.degree)) * kPlayerSpeed};
	player.radius = {32.0f, 32.0f};

	Vector2 circlePos = {0};

	bool isDegreeChange = false;

	Object enemy = {
	    {1280.0f / 2.0f, 720.0f / 2.0f},
        {0.0f,           0.0f         },
        {64.0f,          64.0f        },
        0
    };

	bool isDelay = false;
	int delayTime = 0;
	const int kDelayTimeMax = 120;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (!isDelay) {

			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				isDegreeChange = !isDegreeChange;
			}

			if (keys[DIK_UP]) {
				player.degree -= 1;
			}
			if (keys[DIK_DOWN]) {
				player.degree += 1;
			}

			player.speed = {
			    cosf(ToRadian(player.degree) * kPlayerSpeed),
			    sinf(ToRadian(player.degree) * kPlayerSpeed),
			};

			player.speed = Normalize(player.speed);
			player.speed = {
			    player.speed.x * kPlayerSpeed,
			    player.speed.y * kPlayerSpeed,
			};

			player.pos = Add(player.pos, player.speed);
		} else {
			delayTime++;
			if (delayTime >= kDelayTimeMax) {
				delayTime = 0;
				isDelay = false;
			}
		}
#pragma region 壁
		if (player.pos.x >= 1280 - player.radius.x) {
			player.degree = ToDegree(CalculateAngle(player.speed, {-1.0f, 0.0f}));
			player.pos.x = 1280 - player.radius.x;
		}
		if (player.pos.x <= player.radius.x) {
			player.degree = ToDegree(CalculateAngle(player.speed, {1.0f, 0.0f}));
			player.pos.x = player.radius.x;
		}
		if (player.pos.y <= player.radius.y) {
			player.degree = ToDegree(CalculateAngle(player.speed, {0.0f, 1.0f}));
			player.pos.y = player.radius.y;
		}
		if (player.pos.y >= 720 - player.radius.y) {
			player.degree = ToDegree(CalculateAngle(player.speed, {0.0f, -1.0f}));
			player.pos.y = 720 - player.radius.y;
		}
#pragma endregion

#pragma region 敵

		float dist = VectorMagnitude(Sub(player.pos, enemy.pos));
		int r = (int)((player.radius.x - 8 + enemy.radius.x));
		if (!isDelay) {
			if (dist <= r) {
				Vector2 contact = Sub(player.pos, enemy.pos);
				contact = Mul(Normalize(contact), enemy.radius);
				contact = Add(enemy.pos, contact);

				player.degree = ToDegree(CalculateAngle(contact, player.speed));

				Vector2 offsetRadius = Sub(player.radius, {8.0f, 8.0f});

				Vector2 offset =
				    Mul(Normalize(Sub(player.pos, contact)), Add(offsetRadius, {1.0f, 1.0f}));
				// プレイヤー押し戻す
				player.pos = Add(contact, offset);

				player.speed = {
				    cosf(ToRadian(player.degree) * kPlayerSpeed),
				    sinf(ToRadian(player.degree) * kPlayerSpeed),
				};

				player.speed = Normalize(player.speed);
				player.speed = {
				    player.speed.x * kPlayerSpeed,
				    player.speed.y * kPlayerSpeed,
				};

				isDelay = true;
			}
		}
#pragma endregion

		float offset = 40.0f;
		circlePos = {
		    player.pos.x + player.speed.x * offset, player.pos.y + player.speed.y * offset};

		float angle = CalculateAngle(player.speed, {-1.0f, 0.0f});

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
// デバッグ
#ifdef _DEBUG

		Novice::DrawEllipse(
		    (int)player.pos.x, (int)player.pos.y, (int)player.radius.x, (int)player.radius.y, 0.0f,
		    WHITE, kFillModeSolid);

#endif
		Novice::DrawSprite(
		    (int)player.pos.x - 32, (int)player.pos.y - 32, texHandle, 1.0f, 1.0f, 0.0f, WHITE);

		Novice::DrawEllipse(
		    (int)circlePos.x, (int)circlePos.y, (int)8, (int)8, 0.0f, RED, kFillModeSolid);

		Novice::DrawEllipse(
		    (int)enemy.pos.x, (int)enemy.pos.y, (int)enemy.radius.x, (int)enemy.radius.y, 0.0f,
		    GREEN, kFillModeSolid);

		Novice::ScreenPrintf(
		    0, 0, "degree : %d, radian : %lf", player.degree, ToRadian(player.degree));

		Novice::ScreenPrintf(0, 30, "speed : [%lf,%lf]", player.speed.x, player.speed.y);
		Novice::ScreenPrintf(0, 60, "dist : [%lf], r : [%d]", dist, r);
		Novice::ScreenPrintf(0, 90, "delayTime : [%d]", delayTime);
		Novice::ScreenPrintf(0, 120, "twoAngle : [%d] : [%lf]", ToDegree(angle), angle);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
