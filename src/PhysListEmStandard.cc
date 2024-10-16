#include "PhysListEmStandard.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4KleinNishinaModel.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"

#include "G4MscStepLimitType.hh"

#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"

#include "G4BuilderType.hh"
#include "G4SystemOfUnits.hh"

PhysListEmStandard::PhysListEmStandard(const G4String& name)
   :  G4VPhysicsConstructor(name)
{
    G4EmParameters* param = G4EmParameters::Instance();
    param->SetDefaults();
    param->SetVerbose(0);
    param->SetMinEnergy(10*eV);
    param->SetMaxEnergy(10*TeV);
    param->SetNumberOfBinsPerDecade(10);
    param->SetStepFunction(0.1, 100*um);
    param->SetStepFunctionMuHad(0.1, 50*um);
    param->SetStepFunctionLightIons(0.1, 20*um);
    param->SetStepFunctionIons(0.1, 1*um);    
    param->SetMscStepLimitType(fUseDistanceToBoundary);
    param->SetDeexcitationIgnoreCut(true);
    SetPhysicsType(bElectromagnetic);
}

void PhysListEmStandard::ConstructProcess()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  
  // Add standard EM Processes
  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    G4String particleName = particle->GetParticleName();

      ph->RegisterProcess(new G4hMultipleScattering(), particle);          
      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetEmModel(new G4IonParametrisedLossModel());
      ph->RegisterProcess(ionIoni, particle);
      ph->RegisterProcess(new G4NuclearStopping(), particle); 
  }
  // Deexcitation
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);
}