#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* det)
 : fDetector(det)
{ }

void ActionInitialization::BuildForMaster() const
{}

void ActionInitialization::Build() const
{
  
  PrimaryGeneratorAction* prim = new PrimaryGeneratorAction(fDetector);
  SetUserAction(prim);
}  