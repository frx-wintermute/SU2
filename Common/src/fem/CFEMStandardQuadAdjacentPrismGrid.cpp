/*!
 * \file CFEMStandardQuadAdjacentPrismGrid.cpp
 * \brief Functions for the class CFEMStandardQuadAdjacentPrismGrid.
 * \author E. van der Weide
 * \version 7.1.1 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2020, SU2 Contributors (cf. AUTHORS.md)
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

#include "../../include/fem/CFEMStandardQuadAdjacentPrismGrid.hpp"
#include "../../include/toolboxes/CSquareMatrixCM.hpp"

/*----------------------------------------------------------------------------------*/
/*            Public member functions of CFEMStandardQuadAdjacentPrismGrid.         */
/*----------------------------------------------------------------------------------*/

CFEMStandardQuadAdjacentPrismGrid::CFEMStandardQuadAdjacentPrismGrid(const unsigned short val_nPoly,
                                                                     const unsigned short val_orderExact,
                                                                     const unsigned short val_faceID_Elem,
                                                                     const unsigned short val_orientation,
                                                                     const bool           val_useLGL,
                                                                     CGemmBase           *val_gemm)
  : CFEMStandardPrismBase(),
    CFEMStandardQuadBase(val_nPoly, val_orderExact) {

  /*--- Store the faceID of the element and the orientation. ---*/
  faceID_Elem = val_faceID_Elem;
  orientation = val_orientation;

  /*--- Convert the pointer for the gemm functionality. ---*/
  gemmDOFs2Int = dynamic_cast<CGemmStandard *> (val_gemm);
  if( !gemmDOFs2Int )
    SU2_MPI::Error(string("Dynamic cast failure. This should not happen"), CURRENT_FUNCTION);

  /*--- Determine the location of the grid DOFs. ---*/
  vector<passivedouble> rTriangleDOFs, sTriangleDOFs, rLineDOFs;
  if( val_useLGL ) {
    Location1DGridDOFsLGL(nPoly, rLineDOFs);
    LocationTriangleGridDOFsLGL(nPoly, rTriangleDOFs, sTriangleDOFs);
  }
  else {
    Location1DGridDOFsEquidistant(nPoly, rLineDOFs);
    LocationTriangleGridDOFsEquidistant(nPoly, rTriangleDOFs, sTriangleDOFs);
  }

  /*--- Determine the parametric coordinates of all DOFs of the prism. ---*/
  vector<passivedouble> rDOFs, sDOFs, tDOFs;
  LocationAllPointsPrism(rTriangleDOFs, sTriangleDOFs, rLineDOFs, rDOFs, sDOFs, tDOFs);

  /*--- Determine the inverse of the Vandermonde matrix of the DOFs. ---*/
  CSquareMatrixCM VInv(rDOFs.size());
  VandermondePrism(nPoly, rDOFs, sDOFs, tDOFs, VInv.GetMat());
  VInv.Invert();

  /*--- Convert the 2D parametric coordinates of the integration points of the
        quadrilateral face to the 3D parametric coordinates of the adjacent prism. ---*/
  vector<passivedouble> rInt, sInt, tInt;
  ConvertCoor2DQuadFaceTo3DPrism(rLineInt, val_faceID_Elem, val_orientation, rInt, sInt, tInt);

  /*--- Determine the Vandermonde matrix and its derivatives of the integration points.
        Make sure to allocate the number of rows to nIntTotPad and initialize them to zero. ---*/
  ColMajorMatrix<passivedouble> V(nIntegrationPad,  rDOFs.size()), VDr(nIntegrationPad,rDOFs.size()),
                                VDs(nIntegrationPad,rDOFs.size()), VDt(nIntegrationPad,rDOFs.size());
  V.setConstant(0.0);
  VDr.setConstant(0.0);
  VDs.setConstant(0.0);
  VDt.setConstant(0.0);

  VandermondePrism(nPoly, rInt, sInt, tInt, V);
  GradVandermondePrism(nPoly, rInt, sInt, tInt, VDr, VDs, VDt);

  /*--- The Lagrangian basis functions and its gradients can be obtained by
        multiplying V, VDr, VDs, VDt and VInv. ---*/
  derLagBasisInt.resize(3);

  VInv.MatMatMult('R', V,   lagBasisInt);
  VInv.MatMatMult('R', VDr, derLagBasisInt[0]);
  VInv.MatMatMult('R', VDs, derLagBasisInt[1]);
  VInv.MatMatMult('R', VDt, derLagBasisInt[2]);

  /*--- Check if the sum of the elements of the relevant rows of lagBasisInt
        is 1 and derLagBasisInt is 0. ---*/
  CheckRowSum(nIntegration, rDOFs.size(), 1.0, lagBasisInt);
  CheckRowSum(nIntegration, rDOFs.size(), 0.0, derLagBasisInt[0]);
  CheckRowSum(nIntegration, rDOFs.size(), 0.0, derLagBasisInt[1]);
  CheckRowSum(nIntegration, rDOFs.size(), 0.0, derLagBasisInt[2]);

  /*--- Determine the local subconnectivity of this standard element when split
        in several linear elements. Used for a.o. plotting and searching. ---*/
  CFEMStandardQuadBase::SubConnLinearElements();
}

