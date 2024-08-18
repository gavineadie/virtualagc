/*
  File GENERATExRESUME_LOCCTR.c generated by XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
GENERATExRESUME_LOCCTR (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExRESUME_LOCCTR");
  // IF INDEXNEST = NEST THEN (3318)
  if (1
      & (xEQ (COREHALFWORD (mINDEXNEST),
              COREHALFWORD (mGENERATExRESUME_LOCCTRxNEST))))
    // RETURN; (3319)
    {
      reentryGuard = 0;
      return 0;
    }
  // INDEXNEST = NEST; (3320)
  {
    descriptor_t *bitRHS = getBIT (16, mGENERATExRESUME_LOCCTRxNEST);
    putBIT (16, mINDEXNEST, bitRHS);
    bitRHS->inUse = 0;
  }
  // IF NEST = 0 THEN (3321)
  if (1 & (xEQ (COREHALFWORD (mGENERATExRESUME_LOCCTRxNEST), 0)))
    // RETURN; (3322)
    {
      reentryGuard = 0;
      return 0;
    }
  // CALL EMITC(CSECT, NEST); (3323)
  {
    putBITp (16, mEMITCxTYPE, getBIT (8, mCSECT));
    putBITp (16, mEMITCxINST, getBIT (16, mGENERATExRESUME_LOCCTRxNEST));
    EMITC (0);
  }
  // CALL EMITW(0, 1); (3324)
  {
    putFIXED (mEMITWxDATA, 0);
    putBITp (1, mEMITWxMODIFIER, fixedToBit (32, (int32_t)(1)));
    EMITW (0);
  }
  // STOPPERFLAG = FALSE; (3325)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (1, mSTOPPERFLAG, bitRHS);
    bitRHS->inUse = 0;
  }
  // CCREG = 0; (3326)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mCCREG, bitRHS);
    bitRHS->inUse = 0;
  }
  {
    reentryGuard = 0;
    return 0;
  }
}