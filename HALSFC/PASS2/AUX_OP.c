/*
  File AUX_OP.c generated by XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
AUX_OP (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "AUX_OP");
  // RETURN SHR(AUX(GET_AUX(CTR)),1) &  15; (1010)
  {
    reentryGuard = 0;
    return xAND (
        SHR (getFIXED (mAUX
                       + 4
                             * bitToFixed ((putFIXED (mGET_AUXxCTR,
                                                      getFIXED (mAUX_OPxCTR)),
                                            GET_AUX (0)))),
             1),
        15);
  }
}