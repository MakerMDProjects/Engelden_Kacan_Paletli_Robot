/*Engel tanıyan ve engelden kaçan otonom araç için tasarlanan yazılım 13.12.2020 tarihinde Mustafa DEVRİM tarafından yazılmıştır.*/
/*Pin tanımlamaları*/
#define echoPin 10 //Ultrasonik sensörün echo pini Arduino'nun 10.pinine
#define trigPin 11 //Ultrasonik sensörün trig pini Arduino'nun 11.pinine tanımlandı.
#define SAG_MOTOR_IN1 5
#define SAG_MOTOR_IN2 4
#define SAG_MOTOR_EN 3  // Motor pinlerini tanımlıyoruz.
#define SOL_MOTOR_IN1 6
#define SOL_MOTOR_IN2 7
#define SOL_MOTOR_EN 9
byte mtr_pwm = 130, animate = 0;
long sure, uzaklik; //süre ve uzaklık isminde iki değişken tanımlıyoruz.

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(SAG_MOTOR_IN1, OUTPUT);
  pinMode(SAG_MOTOR_IN2, OUTPUT);
  pinMode(SAG_MOTOR_EN, OUTPUT); //Motorlarımızı çıkış olarak tanımlıyoruz.
  pinMode(SOL_MOTOR_IN1, OUTPUT);
  pinMode(SOL_MOTOR_IN2, OUTPUT);
  pinMode(SOL_MOTOR_EN, OUTPUT);
  delay (5000);
  titreme();
}

void loop() {
  mesafe_hesapla();
  if (uzaklik >= 40)
  {
    mtr_pwm = 130;
    hareketler (mtr_pwm, HIGH, LOW, mtr_pwm, HIGH, LOW); //ileri
  }
  else if (uzaklik >= 30)
  {
    mtr_pwm = 120;
    hareketler (mtr_pwm, HIGH, LOW, mtr_pwm, HIGH, LOW); //ileri
  }
  else if (uzaklik >= 20)
  {
    mtr_pwm = 100;
    hareketler (mtr_pwm, HIGH, LOW, mtr_pwm, HIGH, LOW); //ileri
  }
  else if (uzaklik >= 10)
  {
    mtr_pwm = 90;
    hareketler (mtr_pwm, HIGH, LOW, mtr_pwm, HIGH, LOW); //ileri
  }
  else {// değil ise,
    hareketler (mtr_pwm, LOW, LOW, mtr_pwm, LOW, LOW); //dur
    delay(500);
    animate++;
    if (animate == 5)titreme();
    else if (animate == 8)ekseninde_don();
    else if (animate == 13)sallan();
    mtr_pwm = 130;
    hareketler (mtr_pwm, LOW, HIGH, mtr_pwm, HIGH, LOW); //saga don
    delay(400);
    hareketler (mtr_pwm, LOW, LOW, mtr_pwm, LOW, LOW); //dur
    delay(500);
    mesafe_hesapla();
    hareketler (mtr_pwm, HIGH, LOW, mtr_pwm, HIGH, LOW); //ileri
  }
}

byte hareketler(byte SAG_MTR_EN, bool SAG_MTR_IN1, bool SAG_MTR_IN2, byte SOL_MTR_EN, bool SOL_MTR_IN1, bool SOL_MTR_IN2 ) {
  analogWrite(SAG_MOTOR_EN, SAG_MTR_EN);
  analogWrite(SOL_MOTOR_EN, SOL_MTR_EN);
  digitalWrite(SAG_MOTOR_IN1, SAG_MTR_IN1);
  digitalWrite(SAG_MOTOR_IN2, SAG_MTR_IN2);
  digitalWrite(SOL_MOTOR_IN1, SOL_MTR_IN1);
  digitalWrite(SOL_MOTOR_IN2, SOL_MTR_IN2);
}
void mesafe_hesapla() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  uzaklik = sure / 29.1 / 2;
}
/*Özel hareketler*/
void titreme() {
  for (byte i = 0; i < 15; i++) {
    hareketler (mtr_pwm, HIGH, LOW, mtr_pwm, HIGH, LOW); //ileri
    delay(90);
    hareketler (mtr_pwm, LOW, HIGH, mtr_pwm, LOW, HIGH); //geri
    delay(90);
  }
}
void ekseninde_don() {
  mtr_pwm = 80;
  hareketler (mtr_pwm, LOW, HIGH, mtr_pwm, LOW, HIGH); //geri
  delay(2000);
  mtr_pwm = 130;
  hareketler (mtr_pwm, LOW, HIGH, mtr_pwm, HIGH, LOW); //saga don
  delay(3000);  
}
void sallan() {
  mtr_pwm = 130;
  hareketler (mtr_pwm, LOW, HIGH, mtr_pwm, LOW, HIGH); //geri
  delay(150);
  hareketler (mtr_pwm, LOW, LOW, mtr_pwm, LOW, LOW); //dur
  delay(300);
  for(byte j=0;j<15;j++){
  hareketler (mtr_pwm, LOW, HIGH, mtr_pwm, HIGH, LOW); //saga don
  delay(150);
   hareketler (mtr_pwm, HIGH, LOW, mtr_pwm, LOW, HIGH); //sola don
  delay(150);
  }
  animate = 0;
}
