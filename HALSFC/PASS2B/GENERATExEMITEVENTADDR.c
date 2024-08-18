/*
  File GENERATExEMITEVENTADDR.c generated by XCOM-I, 2024-08-09 12:41:32.
*/

#include "runtimeC.h"

int32_t
GENERATExEMITEVENTADDR (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExEMITEVENTADDR");
  // SY = LOC2(OP); (3306)
  {
    descriptor_t *bitRHS
        = getBIT (16, getFIXED (mIND_STACK)
                          + 73 * (COREHALFWORD (mGENERATExEMITEVENTADDRxOP))
                          + 42 + 2 * (0));
    putBIT (16, mGENERATExEMITEVENTADDRxSY, bitRHS);
    bitRHS->inUse = 0;
  }
  // IF SYT_TYPE(SY) >= TASK_LABEL THEN (3307)
  if (1
      & (xGE (BYTE0 (getFIXED (mSYM_TAB)
                     + 34 * (COREHALFWORD (mGENERATExEMITEVENTADDRxSY)) + 32
                     + 1 * (0)),
              BYTE0 (mTASK_LABEL))))
    // CALL EMITPCEADDR(OP); (3308)
    {
      putBITp (16, mGENERATExEMITPCEADDRxOP,
               getBIT (16, mGENERATExEMITEVENTADDRxOP));
      GENERATExEMITPCEADDR (0);
    }
  // ELSE (3309)
  else
    // DO; (3310)
    {
    rs1:;
      // CALL EMITADDR(DATABASE(SYT_SCOPE(SY)),
      // SYT_ADDR(SY)+SYT_CONST(SY)+INX_CON(OP), HADDR); (3311)
      {
        putBITp (
            16, mEMITADDRxCTR,
            getBIT (16,
                    mDATABASE
                        + 2
                              * BYTE0 (getFIXED (mSYM_TAB)
                                       + 34
                                             * (COREHALFWORD (
                                                 mGENERATExEMITEVENTADDRxSY))
                                       + 29 + 1 * (0))));
        putFIXED (
            mEMITADDRxVAL,
            xadd (xadd (getFIXED (
                            getFIXED (mSYM_TAB)
                            + 34 * (COREHALFWORD (mGENERATExEMITEVENTADDRxSY))
                            + 4 + 4 * (0)),
                        getFIXED (
                            getFIXED (mP2SYMS)
                            + 12 * (COREHALFWORD (mGENERATExEMITEVENTADDRxSY))
                            + 0 + 4 * (0))),
                  getFIXED (getFIXED (mIND_STACK)
                            + 73 * (COREHALFWORD (mGENERATExEMITEVENTADDRxOP))
                            + 4 + 4 * (0))));
        putBITp (16, mEMITADDRxOP, getBIT (8, mHADDR));
        EMITADDR (0);
      }
      // CALL RETURN_COLUMN_STACK(OP); (3312)
      {
        putBITp (16, mGENERATExRETURN_COLUMN_STACKxPTR,
                 getBIT (16, mGENERATExEMITEVENTADDRxOP));
        GENERATExRETURN_COLUMN_STACK (0);
      }
      // CALL RETURN_STACK_ENTRY(OP); (3313)
      {
        putBITp (16, mGENERATExRETURN_STACK_ENTRYxP,
                 getBIT (16, mGENERATExEMITEVENTADDRxOP));
        GENERATExRETURN_STACK_ENTRY (0);
      }
    es1:;
    } // End of DO block
  {
    reentryGuard = 0;
    return 0;
  }
}