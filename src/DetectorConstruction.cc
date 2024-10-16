#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

DetectorConstruction::DetectorConstruction()
{
  fBoxSize = 1.*m;
  worldSize = 2*m;
  DefineMaterials();
  SetMaterial("YAPCe");  
}

DetectorConstruction::~DetectorConstruction()
{}

void DetectorConstruction::DefineMaterials()
{
  
  G4double z,a;

  G4double density = 1.e-25*g/cm3, pressure = 1.e-5*pascal, temperature = 2.73 * kelvin;
	vacuum = new G4Material("Vacuum", z=1., a=1.008 * g/mole, density, kStateGas, temperature, pressure);

  G4Element* O  = new G4Element("Oxygen"   ,"O" , z= 8., a=  16.00*g/mole);
  G4Element* Y  = new G4Element("Yttrium"  ,"Y" , z=39., a=   88.91*g/mole);  
  G4Element* Ce = new G4Element("Cerium"   ,"Ce", z=58., a=  140.12*g/mole);  
  G4Element* Al = new G4Element("Aluminium"   ,"Al", z=13., a=  26.98*g/mole);

  YAPCe = new G4Material("YAPCe", 5.37*g/cm3, 4);
  YAPCe->AddElement(Y, 1);
  YAPCe->AddElement(Ce, 1);
  YAPCe->AddElement(Al, 1);
  YAPCe->AddElement(O, 1);
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  if(fPBox) { return fPBox; }

  fBox = new G4Box("Container", fBoxSize/2,fBoxSize/2,fBoxSize/2);
  fLBox = new G4LogicalVolume(fBox, YAPCe, "LYAPCe");
  fPBox = new G4PVPlacement(0, G4ThreeVector(), fLBox, "PYAPCe", 0, false, 0);

  return fPBox;
}


void DetectorConstruction::SetMaterial(const G4String& materialChoice)
{
  //search the material by its name
  G4Material* pttoMaterial = 
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);
  
  if (pttoMaterial) {
    fMaterial = pttoMaterial;
  }
}


void DetectorConstruction::SetSize(G4double value)
{
  fBoxSize = value;
  if(fBox) {
    fBox->SetXHalfLength(fBoxSize/2);
    fBox->SetYHalfLength(fBoxSize/2);
    fBox->SetZHalfLength(fBoxSize/2);
  }
}

void DetectorConstruction::ConstructSDandField()
{
    if ( fFieldMessenger.Get() == 0 ) {
        // Create global magnetic field messenger.
        // Uniform magnetic field is then created automatically if
        // the field value is not zero.
        G4ThreeVector fieldValue = G4ThreeVector();
        G4GlobalMagFieldMessenger* msg =
        new G4GlobalMagFieldMessenger(fieldValue);
        //msg->SetVerboseLevel(1);
        G4AutoDelete::Register(msg);
        fFieldMessenger.Put( msg );
    }
}