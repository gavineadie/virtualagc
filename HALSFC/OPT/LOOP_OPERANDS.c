/*
  File LOOP_OPERANDS.c generated by XCOM-I, 2024-08-09 12:38:53.
*/

#include "runtimeC.h"

descriptor_t *
LOOP_OPERANDS (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (descriptor_t *)0;
    }
  reentryGuard = guardReentry (reentryGuard, "LOOP_OPERANDS");
  // TEMP = GET_CLASS(PTR); (1685)
  {
    descriptor_t *bitRHS
        = (putBITp (16, mGET_CLASSxPTR, getBIT (16, mLOOP_OPERANDSxPTR)),
           GET_CLASS (0));
    putBIT (16, mLOOP_OPERANDSxTEMP, bitRHS);
    bitRHS->inUse = 0;
  }
  // IF TEMP = 3 OR TEMP = 4 THEN (1686)
  if (1
      & (xOR (xEQ (COREHALFWORD (mLOOP_OPERANDSxTEMP), 3),
              xEQ (COREHALFWORD (mLOOP_OPERANDSxTEMP), 4))))
    // IF (SHR(OPR(PTR),9) &  7) =  5 THEN (1687)
    if (1
        & (xEQ (
            xAND (SHR (getFIXED (mOPR + 4 * COREHALFWORD (mLOOP_OPERANDSxPTR)),
                       9),
                  7),
            5)))
      // RETURN PTR + 1; (1688)
      {
        reentryGuard = 0;
        return fixedToBit (
            32, (int32_t)(xadd (COREHALFWORD (mLOOP_OPERANDSxPTR), 1)));
      }
  // RETURN LAST_OPERAND(PTR); (1689)
  {
    reentryGuard = 0;
    return (putBITp (16, mLAST_OPERANDxPTR, getBIT (16, mLOOP_OPERANDSxPTR)),
            LAST_OPERAND (0));
  }
}