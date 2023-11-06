#include <Adafruit_Fingerprint.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(10, 9); // MFRC522 mfrc522(SS_PIN, RST_PIN)
constexpr uint8_t buzzerPin = A3;

int relayPin = 4;

char initial_password1[4] = {'1', '1', '1', '1'};
char initial_password2[4] = {'2', '2', '2', '2'};
char initial_password3[4] = {'3', '3', '3', '3'};
char initial_password4[4] = {'4', '4', '4', '4'};

String tagUID1 = "B0 2A 32 25";
String tagUID2 = "4B 2D CE 79";
String tagUID3 = "09 CC CE 79";
String tagUID4 = "70 0D CE 79";

char password[4];
boolean RFIDMode = true;
char key_pressed = 0;
uint8_t i = 0;

const byte rows = 4;
const byte columns = 3;


char hexaKeys[rows][columns] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};


byte row_pins[rows] = {5, 6, 7, 8};
byte column_pins[columns] = {A2, A1, A0};


Keypad keypad_key = Keypad( makeKeymap(hexaKeys), row_pins, column_pins, rows, columns);

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  pinMode(buzzerPin, OUTPUT);
  lcd.begin();   // LCD screen
  lcd.backlight();
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  finger.begin(57600);

  lcd.setCursor(0, 0);
  lcd.print("  Door Locked");
  lcd.setCursor(0, 1);


}

void loop() {
  rfid();
  key();
  fing();

}
void rfid()
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String tag = "";
  for (byte j = 0; j < mfrc522.uid.size; j++)
  {
    tag.concat(String(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " "));
    tag.concat(String(mfrc522.uid.uidByte[j], HEX));
  }
  tag.toUpperCase();
  if (tag.substring(1) == tagUID1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Tag Matched");
    lcd.setCursor(0, 1);
    lcd.print("    Welcome");
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    delay(3000);
    digitalWrite(relayPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Door Locked");
    lcd.setCursor(0, 1);
  }
  else if (tag.substring(1) == tagUID2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Tag Matched");
    lcd.setCursor(0, 1);
    lcd.print("    Welcome");
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    delay(3000);
    digitalWrite(relayPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Door Locked");
    lcd.setCursor(0, 1);
  }
  else if (tag.substring(1) == tagUID3)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Tag Matched");
    lcd.setCursor(0, 1);
    lcd.print("    Welcome");
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    delay(3000);
    digitalWrite(relayPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Door Locked");
    lcd.setCursor(0, 1);
  }
  else if (tag.substring(1) == tagUID4)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Tag Matched");
    lcd.setCursor(0, 1);
    lcd.print("    Welcome");
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW);
    delay(3000);
    digitalWrite(relayPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Door Locked");
    lcd.setCursor(0, 1);
  }

  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong Tag");
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("  Door Locked");
    lcd.setCursor(0, 1);
  }
}
void key()
{

  key_pressed = keypad_key.getKey(); // Storing keys
  if (key_pressed)
  {
    password[i++] = key_pressed; // Storing in password variable
    lcd.print("*");
  }
  if (i == 4) // If 4 keys are completed
  {
    delay(200);
    if (!(strncmp(password, initial_password1, 4))) // If password is matched
    {
      lcd.clear();
      lcd.print(" Pass Accepted");
      lcd.setCursor(0, 1);
      lcd.print("   Welcome");
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(relayPin, LOW);
      delay(3000);
      digitalWrite(relayPin, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Door Locked");
      lcd.setCursor(0, 1);
      i = 0;
    }
    else if (!(strncmp(password, initial_password2, 4))) // If password is matched
    {
      lcd.clear();
      lcd.print(" Pass Accepted");
      lcd.setCursor(0, 1);
      lcd.print("   Welcome");
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(relayPin, LOW);
      delay(3000);
      digitalWrite(relayPin, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Door Locked");
      lcd.setCursor(0, 1);
      i = 0;
    }
    else if (!(strncmp(password, initial_password3, 4))) // If password is matched
    {
      lcd.clear();
      lcd.print(" Pass Accepted");
      lcd.setCursor(0, 1);
      lcd.print("   Welcome");
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(relayPin, LOW);
      delay(3000);
      digitalWrite(relayPin, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Door Locked");
      lcd.setCursor(0, 1);
      i = 0;
    }
    else if (!(strncmp(password, initial_password4, 4))) // If password is matched
    {
      lcd.clear();
      lcd.print(" Pass Accepted");
      lcd.setCursor(0, 1);
      lcd.print("   Welcome");

      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(buzzerPin, LOW);
      digitalWrite(relayPin, LOW);
      delay(3000);
      digitalWrite(relayPin, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Door Locked");
      lcd.setCursor(0, 1);
      i = 0;
    }
    else
    {
      lcd.clear();
      lcd.print("Wrong Password");
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);

      digitalWrite(relayPin, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Door Locked");
      i = 0;
    }
    lcd.setCursor(0, 1);
  }
}
void fing()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  {
    return -1;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Messy Image");
    lcd.setCursor(0, 1);
    lcd.print("  Try Again");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Door Locked");
    lcd.setCursor(0, 1);
    return -1;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Not Valid Finger");
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(buzzerPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Door Locked");
    lcd.setCursor(0, 1);
    return -1;
  }

  // found a match!
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Door Unlocked");
  lcd.setCursor(0, 1);
  lcd.print("    Welcome");
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  digitalWrite(buzzerPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(relayPin, LOW);
  delay(3000);
  digitalWrite(relayPin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Door Locked");
  lcd.setCursor(0, 1);
  return finger.fingerID;
}
