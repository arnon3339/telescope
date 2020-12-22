#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"



#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4PhysicalVolumeStore.hh"

#include "G4ThreeVector.hh"

#include "globals.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4Colour.hh"
#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"

#include "ProtonCTDetectorROGeometry.hh"
#include "ProtonCTTrackerSD.hh"
#include "ProtonCTCalorimeterSD.hh"

/////////////////////////////////////////////////////////////////////////////
ProtonCTDetectorROGeometry::ProtonCTDetectorROGeometry(G4String aString)
  : G4VUserParallelWorld(aString),ROTKR(0),ROTKRXDivision(0),ROTKRYDivision(0),ROTKRZDivision(0),
    ROCal(0),ROCalXDivision(0),ROCalYDivision(0),ROCalZDivision(0),worldLogical(0),ROFontTKRLog(0),
    ROBackTKRLog(0),ROFontTKRXDivisionLog(0),ROBackTKRXDivisionLog(0),ROFontTKRYDivisionLog(0),
    ROBackTKRYDivisionLog(0),ROTKRZDivisionLog(0),sensitiveTKRLogicalVolume(0),ROCalLog(0),
    ROCalXDivisionLog(0),ROCalYDivisionLog(0),ROCalZDivisionLog(0),sensitiveCalLogicalVolume(0),
    ROTKRZDivisionPhys(0)
{
  isBuilt = false;
  isInitialized = false;
}

/////////////////////////////////////////////////////////////////////////////

void ProtonCTDetectorROGeometry::InitializeTKR(G4double fontZPos,G4double backZPos, G4double TKRSizez,
						 G4double detectorDimX,
						 G4double detectorDimY,
						 G4double detectorDimZ,
						 G4int numberOfVoxelsX,
						 G4int numberOfVoxelsY,
						 G4int numberOfVoxelsZ)
{  
  //detectorToWorldPosition = pos;
  TKRSizeX = detectorDimX;
  TKRSizeY = detectorDimY;
  TKRSizeZ = detectorDimZ;
  numberOfVoxelsAlongX=numberOfVoxelsX;
  numberOfVoxelsAlongY=numberOfVoxelsY;
  numberOfVoxelsAlongZ=numberOfVoxelsZ;

  fontTKRPosZ = fontZPos;
  backTKRPosZ = backZPos;
  TKRBoxSizeZ = TKRSizez;

  isInitialized = true;


  
}

void ProtonCTDetectorROGeometry::InitializeCal(G4double CalPosz,G4double calDimX,G4double calDimY,
                                              G4double calDimZ, G4int numberOfVoxelsZ)
{
  calPosZ = CalPosz;
  calSizeX = calDimX;
  calSizeY = calDimY;
  calSizeZ = calDimZ;
  numberOfVoxelsAlongZ = numberOfVoxelsZ;

}

