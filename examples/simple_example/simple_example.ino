#include <LHConfig.h>


// Create config object and specify location of config file
LHConfig config("/test.conf");

void setup() {  
  Serial.begin(115200);

  // Don't forget to call the begin method before you do anything with the config
  // This will mount the file system and load the stored config
  // It will return 
  //   0 if the config file was read
  //  -1 if the file could not be opened
  //  -2 if the file system could not be mounted
  if( config.begin() == 0){
    Serial.println("Config loaded:");
  }else{
    Serial.println("Adding some test values to the config");
    config.add("run counter", "0");
    config.add("LHConfig","cool");
  }
  
  // this writes the whole config to the serial port
  config.dump();

  // adding a key named "run counter" to the config if it doesn't exist already
  if(!config.exists("run counter")){
    config.add("run counter", "0");
  }

  Serial.println("increasing run counter");
  // add 1 to the run counter and update the config
  int counter = config.get("run counter").toInt();
  counter++;

  // add will update the value if the key already exists, or add a new one if it doesn't
  config.add("run counter", (String)counter);

  // this writes the whole config to the serial port
  config.dump();

  Serial.println("saving to flash");
  // now save it all back to the flash
  config.save();

  Serial.println("done");
  Serial.println("reset board to see that the changes to the config remain.");

}

void loop() {
  // nothing to do here
  delay(1000);

}
