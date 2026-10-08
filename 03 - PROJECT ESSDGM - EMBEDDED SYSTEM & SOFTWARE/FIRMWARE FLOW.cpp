#include <math.h>

// VARIABLE DECLARATIONS RELATED TO PHASES
#define PHASE_1 1 // LEFT MOTOR CALIBRATION PHASE
#define PHASE_2 2 // RIGHT MOTOR CALIBRATION PHASE
#define PHASE_3 3 // WAITING PHASE
#define PHASE_4 4 // DIFFERENT MOTION DEMONSTRATION PHASE
#define PHASE_5 5 // WAITING PHASE
volatile byte X_EXECUTION_PHASE = PHASE_1;

// VARIABLE DECLARATIONS RELATED TO INTERRUPT
#define INTERRUPT_PIN 2
const byte X_INTERRUPT_PIN = INTERRUPT_PIN;

// INTERRUPT SERVICE ROUTINE DECLARATION
void X_CHANGE_EXECUTION_PHASE();

// DIFFERENT CALIBRATION METHOD DEFINITIONS
void X_LEFT_MOTOR_CALIBRATION();
void X_RIGHT_MOTOR_CALIBRATION();

// DIFFERENT MOTION DEMONSTRATION METHOD DECLARATIONS
void X_DEMONSTRATE_ONE_LOCKED_ONE_DRVE(); // EPICYCLIC MOTION
void X_DEMONSTRATE_SAME_RPM_SAME_DIRECTION(); // PURE PITCH MOTION
void X_DEMONSTRATE_SAME_RPM_OPPOSITE_DIRECTION(); // PURE ROLL MOTION

// DEBOUNCE TUNING CONSTANT
const unsigned long X_DEBOUNCE_DELAY_MS = 25;

// MOTOR DRIVER PIN DECLARATIONS

// MOTOR 1 (LEFT)  -> ULN2003 #1 -> 28BYJ-48 #1
const byte M1_IN1 = 10; // Motor 1 Phase A
const byte M1_IN2 = 3;  // Motor 1 Phase B
const byte M1_IN3 = 4;  // Motor 1 Phase C
const byte M1_IN4 = 5;  // Motor 1 Phase D

// MOTOR 2 (RIGHT) -> ULN2003 #2 -> 28BYJ-48 #2
const byte M2_IN1 = 6;  // Motor 2 Phase A
const byte M2_IN2 = 7;  // Motor 2 Phase B
const byte M2_IN3 = 8;  // Motor 2 Phase C
const byte M2_IN4 = 9;  // Motor 2 Phase D

// ---------------------------------------------------
static const byte HALF_STEP_SEQUENCE[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};
static const double STEPS_PER_OUTPUT_REVOLUTION = 4075.7728;
static const byte MIN_SAFE_RPM = 1;
static const byte MAX_SAFE_RPM = 10;
static const bool M1_INVERT_DIRECTION = false;
static const bool M2_INVERT_DIRECTION = false;
static int M1_HALFSTEP_INDEX = 0;
static int M2_HALFSTEP_INDEX = 0;
void rotate_motors_simultaneously(byte m1_direction, byte m1_rotation_angle, byte m1_rpm, byte m2_direction, byte m2_rotation_angle, byte m2_rpm);

// ---------------------------------------------------

// INITIALIZATION SETUP METHOD
void setup() {

  // INTERRUPT RELATED INITIALIZATION
  pinMode(X_INTERRUPT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(X_INTERRUPT_PIN), X_CHANGE_EXECUTION_PHASE, FALLING);
  
  // PHASE INDICATOR LED INITIALIZATION
  pinMode(LED_BUILTIN, OUTPUT);

  // MOTOR 1 (LEFT) DRIVER INITIALIZATION
  pinMode(M1_IN1, OUTPUT); digitalWrite(M1_IN1, LOW);
  pinMode(M1_IN2, OUTPUT); digitalWrite(M1_IN2, LOW);
  pinMode(M1_IN3, OUTPUT); digitalWrite(M1_IN3, LOW);
  pinMode(M1_IN4, OUTPUT); digitalWrite(M1_IN4, LOW);

  // MOTOR 2 (RIGHT) DRIVER INITIALIZATION
  pinMode(M2_IN1, OUTPUT); digitalWrite(M2_IN1, LOW);
  pinMode(M2_IN2, OUTPUT); digitalWrite(M2_IN2, LOW);
  pinMode(M2_IN3, OUTPUT); digitalWrite(M2_IN3, LOW);
  pinMode(M2_IN4, OUTPUT); digitalWrite(M2_IN4, LOW);
}

