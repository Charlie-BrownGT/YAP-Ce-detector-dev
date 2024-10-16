#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{}

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* prim = new PrimaryGeneratorAction();
  SetUserAction(prim);
}  