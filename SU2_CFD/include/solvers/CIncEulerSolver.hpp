/*!
 * \file CIncEulerSolver.hpp
 * \brief Headers of the CIncEulerSolver class
 * \author F. Palacios, T. Economon, T. Albring
 * \version 7.0.0 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation 
 * (http://su2foundation.org)
 *
 * Copyright 2012-2019, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "CSolver.hpp"
#include "../variables/CIncEulerVariable.hpp"

/*!
 * \class CIncEulerSolver
 * \brief Main class for defining the incompressible Euler flow solver.
 * \ingroup Euler_Equations
 * \author F. Palacios, T. Economon, T. Albring
 */
class CIncEulerSolver : public CSolver {
protected:
  
  su2double
  Density_Inf,      /*!< \brief Density at the infinity. */
  Pressure_Inf,     /*!< \brief Pressure at the infinity. */
  *Velocity_Inf,    /*!< \brief Flow Velocity vector at the infinity. */
  Temperature_Inf;  /*!< \brief Temperature at infinity. */

  su2double
  *CD_Inv,       /*!< \brief Drag coefficient (inviscid contribution) for each boundary. */
  *CL_Inv,       /*!< \brief Lift coefficient (inviscid contribution) for each boundary. */
  *CSF_Inv,      /*!< \brief Sideforce coefficient (inviscid contribution) for each boundary. */
  *CMx_Inv,      /*!< \brief x Moment coefficient (inviscid contribution) for each boundary. */
  *CMy_Inv,      /*!< \brief y Moment coefficient (inviscid contribution) for each boundary. */
  *CMz_Inv,      /*!< \brief z Moment coefficient (inviscid contribution) for each boundary. */
  *CoPx_Inv,     /*!< \brief x Moment coefficient (inviscid contribution) for each boundary. */
  *CoPy_Inv,     /*!< \brief y Moment coefficient (inviscid contribution) for each boundary. */
  *CoPz_Inv,     /*!< \brief z Moment coefficient (inviscid contribution) for each boundary. */
  *CFx_Inv,      /*!< \brief x Force coefficient (inviscid contribution) for each boundary. */
  *CFy_Inv,      /*!< \brief y Force coefficient (inviscid contribution) for each boundary. */
  *CFz_Inv,      /*!< \brief z Force coefficient (inviscid contribution) for each boundary. */
  *Surface_CL_Inv,    /*!< \brief Lift coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CD_Inv,    /*!< \brief Drag coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CSF_Inv,   /*!< \brief Side-force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CEff_Inv,  /*!< \brief Side-force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CFx_Inv,   /*!< \brief x Force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CFy_Inv,   /*!< \brief y Force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CFz_Inv,   /*!< \brief z Force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CMx_Inv,   /*!< \brief x Moment coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CMy_Inv,   /*!< \brief y Moment coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CMz_Inv,   /*!< \brief z Moment coefficient (inviscid contribution) for each monitoring surface. */
  *CEff_Inv,          /*!< \brief Efficiency (Cl/Cd) (inviscid contribution) for each boundary. */
  *CMerit_Inv,        /*!< \brief Rotor Figure of Merit (inviscid contribution) for each boundary. */
  *CT_Inv,      /*!< \brief Thrust coefficient (force in -x direction, inviscid contribution) for each boundary. */
  *CQ_Inv,      /*!< \brief Torque coefficient (moment in -x direction, inviscid contribution) for each boundary. */
  *CD_Mnt,      /*!< \brief Drag coefficient (inviscid contribution) for each boundary. */
  *CL_Mnt,      /*!< \brief Lift coefficient (inviscid contribution) for each boundary. */
  *CSF_Mnt,     /*!< \brief Sideforce coefficient (inviscid contribution) for each boundary. */
  *CMx_Mnt,     /*!< \brief x Moment coefficient (inviscid contribution) for each boundary. */
  *CMy_Mnt,     /*!< \brief y Moment coefficient (inviscid contribution) for each boundary. */
  *CMz_Mnt,     /*!< \brief z Moment coefficient (inviscid contribution) for each boundary. */
  *CoPx_Mnt,    /*!< \brief x Moment coefficient (inviscid contribution) for each boundary. */
  *CoPy_Mnt,    /*!< \brief y Moment coefficient (inviscid contribution) for each boundary. */
  *CoPz_Mnt,    /*!< \brief z Moment coefficient (inviscid contribution) for each boundary. */
  *CFx_Mnt,     /*!< \brief x Force coefficient (inviscid contribution) for each boundary. */
  *CFy_Mnt,     /*!< \brief y Force coefficient (inviscid contribution) for each boundary. */
  *CFz_Mnt,     /*!< \brief z Force coefficient (inviscid contribution) for each boundary. */
  *Surface_CL_Mnt,    /*!< \brief Lift coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CD_Mnt,    /*!< \brief Drag coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CSF_Mnt,   /*!< \brief Side-force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CEff_Mnt,  /*!< \brief Side-force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CFx_Mnt,   /*!< \brief x Force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CFy_Mnt,   /*!< \brief y Force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CFz_Mnt,   /*!< \brief z Force coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CMx_Mnt,   /*!< \brief x Moment coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CMy_Mnt,   /*!< \brief y Moment coefficient (inviscid contribution) for each monitoring surface. */
  *Surface_CMz_Mnt,   /*!< \brief z Moment coefficient (inviscid contribution) for each monitoring surface. */
  *CEff_Mnt,          /*!< \brief Efficiency (Cl/Cd) (inviscid contribution) for each boundary. */
  *CMerit_Mnt,        /*!< \brief Rotor Figure of Merit (inviscid contribution) for each boundary. */
  *CT_Mnt,            /*!< \brief Thrust coefficient (force in -x direction, inviscid contribution) for each boundary. */
  *CQ_Mnt,            /*!< \brief Torque coefficient (moment in -x direction, inviscid contribution) for each boundary. */
  **CPressure,        /*!< \brief Pressure coefficient for each boundary and vertex. */
  **CPressureTarget,  /*!< \brief Target Pressure coefficient for each boundary and vertex. */
  **HeatFlux,         /*!< \brief Heat transfer coefficient for each boundary and vertex. */
  **HeatFluxTarget,   /*!< \brief Heat transfer coefficient for each boundary and vertex. */
  **YPlus,            /*!< \brief Yplus for each boundary and vertex. */
  ***CharacPrimVar,   /*!< \brief Value of the characteristic variables at each boundary. */
  *ForceInviscid,     /*!< \brief Inviscid force for each boundary. */
  *MomentInviscid,    /*!< \brief Inviscid moment for each boundary. */
  *ForceMomentum,     /*!< \brief Inviscid force for each boundary. */
  *MomentMomentum,    /*!< \brief Inviscid moment for each boundary. */
  InverseDesign;      /*!< \brief Inverse design functional for each boundary. */
  su2double
  **Inlet_Ptotal,    /*!< \brief Value of the Total P. */
  **Inlet_Ttotal,    /*!< \brief Value of the Total T. */
  ***Inlet_FlowDir;  /*!< \brief Value of the Flow Direction. */

