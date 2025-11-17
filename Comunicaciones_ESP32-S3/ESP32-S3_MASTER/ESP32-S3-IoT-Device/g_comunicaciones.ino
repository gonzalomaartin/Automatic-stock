order pedido;

void suscribirseATopics() {

  // TODO: añadir suscripciones a los topics MQTT ...
  mqtt_subscribe(HELLO_TOPIC);
  mqtt_subscribe(ORDERPROCES_TOPIC);
  mqtt_subscribe(STOCK_TOPIC);
  //mqtt_subscribe(TEMPERATURE_TOPIC);
  //mqtt_subscribe(EMERGENCY_TOPIC);
  //mqtt_subscribe(CONTROLBOX_TOPIC);
  mqtt_subscribe(STATION_STATUS_TOPIC);
  mqtt_subscribe(ASIGNACION_STATUS_TOPIC);
  mqtt_subscribe(DESPALETIZADO_STATUS_TOPIC);
  mqtt_subscribe(CONVEYOR1_STATUS_TOPIC);
  mqtt_subscribe(SENSOR1_STATUS_TOPIC);
  mqtt_subscribe(AGV_STATUS_TOPIC);
}

void alRecibirMensajePorTopic(char* topic, String incomingMessage) {

  // TODO: Controlador que gestiona la recepción de datos

  // A partir de aquí debemos gestionar los mensajes
  //  recibidos por los diferentes topics (canales)
  //

  // If a message is received on the topic ...
  if (strcmp(topic, HELLO_TOPIC) == 0) {
  }
  if (strcmp(topic, STATION_STATUS_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      String state = doc["STATE"];
      if (state == "ready") {
        lcd.clear();
        lcd.print("STATION REDAY");  // The print content is displayed on the LCD
      } else if (state == "start") {
        StaticJsonDocument<200> doc;
        doc["STATE"] = "ready";
        String state_json;
        serializeJson(doc, state_json);
        enviarMensajePorTopic(AGV_STATUS_TOPIC, state_json);
        enviarMensajePorTopic(CONVEYOR1_STATUS_TOPIC, state_json);
        enviarMensajePorTopic(DESPALETIZADO_STATUS_TOPIC, state_json);
        enviarMensajePorTopic(ASIGNACION_STATUS_TOPIC, state_json);
        enviarMensajePorTopic(SENSOR1_STATUS_TOPIC, state_json);
        lcd.clear();
        lcd.print("START PROCESSING");
      } else if (state == "finished") {
        lcd.clear();
        lcd.print("ORDER FINISHED");
        StaticJsonDocument<200> doc;
        delay(5000);
        doc["ACTION"] = "place";
        String action_json;
        serializeJson(doc, action_json);
        enviarMensajePorTopic(AGV_COMMANDS_TOPIC, action_json);
        doc["ACTION"] = "stop";
        serializeJson(doc, action_json);
        enviarMensajePorTopic(CONVEYOR1_COMMANDS_TOPIC, action_json);
        //stop conveyor

      } else warnln("**>> Solicitud no reconocida!");
    } else warnln("**>> Solicitud no reconocida!");
  }
  if (strcmp(topic, DESPALETIZADO_STATUS_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    String order = "Despaletizado_";
    String tempboxesContainerId = pedido.get_Idboxes();
    int tempncontainers = pedido.get_Size();
    container* tempContainers = pedido.get_containers();
    if (!err) {
      String state = doc["STATE"];
      if (state == "ready") {
        for (int i = 0; i < tempncontainers; i++) {
          box* tempBoxes = tempContainers[i].get_boxes();
          for (int j = 0; j < tempContainers[i].get_containerSize(); j++) {
            if (!(tempBoxes[j].get_pickBox())) {
              StaticJsonDocument<200> doc;
              order = order + tempBoxes[j].get_boxID();
              doc["ACTION"] = order;
              String action_json;
              serializeJson(doc, action_json);
              enviarMensajePorTopic(DESPALETIZADO_COMMANDS_TOPIC, action_json);
              tempBoxes[j].pick_box();
              j = 100;
              i = tempncontainers;
            }
          }
          if(i < tempncontainers){
            
          }
        }
      }
    }
  }
  if (strcmp(topic, CONVEYOR1_STATUS_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      String state = doc["STATE"];
      StaticJsonDocument<200> doc;
      String action_json;
      if (state == "ready") {
        doc["ACTION"] = "start";
        serializeJson(doc, action_json);
        enviarMensajePorTopic(CONVEYOR1_COMMANDS_TOPIC, action_json);
      } else if (state == "object") {
        doc["ACTION"] = "stop";
        serializeJson(doc, action_json);
        enviarMensajePorTopic(CONVEYOR1_COMMANDS_TOPIC, action_json);
      }
    }
  }
  if (strcmp(topic, ASIGNACION_STATUS_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    String order = "Colocar_";
    int tempncontainers = pedido.get_Size();
    container* tempContainers = pedido.get_containers();
    if (!err) {
      String state = doc["STATE"];
      if (state == "start") {
        for (int i = 0; i < tempncontainers; i++) {
          box* tempBoxes = tempContainers[i].get_boxes();
          for (int j = 0; j < tempContainers[i].get_containerSize(); j++) {
            if (!(tempBoxes[j].get_placeBox())) {
              StaticJsonDocument<200> doc;
              order = order + tempBoxes[j].get_boxID();
              doc["ACTION"] = order;
              doc["POSE"] = tempBoxes[j].get_boxpos();
              String action_json;
              serializeJson(doc, action_json);
              enviarMensajePorTopic(ASIGNACION_COMMANDS_TOPIC, action_json);
              tempBoxes[j].place_box();
              j = 100;
              i = tempncontainers;
            }
          }
          if(i < tempncontainers){

          }
        }
        box* proveBox = tempContainers[tempncontainers - 1].get_boxes();
        if ((proveBox[tempContainers[tempncontainers - 1].get_containerSize() - 1].get_placeBox())) {
          delay(10000);
          StaticJsonDocument<200> doc;
          doc["STATE"] = "finished";
          String state_json;
          serializeJson(doc, state_json);
          enviarMensajePorTopic(STATION_STATUS_TOPIC, state_json);
        }
      }
    } else warnln("**>> Solicitud no reconocida!");
  } 
  if (strcmp(topic, SENSOR1_STATUS_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      String state = doc["STATE"];
      if (state == "ready") {
        StaticJsonDocument<200> doc;
        doc["ACTION"] = "start";
        String action_json;
        serializeJson(doc, action_json);
        enviarMensajePorTopic(SENSOR1_COMMANDS_TOPIC, action_json);
      }
    }
  }
  if (strcmp(topic, AGV_STATUS_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      String state = doc["STATE"];
      if (state == "ready") {
        StaticJsonDocument<200> doc;
        doc["ACTION"] = "start";
        String action_json;
        serializeJson(doc, action_json);
        enviarMensajePorTopic(AGV_COMMANDS_TOPIC, action_json);
      }
    }
  }
  if (strcmp(topic, ORDERPROCES_TOPIC) == 0) {
    pedido = getOrder(incomingMessage);
    StaticJsonDocument<200> doc;
    doc["STATE"] = "start";
    String state_json;
    serializeJson(doc, state_json);
    enviarMensajePorTopic(STATION_STATUS_TOPIC, state_json);
  }
  /*if (strcmp(topic, STOCK_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      String msg = doc["msg"];
      Serial.println(msg);
    } else warnln("**>> Solicitud no reconocida!");
  }
  if (strcmp(topic, TEMPERATURE_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      JsonArray array = doc.as<JsonArray>();
      for (JsonVariant v : array) {
        JsonObject obj = v.as<JsonObject>();

        String ID_SENSOR_T = obj["ID_SENSOR"];
        float data = obj["DATA"];

        Serial.println(ID_SENSOR_T);
        Serial.println(data);
      }
    } else warnln("**>> Solicitud no reconocida!");
  }
  if (strcmp(topic, EMERGENCY_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      String EMERGENCY = doc["EMERGENCY_TYPE"];
      Serial.println(EMERGENCY);
    } else warnln("**>> Solicitud no reconocida!");
  }
  if (strcmp(topic, CONTROLBOX_TOPIC) == 0) {
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, incomingMessage);
    if (!err) {
      String ID_BOX = doc["ID_BOX"];
      Serial.println(ID_BOX);
    } else warnln("**>> Solicitud no reconocida!");
  }*/
}

void enviarMensajePorTopic(const char* topic, String outgoingMessage) {

  mqtt_publish(topic, outgoingMessage.c_str());
}
