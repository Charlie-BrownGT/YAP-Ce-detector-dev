#include "EventAction.hh"

#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4UnitsTable.hh"

void EventAction::BeginOfEventAction(const G4Event*)
{
  fTotalEnergyDeposit = 0.;
  fNIEL = 0.;
}

void EventAction::EndOfEventAction(const G4Event*)
{

  G4AnalysisManager::Instance()->FillH1(4,fTotalEnergyDeposit);
  G4AnalysisManager::Instance()->FillH1(7,fNIEL);
}