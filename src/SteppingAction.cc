#include "SteppingAction.hh"
#include "Run.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"
#include "G4NIELCalculator.hh"
#include "G4ICRU49NuclearStoppingModel.hh"

SteppingAction::SteppingAction(EventAction* event)
  :fEventAction(event)
{
  fNIELCalculator = new G4NIELCalculator(new G4ICRU49NuclearStoppingModel(),1);
}

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  Run* run = static_cast<Run*>(
             G4RunManager::GetRunManager()->GetNonConstCurrentRun()); 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   
  G4double EdepStep = aStep->GetTotalEnergyDeposit();

  if (EdepStep > 0.) {
    run->AddEdep(EdepStep);
    fEventAction->AddEdep(EdepStep);
  }
  G4double niel = fNIELCalculator->ComputeNIEL(aStep);
  if(niel > 0.) {
    run->AddNIEL(niel);
    fEventAction->AddNIEL(niel);
  }

  const G4VProcess* process = 
    aStep->GetPostStepPoint()->GetProcessDefinedStep();
  if (process) run->CountProcesses(process->GetProcessName());

  // step length of primary particle
  G4int ID         = aStep->GetTrack()->GetTrackID();
  G4double steplen = aStep->GetStepLength();
  if (ID == 1) analysisManager->FillH1(3,steplen);
}