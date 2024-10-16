#include "StepMax.hh"
//#include "StepMaxMessenger.hh"

StepMax::StepMax(const G4String& processName)
 : G4VDiscreteProcess(processName)
{}

StepMax::~StepMax() {}

G4bool StepMax::IsApplicable(const G4ParticleDefinition& particle)
{
  return (particle.GetPDGCharge() != 0. && !particle.IsShortLived());
}

void StepMax::SetMaxStep(G4double step) {fMaxChargedStep = step;}

G4double StepMax::PostStepGetPhysicalInteractionLength( const G4Track&,
                                                   G4double,
                                                   G4ForceCondition* condition )
{
  // condition is set to "Not Forced"
  *condition = NotForced;

  return fMaxChargedStep;
}

G4VParticleChange* StepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
{
   // do nothing
   aParticleChange.Initialize(aTrack);
   return &aParticleChange;
}

G4double StepMax::GetMeanFreePath(const G4Track&,G4double,G4ForceCondition*)
{
   return fMaxChargedStep;
}