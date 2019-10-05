#include <BluetoothSerial.h>

class Bluetooth {

private:

    bool Srvr__btIsOn;// It's true when bluetooth is on
    bool Srvr__btConn;// It's true when bluetooth has connected client 
    BluetoothSerial Srvr__btClient; // Bluetooth client 

public:

    bool is_BluetoothON() const { return Srvr__btIsOn; }
    bool is_BluetoothConnect() const { return Srvr__btConn; }

    int Available() {
        return Srvr__btIsOn ? Srvr__btClient.available() : false;
    }

    void Write(const char*value) {
        // Write data to bluetooth
        if (Srvr__btIsOn) Srvr__btClient.write((const uint8_t*)value, strlen(value));
    }

    int Read() {
        return Srvr__btIsOn ? Srvr__btClient.read() : -1;
    }

    void Flush() {
        // Clear Bluetooth's stream
        if (Srvr__btIsOn) Srvr__btClient.flush();  
    }

    void Update() {
        if (Srvr__btConn != Srvr__btClient.hasClient()) {
            Serial.print("Bluetooth status:");
            Serial.println(Srvr__btConn = !Srvr__btConn ? "connected" : "disconnected"); 
        }
    }

    bool Setup() {
        // Name shown in bluetooth device list of App part (PC or smartphone)
        String devName("esp32");

        // Turning on
        Srvr__btIsOn = Srvr__btClient.begin(devName);

        // Show the connection result
        if (Srvr__btIsOn) Serial.println("Bluetooth is on");
        else Serial.println("Bluetooth is off");

        // There is no connection yet
        Srvr__btConn = false;

        // Return the connection result
        return Srvr__btIsOn;
    }

};
