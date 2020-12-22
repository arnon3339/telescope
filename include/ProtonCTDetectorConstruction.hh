#ifndef ProtonCTDetectorConstruction_H
#define ProtonCTDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"

class G4VPhysicalVolume;
class ProtonCTDetectorROGeometry;
class ProtonCTPhantomGeometry;
class ProtonCTDetectorConstruction;

class ProtonCTDetectorConstruction: public G4VUserDetectorConstruction
{
    public:
        ProtonCTDetectorConstruction();
        ~ProtonCTDetectorConstruction();

        G4VPhysicalVolume* Construct();

        static ProtonCTDetectorConstruction* GetInstance();

        void InitializeDetectorROGeometry(ProtonCTDetectorROGeometry*);

        void BeamLineSupport();

        void BeamPipeFistScatteringFoilsKTW();

        void SecondScatteringFoils();

        void Detector();

        void Calorimeter();

        inline G4LogicalVolume* GetDetectorLogicalVolume(){return logdetector;};

    private:
        static ProtonCTDetectorConstruction* instance;

        void SetDefaultDimensions();
        void ConstrucProtonCTDetectorConstruction();

        G4VPhysicalVolume* physScanningRoom;
	
        
        G4double firstScatteringFoilXSize;
        G4double firstScatteringFoilYSize;
        G4double firstScatteringFoilZSize;
        G4double firstScatteringFoilZPosition;
        
        G4double kaptonWindowXSize;
        G4double kaptonWindowYSize;
        G4double kaptonWindowZSize;
        G4double kaptonWindowZPosition;
        
        G4double secondScatteringFoilXSize;
        G4double secondScatteringFoilYSize;
        G4double secondScatteringFoilZSize;
        G4double secondScatteringFoilZPosition;

        G4double detectorSizeX; 
        G4double detectorSizeY; 
        G4double detectorSizeZ;
        
        G4double calorimeterSizeX; 
        G4double calorimeterSizeY; 
        G4double calorimeterSizeZ;

        G4VPhysicalVolume* physiBeamLineSupport;
        G4VPhysicalVolume* physiBeamLineCover;
        G4VPhysicalVolume* physiBeamLineCover2;

        G4Box* firstScatteringFoil;
        G4VPhysicalVolume* physiFirstScatteringFoil;

        G4VPhysicalVolume* physiKaptonWindow;

        G4Box* secondScatteringFoil;
        G4VPhysicalVolume* physiSecondScatteringFoil;

        ProtonCTPhantomGeometry* Phantom;

        G4VisAttributes* blue;
        G4VisAttributes* gray;
        G4VisAttributes* white;
        G4VisAttributes* red;
        G4VisAttributes* yellow;
        G4VisAttributes* green;
        G4VisAttributes* darkGreen;
        G4VisAttributes* darkOrange3;
        G4VisAttributes* skyBlue;

        G4Material* beamLineSupportMaterial;
        G4Material* vacuumZoneMaterial;
        G4Material* firstScatteringFoilMaterial;
        G4Material* kaptonWindowMaterial;
        G4Material* secondScatteringFoilMaterial;
        G4Material* TrackerMaterial;
        G4Material* spaceMaterial;
        G4Material* calorimeterMaterial;

        ProtonCTDetectorROGeometry* RO;

        G4Box*  soliddetector;
        G4LogicalVolume*    logdetector; 
        G4VPhysicalVolume*  physdetector;

        G4double        detectorZPosition;
        G4ThreeVector   detectorPosition;

        G4double            calorimeterZPosition;
        G4Box*              solidCalorimeter;
        G4LogicalVolume*    logCalorimeter; 
        G4VPhysicalVolume*  physCalorimeter;

        G4double sizeOfVoxelAlongX; 
        G4double sizeOfVoxelAlongY; 
        G4double sizeOfVoxelAlongZ;

        G4int numberOfVoxelsAlongX; 
        G4int numberOfVoxelsAlongY;
        G4int numberOfVoxelsAlongZ;

        G4Region* aRegion;
};

#endif