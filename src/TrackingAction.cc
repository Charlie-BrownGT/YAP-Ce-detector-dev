#include "TrackingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "Run.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

TrackingAction::TrackingAction(PrimaryGeneratorAction* prim)
 :fPrimary(prim)
{ }

void TrackingAction::PreUserTrackingAction(const G4Track*)
{}

void TrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  //increase nb of processed tracks 
  //count nb of steps of this track
  G4int   nbSteps = aTrack->GetCurrentStepNumber();
  G4double Trleng = aTrack->GetTrackLength();
  
  Run* run = static_cast<Run*>(
             G4RunManager::GetRunManager()->GetNonConstCurrentRun()); 
    
  if (aTrack->GetDefinition()->GetPDGCharge() == 0.) {
    run->CountTraks0(1); 
    run->CountSteps0(nbSteps);
  
  } else {
    run->CountTraks1(1); 
    run->CountSteps1(nbSteps);
  }
  
  //true and projected ranges for primary particle
  if (aTrack->GetTrackID() == 1) {
    run->AddTrueRange(Trleng);
    G4ThreeVector vertex = fPrimary->GetParticleGun()->GetParticlePosition();
    G4ThreeVector position = aTrack->GetPosition() - vertex;      
    run->AddProjRange(position.x());
    run->AddTransvDev(position.y());
    run->AddTransvDev(position.z());
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(1,Trleng);
    analysisManager->FillH1(2,(float)nbSteps);        
  }              
}