#ifndef ProtonCTDetectorROGeometry_h
#define ProtonCTDetectorROGeometry_h 

//#include "G4VReadOutGeometry.hh"
#include "G4VUserParallelWorld.hh"
#include "G4ThreeVector.hh"
#include "G4Box.hh"

class ProtonCTDetectorROGeometry : public G4VUserParallelWorld
{
public:
  ProtonCTDetectorROGeometry(G4String);
  ~ProtonCTDetectorROGeometry();

  void InitializeTKR(G4double font,G4double back,G4double Z,
		  G4double TKRDimX,
		  G4double TKRDimY,
		  G4double TKRDimZ,
		  G4int numberOfVoxelsX,
		  G4int numberOfVoxelsY,
		  G4int numberOfVoxelsZ);

  void InitializeCal(G4double CalPosZ,
      G4double calDimX,
		  G4double calDimY,
		  G4double calDimZ,
		  G4int numberOfVoxelsZ);

  void UpdateROGeometry();

  virtual void Construct();
  virtual void ConstructSD();

private:  
  //Parameters used for the construction
  G4ThreeVector detectorToWorldPosition; 
  G4double TKRSizeX;
  G4double TKRSizeY; 
  G4double TKRSizeZ;
  G4double TKRBoxSizeZ;

  G4double calSizeX;
  G4double calSizeY; 
  G4double calSizeZ;

  G4int numberOfVoxelsAlongX;
  G4int numberOfVoxelsAlongY; 
  G4int numberOfVoxelsAlongZ; 
  
  //Solids that are updated on-the fly
  G4Box* ROTKR;
  G4Box* ROTKRXDivision;
  G4Box* ROTKRYDivision;
  G4Box* ROTKRZDivision;

  G4Box* ROCal;
  G4Box* ROCalXDivision;
  G4Box* ROCalYDivision;
  G4Box* ROCalZDivision;

  //Logical volumes used for the re-build on-the-fly
  G4LogicalVolume* worldLogical;
  G4LogicalVolume* ROFontTKRLog;
  G4LogicalVolume* ROBackTKRLog;
  G4LogicalVolume* ROFontTKRXDivisionLog;
  G4LogicalVolume* ROBackTKRXDivisionLog;
  G4LogicalVolume* ROFontTKRYDivisionLog;
  G4LogicalVolume* ROBackTKRYDivisionLog;
  G4LogicalVolume* ROTKRZDivisionLog;
  G4LogicalVolume* sensitiveTKRLogicalVolume;

  G4LogicalVolume* ROCalLog;
  G4LogicalVolume* ROCalXDivisionLog;
  G4LogicalVolume* ROCalYDivisionLog;
  G4LogicalVolume* ROCalZDivisionLog;
  G4LogicalVolume* sensitiveCalLogicalVolume;

  G4VPhysicalVolume* ROTKRZDivisionPhys;

  G4double calPosZ;

  G4double fontTKRPosZ;
  G4double backTKRPosZ;


  G4bool isBuilt;
  G4bool isInitialized;
};
#endif