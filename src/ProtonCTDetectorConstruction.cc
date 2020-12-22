#include "G4Color.hh"
// #include "G4Colour.hh"








#include "G4UnitsTable.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4GeometryManager.hh"
#include "G4SolidStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4UserLimits.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "ProtonCTDetectorConstruction.hh"
#include "ProtonCTDetectorROGeometry.hh"
#include "ProtonCTPhantomGeometry.hh"
#include "G4SystemOfUnits.hh"

#include <cmath>

ProtonCTDetectorConstruction* ProtonCTDetectorConstruction::instance = 0;
ProtonCTDetectorConstruction::ProtonCTDetectorConstruction()
    :physScanningRoom(0),physiBeamLineSupport(0),physiBeamLineCover(0),physiBeamLineCover2(0),
    firstScatteringFoil(0),physiFirstScatteringFoil(0),physiKaptonWindow(0),secondScatteringFoil(0),
    physiSecondScatteringFoil(0),Phantom(0),soliddetector(0),logdetector(0),physdetector(0),aRegion(0)

{

    static G4String ROGeometryName = "DetectorROGeometry";
    RO = new ProtonCTDetectorROGeometry(ROGeometryName);

    G4cout << "Going to register Parallel world...";
    RegisterParallelWorld(RO);
    G4cout << "... done" << G4endl;

    //detectorMessenger = new ProtonCTDetectorConstructionMessenger(this);

}

ProtonCTDetectorConstruction::~ProtonCTDetectorConstruction()
{
    delete Phantom;
}

ProtonCTDetectorConstruction* ProtonCTDetectorConstruction::GetInstance()
{
    return instance;
}

G4VPhysicalVolume* ProtonCTDetectorConstruction::Construct()
{
    SetDefaultDimensions();

    ConstrucProtonCTDetectorConstruction();

    InitializeDetectorROGeometry(RO);

    return physScanningRoom;
}

void ProtonCTDetectorConstruction::SetDefaultDimensions()
{
    //Color
    white = new G4VisAttributes( G4Colour());
    white -> SetVisibility(true);
    white -> SetForceSolid(true);
	
    blue = new G4VisAttributes(G4Colour(0. ,0. ,1.));
    blue -> SetVisibility(true);
    blue -> SetForceSolid(true);
	
    gray = new G4VisAttributes( G4Colour(0.5, 0.5, 0.5 ));
    gray-> SetVisibility(true);
    gray-> SetForceSolid(true);
	
    red = new G4VisAttributes(G4Colour(1. ,0. ,0.));
    red-> SetVisibility(true);
    red-> SetForceSolid(true);
	
    yellow = new G4VisAttributes(G4Colour(1., 1., 0. ));
    yellow-> SetVisibility(true);
    yellow-> SetForceSolid(true);
	
    green = new G4VisAttributes( G4Colour(25/255. , 255/255. ,  25/255. ));
    green -> SetVisibility(true);
    green -> SetForceSolid(true);
	
    darkGreen = new G4VisAttributes( G4Colour(0/255. , 100/255. ,  0/255. ));
    darkGreen -> SetVisibility(true);
    darkGreen -> SetForceSolid(true);
    
    darkOrange3 = new G4VisAttributes( G4Colour(205/255. , 102/255. ,  000/255. ));
    darkOrange3 -> SetVisibility(true);
    darkOrange3 -> SetForceSolid(true);
	
    skyBlue = new G4VisAttributes( G4Colour(135/255. , 206/255. ,  235/255. ));
    skyBlue -> SetVisibility(true);
    skyBlue -> SetForceSolid(true);

    //Material
    G4bool isotopes = false;
    G4Material* aluminumNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al", isotopes);
    G4Material* tantalumNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ta", isotopes);
    G4Material* leadNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb", isotopes);
    G4Material* SiNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si", isotopes);

    
    // COMPOUND
    G4Material* airNist =  G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR", isotopes);
    G4Material* kaptonNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_KAPTON", isotopes);
    G4Material* galacticNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic", isotopes);
    G4Material* CsINist = G4NistManager::Instance()->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    
    spaceMaterial                  =       airNist;
    beamLineSupportMaterial        =       aluminumNist;
    vacuumZoneMaterial             =       galacticNist;
    firstScatteringFoilMaterial    =       tantalumNist;
    kaptonWindowMaterial           =       kaptonNist;
    secondScatteringFoilMaterial   =       leadNist;
    TrackerMaterial                =       SiNist;
    calorimeterMaterial            =       aluminumNist;
}

