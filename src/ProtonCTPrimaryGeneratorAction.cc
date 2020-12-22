#include "ProtonCTPrimaryGeneratorAction.hh"
#include "ProtonCTPrimaryGeneratorActionMessenger.hh"

//#include "ProtonCTMatrix.hh"
//#include "ProtonCTDetectorSD.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"

#include "G4Event.hh"
#include "G4Timer.hh"

#include "G4RunManager.hh"



/////////////////////////////////////////////////////////////////////////////
ProtonCTPrimaryGeneratorAction::ProtonCTPrimaryGeneratorAction()
{
    PrimaryGeneratorMessenger = new ProtonCTPrimaryGeneratorActionMessenger(this);
    SetDefaultPrimaryParticle();
    particleGun = new G4GeneralParticleSource();

}

/////////////////////////////////////////////////////////////////////////////
ProtonCTPrimaryGeneratorAction::~ProtonCTPrimaryGeneratorAction()
{
delete PrimaryGeneratorMessenger;
delete  particleGun;
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTPrimaryGeneratorAction::SetDefaultPrimaryParticle()
{
    
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
        particleGun->GeneratePrimaryVertex(anEvent);

}