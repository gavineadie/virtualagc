/*
  File NAME_CHECK.c generated by XCOM-I, 2024-08-09 12:41:08.
*/

#include "runtimeC.h"

descriptor_t *
NAME_CHECK (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (descriptor_t *)0;
    }
  reentryGuard = guardReentry (reentryGuard, "NAME_CHECK");
  // SYB_PTR = SHR(OPR(PTR),16); (3106)
  {
    int32_t numberRHS = (int32_t)(SHR (
        getFIXED (mOPR + 4 * COREHALFWORD (mNAME_CHECKxPTR)), 16));
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mNAME_CHECKxSYB_PTR, bitRHS);
    bitRHS->inUse = 0;
  }
  // IF (SYT_FLAGS(SYB_PTR) & NAME_OR_PARM_FLAG) ~= 0 THEN (3107)
  if (1
      & (xNEQ (xAND (getFIXED (getFIXED (mSYM_TAB)
                               + 34 * (COREHALFWORD (mNAME_CHECKxSYB_PTR)) + 8
                               + 4 * (0)),
                     getFIXED (mNAME_OR_PARM_FLAG)),
               0)))
    // DO; (3108)
    {
    rs1:;
      // IF ~HIGHOPT THEN (3109)
      if (1 & (xNOT (BYTE0 (mHIGHOPT))))
        // CALL ZAP_TABLES; (3110)
        ZAP_TABLES (0);
      // ELSE (3111)
      else
        // CALL ZAP_VARS_BY_TYPE(SYB_PTR); (3112)
        {
          putBITp (16, mZAP_VARS_BY_TYPExSYB_PTR,
                   getBIT (16, mNAME_CHECKxSYB_PTR));
          ZAP_VARS_BY_TYPE (0);
        }
      // RETURN 1; (3113)
      {
        reentryGuard = 0;
        return fixedToBit (32, (int32_t)(1));
      }
    es1:;
    } // End of DO block
  // IF ~KEEP_VALIDITY THEN (3114)
  if (1 & (xNOT (BYTE0 (mNAME_CHECKxKEEP_VALIDITY))))
    // CALL SET_VALIDITY(SYB_PTR,FALSE); (3115)
    {
      putBITp (16, mSET_VALIDITYxPTR, getBIT (16, mNAME_CHECKxSYB_PTR));
      putBITp (8, mSET_VALIDITYxVAL, fixedToBit (32, (int32_t)(0)));
      SET_VALIDITY (0);
    }
  // RETURN 0; (3116)
  {
    reentryGuard = 0;
    return fixedToBit (32, (int32_t)(0));
  }
}