void ProtonCTDetectorConstruction::ConstrucProtonCTDetectorConstruction()
{
    const G4double worldX = 200.0 *cm;
    const G4double worldY = 200.0 *cm;
    const G4double worldZ = 600.0 *cm;

    G4Box* ScanningRoom = new G4Box("TreatmentRoom",worldX/2,worldY/2,worldZ/2);
    G4LogicalVolume* logicScanningRoom = new G4LogicalVolume(ScanningRoom,
                                                              spaceMaterial,
                                                              "logicTreatmentRoom",
                                                              0,0,0);
    physScanningRoom = new G4PVPlacement(0,
                                              G4ThreeVector(),
                                              "physicalTreatmentRoom",
                                              logicScanningRoom,
                                              0,false,0);

    // The treatment room is invisible in the Visualisation
    logicScanningRoom -> SetVisAttributes (G4VisAttributes::Invisible);

    // Components of the Passive Proton Beam Line

    // BeamLineSupport();

    BeamPipeFistScatteringFoilsKTW();

    // SecondScatteringFoils();

    Detector();

    // Calorimeter();

    // Phantom = new ProtonCTPhantomGeometry(physScanningRoom);
    // Phantom->buildPhantom();

    if (!aRegion)
    {
        aRegion = new G4Region("DetectorLog");
        logdetector -> SetRegion(aRegion);
        aRegion->AddRootLogicalVolume( logdetector );
    }
}

void ProtonCTDetectorConstruction::BeamLineSupport()
{
    // ------------------//
    // BEAM LINE SUPPORT //
    //-------------------//
    const G4double beamLineSupportXSize = 50. *cm;
    const G4double beamLineSupportYSize = 1.5 *cm;
    const G4double beamLineSupportZSize = 450 *cm;
    
    const G4double beamLineSupportXPosition = 0. *mm;
    const G4double beamLineSupportYPosition = -15. *cm;
    const G4double beamLineSupportZPosition = 0.*mm;
    
    G4Box* beamLineSupport = new G4Box("BeamLineSupport",
                                        beamLineSupportXSize/2,
                                        beamLineSupportYSize/2,
                                        beamLineSupportZSize/2);
    
    G4LogicalVolume* logicBeamLineSupport = new G4LogicalVolume(beamLineSupport,
                                                                beamLineSupportMaterial,
                                                                "BeamLineSupport");
    physiBeamLineSupport = new G4PVPlacement(0, G4ThreeVector(beamLineSupportXPosition,
                                                              beamLineSupportYPosition,
                                                              beamLineSupportZPosition),
                                             "BeamLineSupport",
                                             logicBeamLineSupport,
                                             physScanningRoom, false, 0);
    
    // Visualisation attributes of the beam line support
    
    logicBeamLineSupport -> SetVisAttributes(gray);

    //---------------------------------//
    //  Beam line cover 1 (left panel) //
    //---------------------------------//
    const G4double beamLineCoverXSize = 1.5 *cm;
    const G4double beamLineCoverYSize = 50. *cm;
    const G4double beamLineCoverZSize = 450 *cm;
    
    const G4double beamLineCoverXPosition = -25. *cm;
    const G4double beamLineCoverYPosition = -40. *cm;
    const G4double beamLineCoverZPosition =  0. *cm;
    
    G4Box* beamLineCover = new G4Box("BeamLineCover",
                                        beamLineCoverXSize/2,
                                        beamLineCoverYSize/2,
                                        beamLineCoverZSize/2);
    
    G4LogicalVolume* logicBeamLineCover = new G4LogicalVolume(beamLineCover,
                                                              beamLineSupportMaterial,
                                                              "BeamLineCover");
    
    physiBeamLineCover = new G4PVPlacement(0, G4ThreeVector(beamLineCoverXPosition,
                                                            beamLineCoverYPosition,
                                                            beamLineCoverZPosition),
                                           "BeamLineCover",
                                           logicBeamLineCover,
                                           physScanningRoom,
                                           false,
                                           0);
    
    // ---------------------------------//
    //  Beam line cover 2 (rigth panel) //
    // ---------------------------------//
    // It has the same characteristic of beam line cover 1 but set in a different position
    physiBeamLineCover2 = new G4PVPlacement(0, G4ThreeVector(-beamLineCoverXPosition,
                                                             beamLineCoverYPosition,
                                                             beamLineCoverZPosition),
                                            "BeamLineCover2",
                                            logicBeamLineCover,
                                            physScanningRoom,
                                            false,
                                            0);
    
    logicBeamLineCover -> SetVisAttributes(blue);
}