// LOOPING LOOP METHOD
void loop() {

  // PHASE SELECTOR SWITCH CASE
  switch (X_EXECUTION_PHASE) {
    
    case PHASE_1:
      digitalWrite(LED_BUILTIN, HIGH);
      X_LEFT_MOTOR_CALIBRATION();
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      break;

    case PHASE_2:
      digitalWrite(LED_BUILTIN, HIGH);
      X_RIGHT_MOTOR_CALIBRATION();
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
      break;
      
    case PHASE_3:
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    
    case PHASE_4:
      digitalWrite(LED_BUILTIN, LOW);
      X_DEMONSTRATE_ONE_LOCKED_ONE_DRVE();
      X_DEMONSTRATE_SAME_RPM_SAME_DIRECTION();
      X_DEMONSTRATE_SAME_RPM_OPPOSITE_DIRECTION();
      X_EXECUTION_PHASE = PHASE_5;
      break;
    
    case PHASE_5:
      digitalWrite(LED_BUILTIN, HIGH);
      break;

    default:
      X_EXECUTION_PHASE = PHASE_1;
      break;
  }
  
}

// INTERRUPT SERVICE ROUTINE DEFINITION
void X_CHANGE_EXECUTION_PHASE() {
  static unsigned long X_LAST_INTERRUPT_TIME = 0;
  unsigned long X_NOW = millis();
  if (X_NOW - X_LAST_INTERRUPT_TIME > X_DEBOUNCE_DELAY_MS) X_EXECUTION_PHASE = (X_EXECUTION_PHASE % 5) + 1;
  X_LAST_INTERRUPT_TIME = X_NOW;
}

// DIFFERENT CALIBRATION METHOD DEFINITIONS

// LEFT MOTOR CALIBRATION
void X_LEFT_MOTOR_CALIBRATION() {
  rotate_motors_simultaneously(1, 2, 6, 0, 0, 6);
  return;
}

// RIGHT MOTOR CALIBRATION
void X_RIGHT_MOTOR_CALIBRATION() {
  rotate_motors_simultaneously(1, 0, 6, 0, 2, 6);
  return;
}

// DIFFERENT MOTION DEMONSTRATION METHOD DEFINITIONS

// EPICYCLIC MOTION
void X_DEMONSTRATE_ONE_LOCKED_ONE_DRVE() {
  rotate_motors_simultaneously(1, 30, 6, 0, 0, 6);
  rotate_motors_simultaneously(1, 30, 6, 0, 0, 6);
  rotate_motors_simultaneously(0, 90, 6, 0, 0, 6);
  rotate_motors_simultaneously(0, 30, 6, 0, 0, 6);
  rotate_motors_simultaneously(1, 30, 6, 0, 0, 6);
  rotate_motors_simultaneously(1, 30, 6, 0, 0, 6);
  return;
}

// PURE PITCH MOTION
void X_DEMONSTRATE_SAME_RPM_SAME_DIRECTION() {
  rotate_motors_simultaneously(1, 30, 6, 0, 30, 6);
  rotate_motors_simultaneously(1, 30, 6, 0, 30, 6);
  rotate_motors_simultaneously(0, 90, 6, 1, 90, 6);
  rotate_motors_simultaneously(0, 30, 6, 1, 30, 6);
  rotate_motors_simultaneously(1, 30, 6, 0, 30, 6);
  rotate_motors_simultaneously(1, 30, 6, 0, 30, 6);
  return;
}

// PURE ROLL MOTION
void X_DEMONSTRATE_SAME_RPM_OPPOSITE_DIRECTION() {
  rotate_motors_simultaneously(1, 30, 6, 1, 30, 6);
  rotate_motors_simultaneously(1, 30, 6, 1, 30, 6);
  rotate_motors_simultaneously(0, 90, 6, 0, 90, 6);
  rotate_motors_simultaneously(0, 30, 6, 0, 30, 6);
  rotate_motors_simultaneously(1, 30, 6, 1, 30, 6);
  rotate_motors_simultaneously(1, 30, 6, 1, 30, 6);
  return;
}

// -------------------------------------------------

