#ifndef EVENTTYPES_H
#define EVENTTYPES_H

#include "paramdata.h"
#include "statedata.h"

enum EEvents {
  CLIENTNO = 1,
  PARAMREQUEST,
  PARAMMESSAGE,
  STATEREQUEST,
  STATEMESSAGE,
  RESET,
  TACT,
};

struct TEvents {
  EEvents type;
  union {
    int no;
    TParamData p;
    TStateData s;
  } data;
};

#endif // EVENTTYPES_H
