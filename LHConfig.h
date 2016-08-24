#ifndef LHConfig_h
#define LHConfig_h

#include <Arduino.h>
#include <LinkedList.h>
#include <FS.h>

class LHConfig{
  public:
    class ConfigPair {
        public:
        String key, val;    
    };
  
    LHConfig(String filename);
    int begin();
    int load();
    int save();
    void add(String key, String val);
    String get(String key);
    ConfigPair* get(int num);
    int size();
    void dump();
    bool exists(String key);
    void remove(String key);
    void clean();
    
  private:
    LinkedList<ConfigPair*> data;
    String file_name;
};

#endif