/*
  File GENERATExMAT_NEGATE.c generated by XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
GENERATExMAT_NEGATE (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExMAT_NEGATE");
  // IF OPCODE = XXASN THEN (9043)
  if (1 & (xEQ (COREHALFWORD (mOPCODE), BYTE0 (mXXASN))))
    // DO; (9044)
    {
    rs1:;
      // RESULT = GET_OPERAND(1); (9045)
      {
        descriptor_t *bitRHS = (putBITp (16, mGENERATExGET_OPERANDxOP,
                                         fixedToBit (32, (int32_t)(1))),
                                GENERATExGET_OPERAND (0));
        putBIT (16, mRESULT, bitRHS);
        bitRHS->inUse = 0;
      }
      // TMP = NEWPREC(TAG &  63); (9046)
      {
        descriptor_t *bitRHS = getBIT (
            16, mGENERATExNEWPREC + 2 * xAND (COREHALFWORD (mTAG), 63));
        int32_t numberRHS;
        numberRHS = bitToFixed (bitRHS);
        putFIXED (mTMP, numberRHS);
        bitRHS->inUse = 0;
      }
      // IF VDLP_ACTIVE THEN (9047)
      if (1 & (bitToFixed (getBIT (1, mVDLP_ACTIVE))))
        // DO; (9048)
        {
        rs1s1:;
          // CALL FORCE_ACCUMULATOR(RESULT, TMP | CLASS); (9049)
          {
            putBITp (16, mGENERATExFORCE_ACCUMULATORxOP, getBIT (16, mRESULT));
            putBITp (16, mGENERATExFORCE_ACCUMULATORxOPTYPE,
                     fixedToBit (32, (int32_t)(xOR (getFIXED (mTMP),
                                                    COREHALFWORD (mCLASS)))));
            GENERATExFORCE_ACCUMULATOR (0);
          }
          // VMCOPY(RESULT) = SHR(TAG,6); (9050)
          {
            int32_t numberRHS = (int32_t)(SHR (COREHALFWORD (mTAG), 6));
            putBIT (8,
                    getFIXED (mIND_STACK) + 73 * (COREHALFWORD (mRESULT)) + 67
                        + 1 * (0),
                    fixedToBit (8, numberRHS));
          }
        es1s1:;
        } // End of DO block
      // ELSE (9051)
      else
        // IF (TYPE(RESULT)&8) ~= TMP THEN (9052)
        if (1
            & (xNEQ (xAND (COREHALFWORD (getFIXED (mIND_STACK)
                                         + 73 * (COREHALFWORD (mRESULT)) + 50
                                         + 2 * (0)),
                           8),
                     getFIXED (mTMP))))
          // DO; (9053)
          {
          rs1s2:;
            // RESULT = VECMAT_CONVERT(RESULT, TMP | CLASS); (9054)
            {
              int32_t numberRHS = (int32_t)((
                  putBITp (16, mGENERATExVECMAT_CONVERTxOP,
                           getBIT (16, mRESULT)),
                  putBITp (
                      16, mGENERATExVECMAT_CONVERTxPREC_SPEC,
                      fixedToBit (32, (int32_t)(xOR (getFIXED (mTMP),
                                                     COREHALFWORD (mCLASS))))),
                  GENERATExVECMAT_CONVERT (0)));
              descriptor_t *bitRHS;
              bitRHS = fixedToBit (32, (int32_t)(numberRHS));
              putBIT (16, mRESULT, bitRHS);
              bitRHS->inUse = 0;
            }
            // LASTRESULT = RESULT; (9055)
            {
              descriptor_t *bitRHS = getBIT (16, mRESULT);
              putBIT (16, mLASTRESULT, bitRHS);
              bitRHS->inUse = 0;
            }
          es1s2:;
          } // End of DO block
    es1:;
    } // End of DO block
  // ELSE (9056)
  else
    // DO; (9057)
    {
    rs2:;
      // CALL ARG_ASSEMBLE; (9058)
      GENERATExARG_ASSEMBLE (0);
      // TEMPSPACE = ROW(0) * COLUMN(0); (9059)
      {
        int32_t numberRHS = (int32_t)(xmultiply (
            COREHALFWORD (getFIXED (mIND_STACK) + 73 * (0) + 48 + 2 * (0)),
            COREHALFWORD (getFIXED (mIND_STACK) + 73 * (0) + 24 + 2 * (0))));
        putFIXED (mTEMPSPACE, numberRHS);
      }
      // CLASS3_OP=TRUE; (9060)
      {
        int32_t numberRHS = (int32_t)(1);
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (1, mGENERATExCLASS3_OP, bitRHS);
        bitRHS->inUse = 0;
      }
      // CALL MAT_TEMP; (9061)
      GENERATExMAT_TEMP (0);
    es2:;
    } // End of DO block
  {
    reentryGuard = 0;
    return 0;
  }
}