#ifndef STATEDATA_H
#define STATEDATA_H

struct TQueue {
  qint32 passengersCount;
  qint32 lastPassengerHandlingStartTime;
  qint32 index;
};
struct TStateData {
  qint32 timePassed;
  qint32 passengersToBeDistributed;
  qint32 rejectedPassengers;
  TQueue queues[9999];
  qint32 queuesCount;
};

#endif // STATEDATA_H
