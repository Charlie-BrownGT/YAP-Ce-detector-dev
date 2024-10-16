#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class DetectorConstruction;
class PhysicsListMessenger;
class G4VPhysicsConstructor;
class G4VProcess;

class PhysicsList: public G4VModularPhysicsList
{
  public:
    PhysicsList(DetectorConstruction*);
   ~PhysicsList() override;

    void ConstructParticle() override;
    void ConstructProcess() override;
    void AddPhysicsList(const G4String& name);

  private:    
    G4VPhysicsConstructor* fEmPhysicsList = nullptr;
    G4String               fEmName = " ";
    DetectorConstruction*  fDet = nullptr;
};

#endif