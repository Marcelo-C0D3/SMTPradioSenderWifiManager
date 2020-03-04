#include <Arduino.h>

/* \-------------------------\
    \  SMTP SENDER Core 2.42  \
     \     by KingC0d3R        \
      \-------------------------\ */

#include <ESP8266WiFi.h>
#include <DNSServer.h>        //Local DNS Server used for redirecting all requests to the configuration portal ( https://github.com/zhouhan0126/DNSServer---esp32 )
#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal

#include <..\lib\GmailSender\Gsender.cpp> // WiFi Configuration Magic ( https://github.com/zhouhan0126/WIFIMANAGER-ESP32 ) >> https://github.com/tzapu/WiFiManager (ORIGINAL)
#include <..\lib\WiFiManager\WiFiManager.cpp>
#include <main.h>

bool shouldSaveConfig = false;

void sender() // Function Sending menssages.
{

  Gsender *gsender = Gsender::Instance(); // Getting pointer to class instance
  if (gsender->Subject(subject)->Send("marceloloch.newaa@gmail.com", assunto))
  {
    Serial.println("Message send.");
  }
  else
  {
    Serial.print("Error sending message: ");
    Serial.println(gsender->getError());
  }
}
void configModeCallback (WiFiManager *myWiFiManager) {
  //  Serial.println("Entered config mode");
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
  Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede

}

//callback que indica que salvamos uma nova rede para se conectar (modo estação)
void saveConfigCallback () {
  //  Serial.println("Should save config");
  Serial.println("Configuração salva");
  Serial.println(WiFi.softAPIP()); //imprime o IP do AP
}

void setup() //Set initial configurations.
{
  Serial.begin(115200);

  WiFiManager wifiManager;

  wifiManager.autoConnect("ESP_WIFI", "807060503020"); //cria uma rede com senha
  //callback para quando entra em modo de configuração AP
  wifiManager.setAPCallback(configModeCallback);         //callback para quando se conecta em uma rede, ou seja, quando passa a trabalhar em modo estação
  wifiManager.setSaveConfigCallback(saveConfigCallback); // save configs
  
  pinMode(D1, OUTPUT);
  pinMode(A0, INPUT);
  Serial.println();
  //iniciar a interrupcao
  usrInit();
}

int x = 0;

void loop()
{
  //verificacao no loop
  //  valor_AD = analogRead(A0);
  //  soma = soma + valor_AD;
  //  i++;
  //
  //  if ( i == 100) {
  //    media = soma / i;
  //    Serial.println(media);
  //    i = 0;
  //    soma = 0;
  //  }else if (media > 50 && (state == 0 || state == 1)) {
  //     reset_timer1();
  //     state = 3;
  //  } else if (_timeout2 && (state == 0 || state == 2)) {
  //    state = 1;
  //    digitalWrite(D1, HIGH);
  //    assunto = "A rádio está fora do ár ou muda.";
  //    subject = "Radio - OFF";
  //    sender();
  //    _timeout1 = false;
  //  }else if (media > 50 && _timeout1 && (state == 0 || state == 3)) {
  //    state = 2;
  //    digitalWrite(D1, HIGH);
  //    subject = "Radio - ON";
  //    assunto = "A rádio está ativa";
  //    sender();
  //    _timeout2 = false;
  //  }
  //
  //  if (i == 1 && media > 45) {
  //    reset_timer2();
  //    digitalWrite(D1, LOW);
  //    yield();
  //  }
  if (x == 0)
  {
    x = 1;
    Serial.println(x);
    assunto = "testar";
    subject = "title";
    sender();

  }
}