void CFEMStandardQuadAdjacentPrismGrid::CoorIntPoints(const bool                notUsed,
                                                      ColMajorMatrix<su2double> &matCoorDOF,
                                                      ColMajorMatrix<su2double> &matCoorInt) {

  /*--- Call the general functionality of gemmDOFs2Int with the appropriate
        arguments to compute the coordinates in the integration points
        of the face. ---*/
  gemmDOFs2Int->gemm(lagBasisInt, 3, matCoorDOF, matCoorInt, nullptr);
}

void CFEMStandardQuadAdjacentPrismGrid::DerivativesCoorIntPoints(const bool                         notUsed,
                                                                 ColMajorMatrix<su2double>          &matCoorDOF,
                                                                 vector<ColMajorMatrix<su2double> > &matDerCoorInt) {
  /*--- Call the general functionality of gemmDOFs2Int with the appropriate
        arguments to compute the derivatives of the coordinates in the
        integration points of the face. ---*/
  gemmDOFs2Int->gemm(derLagBasisInt[0], 3, matCoorDOF, matDerCoorInt[0], nullptr);
  gemmDOFs2Int->gemm(derLagBasisInt[1], 3, matCoorDOF, matDerCoorInt[1], nullptr);
  gemmDOFs2Int->gemm(derLagBasisInt[2], 3, matCoorDOF, matDerCoorInt[2], nullptr);
}

/*----------------------------------------------------------------------------------*/
/*            Private member functions of CFEMStandardQuadAdjacentPrismGrid.        */
/*----------------------------------------------------------------------------------*/

void CFEMStandardQuadAdjacentPrismGrid::ConvertVolumeToSurfaceGradients(vector<ColMajorMatrix<su2double> > &matDerVol,
                                                                        vector<ColMajorMatrix<su2double> > &matDerFace) {

  /*--- The conversion of the gradients only takes place for elements on side 0
        of the element, i.e. orientation == 0. Check this. ---*/
  assert(orientation == 0);

  /*--- Set the indices of the volume gradients to copy to the surface gradients.
        Note that for face 4 this is not correct, but is used as a first step. ---*/
  unsigned short ind0,  ind1;

  switch( faceID_Elem ) {
    case 2: ind0 = 2; ind1 = 0; break;
    case 3: ind0 = 1; ind1 = 2; break;
    case 4: ind0 = 2; ind1 = 1; break;
  }

  /*--- Copy the surface gradients from the appropriate volume gradients. ---*/
  matDerFace.resize(2);
  matDerFace[0] = matDerVol[ind0];
  matDerFace[1] = matDerVol[ind1];

  /*--- Correct the second surface gradient for face 4. ---*/
  if(faceID_Elem == 4) {
    const unsigned short nCols = matDerFace[1].cols();
    const unsigned short nRows = matDerFace[1].rows();
    for(unsigned short j=0; j<nCols; ++j) {
      SU2_OMP_SIMD_IF_NOT_AD
      for(unsigned short i=0; i<nRows; ++i)
        matDerFace[1](i,j) -= matDerVol[0](i,j);
    }
  }
}