/*void ProtonCTDetectorROGeometry::UpdateROGeometry()
{
  //Nothing happens if the RO geometry is not built. But parameters are properly set.
  if (!isBuilt)
    {
      //G4Exception("ProtonCTDetectorROGeometry::UpdateROGeometry","had001",
      //		  JustWarning,"Cannot update geometry before it is built");
      return;
    }
 
  //1) Update the dimensions of the G4Boxes
  G4double halfDetectorSizeX = detectorSizeX;
  G4double halfDetectorSizeY = detectorSizeY;
  G4double halfDetectorSizeZ = detectorSizeZ;

  RODetector->SetXHalfLength(halfDetectorSizeX);
  RODetector->SetYHalfLength(halfDetectorSizeY);
  RODetector->SetZHalfLength(halfDetectorSizeZ);

  G4double halfXVoxelSizeX = halfDetectorSizeX/numberOfVoxelsAlongX;
  G4double halfXVoxelSizeY = halfDetectorSizeY;
  G4double halfXVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelXThickness = 2*halfXVoxelSizeX;
  
  RODetectorXDivision->SetXHalfLength(halfXVoxelSizeX);
  RODetectorXDivision->SetYHalfLength(halfXVoxelSizeY);
  RODetectorXDivision->SetZHalfLength(halfXVoxelSizeZ);

  G4double halfYVoxelSizeX = halfXVoxelSizeX;
  G4double halfYVoxelSizeY = halfDetectorSizeY/numberOfVoxelsAlongY;
  G4double halfYVoxelSizeZ = halfDetectorSizeZ;
  G4double voxelYThickness = 2*halfYVoxelSizeY;

  RODetectorYDivision->SetXHalfLength(halfYVoxelSizeX);
  RODetectorYDivision->SetYHalfLength(halfYVoxelSizeY);
  RODetectorYDivision->SetZHalfLength(halfYVoxelSizeZ);

  G4double halfZVoxelSizeX = halfXVoxelSizeX;
  G4double halfZVoxelSizeY = halfYVoxelSizeY;
  G4double halfZVoxelSizeZ = halfDetectorSizeZ/numberOfVoxelsAlongZ;
  G4double voxelZThickness = 2*halfZVoxelSizeZ;

  RODetectorZDivision->SetXHalfLength(halfZVoxelSizeX);
  RODetectorZDivision->SetYHalfLength(halfZVoxelSizeY);
  RODetectorZDivision->SetZHalfLength(halfZVoxelSizeZ);

  //Delete and re-build the relevant physical volumes
  G4PhysicalVolumeStore* store =
    G4PhysicalVolumeStore::GetInstance();

  //Delete...
  G4VPhysicalVolume* myVol = store->GetVolume("RODetectorPhys");
  store->DeRegister(myVol);
  //..and rebuild
  G4VPhysicalVolume *RODetectorPhys = new G4PVPlacement(0,
							detectorToWorldPosition,
							RODetectorLog,
							"RODetectorPhys",
							worldLogical,							
							false,0);

  myVol = store->GetVolume("RODetectorXDivisionPhys");
  store->DeRegister(myVol);
  G4VPhysicalVolume *RODetectorXDivisionPhys = new G4PVReplica("RODetectorXDivisionPhys",
							       RODetectorXDivisionLog,
							       RODetectorPhys,
							       kXAxis,
							       numberOfVoxelsAlongX,
							       voxelXThickness);
  myVol = store->GetVolume("RODetectorYDivisionPhys");
  store->DeRegister(myVol);
  G4VPhysicalVolume *RODetectorYDivisionPhys = new G4PVReplica("RODetectorYDivisionPhys",
							       RODetectorYDivisionLog,
							       RODetectorXDivisionPhys,
							       kYAxis,
							       numberOfVoxelsAlongY,
							       voxelYThickness);
  
  myVol = store->GetVolume("RODetectorZDivisionPhys");
  store->DeRegister(myVol);
  new G4PVReplica("RODetectorZDivisionPhys",
		  RODetectorZDivisionLog,
		  RODetectorYDivisionPhys,
		  kZAxis,
		  numberOfVoxelsAlongZ,
		  voxelZThickness);

  return;

}*/

