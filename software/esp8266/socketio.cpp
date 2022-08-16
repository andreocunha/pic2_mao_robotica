#include "socketio.h"
#include "fingers.h"


SocketIOclient socket;

// inicializa o socket.io-client
void init_socket()
{
  socket.begin("192.168.79.196", 4000, "/socket.io/?EIO=4");
//   socket.begin("server-robotic-hand.herokuapp.com", 80);

  socket.onEvent(socketIOEvent);
  Serial.println("Configurado o socket.io");
  delay(500);
}

void connection_socket()
{
  socket.loop();
}


void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    String text = String((char *)&payload[0]);
    String objeto = text.substring(8, text.length()-1);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, objeto);
    JsonObject obj = doc.as<JsonObject>();

    int dedo1 = 180;
    int dedo2 = 180;
    int dedo3 = 180;
    int dedo4 = 180;
    int dedo5 = 180;
    
    dedo1 = obj["dedo1"];
    dedo2 = obj["dedo2"];
    dedo3 = obj["dedo3"];
    dedo4 = obj["dedo4"];
    dedo5 = obj["dedo5"];

    switch(type) {
        case sIOtype_DISCONNECT:
            Serial.printf("[IOc] Desconectado!\n");
            break;
        case sIOtype_CONNECT:
            Serial.printf("[IOc] Conectado ao url: %s\n", payload);

            // join default namespace (no auto join in Socket.IO V3)
            socket.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
            Serial.println((char *)&payload[0]);           
            move_fingers(dedo1, dedo2, dedo3, dedo4, dedo5);
            break;
        case sIOtype_ACK:
            Serial.printf("[IOc] get ack: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_ERROR:
            Serial.printf("[IOc] get error: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_EVENT:
            Serial.printf("[IOc] get binary: %u\n", length);
            hexdump(payload, length);
            break;
        case sIOtype_BINARY_ACK:
            Serial.printf("[IOc] get binary ack: %u\n", length);
            hexdump(payload, length);
            break;
    }
}


// envia uma mensagem para o servidor via socket
void send_socket(String info)
{

  DynamicJsonDocument doc(1024);
  JsonArray array = doc.to<JsonArray>();

  array.add("newinfo");

  // add payload (parameters) for the event
  JsonObject param1 = array.createNestedObject();
  param1["now"] = info;

  // JSON to String (serializion)
  String output;
  serializeJson(doc, output);

  // Send event
  socket.sendEVENT(output);
}

// Recebe algo do servidor
void event(const char *payload, size_t length)
{
  Serial.printf("got message: %s\n", payload);
}
