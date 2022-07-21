#include <Mouse.h>

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(0);

  Mouse.begin();
}

void loop() {
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