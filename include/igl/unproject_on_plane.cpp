#include "unproject_on_plane.h"
#include "projection_constraint.h"
#include <Eigen/Dense>

template <
  typename DerivedUV,
  typename DerivedM,
  typename DerivedVP,
  typename DerivedP,
  typename DerivedZ>
void igl::unproject_on_plane(
  const Eigen::MatrixBase<DerivedUV> & UV,
  const Eigen::MatrixBase<DerivedM> & M,
  const Eigen::MatrixBase<DerivedVP> & VP,
  const Eigen::MatrixBase<DerivedP> & P,
  Eigen::PlainObjectBase<DerivedZ> & Z)
{
  using namespace Eigen;
  typedef typename DerivedZ::Scalar Scalar;
  Matrix<Scalar,2,3> A;
  Matrix<Scalar,2,1> B;
  projection_constraint(UV,M,VP,A,B);
  Matrix<Scalar,3,3> AA;
  AA.topRows(2) = A.template cast<Scalar>();
  AA.row(2) = P.head(3).template cast<Scalar>();
  Matrix<Scalar,3,1> BB;
  BB.head(2) = B.template cast<Scalar>();
  BB(2) = -P(3);
  Z = AA.fullPivHouseholderQr().solve(BB);
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
template  void igl::unproject_on_plane<Eigen::Transpose<Eigen::Matrix<double, 1, 2, 1, 1, 2> >, Eigen::CoeffBasedProduct<Eigen::Matrix<float, 4, 4, 0, 4, 4> const&, Eigen::Matrix<float, 4, 4, 0, 4, 4> const&, 6>, Eigen::Matrix<float, 4, 1, 0, 4, 1>, Eigen::Matrix<double, 1, 4, 1, 1, 4>, Eigen::Matrix<double, 3, 1, 0, 3, 1> >(Eigen::MatrixBase<Eigen::Transpose<Eigen::Matrix<double, 1, 2, 1, 1, 2> > > const&, Eigen::MatrixBase<Eigen::CoeffBasedProduct<Eigen::Matrix<float, 4, 4, 0, 4, 4> const&, Eigen::Matrix<float, 4, 4, 0, 4, 4> const&, 6> > const&, Eigen::MatrixBase<Eigen::Matrix<float, 4, 1, 0, 4, 1> > const&, Eigen::MatrixBase<Eigen::Matrix<double, 1, 4, 1, 1, 4> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, 3, 1, 0, 3, 1> >&);
#endif
