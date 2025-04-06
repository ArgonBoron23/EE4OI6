#define STEP_A 3
#define DIR_A 2
#define STEP_B 9
#define DIR_B 8

void setup() {
  pinMode(STEP_A, OUTPUT);
  pinMode(DIR_A, OUTPUT);
  pinMode(STEP_B, OUTPUT);
  pinMode(DIR_B, OUTPUT);
}

void moveRight(uint32_t steps) {
  //digitalWrite(DIR_A, HIGH); // Motor A DIR
  digitalWrite(DIR_B, HIGH);  // Motor B DIR

  uint32_t previousTime = micros();
  for (uint32_t i = 0; i < steps; i++) {
    while (micros() - previousTime < 100) {} // Wait for 100 microseconds
    //digitalWrite(STEP_A, HIGH); // Motor A step
    digitalWrite(STEP_B, HIGH); // Motor B step
    previousTime = micros();
    while (micros() - previousTime < 100) {} // Wait for 100 microseconds
    //digitalWrite(STEP_A, LOW);
    digitalWrite(STEP_B, LOW);
    previousTime = micros();
  }
}

void moveLeft(uint32_t steps) {
  //digitalWrite(DIR_A, LOW);  // Motor A DIR
  digitalWrite(DIR_B, LOW); // Motor B DIR

  uint32_t previousTime = micros();
  for (uint32_t i = 0; i < steps; i++) {
    while (micros() - previousTime < 100) {} // Wait for 100 microseconds
    //digitalWrite(STEP_A, HIGH); // Motor A step
    digitalWrite(STEP_B, HIGH); // Motor B step
    previousTime = micros();
    while (micros() - previousTime < 100) {} // Wait for 100 microseconds
    //digitalWrite(STEP_A, LOW);
    digitalWrite(STEP_B, LOW);
    previousTime = micros();
  }
}

void loop() {
  moveRight(12000);  // Move right 1000 steps
  delay(1000);      // Wait for 2 seconds
  moveLeft(12000);   // Move left 1000 steps
  delay(1000);      // Wait for 2 seconds
}
