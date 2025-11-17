order getOrder(String incomingMessage) {
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, incomingMessage);
  order tempOrder;
  if (!err) {
    tempOrder = order(doc["N_CONT"].as<int>(), doc["ID_PEDIDO"]);
    JsonArray CONTAINER = doc["CONTAINER"];
    for (JsonVariant v : CONTAINER) {
      container inputContainer = container(v["N_BOX"].as<int>(), v["ID_CONT"]);
      JsonArray Positions = v["BOXES"];
      for (JsonVariant w : Positions) {
        box inputBox = box(w["ID_BOX"], w["POSE"]);
        String id = w["ID_BOX"];
        inputContainer.add_box(inputBox);
      }
      tempOrder.add_container(inputContainer);
    }
    tempOrder.set_Idboxes();
  }
  return tempOrder;
}

bool compareIDs(String ID1, String ID2)
{
  if(ID1 == ID2)
  {
    return true;
  } else
  {
    return false;
  }
}

