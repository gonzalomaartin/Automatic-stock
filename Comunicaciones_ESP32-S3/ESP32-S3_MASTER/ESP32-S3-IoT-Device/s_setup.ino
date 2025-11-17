bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

void on_setup() {

  String hello_msg = String("Hola Mundo! Desde dispositivo ") + deviceID;
  enviarMensajePorTopic(HELLO_TOPIC, hello_msg);

  Wire.begin(SDA, SCL);  // attach the IIC pin
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();           // LCD driver initialization
  lcd.backlight();      // Open the backlight
  lcd.setCursor(0, 0);  // Move the cursor to row 0, column 0
}
