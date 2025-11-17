struct Buffer_Circ {
  String* data; // Puntero a array de Strings
  int bufIN, bufOUT, contador, capacidad;

  // Constructor para inicializar el buffer
  Buffer_Circ(int cap) : bufIN(0), bufOUT(0), contador(0), capacidad(cap) {
    data = new String[capacidad]; // Asigna memoria para el array de Strings
  }

  // Destructor para liberar memoria
  ~Buffer_Circ() {
    delete[] data; // Libera la memoria asignada
  }
};

// Declaraciones de funciones
String get_item(Buffer_Circ* buff);
int put_item(const String& msg, Buffer_Circ* buff);
bool vacia(Buffer_Circ* buff);
bool llena(Buffer_Circ* buff);
void listanddelete(Buffer_Circ* buff, String& result);
int tam(Buffer_Circ* buff);

// Implementación de las funciones
String get_item(Buffer_Circ* buff) 
{
  if (vacia(buff)) // Comprueba si el buffer está vacío
    return ""; // Si está vacío, devuelve una cadena vacía
  else 
  {
    String item = buff->data[buff->bufOUT]; // Obtiene el elemento en bufOUT
    buff->contador--; // Decrementa el contador
    buff->bufOUT = (buff->bufOUT + 1) % buff->capacidad; // Actualiza bufOUT de manera circular
    return item; // Devuelve el elemento
  }
}

int put_item(const String& msg, Buffer_Circ* buff) 
{
  if (llena(buff)) // Comprueba si el buffer está lleno
    return -1; // Si está lleno, devuelve -1
  else 
  {
    buff->data[buff->bufIN] = msg; // Inserta el mensaje en bufIN
    buff->contador++; // Incrementa el contador
    buff->bufIN = (buff->bufIN + 1) % buff->capacidad; // Actualiza bufIN de manera circular
    return 0; // Devuelve 0 indicando éxito
  }
}

bool vacia(Buffer_Circ* buff) 
{
  return buff->contador == 0; // Devuelve true si el contador es 0
}

bool llena(Buffer_Circ* buff) 
{
  return buff->contador == buff->capacidad; // Devuelve true si el contador es igual a la capacidad
}

void listanddelete(Buffer_Circ* buff, String& result) 
{
  StaticJsonDocument<1000> doc;  // Crea un documento JSON con capacidad adecuada
  JsonArray data = doc.createNestedArray("data"); // Crea un array JSON anidado
  
  while (!vacia(buff)) // Mientras el buffer no esté vacío
  { 
    data.add(buff->data[buff->bufOUT]); // Añade el elemento actual al array JSON
    buff->contador--; // Decrementa el contador
    buff->bufOUT = (buff->bufOUT + 1) % buff->capacidad; // Actualiza bufOUT de manera circular
  }
  serializeJson(doc, result); // Serializa el documento JSON en la cadena result
  
  enviarMensajePorTopic(INCIDENCE_TOPIC, result); // Envía el mensaje por el tópico MQTT
  delay(100); // Espera un breve tiempo
}

int tam(Buffer_Circ* buff) 
{
  return buff->contador; // Devuelve el número de elementos en el buffer
}

void us(void *pvParameters)
{
  while(1)
  {
    StaticJsonDocument<200> doc; // Crea el mensaje en formato JSON
    doc["ID_SENSOR"] = "us001"; // ID del sensor
    doc["PROXIMITY_TYPE"] = "near"; // Tipo de proximidad
    String state_json;
    serializeJson(doc, state_json); // Serializa el documento JSON en una cadena

    digitalWrite(US_SENSOR1, LOW);
    delay(200);

    // Generar un pulso de 10 microsegundos en el pin de disparo
    digitalWrite(US_SENSOR1, HIGH);
    delay(100);
    digitalWrite(US_SENSOR1, LOW);

    // Leer la duración del pulso en el pin de eco
    long time = pulseIn(US_SENSOR2, HIGH);

    // Calcular la distancia en cm
    int distance = time * 0.034 / 2;

    // Verificar si la distancia es menor que el umbral
    if (distance < 5) 
    {
      enviarMensajePorTopic(PROXIMITY_TOPIC, state_json); // Envía el mensaje por el tópico
      while(distance < 5)
      { 
        long time = pulseIn(US_SENSOR2, HIGH);
        int distance = time * 0.034 / 2;
        vTaskDelay(100/ portTICK_PERIOD_MS); // Espera un breve tiempo
      }
    }

    // Esperar un breve tiempo antes de tomar otra lectura
    vTaskDelay(200/ portTICK_PERIOD_MS);
  }
}

void readbutton(void *pvParameters)  // Lee el botón continuamente, si está pulsado envía una señal
{
  try
  {
    while(1)
    {
      vTaskDelay(200 / portTICK_PERIOD_MS); // Espera un breve tiempo
      
      StaticJsonDocument<200> doc; // Crea el mensaje en formato JSON
      doc["ID_SENSOR"] = "emb001"; // ID del sensor
      doc["EMERGENCY_TYPE"] = "stop"; // Tipo de emergencia
      String state_json;
      serializeJson(doc, state_json); // Serializa el documento JSON en una cadena

      if(digitalRead(PIN_BUTTON) == LOW) // Si el botón está pulsado
      {
        enviarMensajePorTopic(EMERGENCY_TOPIC, state_json); // Envía el mensaje por el tópico
        while(digitalRead(PIN_BUTTON) == LOW)
        {
          vTaskDelay(100/ portTICK_PERIOD_MS); // Espera un breve tiempo
        }
      }
    }
  }
  catch(...)
  {
    StaticJsonDocument<200> doc; // Crea el mensaje en formato JSON
    doc["ID_SENSOR"] = "EXCEPTION"; // ID del sensor
    doc["EXCEPTION_TYPE"] = "Error with sensor"; // Tipo de excepción
    String state_json;
    serializeJson(doc, state_json); // Serializa el documento JSON en una cadena
  }
}

void ilumination(void *pvParameters)
{
  while(1)
  {
    int adcVal = analogRead(PIN_ANALOG_IN); // Lee el valor del sensor LDR

    StaticJsonDocument<200> doc; // Crea el mensaje en formato JSON
    doc["ID_SENSOR"] = "ldr001"; // ID del sensor
    doc["DATA"] = "lightoff"; // Datos del sensor
    String state_json;
    serializeJson(doc, state_json); // Serializa el documento JSON en una cadena

    if(adcVal > 700)  // Si el LDR capta poca luz
    {
      enviarMensajePorTopic(ILUMINATION_TOPIC, state_json); // Envía el mensaje por el tópico
      while(adcVal = analogRead(PIN_ANALOG_IN) > 700)
      {
        vTaskDelay(100/ portTICK_PERIOD_MS); // Espera un breve tiempo
      }
    }
  }
}
