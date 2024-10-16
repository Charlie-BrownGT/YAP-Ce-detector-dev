#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction( DetectorConstruction* det)
 :fDetector(det)
{  
  fParticleGun  = new G4ParticleGun(1);

  G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(2, 4, 0.);

  fParticleGun->SetParticleDefinition(ion);
  fParticleGun->SetParticleCharge(2.0);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  fParticleGun->SetParticleEnergy(100.*GeV);
  fParticleGun->SetParticlePosition(G4ThreeVector(-0.4999*m,0.*cm,0.*cm));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{ 
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fParticleGun->GeneratePrimaryVertex(anEvent); 
}