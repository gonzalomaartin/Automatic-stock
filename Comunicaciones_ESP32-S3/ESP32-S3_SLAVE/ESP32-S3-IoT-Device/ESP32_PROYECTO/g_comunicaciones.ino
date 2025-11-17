#include "Config.h"

Buffer_Circ Buffer(100); // Instancia del buffer con capacidad de 100 elementos

void suscribirseATopics() 
{
  // Añadir suscripciones a los topics MQTT
  mqtt_subscribe(HELLO_TOPIC);
  mqtt_subscribe(ILUMINATION_TOPIC);
  mqtt_subscribe(PROXIMITY_TOPIC);
  mqtt_subscribe(EMERGENCY_TOPIC);
}

void enviarMensajePorTopic(const char* topic, String outgoingMessage) 
{
  mqtt_publish(topic, outgoingMessage.c_str()); // Publica el mensaje en el tópico MQTT
}

void alRecibirMensajePorTopic(char* topic, String msg) {
  JsonDocument doc, vuelta, t;
  DeserializationError err = deserializeJson(doc, msg); 
  String msg1;
  int nuevo_sensor;
  
  if(strcmp(topic, HELLO_TOPIC) != 0 && strcmp(topic, INCIDENCE_TOPIC) != 0)
  {
    put_item(msg, &Buffer); // Inserta el mensaje en el buffer
  }

  if ((float)Buffer.contador / Buffer.capacidad >= 0.8) // Comprueba si el buffer está al 80% de su capacidad
  {
    String result;
    listanddelete(&Buffer, result); // Lista y elimina elementos del buffer
    enviarMensajePorTopic(INCIDENCE_TOPIC, result); // Publica el resultado en MQTT
  }
}