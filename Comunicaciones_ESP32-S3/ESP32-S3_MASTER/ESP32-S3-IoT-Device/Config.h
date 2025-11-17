// COMM BAUDS
#define BAUDS 115200

#define MQTT_BUFFER_SIZE 65535
#define LOGGER_ENABLED            // Comentar para deshabilitar el logger por consola serie

#define LOG_LEVEL TRACE           // nivells en c_logger: TRACE, DEBUG, INFO, WARN, ERROR, FATAL, NONE

// DEVICE
#define DEVICE_ESP_ID             "ESP32S3MASTER"   // ESP32 ID
#define DEVICE_GIIROB_PR2_ID      "giirobpr2_B1" //"giirobpr2_00"

// WIFI
#define NET_SSID                  "iPhone"////"UPV-PSK"
#define NET_PASSWD                "Hxry-Fp0R-8yMS-5HBS"////"giirob-pr2-2023"

// MQTT
#define MQTT_SERVER_IP            "broker.emqx.io"//"mqtt.dsic.upv.es"//
#define MQTT_SERVER_PORT           1883
#define MQTT_USERNAME             "giirob"    // Descomentar para conexión al broker MQTT (user/passwd)
#define MQTT_PASSWORD             "UPV2024"

// SSL
// Define SSL_ROOT_CA to enable TLS/SSL connection

#define HELLO_TOPIC                   "giirob/pr2/B1/hello"    // TODO: topic ejemplo ejercicio inicial
#define ORDERPROCES_TOPIC             "giirob/pr2/B1/orderProces"
#define STATION_STATUS_TOPIC          "giirob/pr2/B1/status"
#define DESPALETIZADO_STATUS_TOPIC    "giirob/pr2/B1/actions/despaletizado/status"
#define DESPALETIZADO_COMMANDS_TOPIC  "giirob/pr2/B1/actions/despaletizado/commands"
#define ASIGNACION_STATUS_TOPIC       "giirob/pr2/B1/actions/asignacion/status"
#define ASIGNACION_COMMANDS_TOPIC     "giirob/pr2/B1/actions/asignacion/commands"
#define CONVEYOR1_STATUS_TOPIC        "giirob/pr2/B1/actions/conveyor1/status"
#define CONVEYOR1_COMMANDS_TOPIC      "giirob/pr2/B1/actions/conveyor1/commands"
#define AGV_STATUS_TOPIC              "giirob/pr2/B1/actions/agv/status"
#define AGV_COMMANDS_TOPIC            "giirob/pr2/B1/actions/agv/commands"
#define SENSOR1_STATUS_TOPIC          "giirob/pr2/B1/control/sensor1/status"
#define SENSOR1_COMMANDS_TOPIC        "giirob/pr2/B1/control/sensor1/commands"
#define STOCK_TOPIC                   "giirob/pr2/B1/control/stock"    // TODO: topic ejemplo ejercicio inicial
#define TEMPERATURE_TOPIC             "giirob/pr2/B1/control/sensors/temperature"    // TODO: topic ejemplo ejercicio inicial
#define EMERGENCY_TOPIC               "giirob/pr2/B1/control/emergency"    // TODO: topic ejemplo ejercicio inicial
#define CONTROLBOX_TOPIC              "giirob/pr2/B1/control/boxes"    // TODO: topic ejemplo ejercicio inicial

#define SDA 14 //Define SDA pins
#define SCL 13 //Define SCL pins




