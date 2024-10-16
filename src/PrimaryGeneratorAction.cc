#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{  
  fParticleGun  = new G4ParticleGun(1);

  G4ParticleDefinition* particle = G4IonTable::GetIonTable()->GetIon(2, 4, 0.);

  fParticleGun->SetParticleDefinition(particle);
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