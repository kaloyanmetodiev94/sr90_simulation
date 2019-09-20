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
// $Id: B2RunAction.cc 66536 2012-12-19 14:32:36Z ihrivnac $
//
/// \file B2RunAction.cc
/// \brief Implementation of the B2RunAction class

#include "B2RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "g4csv.hh"
#include <sstream>
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2RunAction::B2RunAction()
 : G4UserRunAction()
{ 
  // set printing event number per each 100 events
  G4RunManager::GetRunManager()->SetPrintProgress(1000);     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2RunAction::~B2RunAction()
{
   delete G4CsvAnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2RunAction::BeginOfRunAction(const G4Run* run)
{ 
  _anman=G4CsvAnalysisManager::Instance();
  auto runid= run->GetRunID();
  std::ostringstream oss;
  oss <<"hits_"<<runid;

  if (_anman){
	_anman->SetFileName(oss.str());
	_anman->OpenFile(oss.str());
  }

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  auto sdm=G4SDManager::GetSDMpointer();
  auto hctable=sdm->GetHCtable();

  auto hcname=hctable->GetHCname(0);
  _tupid = _anman->CreateNtuple(hcname,hcname);
  _anman->CreateNtupleIColumn(_tupid,"evid");
  _anman->CreateNtupleDColumn(_tupid,"Etot");
  _anman->CreateNtupleIColumn(_tupid,"PDG");
  _anman->FinishNtuple(_tupid);
  _anman->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2RunAction::EndOfRunAction(const G4Run* run)
{
	if(_anman)
	{
	G4cout<<"writing hits to file: " << _anman -> GetFileName() <<G4endl;
	_anman->Write();
	_anman->CloseFile();

	}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VAnalysisManager * B2RunAction::getAnman()
{
	return _anman;
}

G4int B2RunAction::getTupid()
{
	return _tupid;
}
