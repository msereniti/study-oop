#ifndef MODEL_H
#define MODEL_H

#include <QObject>

#include "paramdata.h"
#include "statedata.h"

class TModel {
  //параметры
  static TParamData defaultParameters;
  TParamData parameters;

  //состояние
  static TStateData defaultState;
  TStateData state;

public:
  TModel();

  void init();
  void tact();
  void addPassenger();

  inline TParamData &params() { return parameters; }
  inline TStateData &states() { return state; }
};

#endif // MODEL_H
