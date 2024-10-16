#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"
#include "Run.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"

RunAction::RunAction(const DetectorConstruction* det, 
                                 PrimaryGeneratorAction* kin)
  :fDetector(det),fPrimary(kin)
{ 
  fHistoManager = new HistoManager();
}

RunAction::~RunAction()
{
  delete fHistoManager;
}

G4Run* RunAction::GenerateRun()
{ 
  fRun = new Run(fDetector); 
  return fRun;
}

void RunAction::BeginOfRunAction(const G4Run*)
{    
  // show Rndm status
  if (isMaster)  G4Random::showEngineStatus();
     
  // keep run condition
  if ( fPrimary ) { 
    G4ParticleDefinition* particle 
      = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }    
      
  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }   

}

void RunAction::EndOfRunAction(const G4Run*)
{
  // compute and print statistic 
  if (isMaster) fRun->EndOfRun();
             
  //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();  
  if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }    
  
  // show Rndm status
  if (isMaster)  G4Random::showEngineStatus(); 
}