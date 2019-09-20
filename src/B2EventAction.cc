//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B2EventAction.cc 69652 2013-05-10 09:05:11Z ihrivnac $
//
/// \file B2EventAction.cc
/// \brief Implementation of the B2EventAction class

#include "B2EventAction.hh"

#include "g4csv.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "B2TrackerHit.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::B2EventAction(B2RunAction* act)
: G4UserEventAction(),_runact(act)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::~B2EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::EndOfEventAction(const G4Event* event)
{

  G4int tupidit = _runact->getTupid();
  G4VAnalysisManager* anman = _runact->getAnman();

  // get number of stored trajectories

  //G4TrajectoryContainer* trajectoryContainer = event->GetTrajectoryContainer();
  //G4int n_trajectories = 0;
  //if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // periodic printing

  G4int eventID = event->GetEventID();
  //  G4cout << ">>> Event: " << eventID  << G4endl;
  //  if ( trajectoryContainer ) {
  //   G4cout << "    " << n_trajectories << " trajectories stored in this event." << G4endl;
  //  }
    G4VHitsCollection* hc = event->GetHCofThisEvent()->GetHC(0);
    G4cout << "    " << hc->GetSize() << " hits stored in this event" << G4endl;


    if (anman){
	
	    auto antp = anman->GetType();
	    anman->OpenFile();

	    for(auto i=0u; i < hc->GetSize(); i++)
		{
		auto ht = static_cast<B2TrackerHit*>(hc->GetHit(i));
		G4cout<<"HIT ENERGY/PDG: " << ht->GetEtot() << "/" << ht->GetPDG() << G4endl;
		anman->FillNtupleIColumn(tupidit,0,event->GetEventID());
		anman->FillNtupleDColumn(tupidit,1,ht->GetEtot());
		anman->FillNtupleIColumn(tupidit,2,ht->GetPDG());
		anman->AddNtupleRow(tupidit);
		}
    }
    
 
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
