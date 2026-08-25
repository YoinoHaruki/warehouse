#include <Servo.h>

// --- ピン設定 ---
const int SERVO0_PIN = 6; 
const int SERVO1_PIN = 7;

// --- 角度設定 ---
const float POS_A_0 = 135.0; // モーター0 開始点
const float POS_B_0 = 75.0;  // モーター0 折り返し点

const float POS_A_1 = 180.0; // モーター1 開始点
const float POS_B_1 = 160.0; // モーター1 折り返し点

// ==========================================
// ★ スピード・待機時間の設定（ここを変更）
// ==========================================
// 片道の移動時間 [ms]（例: 2000 = 2秒かけて移動）
// ※ 数値を小さくすると速く、大きくするとゆっくり動きます
const unsigned long MOVE_DURATION_MS = 500;

// 折り返し地点での一時停止時間 [ms]
const int PAUSE_DELAY_MS = 500;
// ==========================================

Servo servo0;
Servo servo1;

const int STEPS = 100; // 補間の細かさ（基本はそのままでOK）

void moveServos(float start0, float end0, float start1, float end1) {
  // 指定した移動時間から1ステップあたりの待機時間を自動計算
  int stepDelay = MOVE_DURATION_MS / STEPS;

  for (int i = 0; i <= STEPS; i++) {
    float progress = (float)i / STEPS;
    
    float currentAngle0 = start0 + (end0 - start0) * progress;
    float currentAngle1 = start1 + (end1 - start1) * progress;

    servo0.write((int)currentAngle0);
    servo1.write((int)currentAngle1);

    delay(stepDelay);
  }
}

void setup() {
  servo0.attach(SERVO0_PIN);
  servo1.attach(SERVO1_PIN);

  // 初期位置（A地点）へセット
  servo0.write((int)POS_A_0);
  servo1.write((int)POS_A_1);
  delay(1000);
}

void loop() {
  // 行き: (135° -> 75°, 180° -> 160°)
  moveServos(POS_A_0, POS_B_0, POS_A_1, POS_B_1);
  delay(PAUSE_DELAY_MS);

  // 帰り: (75° -> 135°, 160° -> 180°)
  moveServos(POS_B_0, POS_A_0, POS_B_1, POS_A_1);
  delay(PAUSE_DELAY_MS);
}