//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// GRINS - General Reacting Incompressible Navier-Stokes
//
// Copyright (C) 2014-2015 Paul T. Bauman, Roy H. Stogner
// Copyright (C) 2010-2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-


//GRINS
#include "grins/physics.h"
#include "grins/velocity_fe_variables.h"
#include "grins/common.h"

//#include "grins/var_typedefs.h"
//#include "grins/solid_mechanics_variables.h"
#include "grins/solid_mechanics_fe_variables.h"

#include "libmesh/fem_context.h"

namespace GRINS
{

  //! Physics class for Immersed Boundary Method
  /*!
    This physics class implements the classical Immersed  Boundary Method.
    This is a templated class, the class SolidMechanics can be instantiated as a specific type
    (right now:ElasticCable or ElasticMembrane)
   */

  template<typename SolidMechanics>
  class ImmersedBoundary : public Physics
  {
  public:

    ImmersedBoundary(const std::string& my_physics_name, const GetPot& input);

    ~ImmersedBoundary(){};

    //! Initializes the FE Variables    
    virtual void init_variables( libMesh::FEMSystem* system );

    //! Sets velocity variables to be time-evolving
    virtual void set_time_evolving_vars( libMesh::FEMSystem* system );

    // Context initialization
    virtual void init_context( AssemblyContext& context );

    virtual void element_time_derivative( bool compute_jacobian, AssemblyContext& context,
                                          CachedValues& cache );

    //! function to pull material density from the input file
    void get_material_density();
    
  protected:

    //! Physical dimension of problem
    /*! \todo Do we really need to cache this? */
    unsigned int _dim;

    //! FE variables for the flow and for the solid
    VelocityFEVariables _flow_vars;
    
    //wtf is wrong with these
    SolidMechanicsFEVariables _disp_vars;  

    //! The solidmechanics class
    SolidMechanics _solid_mech;
   
  private:
    ImmersedBoundary();


  };

} //End namespace block
