#include "lotkareactor_context.h"
#include "cellreaction_data.h"
#include "dimerreactioncapture_data.h"
#include "dimerreactionexchange_data.h"

LotkaReactorContext::LotkaReactorContext() {
    addReaction(new DimerReactionCaptureData(0.1 / 4, 1, 2));
    addReaction(new DimerReactionCaptureData(0.5 / 4, 2, 3));
    addReaction(new CellReactionData(0.07, 3, 1));
//    addReaction(new DimerReactionExchangeData(0.05, 2, 1));
    addReaction(new DimerReactionExchangeData(0.5 / 4, 3, 1));
}

void LotkaReactorContext::solveToOut(std::ostream &out) const {
}