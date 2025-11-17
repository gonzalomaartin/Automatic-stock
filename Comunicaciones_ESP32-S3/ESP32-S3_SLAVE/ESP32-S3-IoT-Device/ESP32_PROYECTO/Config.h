// COMM BAUDS
#define BAUDS 115200

#define LOGGER_ENABLED            // Comentar para deshabilitar el logger por consola serie

#define LOG_LEVEL TRACE           // nivells en c_logger: TRACE, DEBUG, INFO, WARN, ERROR, FATAL, NONE

// DEVICE
//#define DEVICE_ESP_ID             "54CE036142<1"   // ESP32 ID
#define DEVICE_GIIROB_PR2_ID      "97" //"giirobpr2_00"

// WIFI
#define NET_SSID                  "Gonzalo"//"iPhone"//
#define NET_PASSWD                "galbelda"//"Hxry-Fp0R-8yMS-5HBS"//

// MQTT
#define MQTT_SERVER_IP            "broker.emqx.io"
#define MQTT_SERVER_PORT          1883
#define MQTT_USERNAME             "giirob"    // Descomentar esta línea (y la siguiente) para que se conecte al broker MQTT usando usuario y contraseña
#define MQTT_PASSWORD             "UPV2024"


// SSL
// Define SSL_ROOT_CA to enable TLS/SSL connection
#define HELLO_TOPIC               "giirob/pr2/b1/devices/hello"    // TODO: topic ejemplo ejercicio inicial
#define ILUMINATION_TOPIC         "giirob/pr2/b1/control/sensors/ilumination"    // TODO: topic ejemplo ejercicio inicial
#define PROXIMITY_TOPIC           "giirob/pr2/b1/control/sensors/proximity" 
#define EMERGENCY_TOPIC           "giirob/pr2/b1/control/emergency"
#define CONTROLBOX_TOPIC          "giirob/pr2/b1/control/boxes"
#define INCIDENCE_TOPIC           "giirob/pr2/b1/control/incidence"    

// IO
#define PIN_ANALOG_IN             21
#define LED_BUILTIN               42
#define PIN_BUTTON                14
#define US_SENSOR1                 2
#define US_SENSOR2                 0

/* GPIO of CAMERA_MODEL_ESP32S3_EYE */
  #define PWDN_GPIO_NUM     -1
  #define RESET_GPIO_NUM    -1
  #define XCLK_GPIO_NUM      15
  #define SIOD_GPIO_NUM     4
  #define SIOC_GPIO_NUM     5
  
  #define Y9_GPIO_NUM       16
  #define Y8_GPIO_NUM       17
  #define Y7_GPIO_NUM       18
  #define Y6_GPIO_NUM       12
  #define Y5_GPIO_NUM       10
  #define Y4_GPIO_NUM       8
  #define Y3_GPIO_NUM       9
  #define Y2_GPIO_NUM       11
  #define VSYNC_GPIO_NUM    6
  #define HREF_GPIO_NUM     7
  #define PCLK_GPIO_NUM     13


