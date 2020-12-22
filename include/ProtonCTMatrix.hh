#ifndef ProtonCTMatrix_H
#define ProtonCTMatrix_H 1
#include <G4ParticleDefinition.hh>
#include "globals.hh"
#include <vector>
#include <array>
#include <string>
#include <fstream>
#include "g4csv.hh"


#ifndef ProtonCTANALYSISMANAGER_HH
#define ProtonCTANALYSISMANAGER_HH 1

class ProtonCTAnalysisFileMessenger;

/**
 * A class for connecting the simulation to an analysis package.
 */
class ProtonCTAnalysisManager
{
private:
    /**
     * Analysis manager is a singleton object (there is only one instance).
     * The pointer to this object is available through the use of the method GetInstance();
     *
     * @see GetInstance
     */
    ProtonCTAnalysisManager();
    
    
    
public:
    ~ProtonCTAnalysisManager();
    
    /**
     * Get the pointer to the analysis manager.
     */
    static ProtonCTAnalysisManager* GetInstance();
    
    
    
    static ProtonCTAnalysisManager* instance;
    ProtonCTAnalysisFileMessenger* fMess;
    
};

#endif

class ProtonCTMatrix 
{
public:
  ~ProtonCTMatrix();
  ProtonCTMatrix();
  // Get object instance only
  static ProtonCTMatrix* GetInstance();

  void Clear();
  void Initialize(G4int);
  void hitAnalyze();

  void WriteFiles(G4int,G4String);
   
  // Store single matrix data to filename 
  void StoreMatrix(G4String file, void* data,size_t psize);
  void Fill(G4String,G4int,G4int,G4int,G4double);

private:
  static ProtonCTMatrix* instance;
  G4int Count;
  G4int Nhits;
  G4int E_th;
  G4String* parName;
  G4int** matrixID;
  G4int** hitID;
  G4double* Edep;
  G4double* Ehit;
  G4String stdFile, filename;
  std::ofstream ofs;
};
#endif