void rotate_motors_simultaneously(byte m1_direction, byte m1_rotation_angle, byte m1_rpm, byte m2_direction, byte m2_rotation_angle, byte m2_rpm) {

  m1_direction = (m1_direction == 1) ? 1 : 0;
  m2_direction = (m2_direction == 1) ? 1 : 0;

  if (m1_rotation_angle > 90) m1_rotation_angle = 90;
  if (m2_rotation_angle > 90) m2_rotation_angle = 90;

  if (m1_rpm < MIN_SAFE_RPM) m1_rpm = MIN_SAFE_RPM;
  if (m1_rpm > MAX_SAFE_RPM) m1_rpm = MAX_SAFE_RPM;
  if (m2_rpm < MIN_SAFE_RPM) m2_rpm = MIN_SAFE_RPM;
  if (m2_rpm > MAX_SAFE_RPM) m2_rpm = MAX_SAFE_RPM;

  unsigned int m1_target_steps = (unsigned int) round((double) m1_rotation_angle / 360.0 * STEPS_PER_OUTPUT_REVOLUTION);
  unsigned int m2_target_steps = (unsigned int) round((double) m2_rotation_angle / 360.0 * STEPS_PER_OUTPUT_REVOLUTION);

  unsigned long m1_step_interval_us = (unsigned long) (60000000.0 / ((double) m1_rpm * STEPS_PER_OUTPUT_REVOLUTION));
  unsigned long m2_step_interval_us = (unsigned long) (60000000.0 / ((double) m2_rpm * STEPS_PER_OUTPUT_REVOLUTION));

  unsigned int m1_steps_done = 0;
  unsigned int m2_steps_done = 0;
  unsigned long m1_last_step_time = micros();
  unsigned long m2_last_step_time = micros();

  while (m1_steps_done < m1_target_steps || m2_steps_done < m2_target_steps) {

    unsigned long now = micros();

    if (m1_steps_done < m1_target_steps && (now - m1_last_step_time) >= m1_step_interval_us) {
      bool m1_effective_dir = m1_direction;
      if (M1_INVERT_DIRECTION) m1_effective_dir = !m1_effective_dir;

      M1_HALFSTEP_INDEX = m1_effective_dir ? (M1_HALFSTEP_INDEX + 1) % 8 : (M1_HALFSTEP_INDEX + 7) % 8;
      digitalWrite(M1_IN1, HALF_STEP_SEQUENCE[M1_HALFSTEP_INDEX][0]);
      digitalWrite(M1_IN2, HALF_STEP_SEQUENCE[M1_HALFSTEP_INDEX][1]);
      digitalWrite(M1_IN3, HALF_STEP_SEQUENCE[M1_HALFSTEP_INDEX][2]);
      digitalWrite(M1_IN4, HALF_STEP_SEQUENCE[M1_HALFSTEP_INDEX][3]);

      m1_steps_done++;
      m1_last_step_time = now;
    }

    now = micros();
    if (m2_steps_done < m2_target_steps && (now - m2_last_step_time) >= m2_step_interval_us) {
      bool m2_effective_dir = m2_direction;
      if (M2_INVERT_DIRECTION) m2_effective_dir = !m2_effective_dir;

      M2_HALFSTEP_INDEX = m2_effective_dir ? (M2_HALFSTEP_INDEX + 1) % 8 : (M2_HALFSTEP_INDEX + 7) % 8;
      digitalWrite(M2_IN1, HALF_STEP_SEQUENCE[M2_HALFSTEP_INDEX][0]);
      digitalWrite(M2_IN2, HALF_STEP_SEQUENCE[M2_HALFSTEP_INDEX][1]);
      digitalWrite(M2_IN3, HALF_STEP_SEQUENCE[M2_HALFSTEP_INDEX][2]);
      digitalWrite(M2_IN4, HALF_STEP_SEQUENCE[M2_HALFSTEP_INDEX][3]);

      m2_steps_done++;
      m2_last_step_time = now;
    }
  }

  digitalWrite(M1_IN1, LOW); digitalWrite(M1_IN2, LOW); digitalWrite(M1_IN3, LOW); digitalWrite(M1_IN4, LOW);
  digitalWrite(M2_IN1, LOW); digitalWrite(M2_IN2, LOW); digitalWrite(M2_IN3, LOW); digitalWrite(M2_IN4, LOW);

}

// -------------------------------------------------