#include "G4Box.hh"
#include "G4Tubs.hh"
#include "globals.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "ProtonCTPhantomGeometry.hh"

//#include "ProtonCTPhantomGeometryMessenger.hh"

ProtonCTPhantomGeometry* ProtonCTPhantomGeometry::instance = 0;

ProtonCTPhantomGeometry::ProtonCTPhantomGeometry(G4VPhysicalVolume* physicalScanningRoom)
    :motherVolume(physicalScanningRoom),tubsPhantom(0),logPhantom(0),tubsSkelPhantom(0),logSkelPhantom(0),
    tubsLiqPhantom(0),logLiqPhantom(0),boxBrainPhantom(0),logBrainPhantom(0),matPhantom(0),
    matSkelPhantom(0),matLiqPhantom(0)
{
    PhantomRadius               =               10.*cm;
    PhantomHieght               =               10.*cm;
    SkelPhantomInnerRadius      =               9.*cm;
    SkelPhantomOuterRadius      =               10.*cm;
    SkelPhantomHeight           =               10.*cm;
    LiqPhantomRadius            =               9.*cm;
    LiqPhantomHieght            =               10.*cm;

    BrainPhantomXSize           =               5.*cm;
    BrainPhantomYSize           =               5.*cm;
    BrainPhantomZSize           =               5.*cm;

    PhantomAngle                =               0.*deg;

    //phantomMessenger = new ProtonCTPhantomGeometryMessenger(this);

    G4String name, symbol;    
    G4double a, z, d, density, A, Z, nel; 

    A = 1.01*g/mole;
    G4Element* elH = new G4Element ("Hydrogen","H",Z = 1.,A);

    A = 12.011*g/mole;
    G4Element* elC = new G4Element("Carbon","C",Z = 6.,A);  

    A = 14.01*g/mole;
    G4Element* elN = new G4Element("Nitrogen","N",Z = 7.,A);

    A = 16.00*g/mole;
    G4Element* elO = new G4Element("Oxygen","O",Z = 8.,A);

    A = 22.99*g/mole;
    G4Element* elNa = new G4Element("Sodium","Na",Z = 11.,A);

    A = 24.305*g/mole;
    G4Element* elMg = new G4Element("Magnesium","Mg",Z = 12.,A);

    A = 30.974*g/mole;
    G4Element* elP = new G4Element("Phosphorus","P",Z = 15.,A);
  
    A = 32.064*g/mole;
    G4Element* elS = new G4Element("Sulfur","S",Z = 16.,A);
  
    A = 35.453*g/mole;
    G4Element* elCl = new G4Element("Chlorine","Cl",Z = 17.,A);
  
    A = 39.098*g/mole;
    G4Element* elK = new G4Element("Potassium","K",Z = 19.,A);

    A = 40.08*g/mole;
    G4Element* elCa = new G4Element("Calcium","Ca",Z = 20.,A);

    A = 55.85*g/mole;
    G4Element* elFe  = new G4Element("Iron","Fe",Z = 26.,A);
  
    A = 65.38*g/mole;
    G4Element* elZn = new G4Element("Zinc","Zn",Z = 30.,A);

    A = 85.47 *g/mole;
    G4Element* elRb = new G4Element("Rb","Rb",Z = 37.,A);

    A = 87.62 *g/mole;
    G4Element* elSr = new G4Element("Sr","Sr",Z = 38.,A);

    A = 91.22 *g/mole;
    G4Element* elZr = new G4Element("Zr","Zr",Z = 40.,A);

    A = 207.19 *g/mole;
    G4Element* elPb = new G4Element("Lead","Pb", Z = 82.,A);

    density = 19.3*g/cm3;
    a = 183.84*g/mole;
    G4Material* W = new G4Material(name="Tungsten", z=74., a, density);

    // Water
    d = 1.000*g/cm3;
    G4Material* matH2O = new G4Material("Water",d,2);
    matH2O->AddElement(elH,2);
    matH2O->AddElement(elO,1);
    matH2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);

    G4bool isotopes = false;
    G4Material* galacticNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic", isotopes);

    // MIRD Skeleton
    d = 1.4862*g/cm3;
    G4Material* skeleton = new G4Material("skeleton",d,15);
    skeleton -> AddElement(elH,0.0704);
    skeleton -> AddElement(elC,0.2279);
    skeleton -> AddElement(elN,0.0387);
    skeleton -> AddElement(elO,0.4856);
    skeleton -> AddElement(elNa,0.0032); 
    skeleton -> AddElement(elMg,0.0011); 
    skeleton -> AddElement(elP,0.0694);
    skeleton -> AddElement(elS,0.0017);
    skeleton -> AddElement(elCl,0.0014);
    skeleton -> AddElement(elK,0.0015);
    skeleton -> AddElement(elCa,0.0991);
    skeleton -> AddElement(elFe,0.00008);
    skeleton -> AddElement(elZn,0.000048);
    skeleton -> AddElement(elSr,0.000032);
    skeleton -> AddElement(elPb,0.000011);

    // MIRD soft tissue
    d = 0.9869 *g/cm3;
    G4Material* soft = new G4Material("soft_tissue",d,16);
    soft->AddElement(elH,0.1047);
    soft->AddElement(elC,0.2302);
    soft->AddElement(elN,0.0234);
    soft->AddElement(elO,0.6321);
    soft->AddElement(elNa,0.0013);
    soft->AddElement(elMg,0.00015);
    soft->AddElement(elP,0.0024);
    soft->AddElement(elS,0.0022);
    soft->AddElement(elCl,0.0014);
    soft->AddElement(elK,0.0021);
    soft->AddElement(elFe,0.000063);
    soft->AddElement(elZn,0.000032);
    soft->AddElement(elRb,0.0000057);
    soft->AddElement(elSr,0.00000034);
    soft->AddElement(elZr,0.000008);
    soft->AddElement(elPb,0.00000016);

    matPhantom          =       galacticNist;
    matSkelPhantom      =       skeleton;
    matLiqPhantom       =       matH2O;
    matBrainPhantom     =       soft;

    G4VisAttributes* darkOrange = new G4VisAttributes( G4Colour(204/255. , 102/255. ,  0/255.));
    darkOrange -> SetVisibility(true);
    darkOrange -> SetForceSolid(true);

    G4VisAttributes* lightSkyBlue = new G4VisAttributes( G4Colour(135/255. , 206/255. ,  235/255., 0.6));
    lightSkyBlue -> SetVisibility(true);
    lightSkyBlue -> SetForceSolid(true);

    G4VisAttributes* grayC = new G4VisAttributes( G4Colour(0.5, 0.5, 0.5 ));
    grayC-> SetVisibility(true);
    grayC-> SetForceSolid(true);

    visSkelPhantom  =   darkOrange;
    visLiqPhantom   =   lightSkyBlue;
    visBrainPhantom =   grayC;

}

