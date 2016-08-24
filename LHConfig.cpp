#include "LHConfig.h"



LHConfig::LHConfig(String file_name){
    this->file_name="/";
    this->file_name+=file_name;
    
    data = LinkedList<ConfigPair*>();
  }

int LHConfig::begin(){
    if (!SPIFFS.begin()) {
      return -2;
    }

    if(this->file_name != "/"){
        return load();
    }
  }

int LHConfig::load(){    
    File configFile = SPIFFS.open(file_name, "r");
    if(!configFile){      
      // file not found
      return -1;
    }
    
    String line;
    int splitter;
    String key="", val="";  
    char c;
    char stat='k';

    while( c = configFile.read() ) {   
      if(c==255){ break; }        
      if( stat=='k'){
        if(c=='\n'){ 
            key=""; 
            continue;         
        }
        if(c!='='){
          key+=c;
        }else{
          stat='v';
        }          
      }else if(stat=='v'){
        if(c!='\n'){
          val+=c;
        }else{ 
          key.trim();
          val.trim();
          add(key, val);
          key="";
          val="";
          stat='k';
        }
      }
    }
    configFile.close();
    return 0;
  }


int LHConfig::save(){
    if(File configFile = SPIFFS.open(file_name, "w")){    
      for(int i=0; i<data.size(); i++){
        ConfigPair *conf=data.get(i);
        configFile.println(conf->key+"="+conf->val);
      }
      configFile.close();
      return 0;
    }else{
      // cannot open file
      return -1;
    }
  }

  
void LHConfig::add(String key, String val){
    for(int i=0; i<data.size(); i++){
      ConfigPair *conf=data.get(i);
      if(conf->key==key){
        conf->val=val;
        return;
      }
    }
      
    ConfigPair *conf = new ConfigPair();
    conf->key=key;
    conf->val=val;
    data.add(conf);
  }
  

String LHConfig::get(String key){
    for(int i=0; i<data.size(); i++){
      ConfigPair *conf=data.get(i);
      if(conf->key==key){
        return conf->val;
      }
    }
    return "";
  }


LHConfig::ConfigPair* LHConfig::get(int id){
    return data.get(id);
}

int LHConfig::size(){
    return data.size();
}

void LHConfig::dump(){
    for(int i=0; i<data.size(); i++){
      ConfigPair *conf=data.get(i);
      Serial.println(conf->key+"="+conf->val);
    }
  }


bool LHConfig::exists(String key){
    for(int i=0; i<data.size(); i++){
      ConfigPair *conf=data.get(i);
      if(conf->key==key){
          return true;
      }
    }
    return false;
  }
  
  
void LHConfig::remove(String key){
    for(int i=0; i<data.size(); i++){
      ConfigPair *conf=data.get(i);
      if(conf->key==key){
        data.remove(i);
      }
    }
}
  

void LHConfig::clean(){
  ConfigPair* conf;
  while(data.size()>0){
    conf=data.pop();
  }
}
