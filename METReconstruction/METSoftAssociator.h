///////////////////////// -*- C++ -*- /////////////////////////////
// METSoftAssociator.h 
// Header file for class METSoftAssociator
//
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Author: P Loch, S Resconi, TJ Khoo, AS Mete
/////////////////////////////////////////////////////////////////// 
#ifndef METRECONSTRUCTION_METSOFTASSOCIATOR_H
#define METRECONSTRUCTION_METSOFTASSOCIATOR_H 1

// METReconstruction includes
#include "METReconstruction/METAssociator.h"

namespace met{
  class METSoftAssociator final
    : public METAssociator
  { 
    // This macro defines the constructor with the interface declaration
    ASG_TOOL_CLASS(METSoftAssociator, IMETAssocToolBase)


    /////////////////////////////////////////////////////////////////// 
    // Public methods: 
    /////////////////////////////////////////////////////////////////// 
    public: 

    // Constructor with name
    METSoftAssociator(const std::string& name);
    ~METSoftAssociator();

    // AsgTool Hooks
    StatusCode initialize();
    StatusCode finalize();

    /////////////////////////////////////////////////////////////////// 
    // Const methods: 
    ///////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////// 
    // Non-const methods: 
    /////////////////////////////////////////////////////////////////// 

    /////////////////////////////////////////////////////////////////// 
    // Private data: 
    /////////////////////////////////////////////////////////////////// 
    protected: 

    StatusCode executeTool(xAOD::MissingETContainer* metCont, xAOD::MissingETAssociationMap* metMap);
    StatusCode extractPFO(const xAOD::IParticle*,
			  std::vector<const xAOD::IParticle*>&,
			  const xAOD::PFOContainer*,
			  std::map<const xAOD::IParticle*,MissingETBase::Types::constvec_t>&,
			  const xAOD::Vertex*) const {return StatusCode::FAILURE;} // should not be called

    StatusCode extractTracks(const xAOD::IParticle*,
			     std::vector<const xAOD::IParticle*>&,
			     const xAOD::IParticleContainer*,
			     const xAOD::Vertex*) const {return StatusCode::FAILURE;} // should not be called
    StatusCode extractTopoClusters(const xAOD::IParticle*,
				   std::vector<const xAOD::IParticle*>&,
				   const xAOD::IParticleContainer*) const {return StatusCode::FAILURE;} // should not be called

    private:
 
    /// Default constructor: 
    METSoftAssociator();

    bool m_decorateSoftTermConst;
    std::string m_lcmodclus_key;
    std::string m_emmodclus_key;

  }; 

}

#endif //> !METRECONSTRUCTION_METSOFTASSOCIATOR_H
