#include "PhysicsList.hh"
//#include "PhysicsListMessenger.hh"
 
#include "PhysListEmStandard.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"

#include "DetectorConstruction.hh"

#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmParameters.hh"

// particles

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4PhysicsListHelper.hh"
#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"
#include "G4GenericIon.hh"
#include "G4NuclideTable.hh"

#include "G4ProcessManager.hh"
#include "StepMax.hh"
#include "G4Material.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Proton.hh"
#include "G4GenericIon.hh"

PhysicsList::PhysicsList(DetectorConstruction* det) 
  : fDet(det)
{
  //fMessenger = new PhysicsListMessenger(this);
  SetVerboseLevel(1);

  // EM physics
  AddPhysicsList("emstandard_opt3");    
  
  // fix lower limit for cut
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(10*eV, 1*GeV);
  SetDefaultCutValue(1*mm);
}

PhysicsList::~PhysicsList()
{
  //delete fMessenger;
}

void PhysicsList::ConstructParticle()
{
    G4BosonConstructor  pBosonConstructor;
    pBosonConstructor.ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4IonConstructor pIonConstructor;
    pIonConstructor.ConstructParticle();

    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle();  
}

void PhysicsList::ConstructProcess()
{
  AddTransportation();

  fEmPhysicsList->ConstructProcess();
  
  AddDecay();
  AddRadioactiveDecay();  

  // step limitation (as a full process)
  AddStepMax();
  
  // example of Get process
  auto process = GetProcess("RadioactiveDecay");
  if (process != nullptr) {
    G4cout << "\n  GetProcess : " << process->GetProcessName() << G4endl;
  }
}

void PhysicsList::AddPhysicsList(const G4String& name)
{
  if (verboseLevel>0) {
    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
  }
  
  if (name == fEmName) return;

  if (name == "local") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new PhysListEmStandard(name);
    
  } else if (name == "emstandard_opt0") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics();

  } else if (name == "emstandard_opt1") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option1();

  } else if (name == "emstandard_opt2") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option2();

  } else if (name == "emstandard_opt3") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option3();
    
  } else if (name == "emstandard_opt4") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option4();
        
  } else if (name == "emstandardSS") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsSS();
    
  } else if (name == "emstandardGS") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsGS();
    
  } else if (name == "emstandardWVI") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsWVI();
    
  } else if (name == "emlivermore") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLivermorePhysics();
    
  } else if (name == "empenelope") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmPenelopePhysics();
            
  } else if (name == "emlowenergy") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLowEPPhysics();
            
  } else {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
  }
  
  // Em options
  G4EmParameters::Instance()->SetBuildCSDARange(true);        
  G4EmParameters::Instance()->SetGeneralProcessActive(false);
}

void PhysicsList::AddDecay()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
    
  // Decay Process
  G4Decay* fDecayProcess = new G4Decay();

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
    if (fDecayProcess->IsApplicable(*particle) && !particle->IsShortLived()) 
      ph->RegisterProcess(fDecayProcess, particle);    
  }
}

void PhysicsList::AddRadioactiveDecay()
{  
  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
  
  G4bool armFlag = false;
  radioactiveDecay->SetARM(armFlag);                //Atomic Rearangement

  // atomic de-excitation module
  if (armFlag) {
    G4EmParameters::Instance()->SetAuger(true);
    G4EmParameters::Instance()->SetDeexcitationIgnoreCut(true);
  }
  
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();  
  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
  
  // mandatory for G4NuclideTable
  const G4double meanLife = 1*picosecond, halfLife = meanLife*std::log(2);
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(halfLife);
}

void PhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  StepMax* stepMaxProcess = new StepMax();

  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while ((*particleIterator)()){
    G4ParticleDefinition* particle = particleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();

    if (stepMaxProcess->IsApplicable(*particle) && !particle->IsShortLived())
      pmanager->AddDiscreteProcess(stepMaxProcess);
  }
}

void PhysicsList::GetRange(G4double val)
{
  G4LogicalVolume* lBox = fDet->GetWorld()->GetLogicalVolume();
  const G4MaterialCutsCouple* couple = lBox->GetMaterialCutsCouple();
  const G4Material* currMat = lBox->GetMaterial();

  G4ParticleDefinition* part;
  G4double cut;
  part = G4Electron::Electron();
  cut = G4LossTableManager::Instance()->GetRange(part,val,couple);
  G4cout << "material : " << currMat->GetName()       << G4endl;
  G4cout << "particle : " << part->GetParticleName()  << G4endl;
  G4cout << "energy   : " << G4BestUnit(val,"Energy") << G4endl;
  G4cout << "range    : " << G4BestUnit(cut,"Length") << G4endl;
}

G4VProcess* PhysicsList::GetProcess(const G4String& processName) const
{
  G4ParticleDefinition* particle = G4GenericIon::GenericIon();
  G4ProcessVector* procList = particle->GetProcessManager()->GetProcessList();
  G4int nbProc = particle->GetProcessManager()->GetProcessListLength();
  for (G4int k=0; k<nbProc; k++) {
    G4VProcess* process = (*procList)[k];
    if (process->GetProcessName() == processName) return process;
  }
  return nullptr;
}