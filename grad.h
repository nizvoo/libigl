//
//  grad.h
//  Preview3D
//
//  Created by Olga Diamanti on 11/11/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef IGL_GRAD_H
#define IGL_GRAD_H
#include "igl_inline.h"

#include <Eigen/Core>

namespace igl {
  // GRAD
  // G = grad(V,F,X)
  //
  // Compute the numerical gradient at every face of a triangle mesh.
  //
  // Inputs:
  //   V  #vertices by 3 list of mesh vertex positions
  //   F  #faces by 3 list of mesh face indices
  //   X  # vertices list of scalar function values
  // Outputs:
  //   G  #faces by 3 list of gradient values
  //
  
  // Gradient of a scalar function defined on piecewise linear elements (mesh)
  // is constant on each triangle i,j,k:
  // grad(Xijk) = (Xj-Xi) * (Vi - Vk)^R90 / 2A + (Xk-Xi) * (Vj - Vi)^R90 / 2A
  // where Xi is the scalar value at vertex i, Vi is the 3D position of vertex
  // i, and A is the area of triangle (i,j,k). ^R90 represent a rotation of 
  // 90 degrees
  //
  template <typename T, typename S>
  IGL_INLINE void grad(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &V,
    const Eigen::Matrix<S, Eigen::Dynamic, Eigen::Dynamic> &F,
    const Eigen::Matrix<T, Eigen::Dynamic, 1>&X,
    Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic> &G );
}

#ifdef IGL_HEADER_ONLY
#  include "grad.cpp"
#endif

#endif
