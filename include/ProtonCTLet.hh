#ifndef ProtonCTLet_h
#define ProtonCTLet_h 1
#endif

#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include <fstream>
#include <vector>
#include <string>

#include "g4csv.hh"
#include "ProtonCTMatrix.hh"
struct ionLet 
{ 
    G4bool isPrimary;	    // True if particle is primary
    G4int PDGencoding;      // Particle data group id for the particle
    G4String fullName;      // AZ[excitation energy]: like He3[1277.4], He4[0.0], Li7[231.4], ...
    G4String name;          // simple name without excitation energy: He3, He4, Li7, ...
    G4int Z;                // atomic number
    G4int A;		    // mass number
    G4double *letDN , *letDD; // Track averaged LET and Dose averaged LET 
    //friend bool operator<(const ionLet& a, const ionLet& b) {return (a.Z == b.Z) ? b.A < a.A : b.Z < a.Z ;}
    G4bool operator<(const ionLet& a) const{return (this->Z == a.Z) ? this-> A < a.A : this->Z < a.Z ;}
    // For isotopes sort by the mass number, else sort by the atomic one.
};

class G4Material;
class ProtonCTMatrix;
class ProtonCTPrimaryGeneratorAction;
class ProtonCTInteractionParameters;
class ProtonCTDetectorConstruction;

class ProtonCTLet
{
    private:
	ProtonCTLet(ProtonCTDetectorConstruction*); 

    public:
	~ProtonCTLet();
	static ProtonCTLet* GetInstance(ProtonCTDetectorConstruction*);
	static ProtonCTLet* GetInstance();
	static G4bool doCalculation;
	void Initialize();
	void Clear();

void Fill(G4int i, G4int j, G4int k, G4double DE, G4double DX);
void FillEnergySpectrum (G4int trackID,
		 		G4ParticleDefinition* particleDef,
				/*G4double kinEnergy,*/
				G4double DE,
				G4double DX,
				G4int i, G4int j, G4int k); 
	void LetOutput(); 
	void StoreLetAscii();


    private:
	static ProtonCTLet *instance;
	ProtonCTPrimaryGeneratorAction* pPGA;
	// Detector material
	G4Material* detectorMat;  
	G4double density;
	G4String filename;

	std::ofstream ofs;
        std::ofstream stopFile;
	ProtonCTMatrix *matrix;
	G4int nVoxels, numberOfVoxelAlongX, numberOfVoxelAlongY, numberOfVoxelAlongZ ;
	G4double primaryEnergy, energyLimit, binWidth; 
	G4int nBins;
	G4double  nT, dT, nD, dD;
	G4double  nSecondaryT, nSecondaryD, dSecondaryT, dSecondaryD;
	G4double  nPrimaryT, nPrimaryD, dPrimaryT, dPrimaryD ;

	G4double *secondaryLetT,  *secondaryLetD, *totalLetT,  *DtotalLetD, *totalLetD;
	G4String nome_file;

	std::vector<ionLet> ionLetStore;
};