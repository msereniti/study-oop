#include "model.h"

TParamData TModel::defaultParameters = {100,1,-1};
TStateData TModel::defaultState      = {25,75};

TModel::TModel()
{
    init();
}

void TModel::init()
{
    parameters = defaultParameters;
    state = defaultState;
}

void TModel::tact()
{
    state.r1 = (state.r1 + parameters.p1) % parameters.m;
    while (state.r1 < 0) state.r1 += parameters.m;
    state.r2 = (state.r2 + parameters.p2) % parameters.m;
    while (state.r2 < 0) state.r2 += parameters.m;
}
