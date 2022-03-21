/**
 * Temperature Webhook
 * C Fitz
 * 16 March 22
 * 
 * Takes ambient temperature reading using DHT11, converts reading to a string, and uses a webhook to POST data
 * to ThingSpeak where it can be graphed
 * 
 * Based on DHT-test.ino tutorial code from the particle IDE
 * and webhook tutorial found here: https://docs.particle.io/tutorials/device-cloud/webhooks/
 */


// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_DHT.h>

#define DHTPIN A1     // define sensor pin (analog 1)

#define DHTTYPE DHT11		// define sensor model (DHT 11)

DHT dht(DHTPIN, DHTTYPE); //initialise sensor with pin and model

void setup() {

	dht.begin(); //activate the sensor
}

void loop() {
// 30 sec delay between measurements.
	delay(30000);

// Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a 
// very slow sensor)
	//float h = dht.getHumidity();
// Read temperature as Celsius
	float tempData = dht.getTempCelcius();
// Read temperature as Farenheit
	//float f = dht.getTempFarenheit();
	
	String tempString = String::format("%.1f C", tempData);
	Particle.publish("Temp", tempString, PRIVATE);
}

