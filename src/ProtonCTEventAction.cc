#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include "ProtonCTEventAction.hh"
#include "ProtonCTTrackerHit.hh"
#include "ProtonCTTrackerSD.hh"
#include "ProtonCTCalorimeterHit.hh"
#include "ProtonCTCalorimeterSD.hh"
#include "ProtonCTDetectorConstruction.hh"
#include "ProtonCTMatrix.hh"
#include "ProtonCTEventActionMessenger.hh"

/////////////////////////////////////////////////////////////////////////////
ProtonCTEventAction::ProtonCTEventAction() :
drawFlag("all" ),printModulo(10), pointerEventMessenger(0)
{
    trackerCollID = -1;
    calorimeterCollID = -1;
    pointerEventMessenger = new ProtonCTEventActionMessenger(this);
}

/////////////////////////////////////////////////////////////////////////////
ProtonCTEventAction::~ProtonCTEventAction()
{
    delete pointerEventMessenger;
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTEventAction::BeginOfEventAction(const G4Event*)
{
    G4SDManager* pSDManager = G4SDManager::GetSDMpointer();
    if(trackerCollID == -1)
        trackerCollID = pSDManager -> GetCollectionID("ProtonCTTrackerHitsCollection");
    // if(calorimeterCollID==-1) 
    //     calorimeterCollID = pSDManager->GetCollectionID("ProtonCTCalorimeterHitsCollection");
  
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTEventAction::EndOfEventAction(const G4Event* evt)
{
    if(trackerCollID < 0 && calorimeterCollID < 0)
        return;
    G4HCofThisEvent* HCE = evt -> GetHCofThisEvent();
    
    // Clear voxels hit list
    G4int numberOfVoxelsAlongX = G4lrint(30000/28);
    G4int numberOfVoxelsAlongY = G4lrint(15000/28);
    G4int numberOfVoxelsAlongZ = 1;

    ProtonCTMatrix* matrix = ProtonCTMatrix::GetInstance();
    matrix = new ProtonCTMatrix();
    if(HCE)
    {
        ProtonCTTrackerHitsCollection* THC = (ProtonCTTrackerHitsCollection*)(HCE -> GetHC(trackerCollID));
        // ProtonCTCalorimeterHitsCollection* CHC = (ProtonCTCalorimeterHitsCollection*)(HCE -> GetHC(calorimeterCollID));
        if(THC)
        {  
                // Fill the matrix with the information: voxel and associated energy deposit
                // in the detector at the end of the event
                
                G4int HitCount = THC -> entries();
                matrix->Initialize(HitCount);
                G4cout<<"Tracker is here."<<G4endl;
                for (G4int h=0; h<HitCount; h++)
                {
                    G4String parName = ((*THC)[h])->GetParName();
                    G4int i = ((*THC)[h]) -> GetXID();
                    G4int j = ((*THC)[h]) -> GetYID();
                    G4int k = ((*THC)[h]) -> GetZID();
                    G4double energyDeposit = ((*THC)[h]) -> GetEdep();
                    matrix -> Fill(parName,i, j, k, energyDeposit/keV);  
                    G4cout<<parName<<","<<i<<","<<j<<","<<k<<","<<energyDeposit/keV<<G4endl;
                }
                matrix->hitAnalyze();
        }matrix->WriteFiles(evt->GetEventID(), "Tracker/");
                
        // if(CHC){
        //     // Fill the matrix with the information: voxel and associated energy deposit
        //     // in the detector at the end of the event
        //     G4int HitCount = CHC -> entries();
        //     matrix->Initialize(HitCount);
        //     for (G4int h=0; h<HitCount; h++)
        //     {
        //         G4String parName = ((*CHC)[h])->GetParName();
        //         G4int i = ((*CHC)[h]) -> GetXID();
        //         G4int j = ((*CHC)[h]) -> GetYID();
        //         G4int k = ((*CHC)[h]) -> GetZID();
        //         G4double energyDeposit = ((*CHC)[h]) -> GetEdep();
        //         matrix -> Fill(parName,i, j, k, energyDeposit);  
        //         //G4cout<<"Calorimeter is here."<<G4endl;
        //     }
        //     matrix->hitAnalyze();
        // }matrix->WriteFiles(evt->GetEventID(), "Calorimeter/");
                
    }
}