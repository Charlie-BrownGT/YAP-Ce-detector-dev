#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"

class G4LogicalVolume;
class G4Material;
class DetectorMessenger;
class G4GlobalMagFieldMessenger;
class G4Box;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
    void DefineMaterials();
    void ConstructSDandField();
               
  private:
  
    G4VPhysicalVolume *fPBox, *physWorld;
    G4LogicalVolume *fLBox, *logicWorld;
    G4Box *fBox, *solidWorld;

    G4Material *YAPCe, *vacuum;

    G4double fBoxSize, worldSize;

    G4Cache<G4GlobalMagFieldMessenger*> fFieldMessenger = nullptr;
};

#endif