void ProtonCTDetectorConstruction::BeamPipeFistScatteringFoilsKTW()
{
    // ------------//
    // VACUUM PIPE //
    //-------------//
    //
    // First track of the beam line is inside vacuum;
    // The PIPE contains the FIRST SCATTERING FOIL and the KAPTON WINDOW
    const G4double  vacuumZoneXSize = 52.5 *mm;
    const G4double  vacuumZoneYSize = 52.5 *mm;
    const G4double  vacuumZoneZSize = 100.0 *mm;

    const G4double  vacuumZoneXPosition = 0. *cm;
    const G4double  vacuumZoneYPosition = 0. *cm;
    const G4double  vacuumZoneZPosition = -215. *cm;

    G4Box* vacuumZone = new G4Box("VacuumZone", vacuumZoneXSize/2, vacuumZoneYSize/2, vacuumZoneZSize/2);
    G4LogicalVolume* logicVacuumZone = new G4LogicalVolume(vacuumZone, vacuumZoneMaterial, "VacuumZone");
    G4VPhysicalVolume* physiVacuumZone = new G4PVPlacement(0, G4ThreeVector(vacuumZoneXPosition, vacuumZoneYPosition, vacuumZoneZPosition),
                                                           "VacuumZone", logicVacuumZone, physScanningRoom, false, 0);
    // --------------------------//
    // THE FIRST SCATTERING FOIL //
    // --------------------------//
    // A thin foil performing a first scattering
    // of the original beam

    firstScatteringFoilXSize    =   52.5 *mm;
    firstScatteringFoilYSize    =   52.5 *mm;
    firstScatteringFoilZSize    =   0.0075 *mm;

    firstScatteringFoilZPosition    =   0.* cm;

    firstScatteringFoil = new G4Box("FirstScatteringFoil",
                                    firstScatteringFoilXSize/2,
                                    firstScatteringFoilYSize/2,
                                    firstScatteringFoilZSize/2);
    
    G4LogicalVolume* logicFirstScatteringFoil = new G4LogicalVolume(firstScatteringFoil,
                                                                    firstScatteringFoilMaterial,
                                                                    "FirstScatteringFoil");
    
    physiFirstScatteringFoil = new G4PVPlacement(0, G4ThreeVector(0., 0.,firstScatteringFoilZPosition),
                                                 "FirstScatteringFoil", logicFirstScatteringFoil, physiVacuumZone,
                                                 false, 0);
    
    logicFirstScatteringFoil -> SetVisAttributes(skyBlue);
    // -------------------//
    // THE KAPTON WINDOWS //
    //--------------------//
    //It prmits the passage of the beam from vacuum to air
    kaptonWindowXSize   =   5.25*cm;
    kaptonWindowYSize   =   5.25*cm;
    kaptonWindowZSize   =   0.010*mm;

    kaptonWindowZPosition   =   vacuumZoneZSize/2 - kaptonWindowZSize/2;

    G4Box* solidKaptonWindow = new G4Box("KaptonWindow",
                                         kaptonWindowXSize/2,
                                         kaptonWindowYSize/2,
                                         kaptonWindowZSize/2);
    
    G4LogicalVolume* logicKaptonWindow = new G4LogicalVolume(solidKaptonWindow,
                                                             kaptonWindowMaterial,
                                                             "KaptonWindow");
    
    physiKaptonWindow = new G4PVPlacement(0, G4ThreeVector(0., 0., kaptonWindowZPosition),
                                          "KaptonWindow", logicKaptonWindow,
                                          physiVacuumZone, false,	0);
    
    logicKaptonWindow -> SetVisAttributes(darkOrange3);
}

void ProtonCTDetectorConstruction::SecondScatteringFoils()
{
    secondScatteringFoilXSize   =   52.5   *mm;;
    secondScatteringFoilYSize   =   52.5   *mm;;
    secondScatteringFoilZSize   =   1.9     *mm;

    secondScatteringFoilZPosition   =   -200. *cm;

    secondScatteringFoil = new G4Box("ScatteringFoil",
                                    secondScatteringFoilXSize/2,
                                    secondScatteringFoilYSize/2,
                                    secondScatteringFoilZSize/2);
    
    G4LogicalVolume* logicSecondScatteringFoil = new G4LogicalVolume(secondScatteringFoil,
                                                                    secondScatteringFoilMaterial,
                                                                    "ScatteringFoil");
    
    physiSecondScatteringFoil = new G4PVPlacement(0, G4ThreeVector(0., 0.,secondScatteringFoilZPosition),
                                                 "ScatteringFoil", logicSecondScatteringFoil, physScanningRoom,
                                                 false, 0);
    
    logicSecondScatteringFoil -> SetVisAttributes(skyBlue);
}

