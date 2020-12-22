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
//#include "ProtonCTMatrix.hh"
#include "G4SystemOfUnits.hh"

/////////////////////////////////////////////////////////////////////////////
ProtonCTSteppingAction::ProtonCTSteppingAction( ProtonCTRunAction *run)
{
    runAction = run;
}

/////////////////////////////////////////////////////////////////////////////
ProtonCTSteppingAction::~ProtonCTSteppingAction()
{
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTSteppingAction::UserSteppingAction(const G4Step* aStep)
{
    G4String particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();
}