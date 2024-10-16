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
    ~DetectorConstruction() override;
  
    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;
     
    void SetSize     (G4double);              
    void SetMaterial (const G4String&);
  
    inline const G4VPhysicalVolume* GetWorld() const {return fPBox;};
    inline G4double GetSize() const                  {return fBoxSize;};      
    inline const G4Material* GetMaterial() const     {return fMaterial;};
     
    void   DefineMaterials();
                       
  private:
  
    G4VPhysicalVolume*    fPBox = nullptr;
    G4VPhysicalVolume*    physWorld = nullptr;
    G4LogicalVolume*      fLBox = nullptr;
    G4LogicalVolume*      logicWorld = nullptr;
    G4Box*                fBox  = nullptr;
    G4Box*                solidWorld  = nullptr;
     
    G4double              fBoxSize  = 0., worldSize = 0.;
    G4Material*           fMaterial = nullptr;
    G4Material*           YAPCe;
    G4Material*           vacuum;

    G4Cache<G4GlobalMagFieldMessenger*> fFieldMessenger = nullptr;
};

#endif