  su2double
  AllBound_CD_Inv,      /*!< \brief Total drag coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CL_Inv,      /*!< \brief Total lift coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CSF_Inv,     /*!< \brief Total sideforce coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMx_Inv,     /*!< \brief Total x moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMy_Inv,     /*!< \brief Total y moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMz_Inv,     /*!< \brief Total z moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CFx_Inv,     /*!< \brief Total x force coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CFy_Inv,     /*!< \brief Total y force coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CFz_Inv,     /*!< \brief Total z force coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CoPx_Inv,    /*!< \brief Total x moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CoPy_Inv,    /*!< \brief Total y moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CoPz_Inv,    /*!< \brief Total z moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CEff_Inv,    /*!< \brief Efficient coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMerit_Inv,  /*!< \brief Rotor Figure of Merit (inviscid contribution) for all the boundaries. */
  AllBound_CT_Inv,      /*!< \brief Total thrust coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CQ_Inv;      /*!< \brief Total torque coefficient (inviscid contribution) for all the boundaries. */


  su2double
  AllBound_CD_Mnt,      /*!< \brief Total drag coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CL_Mnt,      /*!< \brief Total lift coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CSF_Mnt,     /*!< \brief Total sideforce coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMx_Mnt,     /*!< \brief Total x moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMy_Mnt,     /*!< \brief Total y moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMz_Mnt,     /*!< \brief Total z moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CFx_Mnt,     /*!< \brief Total x force coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CFy_Mnt,     /*!< \brief Total y force coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CFz_Mnt,     /*!< \brief Total z force coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CoPx_Mnt,    /*!< \brief Total x moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CoPy_Mnt,    /*!< \brief Total y moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CoPz_Mnt,    /*!< \brief Total z moment coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CEff_Mnt,    /*!< \brief Efficient coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CMerit_Mnt,  /*!< \brief Rotor Figure of Merit (inviscid contribution) for all the boundaries. */
  AllBound_CT_Mnt,      /*!< \brief Total thrust coefficient (inviscid contribution) for all the boundaries. */
  AllBound_CQ_Mnt;      /*!< \brief Total torque coefficient (inviscid contribution) for all the boundaries. */

