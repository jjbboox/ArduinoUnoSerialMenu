#include "myMenu.h"

#define LENGTH(x)       (sizeof(x)/sizeof(x[0]))

// 在指定的时间间隔内将某一个模拟量从一个值调整到另一个值
void GradientAnalogPin(int analogPin, uint8_t from, uint8_t to, uint16_t msec = 1000) {
    int step = from > to?-1:1;
    uint16_t delayms = msec / ((to - from) * step);
    for(uint8_t f = from; f != to; f += step) {
        analogWrite(analogPin, f);
        delay(delayms);
    }
    analogWrite(analogPin, to);
}

// 001事件处理
void event_MI_001(String param) {
    if(param.equalsIgnoreCase("1") || param.equalsIgnoreCase("on")) {
        digitalWrite(LED_BUILTIN, HIGH);
    }
    else if(param.equalsIgnoreCase("0") || param.equalsIgnoreCase("off")) {
        digitalWrite(LED_BUILTIN, LOW);
    }
    else {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
    Serial.print("板载LED已");
    Serial.println((digitalRead(LED_BUILTIN)==HIGH?"打开":"关闭"));
};

// 002事件处理
void event_MI_002(String param) {
    uint16_t loops = 5;
    if(!param.equals("")) {
        loops = param.toInt();
        if(loops == 0) {
            loops = 5;
        }
    }
    int delay_v = 2500 / loops;
    for(uint16_t i = 0; i < loops; i++ ) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(delay_v);
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(delay_v);
    }
};

// 004-006事件处理 TODO:
void event_MI_004(String param) { Serial.println("< 菜单项004 >被执行了"); };
void event_MI_005(String param) { Serial.println("< 菜单项005 >被执行了"); };
void event_MI_006(String param) { Serial.println("< 菜单项006 >被执行了"); };

// 全彩LED红绿蓝三色模拟输出端口定义
const int RedLedPin = 6;
const int GreenLedPin = 5;
const int BlueLedPin = 3;

// 031事件处理 红色亮度调整
void event_MI_031(String param) {
    static uint16_t brightness = 0;
    uint8_t oldBrightness = brightness;
    if(param.equals("+")) {
        brightness += 10;
        brightness = brightness > 255?255:brightness;
    }
    else if(param.equals("-")) {
        brightness = brightness < 10?0:(brightness - 10);
    }
    else if(!param.equals("")) {
        brightness = param.toInt();
    }
    GradientAnalogPin(RedLedPin, oldBrightness, brightness);
    Serial.print("红色亮度调整为:");
    Serial.println(brightness);
};

// 032事件处理 绿色亮度调整
void event_MI_032(String param) {
    static uint16_t brightness = 0;
    uint8_t oldBrightness = brightness;
    if(param.equals("+")) {
        brightness += 10;
        brightness = brightness > 255?255:brightness;
    }
    else if(param.equals("-")) {
        brightness = brightness < 10?0:(brightness - 10);
    }
    else if(!param.equals("")) {
        brightness = param.toInt();
    }
    GradientAnalogPin(GreenLedPin, oldBrightness, brightness);
    Serial.print("绿色亮度调整为:");
    Serial.println(brightness);
};

// 033事件处理 蓝色亮度调整
void event_MI_033(String param) {
    static uint16_t brightness = 0;
    uint8_t oldBrightness = brightness;
    if(param.equals("+")) {
        brightness += 10;
        brightness = brightness > 255?255:brightness;
    }
    else if(param.equals("-")) {
        brightness = brightness < 10?0:(brightness - 10);
    }
    else if(!param.equals("")) {
        brightness = param.toInt();
    }
    GradientAnalogPin(BlueLedPin, oldBrightness, brightness);
    Serial.print("蓝色亮度调整为:");
    Serial.println(brightness);
};

// 绑定子菜单项的回调函数
MenuItem MI_00301("031", "调整红色亮度", event_MI_031);
MenuItem MI_00302("032", "调整绿色亮度", event_MI_032);
MenuItem MI_00303("033", "调整蓝色亮度", event_MI_033);

// 定义子菜单项列表
MenuObj *subMenuList003[] = { 
    (MenuObj *)&MI_00301, 
    (MenuObj *)&MI_00302, 
    (MenuObj *)&MI_00303,
};

// 绑定根菜单项的回调函数
MenuItem MI_001("001", "切换板载LED状态", event_MI_001);
MenuItem MI_002("002", "5秒内闪烁N(默认为5)下", event_MI_002);
// 003为子菜单，绑定子菜单对象
SubMenu  SM_003("003", "全彩LED控制", subMenuList003, LENGTH(subMenuList003));
MenuItem MI_004("004", "菜单项004", event_MI_004);
MenuItem MI_005("005", "菜单项005", event_MI_005);
MenuItem MI_006("006", "菜单项006", event_MI_006);

// 定义根菜单项列表
MenuObj * rootMenuList[] = { 
    (MenuObj *)&MI_001, 
    (MenuObj *)&MI_002, 
    (MenuObj *)&SM_003, 
    (MenuObj *)&MI_004, 
    (MenuObj *)&MI_005, 
    (MenuObj *)&MI_006 
};

// 创建根菜单
SubMenu root("000", "根目录", rootMenuList, LENGTH(rootMenuList));
