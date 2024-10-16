#ifndef PhysListEmStandard_h
#define PhysListEmStandard_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

class PhysListEmStandard : public G4VPhysicsConstructor
{
  public: 
    PhysListEmStandard(const G4String& name = "standard");
   ~PhysListEmStandard() override = default;

  public: 
    // This method is dummy for physics
    void ConstructParticle() override {};
 
    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type 
    void ConstructProcess() override;
};
#endif