  su2double
  Total_ComboObj,        /*!< \brief Total 'combo' objective for all monitored boundaries */
  Total_CD,              /*!< \brief Total drag coefficient for all the boundaries. */
  Total_CL,              /*!< \brief Total lift coefficient for all the boundaries. */
  Total_CSF,             /*!< \brief Total sideforce coefficient for all the boundaries. */
  Total_CMx,             /*!< \brief Total x moment coefficient for all the boundaries. */
  Total_CMy,             /*!< \brief Total y moment coefficient for all the boundaries. */
  Total_CMz,             /*!< \brief Total z moment coefficient for all the boundaries. */
  Total_CoPx,            /*!< \brief Total x moment coefficient for all the boundaries. */
  Total_CoPy,            /*!< \brief Total y moment coefficient for all the boundaries. */
  Total_CoPz,            /*!< \brief Total z moment coefficient for all the boundaries. */
  Total_CFx,             /*!< \brief Total x force coefficient for all the boundaries. */
  Total_CFy,             /*!< \brief Total y force coefficient for all the boundaries. */
  Total_CFz,             /*!< \brief Total z force coefficient for all the boundaries. */
  Total_CEff,            /*!< \brief Total efficiency coefficient for all the boundaries. */
  Total_CMerit,          /*!< \brief Total rotor Figure of Merit for all the boundaries. */
  Total_CT,              /*!< \brief Total thrust coefficient for all the boundaries. */
  Total_CQ,              /*!< \brief Total torque coefficient for all the boundaries. */
  Total_Heat,            /*!< \brief Total heat load for all the boundaries. */
  Total_MaxHeat,         /*!< \brief Maximum heat flux on all boundaries. */
  Total_CpDiff,          /*!< \brief Total Equivalent Area coefficient for all the boundaries. */
  Total_HeatFluxDiff,    /*!< \brief Total Equivalent Area coefficient for all the boundaries. */
  Total_Custom_ObjFunc,  /*!< \brief Total custom objective function for all the boundaries. */
  Total_MassFlowRate;    /*!< \brief Total Mass Flow Rate on monitored boundaries. */
  su2double
  *Surface_CL,          /*!< \brief Lift coefficient for each monitoring surface. */
  *Surface_CD,          /*!< \brief Drag coefficient for each monitoring surface. */
  *Surface_CSF,         /*!< \brief Side-force coefficient for each monitoring surface. */
  *Surface_CEff,        /*!< \brief Side-force coefficient for each monitoring surface. */
  *Surface_CFx,         /*!< \brief x Force coefficient for each monitoring surface. */
  *Surface_CFy,         /*!< \brief y Force coefficient for each monitoring surface. */
  *Surface_CFz,         /*!< \brief z Force coefficient for each monitoring surface. */
  *Surface_CMx,         /*!< \brief x Moment coefficient for each monitoring surface. */
  *Surface_CMy,         /*!< \brief y Moment coefficient for each monitoring surface. */
  *Surface_CMz,         /*!< \brief z Moment coefficient for each monitoring surface. */
  *Surface_HF_Visc,     /*!< \brief Total (integrated) heat flux for each monitored surface. */
  *Surface_MaxHF_Visc;  /*!< \brief Maximum heat flux for each monitored surface. */

  su2double *SecondaryVar_i,  /*!< \brief Auxiliary vector for storing the solution at point i. */
  *SecondaryVar_j;            /*!< \brief Auxiliary vector for storing the solution at point j. */
  su2double *PrimVar_i,       /*!< \brief Auxiliary vector for storing the solution at point i. */
  *PrimVar_j;                 /*!< \brief Auxiliary vector for storing the solution at point j. */
  bool space_centered,  /*!< \brief True if space centered scheeme used. */
  euler_implicit,       /*!< \brief True if euler implicit scheme used. */
  least_squares;        /*!< \brief True if computing gradients by least squares. */
  su2double Gamma;                  /*!< \brief Fluid's Gamma constant (ratio of specific heats). */
  su2double Gamma_Minus_One;        /*!< \brief Fluids's Gamma - 1.0  . */
  
  su2double *Primitive,  /*!< \brief Auxiliary nPrimVar vector. */
  *Primitive_i,          /*!< \brief Auxiliary nPrimVar vector for storing the primitive at point i. */
  *Primitive_j;          /*!< \brief Auxiliary nPrimVar vector for storing the primitive at point j. */
  
  CFluidModel  *FluidModel;   /*!< \brief fluid model used in the solver */
  su2double **Preconditioner; /*!< \brief Auxiliary matrix for storing the low speed preconditioner. */

  /* Sliding meshes variables */

  su2double ****SlidingState;
  int **SlidingStateNodes;

  CIncEulerVariable* nodes = nullptr;  /*!< \brief The highest level in the variable hierarchy this solver can safely use. */

  /*!
   * \brief Return nodes to allow CSolver::base_nodes to be set.
   */
  inline CVariable* GetBaseClassPointerToNodes() override { return nodes; }

public:
  
  /*!
   * \brief Constructor of the class.
   */
  CIncEulerSolver(void);
  
  /*!
   * \overload
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  CIncEulerSolver(CGeometry *geometry, CConfig *config, unsigned short iMesh);
  
  /*!
   * \brief Destructor of the class.
   */
  virtual ~CIncEulerSolver(void);

  /*!
   * \brief Set the solver nondimensionalization.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   */
  void SetNondimensionalization(CConfig *config, unsigned short iMesh);

  /*!
   * \brief Compute the pressure at the infinity.
   * \return Value of the pressure at the infinity.
   */
  CFluidModel* GetFluidModel(void);
  
  /*!
   * \brief Compute the density at the infinity.
   * \return Value of the density at the infinity.
   */
  su2double GetDensity_Inf(void);
  
