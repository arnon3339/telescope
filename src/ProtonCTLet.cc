#include "ProtonCTDetectorConstruction.hh"
#include "ProtonCTLet.hh"

#include "ProtonCTMatrix.hh"
#include "ProtonCTInteractionParameters.hh"
#include "ProtonCTPrimaryGeneratorAction.hh"
#include "ProtonCTMatrix.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>

ProtonCTLet* ProtonCTLet::instance = NULL;
G4bool ProtonCTLet::doCalculation = false;

ProtonCTLet* ProtonCTLet::GetInstance(ProtonCTDetectorConstruction *pDet)
{
	if (instance) delete instance;
	instance = new ProtonCTLet(pDet);
	return instance;
}

ProtonCTLet* ProtonCTLet::GetInstance()
{
	return instance;
}

ProtonCTLet::ProtonCTLet(ProtonCTDetectorConstruction* pDet)
  :filename("Let.out"),matrix(0) // Default output filename
{   
}

ProtonCTLet::~ProtonCTLet()
{
	
}

// Fill energy spectrum for every voxel (local energy spectrum)
void ProtonCTLet::Initialize()
{

}
/**
 * Clear all stored data
 */
void ProtonCTLet::Clear()
{

}
void  ProtonCTLet::FillEnergySpectrum(G4int trackID,
                                           G4ParticleDefinition* particleDef,
                                           /*G4double kinEnergy,*/
                                           G4double DE,
                                           G4double DX,
                                           G4int i, G4int j, G4int k)
{
	
}




void ProtonCTLet::LetOutput()
{
	
    
}// end loop over voxels

void ProtonCTLet::StoreLetAscii()
{


 }