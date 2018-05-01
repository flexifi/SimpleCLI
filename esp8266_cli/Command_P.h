#ifndef Command_P_h
#define Command_P_h

#include "Cmd.h"

class Command_P: public Cmd {
  public:
    Command_P(const char* name, std::function<void(Cmd* cmd)> runFnct, std::function<void(uint8_t error)> errorFnct){
      Command_P::runFnct = runFnct;
      Command_P::errorFnct = errorFnct;
      Command_P::name = const_cast<char*>(name);
    }
    
    ~Command_P(){
      if(firstArg) delete firstArg;
      if(next) delete next;
    }

    bool equalsName(const char* name){
      int tmpNameLen = strlen_P(Command_P::name);
      char* tmpName = new char[tmpNameLen + 1];
      strcpy_P(tmpName, Command_P::name);
      tmpName[tmpNameLen] = '\0';
      
      bool res = equalsKeyword(name, tmpName);
      delete tmpName;
      return res;
    }

    Arg* getArg_P(const char* name){
      Arg* h = firstArg;
      while(h){
        if(h->getNamePtr() == name)
          return h;
        h = h->next;
      }
      return NULL;
    }

    bool hasArg_P(const char* name){
      return getArg_P(name) != NULL;
    }

    bool has_P(const char* name){
      Arg* h = getArg_P(name);
      return h ? h->isSet() : false;
    }
    
    String value_P(const char* name){
      Arg* arg = getArg_P(name);
      return arg ? arg->getValue() : String();
    }
};

#endif