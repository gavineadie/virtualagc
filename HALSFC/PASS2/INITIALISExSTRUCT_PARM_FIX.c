/*
  File INITIALISExSTRUCT_PARM_FIX.c generated by XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
INITIALISExSTRUCT_PARM_FIX (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "INITIALISExSTRUCT_PARM_FIX");
  // IF SYT_ARRAY(OP1) = 0 THEN (2557)
  if (1
      & (xEQ (
          COREHALFWORD (getFIXED (mSYM_TAB)
                        + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP1))
                        + 20 + 2 * (0)),
          0)))
    // EXTENT(OP1) = EXTENT(OP2); (2558)
    {
      int32_t numberRHS = (int32_t)(getFIXED (
          getFIXED (mSYM_TAB)
          + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP2)) + 12
          + 4 * (0)));
      putFIXED (getFIXED (mSYM_TAB)
                    + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP1))
                    + 12 + 4 * (0),
                numberRHS);
    }
  // ELSE (2559)
  else
    // DO; (2560)
    {
    rs1:;
      // TMP = EXTENT(OP2) + SYT_DISP(OP2); (2561)
      {
        int32_t numberRHS = (int32_t)(xadd (
            getFIXED (getFIXED (mSYM_TAB)
                      + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP2))
                      + 12 + 4 * (0)),
            COREHALFWORD (
                getFIXED (mP2SYMS)
                + 12 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP2)) + 6
                + 2 * (0))));
        putFIXED (mTMP, numberRHS);
      }
      // IF SYT_ARRAY(OP1) < 0 THEN (2562)
      if (1
          & (xLT (COREHALFWORD (
                      getFIXED (mSYM_TAB)
                      + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP1))
                      + 20 + 2 * (0)),
                  0)))
        // EXTENT(OP1) = TMP; (2563)
        {
          int32_t numberRHS = (int32_t)(getFIXED (mTMP));
          putFIXED (getFIXED (mSYM_TAB)
                        + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP1))
                        + 12 + 4 * (0),
                    numberRHS);
        }
      // ELSE (2564)
      else
        // EXTENT(OP1) = SYT_ARRAY(OP1) * TMP; (2565)
        {
          int32_t numberRHS = (int32_t)(xmultiply (
              COREHALFWORD (
                  getFIXED (mSYM_TAB)
                  + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP1)) + 20
                  + 2 * (0)),
              getFIXED (mTMP)));
          putFIXED (getFIXED (mSYM_TAB)
                        + 34 * (COREHALFWORD (mINITIALISExSTRUCT_PARM_FIXxOP1))
                        + 12 + 4 * (0),
                    numberRHS);
        }
    es1:;
    } // End of DO block
  {
    reentryGuard = 0;
    return 0;
  }
}