#include "basenode_data.h"

BaseNodeData::BaseNodeData(int level) : _sum(0), _parent(0), _level(level) {}

void BaseNodeData::accSum(long double sum) {
    if (_parent) _parent->accSum(sum);
    _sum += sum;
}

bool BaseNodeData::lessThanEps(long double ds) const {
    if (ds == 0.0) return true;
    if (ds < 0.0) ds *= -1;
    return ds < 1e-12;
}
