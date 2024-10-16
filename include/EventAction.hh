#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction
{
  public:
    EventAction() = default;
   ~EventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void   EndOfEventAction(const G4Event*) override;
    
    inline void AddEdep(G4double Edep)    {fTotalEnergyDeposit += Edep;};
    inline void AddNIEL(G4double Edep)    {fNIEL += Edep;};
    inline G4double GetEnergyDeposit()    {return fTotalEnergyDeposit;};
    
  private:
    G4double fTotalEnergyDeposit = 0.;
    G4double fNIEL = 0.;
};

#endif