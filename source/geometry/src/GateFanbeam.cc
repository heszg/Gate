/*----------------------
   GATE version name: gate_v6

   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/


#include "GateFanbeam.hh"
#include "GateFanbeamMessenger.hh"

#include "GateBox.hh"
#include "GateFanbeamHole.hh"
#include "GateObjectChildList.hh"
#include "GateMaterialDatabase.hh"
#include "GateBoxReplicaPlacement.hh"

#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"

//-------------------------------------------------------------------------------------------------------------------
GateFanbeam::GateFanbeam(const G4String& itsName,
							 G4bool acceptsChildren, 
		 			 		 G4int depth)
: GateBox(itsName,"Vacuum",41.,22.,4.,acceptsChildren,depth),
     m_FocalDistanceX(39.7*cm),
     m_SeptalThickness(0.1* cm),m_InnerRadius(0.05*cm),m_Height(4.*cm),
     m_DimensionX(41.0*cm),m_DimensionY(22.0*cm)
{ 
  PreComputeConstants();
  
  G4cout << " Constructor GateFanbeam - begin " << itsName << G4endl;
  G4cout << " m_InnerRadius = " << m_InnerRadius << G4endl;
  G4cout << " m_Material = " << mMaterialName << G4endl;
  
  m_lineInserter = new GateBoxReplicaPlacement(this, "lines", mMaterialName, m_DimensionX, l_Width, m_Height, l_Delta, kYAxis, l_N);
  GetCreator()->GetTheChildList()->AddChild(m_lineInserter);
   
  m_holeInserter = new GateFanbeamHole( "hole", "Air", m_FocalDistanceX, m_SeptalThickness,
  		                                          m_InnerRadius, m_Height, m_DimensionX, l_Width );
  
  m_lineInserter->GetCreator()->GetTheChildList()->AddChild(m_holeInserter);

  m_messenger = new GateFanbeamMessenger(this);
  
  G4cout << " Constructor GateFanbeam - end " << G4endl;
}
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
GateFanbeam::GateFanbeam(const G4String& itsName,const G4String& itsMaterialName,
     G4double itsFocalDistanceX,G4double itsSeptalThickness,G4double itsInnerRadius,
     G4double itsHeight,G4double itsDimensionX,G4double itsDimensionY)
     : GateBox(itsName,itsMaterialName,itsDimensionX,itsDimensionY,itsHeight,false,false),
     m_FocalDistanceX(itsFocalDistanceX),
     m_SeptalThickness(itsSeptalThickness),m_InnerRadius(itsInnerRadius),m_Height(itsHeight),
     m_DimensionX(itsDimensionX),m_DimensionY (itsDimensionY)
{
  PreComputeConstants();
  
  G4cout << " Constructor GateFanbeam - begin " << itsName << G4endl;
  G4cout << " m_InnerRadius = " << m_InnerRadius << G4endl;
  G4cout << " m_Material = " << mMaterialName << G4endl;
  
  m_lineInserter = new GateBoxReplicaPlacement(this, "lines", mMaterialName, m_DimensionX, l_Width, m_Height, l_Delta, kYAxis, l_N);
  GetCreator()->GetTheChildList()->AddChild(m_lineInserter);
  
  m_holeInserter = new GateFanbeamHole( "hole", "Air", m_FocalDistanceX, m_SeptalThickness,
  		                                          m_InnerRadius, m_Height, m_DimensionX, l_Width );
  
  m_lineInserter->GetCreator()->GetTheChildList()->AddChild(m_holeInserter);

  m_messenger = new GateFanbeamMessenger(this);
  
  G4cout << " Constructor GateFanbeam - end " << G4endl;
}
//-------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------------------------
GateFanbeam::~GateFanbeam()
{
  delete m_messenger;
}
//-------------------------------------------------------------------------------------------------------------------

void GateFanbeam::PreComputeConstants()
{
  l_Width  = 2. * (m_InnerRadius + m_SeptalThickness);
  l_Delta  = 2. * (m_InnerRadius + m_SeptalThickness);
  l_N      = int ( m_DimensionY / l_Delta );
}

//-------------------------------------------------------------------------------------------------------------------
void GateFanbeam::ResizeCollimator()
{
  G4cout << "[GateFanbeam::ResizeCollimator] material = " << mMaterialName << "\n" ; 
  
  GetCollimatorCreator()->SetBoxXLength(m_DimensionX);
  GetCollimatorCreator()->SetBoxYLength(m_DimensionY);
  GetCollimatorCreator()->SetBoxZLength(m_Height);
  GetCollimatorCreator()->SetMaterialName(mMaterialName);

  PreComputeConstants();
  
  m_lineInserter->Update(mMaterialName, m_DimensionX, l_Width, m_Height, l_Delta, l_N);
  m_holeInserter->ResizeHole(m_FocalDistanceX, m_SeptalThickness, m_InnerRadius, m_Height, m_DimensionX, l_Width);
}
//-------------------------------------------------------------------------------------------------------------------
