import controlP5.*;
import java.util.List;
import processing.serial.*;

//////////// DO NOT CHANGE THIS CODE /////////////
ControlP5 cp5; // create ControlP5 object       //
Serial port; // connect to Serial port          //
//    
int dim = 3; // dimensions of LED array         //
List<String> code = new ArrayList<String>();    //
CheckBox checkbox;                              //
//////////////////////////////////////////////////


// Modify this depending on which port the Arduino is on.
String arduinoPort = "/dev/cu.usbmodem1411";

void setup() {
  size(500, 600); // width, height
  port = new Serial(this, arduinoPort, 9600);
  cp5 = new ControlP5(this);

  checkbox = cp5.addCheckBox("checkBox")
    .setPosition(100, 100)
    .setSize(40, 40)
    .setItemsPerRow(dim)
    .setSpacingColumn(30)
    .setSpacingRow(30)
    ;

  int id = 0;
  for (int i=0; i < dim; i++) {
    for (int j=0; j < dim; j++) {
      checkbox.addItem(Integer.toString(id), id);
      id++;
    }
  }

  cp5.addButton("submit")
    .setSize(100, 50)
    .setPosition(100, 400)
    ;
}

void draw() {
  background(255, 255, 255); // r g b
  fill(0, 0, 0);
  text("Checkbox LEDs!", 100, 30); // window title, x, y
}

void controlEvent(ControlEvent theEvent) {
  if (theEvent.isFrom(checkbox)) {
    for (int i=0; i < checkbox.getArrayValue().length; i++) {
      int n = (int)checkbox.getArrayValue()[i];
      if (n == 1 && !code.contains(Integer.toString(i))) {
        code.add(Integer.toString(i));
        port.write(Integer.toString(i)); // light LED one by one
      }
    }
  }
}

void submit() {
  port.write("\n");
  checkbox.deactivateAll();
  code.clear();
}