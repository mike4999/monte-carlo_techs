#include "treesimcontextfactory.h"

#include "../treebasedsimulation_context.h"

TreeSimContextFactory::TreeSimContextFactory(int levels) : _levels(levels) {}

SimulationBaseContext *TreeSimContextFactory::createContext(AreaData *area) const {
    return new TreeBasedSimulationContext(area, _levels);
}

void TreeSimContextFactory::setWidth(int levels) {
    _levels = levels;
}
