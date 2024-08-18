/*
  File GENERATExRESTORE_R1R3.c generated by XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
GENERATExRESTORE_R1R3 (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExRESTORE_R1R3");
  // DO FOR I = 0 TO 1; (2994)
  {
    int32_t from45, to45, by45;
    from45 = 0;
    to45 = 1;
    by45 = 1;
    for (putBIT (16, mGENERATExRESTORE_R1R3xI, fixedToBit (16, from45));
         bitToFixed (getBIT (16, mGENERATExRESTORE_R1R3xI)) <= to45; putBIT (
             16, mGENERATExRESTORE_R1R3xI,
             fixedToBit (16, bitToFixed (getBIT (16, mGENERATExRESTORE_R1R3xI))
                                 + by45)))
      {
        // FLAG(I) = SHR(CODE(GET_CODE(CODE_LINE-1)),16); (2995)
        {
          int32_t numberRHS = (int32_t)(SHR (
              getFIXED (
                  mCODE
                  + 4
                        * (putFIXED (mGET_CODExCTR,
                                     xsubtract (getFIXED (mCODE_LINE), 1)),
                           GET_CODE (0))),
              16));
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16,
                  mGENERATExRESTORE_R1R3xFLAG
                      + 2 * (COREHALFWORD (mGENERATExRESTORE_R1R3xI)),
                  bitRHS);
          bitRHS->inUse = 0;
        }
        // VALUE(I) = CODE(GET_CODE(CODE_LINE-1)) &  65535; (2996)
        {
          int32_t numberRHS = (int32_t)(xAND (
              getFIXED (
                  mCODE
                  + 4
                        * (putFIXED (mGET_CODExCTR,
                                     xsubtract (getFIXED (mCODE_LINE), 1)),
                           GET_CODE (0))),
              65535));
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16,
                  mGENERATExRESTORE_R1R3xVALUE
                      + 2 * (COREHALFWORD (mGENERATExRESTORE_R1R3xI)),
                  bitRHS);
          bitRHS->inUse = 0;
        }
        // IF (FLAG(I) = PROLOG) | (FLAG(I) = DELTA) |   (FLAG(I) = RLD) THEN
        // (2997)
        if (1
            & (xOR (
                xOR (xEQ (COREHALFWORD (
                              mGENERATExRESTORE_R1R3xFLAG
                              + 2 * COREHALFWORD (mGENERATExRESTORE_R1R3xI)),
                          BYTE0 (mPROLOG)),
                     xEQ (COREHALFWORD (
                              mGENERATExRESTORE_R1R3xFLAG
                              + 2 * COREHALFWORD (mGENERATExRESTORE_R1R3xI)),
                          BYTE0 (mDELTA))),
                xEQ (COREHALFWORD (
                         mGENERATExRESTORE_R1R3xFLAG
                         + 2 * COREHALFWORD (mGENERATExRESTORE_R1R3xI)),
                     BYTE0 (mRLD)))))
          // CODE_LINE = CODE_LINE - 1; (2998)
          {
            int32_t numberRHS
                = (int32_t)(xsubtract (getFIXED (mCODE_LINE), 1));
            putFIXED (mCODE_LINE, numberRHS);
          }
      }
  } // End of DO for-loop block
  // IF (INST = BC) | (INST = BCF) | (INST = BCR) | (INST = BCRE) & (COND ~=
  // ALWAYS) THEN (2999)
  if (1
      & (xOR (
          xOR (xOR (xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xINST),
                         BYTE0 (mBC)),
                    xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xINST),
                         BYTE0 (mBCF))),
               xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xINST), BYTE0 (mBCR))),
          xAND (
              xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xINST), BYTE0 (mBCRE)),
              xNEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xCOND),
                    BYTE0 (mALWAYS))))))
    // DO; (3000)
    {
    rs2:;
      // CALL EMITC(RXTYPE, SHL(IHL,8) | SHL(XREG & RM,4)); (3001)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mRXTYPE));
        putBITp (
            16, mEMITCxINST,
            fixedToBit (
                32, (int32_t)(xOR (
                        SHL (BYTE0 (mIHL), 8),
                        SHL (xAND (COREHALFWORD (mGENERATExRESTORE_R1R3xXREG),
                                   getFIXED (mRM)),
                             4)))));
        EMITC (0);
      }
      // CALL EMITC(CSYM, TEMPBASE); (3002)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mCSYM));
        putBITp (16, mEMITCxINST, getBIT (8, mTEMPBASE));
        EMITC (0);
      }
      // CALL EMITC(ADCON, STACKLOC); (3003)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mADCON));
        putBITp (16, mEMITCxINST,
                 getBIT (16, mGENERATExRESTORE_R1R3xSTACKLOC));
        EMITC (0);
      }
      // CALL OPSTAT(IHL,XREG); (3004)
      {
        putBITp (16, mGENERATExOPSTATxINST, getBIT (8, mIHL));
        putBITp (16, mGENERATExOPSTATxXREG,
                 getBIT (16, mGENERATExRESTORE_R1R3xXREG));
        GENERATExOPSTAT (0);
      }
      // CALL EMITC(SRSTYPE, SHL(SLL,8) | SHL(XREG,4)); (3005)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mSRSTYPE));
        putBITp (16, mEMITCxINST,
                 fixedToBit (
                     32, (int32_t)(xOR (
                             SHL (BYTE0 (mSLL), 8),
                             SHL (COREHALFWORD (mGENERATExRESTORE_R1R3xXREG),
                                  4)))));
        EMITC (0);
      }
      // CALL EMITC(SHCOUNT, 16); (3006)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mSHCOUNT));
        putBITp (16, mEMITCxINST, fixedToBit (32, (int32_t)(16)));
        EMITC (0);
      }
      // CALL OPSTAT(SLL,XREG); (3007)
      {
        putBITp (16, mGENERATExOPSTATxINST, getBIT (8, mSLL));
        putBITp (16, mGENERATExOPSTATxXREG,
                 getBIT (16, mGENERATExRESTORE_R1R3xXREG));
        GENERATExOPSTAT (0);
      }
    es2:;
    } // End of DO block
  // ELSE (3008)
  else
    // DO; (3009)
    {
    rs3:;
      // CALL EMITC(SRSTYPE, SHL(LH,8) | SHL(XREG & RM,4)); (3010)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mSRSTYPE));
        putBITp (
            16, mEMITCxINST,
            fixedToBit (
                32, (int32_t)(xOR (
                        SHL (BYTE0 (mLH), 8),
                        SHL (xAND (COREHALFWORD (mGENERATExRESTORE_R1R3xXREG),
                                   getFIXED (mRM)),
                             4)))));
        EMITC (0);
      }
      // CALL EMITC(CSYM, TEMPBASE); (3011)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mCSYM));
        putBITp (16, mEMITCxINST, getBIT (8, mTEMPBASE));
        EMITC (0);
      }
      // CALL EMITC(ADCON, STACKLOC); (3012)
      {
        putBITp (16, mEMITCxTYPE, getBIT (8, mADCON));
        putBITp (16, mEMITCxINST,
                 getBIT (16, mGENERATExRESTORE_R1R3xSTACKLOC));
        EMITC (0);
      }
      // CALL OPSTAT(LH,XREG); (3013)
      {
        putBITp (16, mGENERATExOPSTATxINST, getBIT (8, mLH));
        putBITp (16, mGENERATExOPSTATxXREG,
                 getBIT (16, mGENERATExRESTORE_R1R3xXREG));
        GENERATExOPSTAT (0);
      }
    es3:;
    } // End of DO block
  // IF (FLAG(1) = PROLOG) | (FLAG(1) = DELTA) |  (FLAG(1) = RLD)  THEN (3014)
  if (1
      & (xOR (xOR (xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xFLAG + 2 * 1),
                        BYTE0 (mPROLOG)),
                   xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xFLAG + 2 * 1),
                        BYTE0 (mDELTA))),
              xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xFLAG + 2 * 1),
                   BYTE0 (mRLD)))))
    // CALL EMITC(FLAG(1), VALUE(1)); (3015)
    {
      putBITp (16, mEMITCxTYPE,
               getBIT (16, mGENERATExRESTORE_R1R3xFLAG + 2 * 1));
      putBITp (16, mEMITCxINST,
               getBIT (16, mGENERATExRESTORE_R1R3xVALUE + 2 * 1));
      EMITC (0);
    }
  // IF (FLAG = PROLOG) | (FLAG = DELTA) |   (FLAG = RLD) THEN (3016)
  if (1
      & (xOR (xOR (xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xFLAG),
                        BYTE0 (mPROLOG)),
                   xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xFLAG),
                        BYTE0 (mDELTA))),
              xEQ (COREHALFWORD (mGENERATExRESTORE_R1R3xFLAG), BYTE0 (mRLD)))))
    // CALL EMITC(FLAG, VALUE); (3017)
    {
      putBITp (16, mEMITCxTYPE, getBIT (16, mGENERATExRESTORE_R1R3xFLAG));
      putBITp (16, mEMITCxINST, getBIT (16, mGENERATExRESTORE_R1R3xVALUE));
      EMITC (0);
    }
  // R_VAR(XREG) = 0; (3018)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mR_VAR + 2 * (COREHALFWORD (mGENERATExRESTORE_R1R3xXREG)),
            bitRHS);
    bitRHS->inUse = 0;
  }
  // DO I = 1 TO STACK_MAX; (3019)
  {
    int32_t from46, to46, by46;
    from46 = 1;
    to46 = bitToFixed (getBIT (16, mSTACK_MAX));
    by46 = 1;
    for (putBIT (16, mGENERATExRESTORE_R1R3xI, fixedToBit (16, from46));
         bitToFixed (getBIT (16, mGENERATExRESTORE_R1R3xI)) <= to46; putBIT (
             16, mGENERATExRESTORE_R1R3xI,
             fixedToBit (16, bitToFixed (getBIT (16, mGENERATExRESTORE_R1R3xI))
                                 + by46)))
      {
        // IF STACK_PTR(I) < 0 &  FORM(I) = CSYM & BASE(I) = XREG  THEN (3020)
        if (1
            & (xAND (
                xAND (xLT (COREHALFWORD (
                               mSTACK_PTR
                               + 2 * COREHALFWORD (mGENERATExRESTORE_R1R3xI)),
                           0),
                      xEQ (COREHALFWORD (
                               getFIXED (mIND_STACK)
                               + 73 * (COREHALFWORD (mGENERATExRESTORE_R1R3xI))
                               + 32 + 2 * (0)),
                           BYTE0 (mCSYM))),
                xEQ (COREHALFWORD (
                         getFIXED (mIND_STACK)
                         + 73 * (COREHALFWORD (mGENERATExRESTORE_R1R3xI)) + 22
                         + 2 * (0)),
                     COREHALFWORD (mGENERATExRESTORE_R1R3xXREG)))))
          // FORM(I) = SYM; (3021)
          {
            descriptor_t *bitRHS = getBIT (8, mSYM);
            putBIT (16,
                    getFIXED (mIND_STACK)
                        + 73 * (COREHALFWORD (mGENERATExRESTORE_R1R3xI)) + 32
                        + 2 * (0),
                    bitRHS);
            bitRHS->inUse = 0;
          }
      }
  } // End of DO for-loop block
  {
    reentryGuard = 0;
    return 0;
  }
}