  /*!
   * \brief Compute 2-norm of the velocity at the infinity.
   * \return Value of the 2-norm of the velocity at the infinity.
   */
  su2double GetModVelocity_Inf(void);
  
  /*!
   * \brief Compute the pressure at the infinity.
   * \return Value of the pressure at the infinity.
   */
  su2double GetPressure_Inf(void);
  
    /*!
   * \brief Get the temperature value at infinity.
   * \return Value of the temperature at infinity.
   */
  su2double GetTemperature_Inf(void);

  /*!
   * \brief Compute the density multiply by velocity at the infinity.
   * \param[in] val_dim - Index of the velocity vector.
   * \return Value of the density multiply by the velocity at the infinity.
   */
  su2double GetDensity_Velocity_Inf(unsigned short val_dim);
  
  /*!
   * \brief Get the velocity at the infinity.
   * \param[in] val_dim - Index of the velocity vector.
   * \return Value of the velocity at the infinity.
   */
  su2double GetVelocity_Inf(unsigned short val_dim);
  
  /*!
   * \brief Get the velocity at the infinity.
   * \return Value of the velocity at the infinity.
   */
  su2double *GetVelocity_Inf(void);

  /*!
   * \brief Set the velocity at infinity.
   * \param[in] val_dim - Index of the velocity vector.
   * \param[in] val_velocity - Value of the velocity.
   */
  void SetVelocity_Inf(unsigned short val_dim, su2double val_velocity);

  /*!
   * \brief Compute the time step for solving the Euler equations.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   * \param[in] Iteration - Value of the current iteration.
   */
  void SetTime_Step(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                    unsigned short iMesh, unsigned long Iteration);
  
