#include "ProtonCTTrackerSD.hh"
#include "ProtonCTTrackerHit.hh"
#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
//#include "ProtonCTMatrix.hh"
//#include "ProtonCTLet.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
//#include "ProtonCTMatrix.hh"


#include "G4SteppingManager.hh"
#include "G4TrackVector.hh"
#include "ProtonCTSteppingAction.hh"
#include "G4ios.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4TrackVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4UserEventAction.hh"
#include "G4TransportationManager.hh"
#include "G4VSensitiveDetector.hh"
#include "ProtonCTRunAction.hh"
#include "G4SystemOfUnits.hh"


/////////////////////////////////////////////////////////////////////////////
ProtonCTTrackerSD::ProtonCTTrackerSD(G4String name):
G4VSensitiveDetector(name)
{
    G4String HCname;
    collectionName.insert(HCname="ProtonCTTrackerHitsCollection");
    HitsCollection = NULL;
    sensitiveDetectorName = name;
}

/////////////////////////////////////////////////////////////////////////////
ProtonCTTrackerSD::~ProtonCTTrackerSD()
{
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTTrackerSD::Initialize(G4HCofThisEvent*)
{
    
    HitsCollection = new ProtonCTTrackerHitsCollection(sensitiveDetectorName,
                                                             collectionName[0]);
}

/////////////////////////////////////////////////////////////////////////////
G4bool ProtonCTTrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory* )
{
    
    
    if (aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() != "ROTKRZDivisionPhys") return false;

    // Get kinetic energy
    G4Track * theTrack = aStep  ->  GetTrack();
    G4double kineticEnergy =  theTrack -> GetKineticEnergy();

    
    G4ParticleDefinition *particleDef = theTrack -> GetDefinition();
    //Get particle name
    G4String particleName =  particleDef -> GetParticleName();
    
    G4int pdg = particleDef ->GetPDGEncoding();
    
    // Get unique track_id (in an event)
    G4int trackID = theTrack -> GetTrackID();
    
    G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
    if (energyDeposit < 100. *keV) return false;

    G4double DX = aStep -> GetStepLength();
    G4int Z = particleDef-> GetAtomicNumber();
    G4int A = particleDef-> GetAtomicMass();
    G4StepPoint* PreStep = aStep->GetPreStepPoint();
    
    // Read voxel indexes: i is the x index, k is the z index
    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int k  = touchable->GetVolume()->GetCopyNo();
    G4int i  = touchable->GetReplicaNumber(2);
    G4int j  = touchable->GetReplicaNumber(1);
    
    G4TouchableHandle touchPreStep = PreStep->GetTouchableHandle();
    G4VPhysicalVolume* volumePre = touchPreStep->GetVolume();
    G4String namePre = volumePre->GetName();
    //G4double eKin = aStep -> GetPreStepPoint() -> GetKineticEnergy();
    
     ProtonCTTrackerHit* detectorHit = new ProtonCTTrackerHit();
     detectorHit -> SetHit(particleName,i, j, k, energyDeposit); 
     HitsCollection -> insert(detectorHit);
    
    return true;
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTTrackerSD::EndOfEvent(G4HCofThisEvent* HCE)
{
    
    static G4int HCID = -1;
    if(HCID < 0)
    { 
        HCID = GetCollectionID(0); 
    }
    
    HCE -> AddHitsCollection(HCID,HitsCollection);
}