/////////////////////////////////////////////////////////////////////////////
ProtonCTDetectorROGeometry::~ProtonCTDetectorROGeometry()
{;}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTDetectorROGeometry::Construct()
{
  // A dummy material is used to fill the volumes of the readout geometry.
  // (It will be allowed to set a NULL pointer in volumes of such virtual
  // division in future, since this material is irrelevant for tracking.)
  

  //
  // World
  //
  G4VPhysicalVolume* ghostWorld = GetWorld();
  worldLogical = ghostWorld->GetLogicalVolume();
  
  if (!isInitialized)
    {
      G4Exception("ProtonCTDetectorROGeometry::Construct","had001",
		  FatalException,"Parameters of the RO geometry are not initialized");
      return;
    }

  
  G4double halfTKRSizeX = TKRSizeX;
  G4double halfTKRSizeY = TKRSizeY;
  G4double halfTKRSizeZ = TKRSizeZ;
    
    // World volume of ROGeometry ... SERVE SOLO PER LA ROG

  // TKR ROGeometry 
  ROTKR = new G4Box("ROTKR", 
			 halfTKRSizeX, 
			 halfTKRSizeY, 
			 TKRBoxSizeZ/2);
  
  ROFontTKRLog = new G4LogicalVolume(ROTKR,
				      0,
				      "ROFontTKRLog",
				      0,0,0);

  ROBackTKRLog = new G4LogicalVolume(ROTKR,
				      0,
				      "ROBackTKRLog",
				      0,0,0);
  
  
  G4VPhysicalVolume *physFontTKR = new G4PVPlacement(0,G4ThreeVector(0., 0., fontTKRPosZ),
							ROFontTKRLog,
							"FontTKR",
							worldLogical,							
							false,0);

  G4VPhysicalVolume *physBackTKR = new G4PVPlacement(0,G4ThreeVector(0., 0., backTKRPosZ),
            ROBackTKRLog,
							"BackTKR",
							worldLogical,							
							false,0);



  
  // Division along X axis: the TKR is divided in slices along the X axis
  
  G4double halfXVoxelSizeX = halfTKRSizeX/numberOfVoxelsAlongX;
  G4double halfXVoxelSizeY = halfTKRSizeY;
  G4double halfXVoxelSizeZ = TKRBoxSizeZ/2;
  G4double voxelXThickness = 2*halfXVoxelSizeX;
  

  ROTKRXDivision = new G4Box("ROTKRXDivision",
				  halfXVoxelSizeX,
				  halfXVoxelSizeY,
				  halfXVoxelSizeZ);
  
  ROFontTKRXDivisionLog = new G4LogicalVolume(ROTKRXDivision,
					       0,
					       "ROTKRXDivisionLog",
					       0,0,0);

  ROBackTKRXDivisionLog = new G4LogicalVolume(ROTKRXDivision,
					       0,
					       "ROTKRXDivisionLog",
					       0,0,0);

  G4VPhysicalVolume *ROFontTKRXDivisionPhys = new G4PVReplica("ROFontTKRXDivisionPhys",
                                                              ROFontTKRXDivisionLog,
                                                              physFontTKR,
                                                              kXAxis,
                                                              numberOfVoxelsAlongX,
                                                              voxelXThickness);

    G4VPhysicalVolume *ROBackTKRXDivisionPhys = new G4PVReplica("ROBackTKRXDivisionPhys",
                                                              ROBackTKRXDivisionLog,
                                                              physBackTKR,
                                                              kXAxis,
                                                              numberOfVoxelsAlongX,
                                                              voxelXThickness);

  // Division along Y axis: the slices along the X axis are divided along the Y axis

  G4double halfYVoxelSizeX = halfXVoxelSizeX;
  G4double halfYVoxelSizeY = halfTKRSizeY/numberOfVoxelsAlongY;
  G4double halfYVoxelSizeZ = TKRBoxSizeZ/2;
  G4double voxelYThickness = 2*halfYVoxelSizeY;

  ROTKRYDivision = new G4Box("ROTKRYDivision",
				  halfYVoxelSizeX, 
				  halfYVoxelSizeY,
				  halfYVoxelSizeZ);

  ROFontTKRYDivisionLog = new G4LogicalVolume(ROTKRYDivision,
					       0,
					       "ROFontTKRYDivisionLog",
					       0,0,0);

  ROBackTKRYDivisionLog = new G4LogicalVolume(ROTKRYDivision,
					       0,
					       "ROBackTKRYDivisionLog",
					       0,0,0);
 
  G4VPhysicalVolume *ROFontTKRYDivisionPhys = new G4PVReplica("ROFontTKRYDivisionPhys",
							      ROFontTKRYDivisionLog,
							      ROFontTKRXDivisionPhys,
							      kYAxis,
							      numberOfVoxelsAlongY,
							      voxelYThickness);

  G4VPhysicalVolume *ROBackTKRYDivisionPhys = new G4PVReplica("ROBackTKRYDivisionPhys",
							      ROBackTKRYDivisionLog,
							      ROBackTKRXDivisionPhys,
							      kYAxis,
							      numberOfVoxelsAlongY,
							      voxelYThickness); 
  
  // Division along Z axis: the slices along the Y axis are divided along the Z axis

  G4double halfZVoxelSizeX = halfXVoxelSizeX;
  G4double halfZVoxelSizeY = halfYVoxelSizeY;
  G4double halfZVoxelSizeZ = halfTKRSizeZ;
  G4double voxelZThickness = 2*halfZVoxelSizeZ;
 
  ROTKRZDivision = new G4Box("ROTKRZDivision",
				  halfZVoxelSizeX,
				  halfZVoxelSizeY, 
				  halfZVoxelSizeZ);
 
  ROTKRZDivisionLog = new G4LogicalVolume(ROTKRZDivision,
					       0,
					       "ROTKRZDivisionLog",
					       0,0,0);
 
  for (G4int i = 0; i < 2; i++)
  {
    ROTKRZDivisionPhys = new G4PVPlacement(0,G4ThreeVector(0.,0.,- TKRBoxSizeZ/2 + TKRBoxSizeZ/4 + i*(TKRBoxSizeZ/2)),
        "ROTKRZDivisionPhys",
        ROTKRZDivisionLog,
			  ROFontTKRYDivisionPhys,
			  false,	
			  i);
  }

  for (G4int i = 2; i < 4; i++)
  {
    ROTKRZDivisionPhys = new G4PVPlacement(0,G4ThreeVector(0.,0.,- TKRBoxSizeZ/2 + TKRBoxSizeZ/4 + (i-2)*(TKRBoxSizeZ/2)),
			  "ROTKRZDivisionPhys",	
        ROTKRZDivisionLog,	
			  ROBackTKRYDivisionPhys,
			  false,	
			  i);
  }

  /*---------------- Calolimeter Geometry --------------*/
  /*

  G4double halfCalSizeX = calSizeX;
  G4double halfCalSizeY = calSizeY;
  G4double halfCalSizeZ = calSizeZ;

  ROCal = new G4Box("ROCal", 
			 halfCalSizeX, 
			 halfCalSizeY, 
			 halfTKRSizeZ);
  
  ROCalLog = new G4LogicalVolume(ROCal,
				      0,
				      "ROCalorimeter",
				      0,0,0);

  G4VPhysicalVolume *physCal = new G4PVPlacement(0,G4ThreeVector(0., 0., calPosZ - 7. *cm),
							ROCalLog,
							"physCal",
							worldLogical,							
							false,0);

  // Division along X axis: the Cal is divided in slices along the X axis
  
  halfXVoxelSizeZ = halfTKRSizeZ;
  voxelXThickness = 2*halfXVoxelSizeX;
  

  ROCalXDivision = new G4Box("ROCalXDivision",
				  halfXVoxelSizeX,
				  halfXVoxelSizeY,
				  halfXVoxelSizeZ);
  
  ROCalXDivisionLog = new G4LogicalVolume(ROCalXDivision,
					       0,
					       "ROCalXDivisionLog",
					       0,0,0);

  G4VPhysicalVolume *ROCalXDivisionPhys = new G4PVReplica("ROCalXDivisionPhys",
                                                              ROCalXDivisionLog,
                                                              physCal,
                                                              kXAxis,
                                                              numberOfVoxelsAlongX,
                                                              voxelXThickness);

  // Division along Y axis: the slices along the X axis are divided along the Y axis

  halfYVoxelSizeZ = halfTKRSizeZ;
  voxelYThickness = 2*halfYVoxelSizeY;

  ROCalYDivision = new G4Box("ROCalYDivision",
				  halfYVoxelSizeX, 
				  halfYVoxelSizeY,
				  halfYVoxelSizeZ);

  ROCalYDivisionLog = new G4LogicalVolume(ROCalYDivision,
					       0,
					       "ROCalYDivisionLog",
					       0,0,0);
 
  G4VPhysicalVolume *ROCalYDivisionPhys = new G4PVReplica("ROCalYDivisionPhys",
							      ROCalYDivisionLog,
							      ROCalXDivisionPhys,
							      kYAxis,
							      numberOfVoxelsAlongY,
							      voxelYThickness);
  
  // Division along Z axis: the slices along the Y axis are divided along the Z axis

  /* voxelZThickness = 0.5* mm;
  numberOfVoxelsAlongZ = halfCalSizeZ*2/voxelZThickness;
 
  ROCalZDivision = new G4Box("ROCalZDivision",
				  halfZVoxelSizeX,
				  halfZVoxelSizeY, 
				  voxelZThickness/2);
 
  ROCalZDivisionLog = new G4LogicalVolume(ROCalZDivision,
					       0,
					       "ROCalZDivisionLog",
					       0,0,0);
 
  G4VPhysicalVolume*  ROCalZDivisionPhys = new G4PVReplica("ROCalZDivisionPhys",
                                                              ROCalZDivisionLog,
                                                              ROCalYDivisionPhys,
                                                              kZAxis,
                                                              numberOfVoxelsAlongZ,
                                                              voxelZThickness);
  */
  sensitiveTKRLogicalVolume = ROTKRZDivisionLog;
  // sensitiveCalLogicalVolume = ROCalYDivisionLog;
  isBuilt = true;
}

void ProtonCTDetectorROGeometry::ConstructSD()
{
 
 G4String sensitiveTKRName = "ROTKR";
 //G4String sensitiveCalName = "ROCal";
 
 ProtonCTTrackerSD* TrackerSD = new ProtonCTTrackerSD(sensitiveTKRName);
 //ProtonCTCalorimeterSD* CalorimeterSD = new ProtonCTCalorimeterSD(sensitiveCalName);

 SetSensitiveDetector(sensitiveTKRLogicalVolume,TrackerSD);
  //SetSensitiveDetector(sensitiveCalLogicalVolume,CalorimeterSD);
}