ProtonCTPhantomGeometry::~ProtonCTPhantomGeometry()
{
    //delete phantomMessenger;
}

void ProtonCTPhantomGeometry::buildPhantom()
{
    //Phantom
    tubsPhantom = new G4Tubs("PhantomSkel",0.,PhantomRadius,PhantomHieght/2,0.0*deg,360.*deg);
    logPhantom = new G4LogicalVolume(tubsPhantom,matPhantom, "Phantom");

    // Skeleton Pantom
    tubsSkelPhantom = new G4Tubs("PhantomSkel",SkelPhantomInnerRadius,SkelPhantomOuterRadius,SkelPhantomHeight/2,0.0*deg,360.*deg);
    logSkelPhantom = new G4LogicalVolume(tubsSkelPhantom,matSkelPhantom,"PhantomSkel");

    //Liquid Phantom
    tubsLiqPhantom = new G4Tubs("LiquidPhantom",0., LiqPhantomRadius, LiqPhantomHieght/2, 0.0*deg, 360.*deg);
    logLiqPhantom = new G4LogicalVolume(tubsLiqPhantom,matLiqPhantom,"LiquidPhantom");

    // Brain Phantom
    boxBrainPhantom = new G4Box("BrainPhantom",BrainPhantomXSize/2,BrainPhantomYSize/2,BrainPhantomZSize/2);
    logBrainPhantom = new G4LogicalVolume(boxBrainPhantom,matBrainPhantom,"BrainPhantom");

    //-------------------------------------------------Placement--------------------------------------------------------------------
    G4cout << "Phatom angle is " << PhantomAngle/deg << "degree" << G4endl;
    G4double phi = 90. *deg;
    G4RotationMatrix rm;                                                                    
    rm.rotateX(phi);
    rm.rotateY(PhantomAngle);

    physPhantom = new G4PVPlacement(G4Transform3D(rm, G4ThreeVector(0. , 0., 135. *cm)),
                                                "Phantom",logPhantom,motherVolume,false,0);

    rm.rotateX(-phi);
    rm.rotateY(-PhantomAngle);
    //Skeleton Pantom
    new G4PVPlacement(G4Transform3D(rm, G4ThreeVector(0. , 0., 0.)),
                                                "PhantomSkel",logSkelPhantom,physPhantom,false,0);

    

    //Liquid Pantom
    new G4PVPlacement(G4Transform3D(rm, G4ThreeVector(0. , 0., 0.)),
                                                "PhantomLiq",logLiqPhantom,physPhantom,false,0);

    //Brain Pantom
    new G4PVPlacement(G4Transform3D(rm, G4ThreeVector(0. , 0., 0.)),
                                                "PhantomBrain",logBrainPhantom,physPhantom,false,0);

    logPhantom->SetVisAttributes(G4VisAttributes::GetInvisible());
    logSkelPhantom->SetVisAttributes(visSkelPhantom);
    logLiqPhantom->SetVisAttributes(visLiqPhantom);
    logBrainPhantom->SetVisAttributes (visBrainPhantom);   
}

/*void ProtonCTPhantomGeometry::UpdateGeometry()
{
    G4GeometryManager::GetInstance() -> OpenGeometry();
    G4RunManager::GetRunManager()->GetUserDetectorConstruction();
    ConstructPhantom();

    // Inform the kernel about the new geometry
    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
}*/

ProtonCTPhantomGeometry* ProtonCTPhantomGeometry::GetInstance()
{
    return instance;
}

/*void ProtonCTPhantomGeometry::SetRatationAngle(G4double value)
{
    PhantomAngle = value;
    G4cout << "The phantom has rotated to the new angle" << G4endl;
    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
}
*/
