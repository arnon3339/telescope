
#ifndef ProtonCTInteractionParameters_H
#define ProtonCTInteractionParameters_H 1

#include "G4EmCalculator.hh"
#include "G4NistMaterialBuilder.hh"
#include "G4NistElementBuilder.hh"

class ProtonCTDetectorConstruction;
class ProtonCTParameterMessenger; 
class G4ParticleDefinition;
class G4Material;

class ProtonCTInteractionParameters : public G4EmCalculator 
{
public:

  ProtonCTInteractionParameters(G4bool);
  ~ProtonCTInteractionParameters();

  // Get data for Mass SP    
  // G4NistMaterialBuilder class materials
  // User must provide: material kinetic energy lower limit, kinetic energy upper limit, number of points to retrieve,
  // [particle], [output filename].

  G4bool GetStoppingTable (const G4String& vararg);
  G4double GetStopping (G4double energy,
			const G4ParticleDefinition*, 
			const G4Material*, 
			G4double density = 0.);

  void ListOfNistMaterials (const G4String& vararg);
  void BeamOn();
  bool ParseArg (const G4String& vararg);	

private:
  G4Material* GetNistMaterial(G4String material);
  G4NistElementBuilder* nistEle;
  G4NistMaterialBuilder* nistMat;
  std::ofstream outfile;
  std::ostream data;
  G4Material* Pmaterial;
  ProtonCTParameterMessenger* pMessenger; 
  bool beamFlag;

  G4double kinEmin, kinEmax, npoints;
  G4String particle, material, filename; 
  G4double dedxtot, density;
  std::vector<G4double> energy;
  std::vector<G4double> massDedx;

};
#endif