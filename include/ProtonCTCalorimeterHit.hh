#ifndef ProtonCTCalorimeterHit_h
#define ProtonCTCalorimeterHit_h 1


#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"


class ProtonCTCalorimeterHit : public G4VHit
{
public:
  ProtonCTCalorimeterHit();
  ProtonCTCalorimeterHit(const ProtonCTCalorimeterHit&);
  ProtonCTCalorimeterHit(G4String, G4int, G4int, G4int, G4double);
  virtual ~ProtonCTCalorimeterHit();
 
 
  const ProtonCTCalorimeterHit& operator=(const ProtonCTCalorimeterHit&);
 
  G4int operator==(const ProtonCTCalorimeterHit&) const;

//******************************MT
inline void* operator new(size_t);
inline void operator delete(void*);
//******************************MT

private:
  G4String parName;
  G4int xHitID; // Hit x voxel 
  G4int zHitID; // Hit z voxel
  G4int yHitID; // Hit y voxel 
  G4double energyDeposit; // Energy deposit associated with the hit

public:
  // Methods to get the information - energy deposit and associated
  // position in the phantom - of the hits stored in the hits collection  
 
  inline G4String GetParName()
  {return parName;}

  inline G4int GetXID() // Get x index of the voxel 
  {return xHitID;}

  inline G4int GetZID() // Get y index of the voxel   
  {return zHitID;}

  inline G4int GetYID() // Get z index of the voxel  
  {return yHitID;}
   
  inline G4double GetEdep() // Get energy deposit
  {return energyDeposit;}
 
  // Methods to store the information of the hit ( energy deposit, position in the phantom )
  // in the hits collection

  inline void SetHit(G4String Name,G4int xx, G4int yy, G4int zz, G4double eDep)
  {
    parName = Name;
    xHitID = xx;
    yHitID = yy;
    zHitID = zz;
    energyDeposit = eDep;
  }
};

typedef G4THitsCollection<ProtonCTCalorimeterHit> ProtonCTCalorimeterHitsCollection;
//******************************MT
extern G4ThreadLocal G4Allocator<ProtonCTCalorimeterHit>* ProtonCTCalorimeterHitAllocator;
//******************************MT

inline void* ProtonCTCalorimeterHit::operator new(size_t)
{
 
  
 if(!ProtonCTCalorimeterHitAllocator) 
  ProtonCTCalorimeterHitAllocator= new G4Allocator<ProtonCTCalorimeterHit>;
 void *aHit;

 aHit = (void *) ProtonCTCalorimeterHitAllocator->MallocSingle();
 return aHit;

}

inline void ProtonCTCalorimeterHit::operator delete(void *aHit)
{
if(!ProtonCTCalorimeterHitAllocator) 
  ProtonCTCalorimeterHitAllocator= new G4Allocator<ProtonCTCalorimeterHit>;

ProtonCTCalorimeterHitAllocator->FreeSingle((ProtonCTCalorimeterHit*) aHit);
}

#endif
