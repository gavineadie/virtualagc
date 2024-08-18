/*
  File GENERATExSET_AREA.c generated by XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
GENERATExSET_AREA (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExSET_AREA");
  // IF TYPE(PTR) < ANY_LABEL THEN (5158)
  if (1
      & (xLT (COREHALFWORD (getFIXED (mIND_STACK)
                            + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR)) + 50
                            + 2 * (0)),
              BYTE0 (mANY_LABEL))))
    // DO CASE PACKTYPE(TYPE(PTR)); (5159)
    {
    rs1:
      switch (BYTE0 (
          mPACKTYPE
          + 1
                * COREHALFWORD (getFIXED (mIND_STACK)
                                + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR))
                                + 50 + 2 * (0))))
        {
        case 0:
          // AREASAVE = ROW(PTR) * COLUMN(PTR); (5161)
          {
            int32_t numberRHS = (int32_t)(xmultiply (
                COREHALFWORD (getFIXED (mIND_STACK)
                              + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR))
                              + 48 + 2 * (0)),
                COREHALFWORD (getFIXED (mIND_STACK)
                              + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR))
                              + 24 + 2 * (0))));
            putFIXED (mAREASAVE, numberRHS);
          }
          break;
        case 1:
          // AREASAVE = 1; (5162)
          {
            int32_t numberRHS = (int32_t)(1);
            putFIXED (mAREASAVE, numberRHS);
          }
          break;
        case 2:
          // IF SIZE(PTR) < 0 THEN (5163)
          if (1
              & (xLT (
                  COREHALFWORD (getFIXED (mIND_STACK)
                                + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR))
                                + 48 + 2 * (0)),
                  0)))
            {
              descriptor_t *bitRHS = getBIT (
                  16, getFIXED (mIND_STACK)
                          + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR)) + 48
                          + 2 * (0));
              int32_t numberRHS;
              numberRHS = bitToFixed (bitRHS);
              putFIXED (mAREASAVE, numberRHS);
              bitRHS->inUse = 0;
            }
          else
            {
              int32_t numberRHS = (int32_t)((
                  putFIXED (
                      mCSxLEN,
                      xadd (COREHALFWORD (
                                getFIXED (mIND_STACK)
                                + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR))
                                + 48 + 2 * (0)),
                            2)),
                  CS (0)));
              putFIXED (mAREASAVE, numberRHS);
            }
          break;
        case 3:
          // AREASAVE = 1; (5167)
          {
            int32_t numberRHS = (int32_t)(1);
            putFIXED (mAREASAVE, numberRHS);
          }
          break;
        case 4:
          // AREASAVE = EXTENT(DEL(PTR)) + SYT_DISP(DEL(PTR)); (5168)
          {
            int32_t numberRHS = (int32_t)(xadd (
                getFIXED (
                    getFIXED (mSYM_TAB)
                    + 34
                          * (COREHALFWORD (
                              getFIXED (mIND_STACK)
                              + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR))
                              + 28 + 2 * (0)))
                    + 12 + 4 * (0)),
                COREHALFWORD (
                    getFIXED (mP2SYMS)
                    + 12
                          * (COREHALFWORD (
                              getFIXED (mIND_STACK)
                              + 73 * (COREHALFWORD (mGENERATExSET_AREAxPTR))
                              + 28 + 2 * (0)))
                    + 6 + 2 * (0))));
            putFIXED (mAREASAVE, numberRHS);
          }
          break;
        }
    } // End of DO CASE block
  {
    reentryGuard = 0;
    return 0;
  }
}