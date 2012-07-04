#include "rejectionsimulation_context.h"

RejectionSimulationContext::RejectionSimulationContext(AreaData *area) :
    EventBasedSimulationContext(area), _maxRate(0) {}

BaseEventData *RejectionSimulationContext::randomEvent() const {
    double r;
    int n;
    BaseEventData *selectedEvent;
    do {
        r = randomN01() * _events.size();
        n = int(r);
        selectedEvent = _events[n];
    } while (n - r + 1 >= selectedEvent->rate() / _maxRate);
    return selectedEvent;
}

void RejectionSimulationContext::clearAllEvents() {
    EventBasedSimulationContext::clearAllEvents();
    _maxRate = 0;
}

void RejectionSimulationContext::doWhenEventAddedWithRate(double rate) {
    if (rate > _maxRate) _maxRate = rate;
}

