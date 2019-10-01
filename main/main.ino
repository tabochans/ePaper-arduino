#include "epaper.h"

void setup() {
  Serial.begin(115200);
  delay(10);
  
  ePaper paper;
  paper.Init_SPI();

  delay(100);

  paper.Init_ePaper();
  paper.LoadCheckerBoard(8);
  paper.ShowImage();
  

}

void loop() {
}
