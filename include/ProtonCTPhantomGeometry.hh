#ifndef ProtonCTPhantomGeometry_H
#define ProtonCTPhantomGeometry_H 1

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"

//class ProtonCTPhantomGeometryMessenger;
class G4VPhysicalVolume;
class G4LogicalVolume;
class G4PVPlacement;

class ProtonCTPhantomGeometry
{
    public:
        ProtonCTPhantomGeometry(G4VPhysicalVolume*);
        ~ProtonCTPhantomGeometry();
    public:
        static ProtonCTPhantomGeometry* GetInstance();
        void buildPhantom();

    private:
        static ProtonCTPhantomGeometry* instance;
        //ProtonCTPhantomGeometryMessenger*   phantomMessenger;

        G4double                PhantomRadius;
        G4double                PhantomHieght;
        G4double                SkelPhantomInnerRadius;
        G4double                SkelPhantomOuterRadius;
        G4double                SkelPhantomHeight;
        G4double                LiqPhantomRadius;
        G4double                LiqPhantomHieght;

        G4double                BrainPhantomXSize;
        G4double                BrainPhantomYSize;
        G4double                BrainPhantomZSize;

        G4double                PhantomAngle;

        G4VPhysicalVolume*      motherVolume;

        G4Tubs*                 tubsPhantom;
        G4LogicalVolume*        logPhantom;
        G4VPhysicalVolume*      physPhantom;

        G4Tubs*                 tubsSkelPhantom;
        G4LogicalVolume*        logSkelPhantom;

        G4Tubs*                 tubsLiqPhantom;
        G4LogicalVolume*        logLiqPhantom;

        G4Box*                  boxBrainPhantom;
        G4LogicalVolume*        logBrainPhantom;

        G4Material*             matPhantom;
        G4Material*             matSkelPhantom;
        G4Material*             matLiqPhantom;
        G4Material*             matBrainPhantom;

        G4VisAttributes*        visSkelPhantom;
        G4VisAttributes*        visLiqPhantom;
        G4VisAttributes*        visBrainPhantom;

};

#endif

