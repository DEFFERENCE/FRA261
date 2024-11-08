
const int Encoder_A = 27;  // Define encoder pins
const int Encoder_B = 28;
const int Time_Interval = 100;  // Update interval in milliseconds
const float counts_per_revolution = 2048.0 * 4; // Quadrature mode
const float radians_per_count = (2 * PI) / counts_per_revolution;

volatile long count = 0;  // Use volatile for shared variables in ISR
int inputA, inputB;
bool homingFlag = false;

unsigned long last_time = 0;

void setup() {
  Serial.begin(9600);

  pinMode(Encoder_A, INPUT);
  pinMode(Encoder_B, INPUT);

  // Attach interrupts for encoder signals
  attachInterrupt(digitalPinToInterrupt(Encoder_A), handleEncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(Encoder_B), handleEncoderB, CHANGE);
}

void loop() {
  unsigned long current_time = millis();
  if (current_time - last_time >= Time_Interval) {
    static long prev_count = 0;

    // Initialize position and velocity
    double position = 0.0;
    double velocity = 0.0;

    // Calculate position in radians
    position = count * radians_per_count;

    // Calculate velocity in rad/s
    double delta_count = count - prev_count;
    double delta_time = (current_time - last_time); // Time in ms
    velocity = (delta_count * radians_per_count) * 1000 / delta_time; // Convert ms to s

    // Update previous values for next iteration
    prev_count = count;
    last_time = current_time;

    // Output position and velocity in a comma-separated format for SerialPlot
    Serial.print(position);
    Serial.print(",");
    Serial.println(velocity);
  }
}

void handleEncoderA() {
  // Read both encoder inputs
  inputA = digitalRead(Encoder_A);
  inputB = digitalRead(Encoder_B);

  // Update count based on A transition
  if (inputA == HIGH) {
    if (inputB == LOW) {
      count++;  // Clockwise
    } else {
      count--;  // Counterclockwise
    }
  } else {
    if (inputB == HIGH) {
      count++;  // Clockwise
    } else {
      count--;  // Counterclockwise
    }
  }
}

void handleEncoderB() {
  // Read both encoder inputs
  inputA = digitalRead(Encoder_A);
  inputB = digitalRead(Encoder_B);

  // Update count based on B transition
  if (inputB == HIGH) {
    if (inputA == HIGH) {
      count++;  // Clockwise
    } else {
      count--;  // Counterclockwise
    }
  } else {
    if (inputA == LOW) {
      count++;  // Clockwise
    } else {
      count--;  // Counterclockwise
    }
  }
}
