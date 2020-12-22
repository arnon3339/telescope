#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "ProtonCTEventAction.hh"
#include "ProtonCTPhysicsList.hh"
#include "ProtonCTPrimaryGeneratorAction.hh"
#include "ProtonCTRunAction.hh"
//#include "ProtonCTMatrix.hh"
#include "Randomize.hh"

#include "G4UImessenger.hh"
#include "globals.hh"
#include "ProtonCTSteppingAction.hh"
#include "ProtonCTDetectorConstruction.hh"

#include "G4ScoringManager.hh"
#include "G4ParallelWorldPhysics.hh"
#include <time.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <iostream>

//************************MT*********************
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "ProtonCTActionInitialization.hh"


#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"


//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc ,char ** argv)
{
    if (mkdir("Output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1)
    {
        std::string checkDelDir = "";
        while(1)
        {
            std::cout<<"The \033[1mOutput\033[0m directory now contrains the previous data.\nDo you really want to remove it? [No[n]/Yes[y]] : ";

            getline (std::cin, checkDelDir);
            if (checkDelDir == "N" || checkDelDir == "n" )
                {
                    std::cout<<"\nPlease save your old data from \033[1mOutput\033[0m directory in other place.\nTo get the new data, the program must remove the old one.\nSee Ya :)"<<std::endl;
                    return 0;
                }
            else if (checkDelDir == "y" || checkDelDir == "Y")
            {
                system("rm -r Output");
                std::cout<<"\nThe \033[1mOutput\033[0m directory is recreated."<<std::endl;
                break;
            }
            else
            {
                std::cout<<"\nYou input the wrong character, please try again.\n"<<std::endl;
                continue;
            }
        }
    }
    mkdir("Output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("Output/HitCollection", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("Output/DigitalCollection", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("Output/HitCollection/Tracker", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("Output/DigitalCollection/Tracker", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("Output/HitCollection/Calorimeter", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir("Output/DigitalCollection/Calorimeter", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    // Set the Random engine
    // The following guarantees random generation also for different runs
    // in multithread
    CLHEP::RanluxEngine defaultEngine( 1234567, 4 );
    G4Random::setTheEngine( &defaultEngine );
    G4int seed = time( NULL );
    G4Random::setTheSeed( seed );
    
#ifdef G4MULTITHREADED
    
    G4MTRunManager* runManager = new G4MTRunManager;
#else
    G4RunManager* runManager = new G4RunManager;
#endif
    
    G4ScoringManager *scoringManager = G4ScoringManager::GetScoringManager();
    scoringManager->SetVerboseLevel(1);

    ProtonCTDetectorConstruction* detector = new ProtonCTDetectorConstruction();
    
    runManager -> SetUserInitialization(detector);

    // Initialize command based scoring
    G4ScoringManager::GetScoringManager();
    
    // Initialize the physics
    G4PhysListFactory factory;
    G4VModularPhysicsList* phys = 0;
    G4String physName = "";
    
    // Physics List name defined via environment variable
    char* path = getenv("PHYSLIST");
    if (path) { physName = G4String(path); }
    
    if(physName != "" && factory.IsReferencePhysList(physName))
    {
        phys = factory.GetReferencePhysList(physName);
    }
    if (phys)
    {
        G4cout << "Going to register G4ParallelWorldPhysics" << G4endl;
        phys->RegisterPhysics(new G4ParallelWorldPhysics("DetectorROGeometry"));
    }
    else
    {
        G4cout << "Using ProtonCTPhysicsList()" << G4endl;
        phys = new ProtonCTPhysicsList();
    }
    
    runManager->SetUserInitialization(phys);
    
    //************************MT
    runManager->SetUserInitialization(new ProtonCTActionInitialization);

    G4cout << "Going to register G4ParallelWorldPhysics" << G4endl;
    
    // Get the pointer to the visualization manager
    G4VisManager* visManager = new G4VisExecutive;
    visManager -> Initialize();

    
    // Get the pointer to the User Interface manager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (argc == 1)   // Define UI session for interactive mode.
    {
        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        G4cout << " UI session starts ..." << G4endl;
        
        UImanager -> ApplyCommand("/control/execute defaultMacro.mac");
        
        
        ui -> SessionStart();
        delete ui;
    }
    else           // Batch mode
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager -> ApplyCommand(command+fileName);
    }
    /*
    // Job termination
    if ( ProtonCTMatrix * pMatrix = ProtonCTMatrix::GetInstance() )
    {
        // pMatrix -> TotalEnergyDeposit();
        pMatrix -> StoreDoseFluenceAscii();
        
    }
    
    if (ProtonCTLet *let = ProtonCTLet::GetInstance())
        if(let -> doCalculation)
        {
            let -> LetOutput(); 	// Calculate let
            let -> StoreLetAscii(); // Store it
        }*/
    
    delete visManager;

    
   // delete geometryMessenger;
    //delete geometryController;
    //delete pInteraction;
    delete runManager;
    //delete analysis;
    return 0;
    
}
