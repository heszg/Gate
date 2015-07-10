/*
 * GateTessellatedSolid.hh
 *
 *  Created on: 2015.07.01.
 *      Author: heszg
 */

#ifndef GATETESSELLATEDSOLID_H
#define GATETESSELLATEDSOLID_H

#include "globals.hh"
#include "GateVVolume.hh"
#include "GateVolumeManager.hh"
#include "G4TwoVector.hh"
#include "G4ThreeVector.hh"
#include "G4VisExtent.hh"
#include "G4TessellatedSolid.hh"

class G4TessellatedSolid;
class GateTessellatedSolidMessenger;

typedef std::vector<int> GateFacetVertices;
typedef std::vector< GateFacetVertices > GateFacetVerticesList;

class GateTessellatedSolid : public GateVVolume
{
public:
  //! Constructor
  GateTessellatedSolid(const G4String& itsName,
                 G4bool acceptsChildren=true,
                 G4int depth=0);

  GateTessellatedSolid(const G4String& itsName,
                 const G4String& itsMaterialName,
				 G4ThreeVectorList itsVertices,
				 GateFacetVerticesList itsFacets,
                 G4bool acceptsChildren=true,
                 G4int depth=0);
  //! Destructor
  virtual ~GateTessellatedSolid();

  FCT_FOR_AUTO_CREATOR_VOLUME(GateTessellatedSolid)

  virtual G4LogicalVolume* ConstructOwnSolidAndLogicalVolume(G4Material* mater, G4bool flagUpdateOnly);

  virtual void DestroyOwnSolidAndLogicalVolume();

  /*! \brief Implementation of the virtual method DescribeMyself(), to print-out
    \brief a description of the creator

    \param level: the print-out indentation (cosmetic parameter)
  */
  virtual void DescribeMyself(size_t level);

  inline G4double GetHalfDimension(size_t axis) {
    G4VisExtent extent = m_TessellatedSolid_solid->GetExtent();
    if (axis==0) {
		return (extent.GetXmax() - extent.GetXmin())/2.0;
    } else if (axis==1) {
		return (extent.GetYmax() - extent.GetYmin())/2.0;
    } else if (axis==2) {
		return (extent.GetZmax() - extent.GetZmin())/2.0;
    }
    return 0.0;
  }

  //! Overload of the dummy virtual method ComputeMyOwnVolume() defined by the base-class
  //! Returns the volume of the solid
  G4double ComputeMyOwnVolume()  const;

  //! \name getters and setters
  //@{
  inline G4ThreeVectorList GetVertices() 	{ return m_vertices; }
  inline GateFacetVerticesList GetFacets() 	{ return m_facets; }
  inline G4ThreeVector GetCenter()	{ return m_center; }

  void SetVertices(G4ThreeVectorList val)	{ m_vertices = val; }
  void SetVertex(G4int index, G4ThreeVector val)	{ m_vertices[index] = val; }
  void SetVertex(G4int index, G4double x, G4double y, G4double z)	{ m_vertices[index].set(x, y, z); }

  void SetFacets(GateFacetVerticesList val)	{ m_facets = val; }
  void SetFacets(G4int index, GateFacetVertices val)	{ m_facets[index] = val; }
  void SetFacets(G4int index, G4int vertexIndex, G4int val)	{ m_facets[index][vertexIndex] = val; }

  void SetCenter(G4ThreeVector val)	{ m_center = val; }

  //@}

  /**
	\brief Add a new vertex to the solid
	\param val	is the coordinates of the vertex
	\return the ID of the new vertex
  */
  G4ThreeVectorList::size_type  AddVertex(G4ThreeVector val)	
  { 
	  m_vertices.push_back( val );
	  return m_vertices.size()-1;
  }


  /**
	\brief Add a new facet to the solid
	\param val	is the list of vertex indexes of the new facet
	\return the ID of the new facet
  */
  GateFacetVerticesList::size_type  AddFacet( GateFacetVertices val )	
  { 
	  m_facets.push_back( val );
	  return m_facets.size()-1;
  }

  /**
	\brief Add a new facet to the solid
	\param val	is the list of vertex indexes of the new facet
	\return the ID of the new facet
  */
  GateFacetVerticesList::size_type  AddFacet( G4ThreeVector val )	
  { 
	  GateFacetVertices tmp(3, 0);
	  tmp[0] = val.x();
	  tmp[1] = val.y();
	  tmp[2] = val.z();
	  m_facets.push_back( tmp );
	  return m_facets.size()-1;
  }



private:
  //! \name own geometry
  //@{
  G4TessellatedSolid*			m_TessellatedSolid_solid;       	    //!< Solid pointer
  G4LogicalVolume*				m_TessellatedSolid_log; 	      	    //!< logical volume pointer
  //@}

  //! \name parameters
  //@{
  G4ThreeVector m_center;		//!< center of the solid
  G4ThreeVectorList m_vertices; //!< vertices
  GateFacetVerticesList m_facets; //!< facets
  //@}

  //! Messenger
  GateTessellatedSolidMessenger* m_Messenger;

};

MAKE_AUTO_CREATOR_VOLUME(tessellatedsolid,GateTessellatedSolid)


#endif /* GATETESSELLATEDSOLID_H */
