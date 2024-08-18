/*
  File GENERATExIDENT_DISJOINT_CHECK.c generated by XCOM-I, 2024-08-09
  12:41:32.
*/

#include "runtimeC.h"

int32_t
GENERATExIDENT_DISJOINT_CHECK (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExIDENT_DISJOINT_CHECK");
  // OPER_PARM_FLAG,NON_IDENT,DISJOINT,CONSEC_VAC=FALSE; (8832)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (1, mGENERATExOPER_PARM_FLAG, bitRHS);
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT, bitRHS);
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxCONSEC_VAC, bitRHS);
    bitRHS->inUse = 0;
  }
  // IF SYMFORM(FORM(OP)) THEN (8833)
  if (1
      & (bitToFixed (getBIT (
          1, mSYMFORM
                 + 1
                       * COREHALFWORD (
                           getFIXED (mIND_STACK)
                           + 73
                                 * (COREHALFWORD (
                                     mGENERATExIDENT_DISJOINT_CHECKxOP))
                           + 32 + 2 * (0))))))
    // DO; (8834)
    {
    rs1:;
      // OPER_PARM_FLAG=(SYT_FLAGS(LOC(OP)) & PARM_FLAGS)~=0; (8835)
      {
        int32_t numberRHS = (int32_t)(xNEQ (
            xAND (getFIXED (
                      getFIXED (mSYM_TAB)
                      + 34
                            * (COREHALFWORD (
                                getFIXED (mIND_STACK)
                                + 73
                                      * (COREHALFWORD (
                                          mGENERATExIDENT_DISJOINT_CHECKxOP))
                                + 40 + 2 * (0)))
                      + 8 + 4 * (0)),
                  getFIXED (mPARM_FLAGS)),
            0));
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (1, mGENERATExOPER_PARM_FLAG, bitRHS);
        bitRHS->inUse = 0;
      }
      // OPER_SYMPTR=LOC(OP); (8836)
      {
        descriptor_t *bitRHS = getBIT (
            16, getFIXED (mIND_STACK)
                    + 73 * (COREHALFWORD (mGENERATExIDENT_DISJOINT_CHECKxOP))
                    + 40 + 2 * (0));
        putBIT (16, mGENERATExOPER_SYMPTR, bitRHS);
        bitRHS->inUse = 0;
      }
      // OPER_STRUCT = SYT_TYPE(LOC(OP)) = STRUCTURE; (8837)
      {
        int32_t numberRHS = (int32_t)(xEQ (
            BYTE0 (getFIXED (mSYM_TAB)
                   + 34
                         * (COREHALFWORD (
                             getFIXED (mIND_STACK)
                             + 73
                                   * (COREHALFWORD (
                                       mGENERATExIDENT_DISJOINT_CHECKxOP))
                             + 40 + 2 * (0)))
                   + 32 + 1 * (0)),
            BYTE0 (mSTRUCTURE)));
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (1, mGENERATExOPER_STRUCT, bitRHS);
        bitRHS->inUse = 0;
      }
      // OPER_SYMPTR2 = LOC2(OP); (8838)
      {
        descriptor_t *bitRHS = getBIT (
            16, getFIXED (mIND_STACK)
                    + 73 * (COREHALFWORD (mGENERATExIDENT_DISJOINT_CHECKxOP))
                    + 42 + 2 * (0));
        putBIT (16, mGENERATExOPER_SYMPTR2, bitRHS);
        bitRHS->inUse = 0;
      }
      // CONSEC_VAC=TAG_BITS(N)=VAC; (8839)
      {
        int32_t numberRHS = (int32_t)(xEQ (
            bitToFixed (
                (putBITp (16, mGENERATExTAG_BITSxOP,
                          getBIT (16, mGENERATExIDENT_DISJOINT_CHECKxN)),
                 GENERATExTAG_BITS (0))),
            BYTE0 (mVAC)));
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxCONSEC_VAC, bitRHS);
        bitRHS->inUse = 0;
      }
    es1:;
    } // End of DO block
  // ELSE (8840)
  else
    // NON_IDENT,DISJOINT=TRUE; (8841)
    {
      int32_t numberRHS = (int32_t)(1);
      descriptor_t *bitRHS;
      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
      putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT, bitRHS);
      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
      putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
      bitRHS->inUse = 0;
    }
  // IF ~NON_IDENT & RECVR_SYMPTR~=OPER_SYMPTR THEN (8842)
  if (1
      & (xAND (xNOT (BYTE0 (mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT)),
               xNEQ (COREHALFWORD (mGENERATExRECVR_SYMPTR),
                     COREHALFWORD (mGENERATExOPER_SYMPTR)))))
    // DO; (8843)
    {
    rs2:;
      // IF (~ASSIGN_PARM_FLAG & ~OPER_PARM_FLAG) THEN (8844)
      if (1
          & (xAND (xNOT (BYTE0 (mGENERATExASSIGN_PARM_FLAG)),
                   xNOT (BYTE0 (mGENERATExOPER_PARM_FLAG)))))
        // NON_IDENT,DISJOINT=TRUE; (8845)
        {
          int32_t numberRHS = (int32_t)(1);
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT, bitRHS);
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
          bitRHS->inUse = 0;
        }
      // IF ASSIGN_PARM_FLAG & ~OPER_PARM_FLAG THEN (8846)
      if (1
          & (xAND (BYTE0 (mGENERATExASSIGN_PARM_FLAG),
                   xNOT (BYTE0 (mGENERATExOPER_PARM_FLAG)))))
        // IF SYT_NEST(LOC(OP))>=RECVR_NEST_LEVEL THEN (8847)
        if (1
            & (xGE (
                BYTE0 (getFIXED (mSYM_TAB)
                       + 34
                             * (COREHALFWORD (
                                 getFIXED (mIND_STACK)
                                 + 73
                                       * (COREHALFWORD (
                                           mGENERATExIDENT_DISJOINT_CHECKxOP))
                                 + 40 + 2 * (0)))
                       + 28 + 1 * (0)),
                BYTE0 (mGENERATExRECVR_NEST_LEVEL))))
          // NON_IDENT,DISJOINT=TRUE; (8848)
          {
            int32_t numberRHS = (int32_t)(1);
            descriptor_t *bitRHS;
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT, bitRHS);
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
            bitRHS->inUse = 0;
          }
      // IF OPER_PARM_FLAG & ~ASSIGN_PARM_FLAG THEN (8849)
      if (1
          & (xAND (BYTE0 (mGENERATExOPER_PARM_FLAG),
                   xNOT (BYTE0 (mGENERATExASSIGN_PARM_FLAG)))))
        // IF RECVR_NEST_LEVEL>=SYT_NEST(LOC(OP)) THEN (8850)
        if (1
            & (xGE (
                BYTE0 (mGENERATExRECVR_NEST_LEVEL),
                BYTE0 (getFIXED (mSYM_TAB)
                       + 34
                             * (COREHALFWORD (
                                 getFIXED (mIND_STACK)
                                 + 73
                                       * (COREHALFWORD (
                                           mGENERATExIDENT_DISJOINT_CHECKxOP))
                                 + 40 + 2 * (0)))
                       + 28 + 1 * (0)))))
          // NON_IDENT,DISJOINT=TRUE; (8851)
          {
            int32_t numberRHS = (int32_t)(1);
            descriptor_t *bitRHS;
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT, bitRHS);
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
            bitRHS->inUse = 0;
          }
    es2:;
    } // End of DO block
  // IF ~DISJOINT THEN (8852)
  if (1 & (xNOT (BYTE0 (mGENERATExIDENT_DISJOINT_CHECKxDISJOINT))))
    // DO; (8853)
    {
    rs3:;
      // IF STMT_PREC~=0 THEN (8854)
      if (1 & (xNEQ (COREHALFWORD (mGENERATExSTMT_PREC), 0)))
        // DATA_WIDTH=4; (8855)
        {
          int32_t numberRHS = (int32_t)(4);
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16, mGENERATExDATA_WIDTH, bitRHS);
          bitRHS->inUse = 0;
        }
      // ELSE (8856)
      else
        // DATA_WIDTH=2; (8857)
        {
          int32_t numberRHS = (int32_t)(2);
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16, mGENERATExDATA_WIDTH, bitRHS);
          bitRHS->inUse = 0;
        }
      // START_PART=INX_CON(OP); (8858)
      {
        int32_t numberRHS = (int32_t)(getFIXED (
            getFIXED (mIND_STACK)
            + 73 * (COREHALFWORD (mGENERATExIDENT_DISJOINT_CHECKxOP)) + 4
            + 4 * (0)));
        putFIXED (mGENERATExSTART_PART, numberRHS);
      }
      // SRCEPART_SIZE = START_PART + ROW(OP) * COLUMN(OP) * DATA_WIDTH; (8859)
      {
        int32_t numberRHS = (int32_t)(xadd (
            getFIXED (mGENERATExSTART_PART),
            xmultiply (
                xmultiply (
                    COREHALFWORD (getFIXED (mIND_STACK)
                                  + 73
                                        * (COREHALFWORD (
                                            mGENERATExIDENT_DISJOINT_CHECKxOP))
                                  + 48 + 2 * (0)),
                    COREHALFWORD (getFIXED (mIND_STACK)
                                  + 73
                                        * (COREHALFWORD (
                                            mGENERATExIDENT_DISJOINT_CHECKxOP))
                                  + 24 + 2 * (0))),
                COREHALFWORD (mGENERATExDATA_WIDTH))));
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (16, mGENERATExSRCEPART_SIZE, bitRHS);
        bitRHS->inUse = 0;
      }
      // SRCEPART_SIZE = SRCEPART_SIZE + (ROW(OP) - 1) * DEL(OP); (8860)
      {
        int32_t numberRHS = (int32_t)(xadd (
            COREHALFWORD (mGENERATExSRCEPART_SIZE),
            xmultiply (
                xsubtract (
                    COREHALFWORD (getFIXED (mIND_STACK)
                                  + 73
                                        * (COREHALFWORD (
                                            mGENERATExIDENT_DISJOINT_CHECKxOP))
                                  + 48 + 2 * (0)),
                    1),
                COREHALFWORD (
                    getFIXED (mIND_STACK)
                    + 73 * (COREHALFWORD (mGENERATExIDENT_DISJOINT_CHECKxOP))
                    + 28 + 2 * (0)))));
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (16, mGENERATExSRCEPART_SIZE, bitRHS);
        bitRHS->inUse = 0;
      }
      // IF ~RECVR_STRUCT & ~OPER_STRUCT THEN (8861)
      if (1
          & (xAND (xNOT (BYTE0 (mGENERATExRECVR_STRUCT)),
                   xNOT (BYTE0 (mGENERATExOPER_STRUCT)))))
        // DO; (8862)
        {
        rs3s1:;
          // IF CONSEC_VAC & ~NONPART THEN (8863)
          if (1
              & (xAND (BYTE0 (mGENERATExIDENT_DISJOINT_CHECKxCONSEC_VAC),
                       xNOT (BYTE0 (mGENERATExNONPART)))))
            // IF INX_OK & INX(OP) = 0 THEN (8864)
            if (1
                & (xAND (BYTE0 (mGENERATExINX_OK),
                         xEQ (COREHALFWORD (
                                  getFIXED (mIND_STACK)
                                  + 73
                                        * (COREHALFWORD (
                                            mGENERATExIDENT_DISJOINT_CHECKxOP))
                                  + 34 + 2 * (0)),
                              0))))
              // IF RECVR_SYMPTR = OPER_SYMPTR THEN (8865)
              if (1
                  & (xEQ (COREHALFWORD (mGENERATExRECVR_SYMPTR),
                          COREHALFWORD (mGENERATExOPER_SYMPTR))))
                // DISJOINT = PART_SIZE <= START_PART | SRCEPART_SIZE <=
                // START_OFF; (8866)
                {
                  int32_t numberRHS = (int32_t)(xOR (
                      xLE (COREHALFWORD (mGENERATExPART_SIZE),
                           getFIXED (mGENERATExSTART_PART)),
                      xLE (COREHALFWORD (mGENERATExSRCEPART_SIZE),
                           getFIXED (mGENERATExSTART_OFF))));
                  descriptor_t *bitRHS;
                  bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                  putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
                  bitRHS->inUse = 0;
                }
              // ELSE (8867)
              else
                // DISJOINT = PART_SIZE <= START_PART; (8868)
                {
                  int32_t numberRHS
                      = (int32_t)(xLE (COREHALFWORD (mGENERATExPART_SIZE),
                                       getFIXED (mGENERATExSTART_PART)));
                  descriptor_t *bitRHS;
                  bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                  putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
                  bitRHS->inUse = 0;
                }
        es3s1:;
        } // End of DO block
      // ELSE (8869)
      else
        // IF RECVR_STRUCT & OPER_STRUCT THEN (8870)
        if (1
            & (xAND (BYTE0 (mGENERATExRECVR_STRUCT),
                     BYTE0 (mGENERATExOPER_STRUCT))))
          // DO; (8871)
          {
          rs3s2:;
            // IF RECVR_SYMPTR = OPER_SYMPTR THEN (8872)
            if (1
                & (xEQ (COREHALFWORD (mGENERATExRECVR_SYMPTR),
                        COREHALFWORD (mGENERATExOPER_SYMPTR))))
              // DO; (8873)
              {
              rs3s2s1:;
                // DISJOINT = ~(RECVR_SYMPTR2 = OPER_SYMPTR2); (8874)
                {
                  int32_t numberRHS = (int32_t)(xNOT (
                      xEQ (COREHALFWORD (mGENERATExRECVR_SYMPTR2),
                           COREHALFWORD (mGENERATExOPER_SYMPTR2))));
                  descriptor_t *bitRHS;
                  bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                  putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
                  bitRHS->inUse = 0;
                }
                // IF ~DISJOINT & INX_OK & INX(OP) = 0 THEN (8875)
                if (1
                    & (xAND (
                        xAND (xNOT (BYTE0 (
                                  mGENERATExIDENT_DISJOINT_CHECKxDISJOINT)),
                              BYTE0 (mGENERATExINX_OK)),
                        xEQ (COREHALFWORD (
                                 getFIXED (mIND_STACK)
                                 + 73
                                       * (COREHALFWORD (
                                           mGENERATExIDENT_DISJOINT_CHECKxOP))
                                 + 34 + 2 * (0)),
                             0))))
                  // DISJOINT = PART_SIZE <= START_PART | SRCEPART_SIZE <=
                  // START_OFF; (8876)
                  {
                    int32_t numberRHS = (int32_t)(xOR (
                        xLE (COREHALFWORD (mGENERATExPART_SIZE),
                             getFIXED (mGENERATExSTART_PART)),
                        xLE (COREHALFWORD (mGENERATExSRCEPART_SIZE),
                             getFIXED (mGENERATExSTART_OFF))));
                    descriptor_t *bitRHS;
                    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                    putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT,
                            bitRHS);
                    bitRHS->inUse = 0;
                  }
              es3s2s1:;
              } // End of DO block
            // ELSE (8877)
            else
              // IF INX_OK & INX(OP) = 0 THEN (8878)
              if (1
                  & (xAND (
                      BYTE0 (mGENERATExINX_OK),
                      xEQ (COREHALFWORD (
                               getFIXED (mIND_STACK)
                               + 73
                                     * (COREHALFWORD (
                                         mGENERATExIDENT_DISJOINT_CHECKxOP))
                               + 34 + 2 * (0)),
                           0))))
                // IF ASSIGN_PARM_FLAG & ~OPER_PARM_FLAG THEN (8879)
                if (1
                    & (xAND (BYTE0 (mGENERATExASSIGN_PARM_FLAG),
                             xNOT (BYTE0 (mGENERATExOPER_PARM_FLAG)))))
                  // DISJOINT = SRCEPART_SIZE <= START_OFF; (8880)
                  {
                    int32_t numberRHS = (int32_t)(xLE (
                        COREHALFWORD (mGENERATExSRCEPART_SIZE),
                        getFIXED (mGENERATExSTART_OFF)));
                    descriptor_t *bitRHS;
                    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                    putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT,
                            bitRHS);
                    bitRHS->inUse = 0;
                  }
                // ELSE (8881)
                else
                  // IF ~ASSIGN_PARM_FLAG & OPER_PARM_FLAG THEN (8882)
                  if (1
                      & (xAND (xNOT (BYTE0 (mGENERATExASSIGN_PARM_FLAG)),
                               BYTE0 (mGENERATExOPER_PARM_FLAG))))
                    // DISJOINT = PART_SIZE <= START_PART; (8883)
                    {
                      int32_t numberRHS
                          = (int32_t)(xLE (COREHALFWORD (mGENERATExPART_SIZE),
                                           getFIXED (mGENERATExSTART_PART)));
                      descriptor_t *bitRHS;
                      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                      putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT,
                              bitRHS);
                      bitRHS->inUse = 0;
                    }
          es3s2:;
          } // End of DO block
        // ELSE (8884)
        else
          // DO; (8885)
          {
          rs3s3:;
            // IF ~(ASSIGN_PARM_FLAG & OPER_PARM_FLAG) THEN (8886)
            if (1
                & (xNOT (xAND (BYTE0 (mGENERATExASSIGN_PARM_FLAG),
                               BYTE0 (mGENERATExOPER_PARM_FLAG)))))
              // DISJOINT = (ASSIGN_PARM_FLAG & RECVR_STRUCT) | (OPER_PARM_FLAG
              // & OPER_STRUCT); (8887)
              {
                int32_t numberRHS
                    = (int32_t)(xOR (xAND (BYTE0 (mGENERATExASSIGN_PARM_FLAG),
                                           BYTE0 (mGENERATExRECVR_STRUCT)),
                                     xAND (BYTE0 (mGENERATExOPER_PARM_FLAG),
                                           BYTE0 (mGENERATExOPER_STRUCT))));
                descriptor_t *bitRHS;
                bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                putBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT, bitRHS);
                bitRHS->inUse = 0;
              }
          es3s3:;
          } // End of DO block
    es3:;
    } // End of DO block
  // IF N=1 THEN (8888)
  if (1 & (xEQ (COREHALFWORD (mGENERATExIDENT_DISJOINT_CHECKxN), 1)))
    // DO; (8889)
    {
    rs4:;
      // LEFT_DISJOINT=DISJOINT; (8890)
      {
        descriptor_t *bitRHS
            = getBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT);
        putBIT (1, mGENERATExLEFT_DISJOINT, bitRHS);
        bitRHS->inUse = 0;
      }
      // LNON_IDENT=NON_IDENT; (8891)
      {
        descriptor_t *bitRHS
            = getBIT (1, mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT);
        putBIT (1, mGENERATExLNON_IDENT, bitRHS);
        bitRHS->inUse = 0;
      }
    es4:;
    } // End of DO block
  // ELSE (8892)
  else
    // DO; (8893)
    {
    rs5:;
      // RIGHT_DISJOINT=DISJOINT; (8894)
      {
        descriptor_t *bitRHS
            = getBIT (1, mGENERATExIDENT_DISJOINT_CHECKxDISJOINT);
        putBIT (1, mGENERATExRIGHT_DISJOINT, bitRHS);
        bitRHS->inUse = 0;
      }
      // RNON_IDENT=NON_IDENT; (8895)
      {
        descriptor_t *bitRHS
            = getBIT (1, mGENERATExIDENT_DISJOINT_CHECKxNON_IDENT);
        putBIT (1, mGENERATExRNON_IDENT, bitRHS);
        bitRHS->inUse = 0;
      }
    es5:;
    } // End of DO block
  // IF NUMOP=1 THEN (8896)
  if (1 & (xEQ (COREHALFWORD (mNUMOP), 1)))
    // RIGHT_DISJOINT,RNON_IDENT=TRUE; (8897)
    {
      int32_t numberRHS = (int32_t)(1);
      descriptor_t *bitRHS;
      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
      putBIT (1, mGENERATExRIGHT_DISJOINT, bitRHS);
      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
      putBIT (1, mGENERATExRNON_IDENT, bitRHS);
      bitRHS->inUse = 0;
    }
  {
    reentryGuard = 0;
    return 0;
  }
}