void ProtonCTDetectorConstruction::Detector()
{
    detectorSizeX   =   3.0  *cm;
    detectorSizeY   =   1.5  *cm;
    detectorSizeZ   =   200.    *um;

    G4double TKRBoxSizeZ = 60.*cm;
    G4double TKRZPosition = 20. *cm;

    G4Box* TKRBox = new G4Box("TKRBox",detectorSizeX/2,detectorSizeY/2,TKRBoxSizeZ/2);
    G4LogicalVolume* logTKRBox = new G4LogicalVolume(TKRBox,spaceMaterial,"TKRBox");
    G4VPhysicalVolume* physFontTKRBox = new G4PVPlacement(0, G4ThreeVector(0., 0., TKRZPosition),
                                                        "FontTKRBox",logTKRBox, physScanningRoom,false,0);
    detectorPosition = G4ThreeVector(0., 0., detectorZPosition);

    soliddetector   =   new G4Box("Detector",detectorSizeX/2,detectorSizeY/2,detectorSizeZ/2);
    logdetector     =   new G4LogicalVolume(soliddetector,
                                            TrackerMaterial,
                                            "Detector");; 

    for (G4int i = 0; i < 5; i++)
    {
        physdetector    =   new G4PVPlacement(0, G4ThreeVector(0., 0., -TKRBoxSizeZ/3 + (TKRBoxSizeZ*i)/6),
                                                 "Detector", logdetector, physFontTKRBox,
                                                 false, i);
    }
    
    logdetector -> SetVisAttributes (red);
}


void ProtonCTDetectorConstruction::Calorimeter()
{
    calorimeterSizeX = detectorSizeX; 
    calorimeterSizeY = detectorSizeY; 
    calorimeterSizeZ = 3.5 *cm;

    calorimeterZPosition = 177.75 *cm;

    G4double calBoxSizeZ = calorimeterSizeZ*4;

    G4Box* calBox = new G4Box("CalBox",calorimeterSizeX/2,calorimeterSizeY/2,calBoxSizeZ/2);
    G4LogicalVolume* logCalBox = new G4LogicalVolume(calBox,spaceMaterial,"CalBox");
    G4VPhysicalVolume* physCalBox = new G4PVPlacement(0, G4ThreeVector(0., 0., calorimeterZPosition),
                                                        "CalBox",logCalBox, physScanningRoom,false,0);
    
    solidCalorimeter = new G4Box("CalorimeterLayer",calorimeterSizeX/2, calorimeterSizeY/2, calorimeterSizeZ/2);
    logCalorimeter = new G4LogicalVolume(solidCalorimeter,calorimeterMaterial,"CalorimeterLayer");
    for (G4int i = 0; i < 4; i++)
    {
        physCalorimeter = new G4PVPlacement(0, G4ThreeVector(0., 0., -calBoxSizeZ/2 + calorimeterSizeZ/2 + i*calorimeterSizeZ),
                                                 "CalorimeterLayer", logCalorimeter, physCalBox,
                                                 false, i);
    }
    logCalBox->SetVisAttributes (green);
    
}

void ProtonCTDetectorConstruction::InitializeDetectorROGeometry(ProtonCTDetectorROGeometry* Ro)
{
    sizeOfVoxelAlongX = 3.0 *cm;
    sizeOfVoxelAlongY = 1.5 *cm;
    sizeOfVoxelAlongZ = 200.    *um;

    numberOfVoxelsAlongX = G4lrint(detectorSizeX / sizeOfVoxelAlongX);
    sizeOfVoxelAlongX = ( detectorSizeX / numberOfVoxelsAlongX );
    numberOfVoxelsAlongY = G4lrint(detectorSizeY / sizeOfVoxelAlongY);
    sizeOfVoxelAlongY = ( detectorSizeY / numberOfVoxelsAlongY );
    numberOfVoxelsAlongZ = 2;
    sizeOfVoxelAlongZ = ( detectorSizeZ / numberOfVoxelsAlongZ );

    Ro->InitializeTKR(115. *cm ,155. *cm, 60.* cm,
                   detectorSizeX/2,
                   detectorSizeY/2,
                   detectorSizeZ/2,
                   numberOfVoxelsAlongX,
                   numberOfVoxelsAlongY,
                   numberOfVoxelsAlongZ);

    sizeOfVoxelAlongZ = 0.5 *mm;
    numberOfVoxelsAlongZ = G4lrint(calorimeterSizeZ/sizeOfVoxelAlongZ);
    Ro->InitializeCal(177.75*cm, 
                    detectorSizeX/2,
                    detectorSizeY/2,
                    calorimeterSizeZ*4/2,
                    numberOfVoxelsAlongZ);
}

