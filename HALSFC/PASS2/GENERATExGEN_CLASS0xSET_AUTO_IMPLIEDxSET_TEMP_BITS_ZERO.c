/*
  File GENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZERO.c generated by
  XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
GENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZERO (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (
      reentryGuard, "GENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZERO");
  // RESULT = SET_OPERAND(PTR1); (11878)
  {
    descriptor_t *bitRHS
        = (putBITp (
               16, mGENERATExSET_OPERANDxOP,
               getBIT (
                   16,
                   mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxPTR1)),
           GENERATExSET_OPERAND (0));
    putBIT (16, mRESULT, bitRHS);
    bitRHS->inUse = 0;
  }
  // HW = SYT_TYPE(PTR2) = BITS; (11879)
  {
    int32_t numberRHS = (int32_t)(xEQ (
        BYTE0 (
            getFIXED (mSYM_TAB)
            + 34
                  * (COREHALFWORD (
                      mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxPTR2))
            + 32 + 1 * (0)),
        BYTE0 (mBITS)));
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (8, mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxHW,
            bitRHS);
    bitRHS->inUse = 0;
  }
  // INX_CON(RESULT) = CON; (11880)
  {
    int32_t numberRHS = (int32_t)(getFIXED (
        mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxCON));
    putFIXED (getFIXED (mIND_STACK) + 73 * (COREHALFWORD (mRESULT)) + 4
                  + 4 * (0),
              numberRHS);
  }
  // IF HW THEN (11881)
  if (1
      & (bitToFixed (getBIT (
          8, mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxHW))))
    // DO; (11882)
    {
    rs1:;
      // OP = ZH; (11883)
      {
        descriptor_t *bitRHS = getBIT (8, mZH);
        putBIT (16,
                mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxOP,
                bitRHS);
        bitRHS->inUse = 0;
      }
      // K = 0; (11884)
      {
        int32_t numberRHS = (int32_t)(0);
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (16, mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxK, bitRHS);
        bitRHS->inUse = 0;
      }
    es1:;
    } // End of DO block
  // ELSE (11885)
  else
    // DO; (11886)
    {
    rs2:;
      // OP = ST; (11887)
      {
        descriptor_t *bitRHS = getBIT (8, mST);
        putBIT (16,
                mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxOP,
                bitRHS);
        bitRHS->inUse = 0;
      }
      // K = LOAD_NUM(-1,0,8); (11888)
      {
        int32_t numberRHS = (int32_t)((
            putBITp (16, mGENERATExLOAD_NUMxR, fixedToBit (32, (int32_t)(-1))),
            putFIXED (mGENERATExLOAD_NUMxNUM, 0),
            putBITp (1, mGENERATExLOAD_NUMxFLAG,
                     fixedToBit (32, (int32_t)(8))),
            GENERATExLOAD_NUM (0)));
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (16, mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxK, bitRHS);
        bitRHS->inUse = 0;
      }
    es2:;
    } // End of DO block
  // I = LUMP_ARRAYSIZE(PTR2); (11889)
  {
    int32_t numberRHS = (int32_t)((
        putBITp (
            16, mGENERATExLUMP_ARRAYSIZExOP,
            getBIT (
                16,
                mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxPTR2)),
        GENERATExLUMP_ARRAYSIZE (0)));
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxI, bitRHS);
    bitRHS->inUse = 0;
  }
  // CALL GUARANTEE_ADDRESSABLE(RESULT, OP); (11890)
  {
    putBITp (16, mGENERATExGUARANTEE_ADDRESSABLExOP, getBIT (16, mRESULT));
    putBITp (
        16, mGENERATExGUARANTEE_ADDRESSABLExINST,
        getBIT (16,
                mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxOP));
    GENERATExGUARANTEE_ADDRESSABLE (0);
  }
  // IF I>1 THEN (11891)
  if (1 & (xGT (COREHALFWORD (mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxI), 1)))
    // DO; (11892)
    {
    rs3:;
      // INDEX = FINDAC(INDEX_REG); (11893)
      {
        descriptor_t *bitRHS = (putBITp (16, mGENERATExFINDACxRCLASS,
                                         fixedToBit (32, (int32_t)(4))),
                                GENERATExFINDAC (0));
        putBIT (16, mINDEX, bitRHS);
        bitRHS->inUse = 0;
      }
      // INX(RESULT) = INDEX; (11894)
      {
        descriptor_t *bitRHS = getBIT (16, mINDEX);
        putBIT (16,
                getFIXED (mIND_STACK) + 73 * (COREHALFWORD (mRESULT)) + 34
                    + 2 * (0),
                bitRHS);
        bitRHS->inUse = 0;
      }
      // CALL LOAD_NUM(INDEX, I-1, 9); (11895)
      {
        putBITp (16, mGENERATExLOAD_NUMxR, getBIT (16, mINDEX));
        putFIXED (
            mGENERATExLOAD_NUMxNUM,
            xsubtract (COREHALFWORD (mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxI),
                       1));
        putBITp (1, mGENERATExLOAD_NUMxFLAG, fixedToBit (32, (int32_t)(9)));
        GENERATExLOAD_NUM (0);
      }
      // FIRSTLABEL = GETSTATNO; (11896)
      {
        descriptor_t *bitRHS = GETSTATNO (0);
        putBIT (16, mFIRSTLABEL, bitRHS);
        bitRHS->inUse = 0;
      }
      // CALL SET_LABEL(FIRSTLABEL, 1); (11897)
      {
        putBITp (16, mGENERATExSET_LABELxSTMTNO, getBIT (16, mFIRSTLABEL));
        putBITp (1, mGENERATExSET_LABELxFLAG1, fixedToBit (32, (int32_t)(1)));
        GENERATExSET_LABEL (0);
      }
      // CALL EMITOP(OP,K,RESULT); (11898)
      {
        putBITp (
            16, mGENERATExEMITOPxINST,
            getBIT (
                16,
                mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxOP));
        putBITp (16, mGENERATExEMITOPxXREG,
                 getBIT (16, mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxK));
        putBITp (16, mGENERATExEMITOPxOP, getBIT (16, mRESULT));
        GENERATExEMITOP (0);
      }
      // CALL EMITPFW(BIX, INDEX, GETSTMTLBL(FIRSTLABEL)); (11899)
      {
        putBITp (16, mGENERATExEMITPFWxINST, getBIT (8, mBIX));
        putBITp (16, mGENERATExEMITPFWxXREG, getBIT (16, mINDEX));
        putBITp (16, mGENERATExEMITPFWxPTR,
                 (putFIXED (mGENERATExGETSTMTLBLxSTATNO,
                            COREHALFWORD (mFIRSTLABEL)),
                  GENERATExGETSTMTLBL (0)));
        GENERATExEMITPFW (0);
      }
      // USAGE(INDEX) = 0; (11900)
      {
        int32_t numberRHS = (int32_t)(0);
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (16, mUSAGE + 2 * (COREHALFWORD (mINDEX)), bitRHS);
        bitRHS->inUse = 0;
      }
    es3:;
    } // End of DO block
  // ELSE (11901)
  else
    // DO; (11902)
    {
    rs4:;
      // IF ( (LASTADDR ~= SYT_ADDR(LOC(RESULT))+CON) |  (LASTLOC ~=
      // LOC(RESULT)) ) THEN (11903)
      if (1
          & (xOR (
              xNEQ (
                  COREHALFWORD (
                      mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxLASTADDR),
                  xadd (
                      getFIXED (getFIXED (mSYM_TAB)
                                + 34
                                      * (COREHALFWORD (
                                          getFIXED (mIND_STACK)
                                          + 73 * (COREHALFWORD (mRESULT)) + 40
                                          + 2 * (0)))
                                + 4 + 4 * (0)),
                      getFIXED (
                          mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxCON))),
              xNEQ (
                  COREHALFWORD (
                      mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxLASTLOC),
                  COREHALFWORD (getFIXED (mIND_STACK)
                                + 73 * (COREHALFWORD (mRESULT)) + 40
                                + 2 * (0))))))
        // DO; (11904)
        {
        rs4s1:;
          // LASTADDR = SYT_ADDR(LOC(RESULT))+CON; (11905)
          {
            int32_t numberRHS = (int32_t)(xadd (
                getFIXED (
                    getFIXED (mSYM_TAB)
                    + 34
                          * (COREHALFWORD (getFIXED (mIND_STACK)
                                           + 73 * (COREHALFWORD (mRESULT)) + 40
                                           + 2 * (0)))
                    + 4 + 4 * (0)),
                getFIXED (
                    mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxCON)));
            descriptor_t *bitRHS;
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (
                16,
                mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxLASTADDR,
                bitRHS);
            bitRHS->inUse = 0;
          }
          // LASTLOC = LOC(RESULT); (11906)
          {
            descriptor_t *bitRHS = getBIT (
                16, getFIXED (mIND_STACK) + 73 * (COREHALFWORD (mRESULT)) + 40
                        + 2 * (0));
            putBIT (
                16,
                mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxLASTLOC,
                bitRHS);
            bitRHS->inUse = 0;
          }
          // CALL EMITOP(OP, K, RESULT); (11907)
          {
            putBITp (
                16, mGENERATExEMITOPxINST,
                getBIT (
                    16,
                    mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxOP));
            putBITp (16, mGENERATExEMITOPxXREG,
                     getBIT (16, mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxK));
            putBITp (16, mGENERATExEMITOPxOP, getBIT (16, mRESULT));
            GENERATExEMITOP (0);
          }
        es4s1:;
        } // End of DO block
    es4:;
    } // End of DO block
  // IF ~HW THEN (11908)
  if (1
      & (xNOT (BYTE0 (
          mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxSET_TEMP_BITS_ZEROxHW))))
    // USAGE(K) = USAGE(K) - 2; (11909)
    {
      int32_t numberRHS = (int32_t)(xsubtract (
          COREHALFWORD (
              mUSAGE
              + 2 * COREHALFWORD (mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxK)),
          2));
      descriptor_t *bitRHS;
      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
      putBIT (
          16,
          mUSAGE
              + 2 * (COREHALFWORD (mGENERATExGEN_CLASS0xSET_AUTO_IMPLIEDxK)),
          bitRHS);
      bitRHS->inUse = 0;
    }
  // CALL RETURN_STACK_ENTRY(RESULT); (11910)
  {
    putBITp (16, mGENERATExRETURN_STACK_ENTRYxP, getBIT (16, mRESULT));
    GENERATExRETURN_STACK_ENTRY (0);
  }
  {
    reentryGuard = 0;
    return 0;
  }
}