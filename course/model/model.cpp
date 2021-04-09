#include "model.h"

TParamData TModel::defaultParameters = {3, 10, 5};
TStateData TModel::defaultState = {0, 0, 0, {}, 0};

TModel::TModel() { init(); }

void TModel::init() {
  parameters = defaultParameters;
  state = defaultState;
}

int sortByPassengersCount(const void *s1, const void *s2) {
  struct TQueue *e1 = (struct TQueue *)s1;
  struct TQueue *e2 = (struct TQueue *)s2;

  return e1->passengersCount - e2->passengersCount;
}

int sortByIndex(const void *s1, const void *s2) {
  struct TQueue *e1 = (struct TQueue *)s1;
  struct TQueue *e2 = (struct TQueue *)s2;

  return e1->index - e2->index;
}

void TModel::tact() {
  state.timePassed++;

  // add missing queues
  for (int queueIndex = parameters.slotsCount_n - 1;
       queueIndex >= state.queuesCount; queueIndex--) {
    state.passengersToBeDistributed += state.queues[queueIndex].passengersCount;
  }
  // remove extra queues
  for (int queueIndex = state.queuesCount; queueIndex < parameters.slotsCount_n;
       queueIndex++) {
    TQueue queue;
    queue.passengersCount = 0;
    queue.lastPassengerHandlingStartTime = 0;
    queue.index = queueIndex;
    state.queues[queueIndex] = queue;
  }
  state.queuesCount = parameters.slotsCount_n;

  // remove handled passengers
  for (int queueIndex = 0; queueIndex < state.queuesCount; queueIndex++) {
    if (state.timePassed -
                state.queues[queueIndex].lastPassengerHandlingStartTime >=
            parameters.handlingTime &&
        state.queues[queueIndex].passengersCount > 0) {
      state.queues[queueIndex].passengersCount--;
      state.queues[queueIndex].lastPassengerHandlingStartTime =
          state.timePassed;
    }
  }

  std::qsort(state.queues, state.queuesCount, sizeof(struct TQueue),
             sortByPassengersCount);

  // redistribute queues that longer then average
  int sumPassengersCount = 0;
  for (int queueIndex = 0; queueIndex < state.queuesCount; queueIndex++) {
    sumPassengersCount += state.queues[queueIndex].passengersCount;
  }
  int average = sumPassengersCount / state.queuesCount;
  int redistributionTrashhold = 1;
  int maxQueuesVolume = state.queuesCount * parameters.maxQueue_m;
  for (int queueIndex = state.queuesCount - 1; queueIndex >= 0; queueIndex--) {
    while (state.queues[queueIndex].passengersCount > 1 &&
           state.queues[queueIndex].passengersCount >
               average + redistributionTrashhold &&
           state.passengersToBeDistributed + 1 < maxQueuesVolume) {
      state.passengersToBeDistributed++;
      state.queues[queueIndex].passengersCount--;
    }
  }

  // distribute passengers into queues
  int uniformDistributionStart = 0;
  int uniformDistributionEnd = 0;
  while (state.passengersToBeDistributed > 0) {
    bool distributedSmbd = false;

    while (uniformDistributionEnd < state.queuesCount &&
           (uniformDistributionEnd == state.queuesCount - 1 ||
            state.queues[uniformDistributionEnd].passengersCount ==
                state.queues[uniformDistributionEnd + 1].passengersCount)) {
      uniformDistributionEnd++;
      uniformDistributionStart = 0;
    }

    if (state.queues[uniformDistributionStart].passengersCount == 0) {
      state.queues[uniformDistributionStart].lastPassengerHandlingStartTime =
          state.timePassed;
    }
    if (state.queues[uniformDistributionStart].passengersCount <
        parameters.maxQueue_m) {
      state.passengersToBeDistributed--;
      state.queues[uniformDistributionStart].passengersCount++;
      distributedSmbd = true;
    } else {
      state.rejectedPassengers++;
    }

    uniformDistributionStart++;

    if (uniformDistributionStart >= uniformDistributionEnd ||
        uniformDistributionStart >= state.queuesCount) {
      uniformDistributionStart = 0;
    }

    if (!distributedSmbd) {
      break;
    }
  }

  // return queues to original order
  std::qsort(state.queues, state.queuesCount, sizeof(struct TQueue),
             sortByIndex);

  // reject passengers when max queue length reduced
  for (int queueIndex = 0; queueIndex < state.queuesCount; queueIndex++) {
    if (state.queues[queueIndex].passengersCount > parameters.maxQueue_m) {
      state.rejectedPassengers +=
          state.queues[queueIndex].passengersCount - parameters.maxQueue_m;
      state.queues[queueIndex].passengersCount = parameters.maxQueue_m;
    }
  }

  // reject passengers that were not distributed
  if (state.passengersToBeDistributed > 0) {
    state.rejectedPassengers += state.passengersToBeDistributed;
    state.passengersToBeDistributed = 0;
  }
}

void TModel::addPassenger() { state.passengersToBeDistributed++; }
