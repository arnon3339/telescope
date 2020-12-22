#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "ProtonCTMatrix.hh"
#include "ProtonCTPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "ProtonCTSteppingAction.hh"

#include "ProtonCTAnalysisFileMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include <time.h>
#include <string>
#include <math.h>

ProtonCTAnalysisManager* ProtonCTAnalysisManager::instance = 0;
ProtonCTAnalysisManager::ProtonCTAnalysisManager()


{
    fMess = new ProtonCTAnalysisFileMessenger(this);
}
ProtonCTAnalysisManager::~ProtonCTAnalysisManager()
{
    delete fMess;
}

ProtonCTAnalysisManager* ProtonCTAnalysisManager::GetInstance(){
    
    if (instance == 0) instance = new ProtonCTAnalysisManager;
    return instance;
}



ProtonCTMatrix* ProtonCTMatrix::instance = NULL;


// Only return a pointer to matrix


ProtonCTMatrix* ProtonCTMatrix::GetInstance()
{
    return instance;
}

ProtonCTMatrix::ProtonCTMatrix(){}
/////////////////////////////////////////////////////////////////////////////
ProtonCTMatrix::~ProtonCTMatrix()
{
    for (G4int i = 0; i < Nhits; i++)
    {
        delete matrixID[i];
        delete hitID[i];
    }
    delete[] matrixID;
    delete[] hitID;

    delete parName;
    delete Edep;
    delete Ehit;
}

void ProtonCTMatrix::Initialize(G4int nhits)
{
    E_th = 100. *keV;
    Count = 0;
    Nhits = nhits;
    matrixID = new G4int*[Nhits];
    hitID = new G4int*[Nhits];
    parName = new G4String[Nhits];
    Edep = new G4double[Nhits];
    Ehit = new G4double[Nhits];
    for(G4int i = 0; i < Nhits; i++)
    {
        matrixID[i] = new G4int[3];
        hitID[i] = new G4int[3];
    }
    for(G4int i = 0; i < Nhits; i++)
    {
        for(G4int j = 0; j < 3; j++)
        {
            matrixID[i][j] = -1;
            hitID[i][j] = -1;
        }
        parName[i] = "";
        Edep[i] = 0.;
        Ehit[i] = 0.;
    }
        
}


void ProtonCTMatrix::Fill(G4String name,G4int ii, G4int jj, G4int kk, G4double energyDeposit)
{
    parName[Count] = name;
    matrixID[Count][0] = ii;
    matrixID[Count][1] = jj;
    matrixID[Count][2] = kk;
    Edep[Count] = energyDeposit;

    ++Count; 
}

void ProtonCTMatrix::hitAnalyze()
{
    G4int num = -1;
    for (G4int i = 0; i < Nhits; i++)
    {
        for (G4int j = 0; j <= num + 1 ; j++)
        {
            if ((hitID[j][2] == matrixID[i][2]) &&
                (abs(hitID[j][0] - matrixID[i][0]) < 3) && 
                (abs(hitID[j][1] - matrixID[i][1]) < 3))
            {
                //G4cout<<"Break is here."<<num<<G4endl;
                break;
            }
            if (j == num + 1)
            {
                num++;
                hitID[num][0] = matrixID[i][0]; 
                hitID[num][1] = matrixID[i][1];
                hitID[num][2] = matrixID[i][2];
                Ehit[num] = Edep[i];
                for (G4int k = i+1; k < Nhits; k++)
                {
                    
                    if ((matrixID[i][2] == matrixID[k][2]) &&
                        (abs(matrixID[i][0] - matrixID[k][0]) < 3) &&
                        (abs(matrixID[i][1] - matrixID[k][1]) < 3))
                        {
                        if (Edep[k] > Ehit[num])
                        {
                            
                            hitID[num][0] = matrixID[k][0]; 
                            hitID[num][1] = matrixID[k][1];
                            hitID[num][2] = matrixID[k][2];
                        }
                        Ehit[num] += Edep[k]; 
                        }
                }
                break;
                //G4cout<<hitID[num][0]<<","<<hitID[num][1]<<","<<hitID[num][2]<<","<<Ehit[num]<<G4endl;
            }

        }
    }
}

void ProtonCTMatrix::WriteFiles(G4int eID, G4String detectorName)
{
    std::string dName = detectorName;
    char file[25];       
    sprintf(file,"_part%d_GW%d.csv",int(eID/1000),G4Threading::G4GetThreadId());
    std::string File = file;
    std::string OutDir = "Output/";
    std::string RawDir = "Raw/";
    File = OutDir + RawDir + detectorName + File;
    ofs.open(File.c_str(), std::ios::app);
    if (ofs.is_open())
    {
        for(G4int i = 0; i < Nhits; i++)
            ofs <<eID<<","<<parName[i]<<","<<matrixID[i][0] << ',' << matrixID[i][1] << ',' << matrixID[i][2] << ',' << Edep[i] << G4endl;
    }
    ofs.close();

    sprintf(file,"_part%d_GW%d.csv",int(eID/10000),G4Threading::G4GetThreadId());
    File = file;
    std::string HitsDir = "HitCollection/";
    File = OutDir + HitsDir + detectorName + File;
    ofs.open(File.c_str(), std::ios::app);
    if (ofs.is_open())
    {
        for(G4int i = 0; i < Nhits; i++)
        {
            if (hitID[i][0] == -1)
                break;
            ofs <<eID<<","<<hitID[i][0] << ',' << hitID[i][1] << ',' << hitID[i][2] << ',' << Ehit[i] << G4endl;
        }
            
    }
    ofs.close();

    if (detectorName == "Tracker/")
    {
        sprintf(file,"_part%d_GW%d.csv",int(eID/10000),G4Threading::G4GetThreadId());
        File = file;
        std::string DigiDir = "DigitalCollection/";
        File = OutDir + DigiDir + detectorName + File;
        ofs.open(File.c_str(), std::ios::app);
        if (ofs.is_open())
        {
            for(G4int i = 0; i < Nhits; i++)
            {
                if (hitID[i][0] == -1)
                    break;
                if (Ehit[i] > 100.*keV)
                    ofs <<eID<<","<<hitID[i][0] << ',' << hitID[i][1] << ',' << hitID[i][2] << G4endl;
            }
                
        }
        ofs.close();
    }
    else
    {
        sprintf(file,"_part%d_GW%d.csv",int(eID/10000),G4Threading::G4GetThreadId());
        File = file;
        std::string DigiDir = "DigitalCollection/";
        File = OutDir + DigiDir + detectorName + File;
        ofs.open(File.c_str(), std::ios::app);
        if (ofs.is_open())
        {
            for(G4int i = 0; i < Nhits; i++)
            {
                if (hitID[i][0] == -1)
                    break;
                ofs <<eID<<","<<hitID[i][0] << ',' << hitID[i][1] << ',' << hitID[i][2]<<","<<Ehit[i] << G4endl;
            }
                
        }
        ofs.close();
    }
    

    
}

