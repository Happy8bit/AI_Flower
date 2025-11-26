
/**
 * SHT30温湿度传感器测试程序
 * 功能：正确读取SHT30传感器的温度和湿度数据
 * 接线说明：
 *   SDA -> A4
 *   SCL -> A5
 *   VCC -> 5V
 *   GND -> GND
 */

#include <Wire.h>
#include <Adafruit_SHT31.h>

// 创建SHT30传感器对象
Adafruit_SHT31 sht30 = Adafruit_SHT31();

void setup() {
  // 初始化串口通信
  Serial.begin(9600);
  Serial.println("SHT30传感器测试程序启动");
  Serial.println("================================");
  
  // 尝试初始化SHT30传感器
  // 0x44是SHT30的默认I2C地址
  if (!sht30.begin(0x44)) {
    Serial.println("未找到SHT30传感器！请检查：");
    Serial.println("1. 接线是否正确（SDA->A4, SCL->A5, VCC->5V, GND->GND");
    Serial.println("2. I2C地址是否正确");
    Serial.println("3. 传感器是否损坏");
    while (1) {
      delay(1000);
    }
  }
  
  Serial.println("SHT30传感器初始化成功");
  Serial.println("----------------------------");
}

void loop() {
  // 读取温度数据（摄氏度）
  float temperature = sht30.readTemperature();
  
  // 读取湿度数据（百分比）
  float humidity = sht30.readHumidity();
  
  // 检查数据是否有效
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("读取SHT30数据失败");
    delay(2000);
    return;
  }
  
  // 打印传感器读数
  Serial.print("温度: ");
  Serial.print(temperature);
  Serial.print("°C  |  湿度: ");
  Serial.print(humidity);
  Serial.println("%");
  
  // 数据有效性检查
  Serial.print("数据质量: ");
  if (temperature >= -40 && temperature <= 125 && humidity >= 0 && humidity <= 100) {
    Serial.println("✓ 正常");
  } else {
    Serial.println("✗ 异常");
  }
  
  Serial.println("----------------------------");
  delay(2000);
}
