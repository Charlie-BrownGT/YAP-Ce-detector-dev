#include "G4Types.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4SteppingVerbose.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

int main(int argc,char** argv) {

  //detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  if (argc == 1) { ui = new G4UIExecutive(argc,argv); }

  //use G4SteppingVerboseWithUnits
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  //construct the run manager
  auto runManager = G4RunManagerFactory::CreateRunManager();
  if (argc==3) {
     G4int nThreads = G4UIcommand::ConvertToInt(argv[2]);
     runManager->SetNumberOfThreads(nThreads);
  }

  DetectorConstruction* det = new DetectorConstruction;
  runManager->SetUserInitialization(det);

  PhysicsList* phys = new PhysicsList(det);
  runManager->SetUserInitialization(phys);
  runManager->SetUserInitialization(new ActionInitialization(det));
  G4VisManager* visManager = nullptr;

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui)  {
   //interactive mode
   visManager = new G4VisExecutive;
   visManager->Initialize();
   UImanager->ApplyCommand("/control/execute vis.mac");
   //UImanager->ApplyCommand("/control/execute beam.mac");
   ui->SessionStart();
   delete ui;
  }
  else  {
   //batch mode
   //UImanager->ApplyCommand("/control/execute beam.mac");
   G4String command = "/control/execute ";
   G4String fileName = argv[1];
   UImanager->ApplyCommand(command+fileName);
  }

  //job termination
  delete visManager;
  delete runManager;
}