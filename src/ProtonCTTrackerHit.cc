#include "ProtonCTTrackerHit.hh"


//**********************MT
G4ThreadLocal G4Allocator<ProtonCTTrackerHit>* ProtonCTTrackerHitAllocator=0;
//**********************MT

ProtonCTTrackerHit::ProtonCTTrackerHit()
: G4VHit()
{
 energyDeposit = 0;
}

ProtonCTTrackerHit::~ProtonCTTrackerHit()
{
}

ProtonCTTrackerHit::ProtonCTTrackerHit(const ProtonCTTrackerHit& right)
  : G4VHit()
{
  parName = right.parName;
 xHitID = right.xHitID;
 zHitID = right.zHitID;
 yHitID = right.yHitID;
 energyDeposit = right.energyDeposit;
}

const ProtonCTTrackerHit& ProtonCTTrackerHit::operator=(const ProtonCTTrackerHit& right)
{
  parName = right.parName;
 xHitID = right.xHitID;
 zHitID = right.zHitID;
 yHitID = right.yHitID;
 energyDeposit = right.energyDeposit;
 return *this;
}

G4int ProtonCTTrackerHit::operator==(const ProtonCTTrackerHit& right) const
{
 return((parName==right.parName)&&(xHitID==right.xHitID)&&(zHitID==right.zHitID)&&(yHitID==right.yHitID));
}

