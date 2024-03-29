#include <hidboot.h>
#include <usbhub.h>
#include <Mouse.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

class MouseRptParser : public MouseReportParser
{
protected:
	void OnMouseMove	(MOUSEINFO *mi);
	void OnLeftButtonUp	(MOUSEINFO *mi);
	void OnLeftButtonDown	(MOUSEINFO *mi);
	void OnRightButtonUp	(MOUSEINFO *mi);
	void OnRightButtonDown	(MOUSEINFO *mi);
	void OnMiddleButtonUp	(MOUSEINFO *mi);
	void OnMiddleButtonDown	(MOUSEINFO *mi);
};
void MouseRptParser::OnMouseMove(MOUSEINFO *mi)
{
    Mouse.move(mi->dX, mi->dY);
};
void MouseRptParser::OnLeftButtonUp	(MOUSEINFO *mi)
{
    Mouse.release(MOUSE_LEFT);
};
void MouseRptParser::OnLeftButtonDown	(MOUSEINFO *mi)
{
    Mouse.press(MOUSE_LEFT);
};
void MouseRptParser::OnRightButtonUp	(MOUSEINFO *mi)
{
    Mouse.release(MOUSE_RIGHT);
};
void MouseRptParser::OnRightButtonDown	(MOUSEINFO *mi)
{
    Mouse.press(MOUSE_RIGHT);
};
void MouseRptParser::OnMiddleButtonUp	(MOUSEINFO *mi)
{
    Mouse.release(MOUSE_MIDDLE);
};
void MouseRptParser::OnMiddleButtonDown	(MOUSEINFO *mi)
{
    Mouse.press(MOUSE_MIDDLE);
};

USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb);

MouseRptParser                               Prs;

void setup()
{
    Serial.begin( 115200 );
#if !defined(__MIPSEL__)
    while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
    Serial.println("Start");

    Mouse.begin();
    Serial.setTimeout(0);

    if (Usb.Init() == -1)
        Serial.println("OSC did not start.");

    delay( 200 );

    HidMouse.SetReportParser(0, &Prs);
}

void loop() {
  Usb.Task();

  if(Serial.available() > 0) {
    String rawdata = Serial.readString();
    String _x = split(rawdata, ',', 0);
    String _y = split(rawdata, ',', 1);

    if((_x != "") && (_y != "")) {
      int x = _x.toInt();
      int y = _y.toInt();

      Mouse.move(x, y);
    }
  }
}

String split(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
