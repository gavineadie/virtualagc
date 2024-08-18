/*
  File GENERATExCLEAR_R.c generated by XCOM-I, 2024-08-09 12:41:32.
*/

#include "runtimeC.h"

int32_t
GENERATExCLEAR_R (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExCLEAR_R");
  // R_VAR(R), R_INX(R) = 0; (2900)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mR_VAR + 2 * (COREHALFWORD (mGENERATExCLEAR_RxR)), bitRHS);
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mR_INX + 2 * (COREHALFWORD (mGENERATExCLEAR_RxR)), bitRHS);
    bitRHS->inUse = 0;
  }
  // R_VAR2(R), R_MULT(R) = 0; (2901)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mR_VAR2 + 2 * (COREHALFWORD (mGENERATExCLEAR_RxR)), bitRHS);
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mR_MULT + 2 * (COREHALFWORD (mGENERATExCLEAR_RxR)), bitRHS);
    bitRHS->inUse = 0;
  }
  // R_INX_CON(R), R_CON(R) = 0; (2902)
  {
    int32_t numberRHS = (int32_t)(0);
    putFIXED (mR_INX_CON + 4 * (COREHALFWORD (mGENERATExCLEAR_RxR)),
              numberRHS);
    putFIXED (mR_CON + 4 * (COREHALFWORD (mGENERATExCLEAR_RxR)), numberRHS);
  }
  // R_TYPE(R), R_INX_SHIFT(R) = 0; (2903)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (8, mR_TYPE + 1 * (COREHALFWORD (mGENERATExCLEAR_RxR)), bitRHS);
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (8, mR_INX_SHIFT + 1 * (COREHALFWORD (mGENERATExCLEAR_RxR)),
            bitRHS);
    bitRHS->inUse = 0;
  }
  // DOUBLE_TYPE(R) = 0; (2904)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (8, mDOUBLE_TYPE + 1 * (COREHALFWORD (mGENERATExCLEAR_RxR)),
            bitRHS);
    bitRHS->inUse = 0;
  }
  // USAGE(R), USAGE_LINE(R) = 0; (2905)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mUSAGE + 2 * (COREHALFWORD (mGENERATExCLEAR_RxR)), bitRHS);
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mUSAGE_LINE + 2 * (COREHALFWORD (mGENERATExCLEAR_RxR)),
            bitRHS);
    bitRHS->inUse = 0;
  }
  // R_CONTENTS(R) = 0; (2906)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (8, mR_CONTENTS + 1 * (COREHALFWORD (mGENERATExCLEAR_RxR)), bitRHS);
    bitRHS->inUse = 0;
  }
  // CALL CLEAR_INX(R); (2907)
  {
    putBITp (16, mGENERATExCLEAR_INXxR, getBIT (16, mGENERATExCLEAR_RxR));
    GENERATExCLEAR_INX (0);
  }
  // IF R = LINKREG THEN (2908)
  if (1 & (xEQ (COREHALFWORD (mGENERATExCLEAR_RxR), BYTE0 (mLINKREG))))
    // CALL SET_LINKREG; (2909)
    SET_LINKREG (0);
  {
    reentryGuard = 0;
    return 0;
  }
}