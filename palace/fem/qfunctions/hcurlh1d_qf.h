// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
// SPDX-License-Identifier: Apache-2.0

#ifndef PALACE_LIBCEED_HCURL_H1D_QF_H
#define PALACE_LIBCEED_HCURL_H1D_QF_H

#include "coeff_qf.h"
#include "utils_qf.h"

// libCEED QFunctions for mixed H(curl)-(H1)ᵈ operators (Piola transformation u =
// adj(J)^T / det(J) ̂u and u = ̂u)
// in[0] is geometry quadrature data, shape [ncomp=2+space_dim*dim, Q]
// in[1] is active vector, shape [qcomp=dim, ncomp=1, Q]
// out[0] is active vector, shape [ncomp=space_dim, Q]

CEED_QFUNCTION(f_apply_hcurlh1d_22)(void *__restrict__ ctx, CeedInt Q,
                                    const CeedScalar *const *in, CeedScalar *const *out)
{
  const CeedScalar *attr = in[0], *wdetJ = in[0] + Q, *adjJt = in[0] + 2 * Q, *u = in[1];
  CeedScalar *v = out[0];

  CeedPragmaSIMD for (CeedInt i = 0; i < Q; i++)
  {
    const CeedScalar u_loc[2] = {u[i + Q * 0], u[i + Q * 1]};
    CeedScalar coeff[3], adjJt_loc[4], v_loc[2];
    CoeffUnpack2((const CeedIntScalar *)ctx, (CeedInt)attr[i], coeff);
    MatUnpack22(adjJt + i, Q, adjJt_loc);
    MultBAx22(adjJt_loc, coeff, u_loc, v_loc);

    v[i + Q * 0] = wdetJ[i] * v_loc[0];
    v[i + Q * 1] = wdetJ[i] * v_loc[1];
  }
  return 0;
}

CEED_QFUNCTION(f_apply_hcurlh1d_33)(void *__restrict__ ctx, CeedInt Q,
                                    const CeedScalar *const *in, CeedScalar *const *out)
{
  const CeedScalar *attr = in[0], *wdetJ = in[0] + Q, *adjJt = in[0] + 2 * Q, *u = in[1];
  CeedScalar *v = out[0];

  CeedPragmaSIMD for (CeedInt i = 0; i < Q; i++)
  {
    const CeedScalar u_loc[3] = {u[i + Q * 0], u[i + Q * 1], u[i + Q * 2]};
    CeedScalar coeff[6], adjJt_loc[9], v_loc[3];
    CoeffUnpack3((const CeedIntScalar *)ctx, (CeedInt)attr[i], coeff);
    MatUnpack33(adjJt + i, Q, adjJt_loc);
    MultBAx33(adjJt_loc, coeff, u_loc, v_loc);

    v[i + Q * 0] = wdetJ[i] * v_loc[0];
    v[i + Q * 1] = wdetJ[i] * v_loc[1];
    v[i + Q * 2] = wdetJ[i] * v_loc[2];
  }
  return 0;
}

CEED_QFUNCTION(f_apply_hcurlh1d_21)(void *__restrict__ ctx, CeedInt Q,
                                    const CeedScalar *const *in, CeedScalar *const *out)
{
  const CeedScalar *attr = in[0], *wdetJ = in[0] + Q, *adjJt = in[0] + 2 * Q, *u = in[1];
  CeedScalar *v = out[0];

  CeedPragmaSIMD for (CeedInt i = 0; i < Q; i++)
  {
    const CeedScalar u_loc[1] = {u[i + Q * 0]};
    CeedScalar coeff[3], adjJt_loc[2], v_loc[1];
    CoeffUnpack2((const CeedIntScalar *)ctx, (CeedInt)attr[i], coeff);
    MatUnpack21(adjJt + i, Q, adjJt_loc);
    MultBAx21(adjJt_loc, coeff, u_loc, v_loc);

    v[i + Q * 0] = wdetJ[i] * v_loc[0];
  }
  return 0;
}

CEED_QFUNCTION(f_apply_hcurlh1d_32)(void *__restrict__ ctx, CeedInt Q,
                                    const CeedScalar *const *in, CeedScalar *const *out)
{
  const CeedScalar *attr = in[0], *wdetJ = in[0] + Q, *adjJt = in[0] + 2 * Q, *u = in[1];
  CeedScalar *v = out[0];

  CeedPragmaSIMD for (CeedInt i = 0; i < Q; i++)
  {
    const CeedScalar u_loc[2] = {u[i + Q * 0], u[i + Q * 1]};
    CeedScalar coeff[6], adjJt_loc[6], v_loc[2];
    CoeffUnpack3((const CeedIntScalar *)ctx, (CeedInt)attr[i], coeff);
    MatUnpack32(adjJt + i, Q, adjJt_loc);
    MultBAx32(adjJt_loc, coeff, u_loc, v_loc);

    v[i + Q * 0] = wdetJ[i] * v_loc[0];
    v[i + Q * 1] = wdetJ[i] * v_loc[1];
  }
  return 0;
}

#endif  // PALACE_LIBCEED_HCURL_H1D_QF_H