  /*!
   * \brief Compute the spatial integration using a centered scheme.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
   */
  void Centered_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                         CConfig *config, unsigned short iMesh, unsigned short iRKStep);
  
  /*!
   * \brief Compute the spatial integration using a upwind scheme.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   */
  void Upwind_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                       CConfig *config, unsigned short iMesh);

  /*!
   * \brief Source term integration.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics - Description of the numerical method.
   * \param[in] second_numerics - Description of the second numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   */
  void Source_Residual(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics, CNumerics *second_numerics,
                       CConfig *config, unsigned short iMesh);
  
  /*!
   * \brief Source term integration.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   */
  void Source_Template(CGeometry *geometry, CSolver **solver_container, CNumerics *numerics,
                       CConfig *config, unsigned short iMesh);
  
  /*!
   * \brief Compute primitive variables and their gradients.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
   * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
   * \param[in] Output - boolean to determine whether to print output.
   */
  void Preprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config, unsigned short iMesh, unsigned short iRKStep, unsigned short RunTime_EqSystem, bool Output);
  
  /*!
   * \brief A virtual member.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   */
  void Postprocessing(CGeometry *geometry, CSolver **solver_container, CConfig *config, unsigned short iMesh);
  
  /*!
   * \brief Compute the velocity^2, SoundSpeed, Pressure, Enthalpy, Viscosity.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] Output - boolean to determine whether to print output.
   * \return - The number of non-physical points.
   */
  unsigned long SetPrimitive_Variables(CSolver **solver_container, CConfig *config, bool Output);
  
  /*!
   * \brief Compute a pressure sensor switch.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   */
  void SetCentered_Dissipation_Sensor(CGeometry *geometry, CConfig *config);
  
  /*!
   * \brief Compute the gradient of the primitive variables using Green-Gauss method,
   *        and stores the result in the <i>Gradient_Primitive</i> variable.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   * \param[in] reconstruction - indicator that the gradient being computed is for upwind reconstruction.
   */
  void SetPrimitive_Gradient_GG(CGeometry *geometry, CConfig *config, bool reconstruction = false);
  
  /*!
   * \brief Compute the gradient of the primitive variables using a Least-Squares method,
   *        and stores the result in the <i>Gradient_Primitive</i> variable.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   * \param[in] reconstruction - indicator that the gradient being computed is for upwind reconstruction.
   */
  void SetPrimitive_Gradient_LS(CGeometry *geometry, CConfig *config, bool reconstruction = false);
  
  /*!
   * \brief Compute the limiter of the primitive variables.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void SetPrimitive_Limiter(CGeometry *geometry, CConfig *config);
  
  /*!
   * \brief Compute the undivided laplacian for the solution, except the energy equation.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void SetUndivided_Laplacian(CGeometry *geometry, CConfig *config);
  
  /*!
   * \brief Compute the max eigenvalue.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void SetMax_Eigenvalue(CGeometry *geometry, CConfig *config);

  /*!
   * \author H. Kline
   * \brief Compute weighted-sum "combo" objective output
   * \param[in] config - Definition of the particular problem.
   */
  void Evaluate_ObjFunc(CConfig *config);

  /*!
   * \author: T. Kattmann
   * \brief Impose via the residual the Euler wall boundary condition.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method.
   * \param[in] visc_numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_Euler_Wall(CGeometry      *geometry, 
                     CSolver        **solver_container, 
                     CNumerics      *conv_numerics, 
                     CNumerics      *visc_numerics, 
                     CConfig        *config,
                     unsigned short val_marker) override;
  
  /*!
   * \brief Impose the far-field boundary condition using characteristics.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method.
   * \param[in] visc_numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_Far_Field(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                    CConfig *config, unsigned short val_marker);
  
  /*!
   * \brief Impose the symmetry boundary condition using the residual.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method.
   * \param[in] visc_numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_Sym_Plane(CGeometry      *geometry,
                    CSolver        **solver_container,
                    CNumerics      *conv_numerics,
                    CNumerics      *visc_numerics,
                    CConfig        *config,
                    unsigned short val_marker) override;

  /*!
   * \brief Impose a subsonic inlet boundary condition.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method.
   * \param[in] visc_numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_Inlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                CConfig *config, unsigned short val_marker);
  
  /*!
   * \brief Impose a custom or verification boundary condition.
   * \param[in] geometry         - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics    - Description of the convective numerical method.
   * \param[in] visc_numerics    - Description of the viscous numerical method.
   * \param[in] config           - Definition of the particular problem.
   * \param[in] val_marker       - Surface marker where the boundary condition is applied.
   */
  void BC_Custom(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                 CConfig *config, unsigned short val_marker);
  
  /*!
   * \brief Impose the outlet boundary condition.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method.
   * \param[in] visc_numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_marker - Surface marker where the boundary condition is applied.
   */
  void BC_Outlet(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics,
                 CConfig *config, unsigned short val_marker);
  
  /*!
   * \brief Impose the interface state across sliding meshes.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] conv_numerics - Description of the numerical method.
   * \param[in] visc_numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   */
   void BC_Fluid_Interface(CGeometry *geometry, CSolver **solver_container, CNumerics *conv_numerics, CNumerics *visc_numerics, CConfig *config);

  /*!
   * \brief Impose a periodic boundary condition by summing contributions from the complete control volume.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] numerics - Description of the numerical method.
   * \param[in] config - Definition of the particular problem.
   */
  void BC_Periodic(CGeometry *geometry, CSolver **solver_container,
                   CNumerics *numerics, CConfig *config);
  
  /*!
   * \brief compare to values.
   * \param[in] a - value 1.
   * \param[in] b - value 2.
   */
  static bool Compareval(std::vector<su2double> a,std::vector<su2double> b);
  
  /*!
   * \brief Update the solution using a Runge-Kutta scheme.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
   */
  void ExplicitRK_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                            unsigned short iRKStep);

  /*!
   * \brief Update the solution using the explicit Euler scheme.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   */
  void ExplicitEuler_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config);
  
  /*!
   * \brief Compute the pressure forces and all the adimensional coefficients.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void Pressure_Forces(CGeometry *geometry, CConfig *config);

  /*!
   * \brief Compute the pressure forces and all the adimensional coefficients.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] config - Definition of the particular problem.
   */
  void Momentum_Forces(CGeometry *geometry, CConfig *config);

  /*!
   * \brief Update the solution using an implicit Euler scheme.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   */
  void ImplicitEuler_Iteration(CGeometry *geometry, CSolver **solver_container, CConfig *config);

  /*!
   * \brief Compute a suitable under-relaxation parameter to limit the change in the solution variables over a nonlinear iteration for stability.
   * \param[in] solver - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   */
  void ComputeUnderRelaxationFactor(CSolver **solver, CConfig *config);
  
  /*!
   * \brief Provide the non dimensional lift coefficient (inviscid contribution).
   * \param val_marker Surface where the coefficient is going to be computed.
   * \return Value of the lift coefficient (inviscid contribution) on the surface <i>val_marker</i>.
   */
  su2double GetCLift_Inv(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional lift coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the lift coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CL(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional drag coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the drag coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CD(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional side-force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the side-force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CSF(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional side-force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the side-force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CEff(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional x force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the x force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFx(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional y force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the y force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFy(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional z force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the z force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFz(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional x moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the x moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMx(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional y moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the y moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMy(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional z moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the z moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMz(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional lift coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the lift coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CL_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional drag coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the drag coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CD_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional side-force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the side-force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CSF_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional side-force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the side-force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CEff_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional x force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the x force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFx_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional y force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the y force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFy_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional z force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the z force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFz_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional x moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the x moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMx_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional y moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the y moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMy_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional z moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the z moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMz_Inv(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional lift coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the lift coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CL_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional drag coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the drag coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CD_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional side-force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the side-force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CSF_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional side-force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the side-force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CEff_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional x force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the x force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFx_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional y force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the y force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFy_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional z force coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the z force coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CFz_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional x moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the x moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMx_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional y moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the y moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMy_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional z moment coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \return Value of the z moment coefficient on the surface <i>val_marker</i>.
   */
  su2double GetSurface_CMz_Mnt(unsigned short val_marker);

  /*!
   * \brief Provide the non dimensional drag coefficient (inviscid contribution).
   * \param val_marker Surface where the coeficient is going to be computed.
   * \return Value of the drag coefficient (inviscid contribution) on the surface <i>val_marker</i>.
   */
  su2double GetCD_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional sideforce coefficient (inviscid contribution).
   * \param val_marker Surface where the coeficient is going to be computed.
   * \return Value of the sideforce coefficient (inviscid contribution) on the surface <i>val_marker</i>.
   */
  su2double GetCSF_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the non dimensional efficiency coefficient (inviscid contribution).
   * \param val_marker Surface where the coeficient is going to be computed.
   * \return Value of the efficiency coefficient (inviscid contribution) on the surface <i>val_marker</i>.
   */
  su2double GetCEff_Inv(unsigned short val_marker);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional sideforce coefficient.
   * \return Value of the sideforce coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CSF(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CEff(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional Equivalent Area coefficient.
   * \return Value of the Equivalent Area coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CpDiff(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional Equivalent Area coefficient.
   * \return Value of the Equivalent Area coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_HeatFluxDiff(void);
  
  /*!
   * \brief Set the value of the Equivalent Area coefficient.
   * \param[in] val_cequivarea - Value of the Equivalent Area coefficient.
   */
  void SetTotal_CpDiff(su2double val_pressure);
  
  /*!
   * \brief Set the value of the Equivalent Area coefficient.
   * \param[in] val_cequivarea - Value of the Equivalent Area coefficient.
   */
  void SetTotal_HeatFluxDiff(su2double val_heat);
  
  /*!
   * \brief Store the total (inviscid + viscous) non dimensional lift coefficient.
   * \param[in] val_Total_CLift - Value of the total lift coefficient.
   */
  void SetTotal_CLift(su2double val_Total_CLift);

  /*!
   * \brief Set the value of the custom objective function.
   * \param[in] val_Total_Custom_ObjFunc - Value of the total custom objective function.
   * \param[in] val_weight - Value of the weight for the custom objective function.
   */
  void SetTotal_Custom_ObjFunc(su2double val_total_custom_objfunc, su2double val_weight);

  /*!
   * \brief Add the value of the custom objective function.
   * \param[in] val_Total_Custom_ObjFunc - Value of the total custom objective function.
   * \param[in] val_weight - Value of the weight for the custom objective function.
   */
  void AddTotal_Custom_ObjFunc(su2double val_total_custom_objfunc, su2double val_weight);

  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional lift coefficient.
   * \return Value of the lift coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CL(void);

  /*!
   * \author H. Kline
   * \brief Set the total "combo" objective (weighted sum of other values).
   * \param[in] ComboObj - Value of the combined objective.
   */
  void SetTotal_ComboObj(su2double ComboObj);

  /*!
   * \author H. Kline
   * \brief Provide the total "combo" objective (weighted sum of other values).
   * \return Value of the "combo" objective values.
   */
  su2double GetTotal_ComboObj(void);

  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional drag coefficient.
   * \return Value of the drag coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CD(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional x moment coefficient.
   * \return Value of the moment x coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CMx(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional y moment coefficient.
   * \return Value of the moment y coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CMy(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional z moment coefficient.
   * \return Value of the moment z coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CMz(void);

  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional x moment coefficient.
   * \return Value of the moment x coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CoPx(void);

  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional y moment coefficient.
   * \return Value of the moment y coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CoPy(void);

  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional z moment coefficient.
   * \return Value of the moment z coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CoPz(void);

  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional x force coefficient.
   * \return Value of the force x coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CFx(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional y force coefficient.
   * \return Value of the force y coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CFy(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional z force coefficient.
   * \return Value of the force z coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CFz(void);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional thrust coefficient.
   * \return Value of the rotor efficiency coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CT(void);
  
  /*!
   * \brief Store the total (inviscid + viscous) non dimensional thrust coefficient.
   * \param[in] val_Total_CT - Value of the total thrust coefficient.
   */
  void SetTotal_CT(su2double val_Total_CT);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional torque coefficient.
   * \return Value of the rotor efficiency coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CQ(void);
  
  /*!
   * \brief Provide the total heat load.
   * \return Value of the heat load (viscous contribution).
   */
  su2double GetTotal_HeatFlux(void);
  
  /*!
   * \brief Provide the total heat load.
   * \return Value of the heat load (viscous contribution).
   */
  su2double GetTotal_MaxHeatFlux(void);
  
  /*!
   * \brief Store the total (inviscid + viscous) non dimensional torque coefficient.
   * \param[in] val_Total_CQ - Value of the total torque coefficient.
   */
  void SetTotal_CQ(su2double val_Total_CQ);
  
  /*!
   * \brief Store the total heat load.
   * \param[in] val_Total_Heat - Value of the heat load.
   */
  void SetTotal_HeatFlux(su2double val_Total_Heat);
  
  /*!
   * \brief Store the total heat load.
   * \param[in] val_Total_Heat - Value of the heat load.
   */
  void SetTotal_MaxHeatFlux(su2double val_Total_MaxHeat);
  
  /*!
   * \brief Provide the total (inviscid + viscous) non dimensional rotor Figure of Merit.
   * \return Value of the rotor efficiency coefficient (inviscid + viscous contribution).
   */
  su2double GetTotal_CMerit(void);

  /*!
   * \brief Provide the total custom objective function.
   * \return Value of the custom objective function.
   */
  su2double GetTotal_Custom_ObjFunc(void);

  /*!
   * \brief Store the total (inviscid + viscous) non dimensional drag coefficient.
   * \param[in] val_Total_CDrag - Value of the total drag coefficient.
   */
  void SetTotal_CD(su2double val_Total_CDrag);
  
  /*!
   * \brief Get the inviscid contribution to the lift coefficient.
   * \return Value of the lift coefficient (inviscid contribution).
   */
  su2double GetAllBound_CL_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the drag coefficient.
   * \return Value of the drag coefficient (inviscid contribution).
   */
  su2double GetAllBound_CD_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the sideforce coefficient.
   * \return Value of the sideforce coefficient (inviscid contribution).
   */
  su2double GetAllBound_CSF_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CEff_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CMx_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CMy_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CMz_Inv(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CoPx_Inv(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CoPy_Inv(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CoPz_Inv(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CFx_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CFy_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CFz_Inv(void);
  
  /*!
   * \brief Get the inviscid contribution to the lift coefficient.
   * \return Value of the lift coefficient (inviscid contribution).
   */
  su2double GetAllBound_CL_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the drag coefficient.
   * \return Value of the drag coefficient (inviscid contribution).
   */
  su2double GetAllBound_CD_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the sideforce coefficient.
   * \return Value of the sideforce coefficient (inviscid contribution).
   */
  su2double GetAllBound_CSF_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CEff_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CMx_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CMy_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CMz_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CoPx_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CoPy_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CoPz_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CFx_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CFy_Mnt(void);

  /*!
   * \brief Get the inviscid contribution to the efficiency coefficient.
   * \return Value of the efficiency coefficient (inviscid contribution).
   */
  su2double GetAllBound_CFz_Mnt(void);

  /*!
   * \brief Provide the Pressure coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
   * \return Value of the pressure coefficient.
   */
  su2double GetCPressure(unsigned short val_marker, unsigned long val_vertex);
  
  /*!
   * \brief Provide the Target Pressure coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
   * \return Value of the pressure coefficient.
   */
  su2double GetCPressureTarget(unsigned short val_marker, unsigned long val_vertex);
  
  /*!
   * \brief Set the value of the target Pressure coefficient.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
   * \return Value of the pressure coefficient.
   */
  void SetCPressureTarget(unsigned short val_marker, unsigned long val_vertex, su2double val_pressure);
  
  /*!
   * \brief Value of the characteristic variables at the boundaries.
   * \param[in] val_marker - Surface marker where the coefficient is computed.
   * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the coefficient is evaluated.
   * \return Value of the pressure coefficient.
   */
  su2double *GetCharacPrimVar(unsigned short val_marker, unsigned long val_vertex);

  /*!
   * \brief Set the total residual adding the term that comes from the Dual Time Strategy.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iRKStep - Current step of the Runge-Kutta iteration.
   * \param[in] iMesh - Index of the mesh in multigrid computations.
   * \param[in] RunTime_EqSystem - System of equations which is going to be solved.
   */
  void SetResidual_DualTime(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                            unsigned short iRKStep, unsigned short iMesh, unsigned short RunTime_EqSystem);
  
  /*!
   * \brief Load a solution from a restart file.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver - Container vector with all of the solvers.
   * \param[in] config - Definition of the particular problem.
   * \param[in] val_iter - Current external iteration number.
   * \param[in] val_update_geo - Flag for updating coords and grid velocity.
   */
  void LoadRestart(CGeometry **geometry, CSolver ***solver, CConfig *config, int val_iter, bool val_update_geo);
  
  /*!
   * \brief Set the initial condition for the Euler Equations.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] ExtIter - External iteration.
   */
  void SetInitialCondition(CGeometry **geometry, CSolver ***solver_container, CConfig *config, unsigned long TimeIter);
  
  /*!
   * \brief Set the freestream pressure.
   * \param[in] Value of freestream pressure.
   */
  void SetPressure_Inf(su2double p_inf);
  
  /*!
   * \brief Set the freestream temperature.
   * \param[in] Value of freestream temperature.
   */
  void SetTemperature_Inf(su2double t_inf);

  /*!
   * \brief Set the freestream temperature.
   * \param[in] Value of freestream temperature.
   */
  void SetDensity_Inf(su2double rho_inf);

  /*!
   * \brief Set the solution using the Freestream values.
   * \param[in] config - Definition of the particular problem.
   */
  void SetFreeStream_Solution(CConfig *config);

  /*!
   * \brief Update the Beta parameter for the incompressible preconditioner.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param[in] solver_container - Container vector with all the solutions.
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMesh - current mesh level for the multigrid.
   */
  void SetBeta_Parameter(CGeometry *geometry, CSolver **solver_container,
                       CConfig *config, unsigned short iMesh);

  /*!
   * \brief Compute the preconditioner for low-Mach flows.
   * \param[in] iPoint - Index of the grid point
   * \param[in] config - Definition of the particular problem.
   */
  void SetPreconditioner(CConfig *config, unsigned long iPoint);
  
  /*!
   * \brief Value of the total temperature at an inlet boundary.
   * \param[in] val_marker - Surface marker where the total temperature is evaluated.
   * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the total temperature is evaluated.
   * \return Value of the total temperature
   */
  su2double GetInlet_Ttotal(unsigned short val_marker, unsigned long val_vertex);
  
  /*!
   * \brief Value of the total pressure at an inlet boundary.
   * \param[in] val_marker - Surface marker where the total pressure is evaluated.
   * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the total pressure is evaluated.
   * \return Value of the total pressure
   */
  su2double GetInlet_Ptotal(unsigned short val_marker, unsigned long val_vertex);
  
  /*!
   * \brief A component of the unit vector representing the flow direction at an inlet boundary.
   * \param[in] val_marker - Surface marker where the flow direction is evaluated
   * \param[in] val_vertex - Vertex of the marker <i>val_marker</i> where the flow direction is evaluated
   * \param[in] val_dim - The component of the flow direction unit vector to be evaluated
   * \return Component of a unit vector representing the flow direction.
   */
  su2double GetInlet_FlowDir(unsigned short val_marker, unsigned long val_vertex, unsigned short val_dim);
  
  /*!
   * \brief Set a uniform inlet profile
   *
   * The values at the inlet are set to match the values specified for
   * inlets in the configuration file.
   *
   * \param[in] config - Definition of the particular problem.
   * \param[in] iMarker - Surface marker where the coefficient is computed.
   */
  void SetUniformInlet(CConfig* config, unsigned short iMarker);
  
  /*!
   * \brief Store of a set of provided inlet profile values at a vertex.
   * \param[in] val_inlet - vector containing the inlet values for the current vertex.
   * \param[in] iMarker - Surface marker where the coefficient is computed.
   * \param[in] iVertex - Vertex of the marker <i>iMarker</i> where the inlet is being set.
   */
  void SetInletAtVertex(su2double *val_inlet, unsigned short iMarker, unsigned long iVertex);
  
  /*!
   * \brief Get the set of value imposed at an inlet.
   * \param[in] val_inlet - vector returning the inlet values for the current vertex.
   * \param[in] val_inlet_point - Node index where the inlet is being set.
   * \param[in] val_kind_marker - Enumerated type for the particular inlet type.
   * \param[in] geometry - Geometrical definition of the problem.
   * \param config - Definition of the particular problem.
   * \return Value of the face area at the vertex.
   */
  su2double GetInletAtVertex(su2double *val_inlet,
                             unsigned long val_inlet_point,
                             unsigned short val_kind_marker,
                             string val_marker,
                             CGeometry *geometry,
                             CConfig *config);
  
  /*!
   * \brief A virtual member.
   */
  void GetOutlet_Properties(CGeometry *geometry, CConfig *config, unsigned short iMesh, bool Output);

  /*!
   * \brief Allocates the final pointer of SlidingState depending on how many donor vertex donate to it. That number is stored in SlidingStateNodes[val_marker][val_vertex].
   * \param[in] val_marker   - marker index
   * \param[in] val_vertex   - vertex index
   */
  void SetSlidingStateStructure(unsigned short val_marker, unsigned long val_vertex);

  /*!
   * \brief Set the outer state for fluid interface nodes.
   * \param[in] val_marker   - marker index
   * \param[in] val_vertex   - vertex index
   * \param[in] val_state    - requested state component
   * \param[in] donor_index  - index of the donor node to set
   * \param[in] component    - set value
   */
  void SetSlidingState(unsigned short val_marker, unsigned long val_vertex, unsigned short val_state, unsigned long donor_index, su2double component);

  /*!
   * \brief Set the number of outer state for fluid interface nodes.
   * \param[in] val_marker - marker index
   * \param[in] val_vertex - vertex index
   * \param[in] value - number of outer states
   */
  void SetnSlidingStates(unsigned short val_marker, unsigned long val_vertex, int value);

  /*!
   * \brief Get the number of outer state for fluid interface nodes.
   * \param[in] val_marker - marker index
   * \param[in] val_vertex - vertex index
   */
  int GetnSlidingStates(unsigned short val_marker, unsigned long val_vertex);

  /*!
   * \brief Get the outer state for fluid interface nodes.
   * \param[in] val_marker - marker index
   * \param[in] val_vertex - vertex index
   * \param[in] val_state  - requested state component
   */
   su2double GetSlidingState(unsigned short val_marker, unsigned long val_vertex, unsigned short val_state, unsigned long donor_index);

  /*!
   * \brief Compute the global error measures (L2, Linf) for verification cases.
   * \param[in] geometry - Geometrical definition.
   * \param[in] config   - Definition of the particular problem.
   */
  void ComputeVerificationError(CGeometry *geometry, CConfig *config);

};

#include "../solver_inlines/CIncEulerSolver.inl"