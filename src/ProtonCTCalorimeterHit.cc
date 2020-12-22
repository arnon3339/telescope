#include "ProtonCTCalorimeterHit.hh"


//**********************MT
G4ThreadLocal G4Allocator<ProtonCTCalorimeterHit>* ProtonCTCalorimeterHitAllocator=0;
//**********************MT

ProtonCTCalorimeterHit::ProtonCTCalorimeterHit()
: G4VHit()
{
 energyDeposit = 0;
}

ProtonCTCalorimeterHit::~ProtonCTCalorimeterHit()
{
}

ProtonCTCalorimeterHit::ProtonCTCalorimeterHit(const ProtonCTCalorimeterHit& right)
  : G4VHit()
{
  parName = right.parName;
 xHitID = right.xHitID;
 zHitID = right.zHitID;
 yHitID = right.yHitID;
 energyDeposit = right.energyDeposit;
}

const ProtonCTCalorimeterHit& ProtonCTCalorimeterHit::operator=(const ProtonCTCalorimeterHit& right)
{
  parName = right.parName;
 xHitID = right.xHitID;
 zHitID = right.zHitID;
 yHitID = right.yHitID;
 energyDeposit = right.energyDeposit;
 return *this;
}

G4int ProtonCTCalorimeterHit::operator==(const ProtonCTCalorimeterHit& right) const
{
 return((parName==right.parName)&&(xHitID==right.xHitID)&&(zHitID==right.zHitID)&&(yHitID==right.yHitID));
}

