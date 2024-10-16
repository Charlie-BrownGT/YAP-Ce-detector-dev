#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class EventAction;
class G4NIELCalculator;

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(EventAction*);
   ~SteppingAction() override = default;

    void UserSteppingAction(const G4Step*) override;

  private:
    EventAction* fEventAction         = nullptr;
    G4NIELCalculator* fNIELCalculator = nullptr;
};
#endif