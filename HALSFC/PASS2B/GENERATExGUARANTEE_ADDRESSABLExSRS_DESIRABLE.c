/*
  File GENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLE.c generated by XCOM-I,
  2024-08-09 12:41:32.
*/

#include "runtimeC.h"

descriptor_t *
GENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLE (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (descriptor_t *)0;
    }
  reentryGuard = guardReentry (reentryGuard,
                               "GENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLE");
  // IF NR_DEREF(OP) THEN (4583)
  if (1
      & (bitToFixed (getBIT (
          8, getFIXED (mIND_STACK)
                 + 73
                       * (COREHALFWORD (
                           mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP))
                 + 60 + 1 * (0)))))
    // RETURN 1; (4584)
    {
      reentryGuard = 0;
      return fixedToBit (32, (int32_t)(1));
    }
  // X=LOC(OP); (4585)
  {
    descriptor_t *bitRHS = getBIT (
        16, getFIXED (mIND_STACK)
                + 73
                      * (COREHALFWORD (
                          mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP))
                + 40 + 2 * (0));
    putBIT (16, mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExX, bitRHS);
    bitRHS->inUse = 0;
  }
  // CURRENT_BASE= SYT_BASE(X); (4586)
  {
    descriptor_t *bitRHS = getBIT (
        16, getFIXED (mP2SYMS)
                + 12
                      * (COREHALFWORD (
                          mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExX))
                + 4 + 2 * (0));
    putBIT (16, mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExCURRENT_BASE,
            bitRHS);
    bitRHS->inUse = 0;
  }
  // IF INX(OP) ~=0 THEN (4587)
  if (1
      & (xNEQ (COREHALFWORD (
                   getFIXED (mIND_STACK)
                   + 73
                         * (COREHALFWORD (
                             mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP))
                   + 34 + 2 * (0)),
               0)))
    // RETURN 1; (4588)
    {
      reentryGuard = 0;
      return fixedToBit (32, (int32_t)(1));
    }
  // IF CHECK_SRS(INST,0,CURRENT_BASE,SYT_DISP(X)+INX_CON(OP)) ~= SRSTYPE THEN
  // (4589)
  if (1
      & (xNEQ (
          bitToFixed ((
              putBITp (16, mCHECK_SRSxINST,
                       getBIT (16, mGENERATExGUARANTEE_ADDRESSABLExINST)),
              putBITp (16, mCHECK_SRSxIX, fixedToBit (32, (int32_t)(0))),
              putBITp (
                  16, mCHECK_SRSxBASE,
                  getBIT (
                      16,
                      mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExCURRENT_BASE)),
              putFIXED (
                  mCHECK_SRSxDISP,
                  xadd (
                      COREHALFWORD (
                          getFIXED (mP2SYMS)
                          + 12
                                * (COREHALFWORD (
                                    mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExX))
                          + 6 + 2 * (0)),
                      getFIXED (
                          getFIXED (mIND_STACK)
                          + 73
                                * (COREHALFWORD (
                                    mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP))
                          + 4 + 4 * (0)))),
              CHECK_SRS (0))),
          BYTE0 (mSRSTYPE))))
    // RETURN 0; (4590)
    {
      reentryGuard = 0;
      return fixedToBit (32, (int32_t)(0));
    }
  // IF NEED_SRS = 1 THEN (4591)
  if (1
      & (xEQ (BYTE0 (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExNEED_SRS),
              1)))
    // RETURN 1; (4592)
    {
      reentryGuard = 0;
      return fixedToBit (32, (int32_t)(1));
    }
  // IF NEED_SRS = 0 THEN (4593)
  if (1
      & (xEQ (BYTE0 (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExNEED_SRS),
              0)))
    // DO; (4594)
    {
    rs1:;
      // I = 0; (4595)
      {
        int32_t numberRHS = (int32_t)(0);
        putFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI, numberRHS);
      }
      // IF (INST& 15) =  8 THEN (4596)
      if (1
          & (xEQ (
              xAND (COREHALFWORD (mGENERATExGUARANTEE_ADDRESSABLExINST), 15),
              8)))
        // DO; (4597)
        {
        rs1s1:;
          // IF OP = LEFTOP THEN (4598)
          if (1
              & (xEQ (COREHALFWORD (
                          mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP),
                      COREHALFWORD (mLEFTOP))))
            // I = RIGHTOP; (4599)
            {
              descriptor_t *bitRHS = getBIT (16, mRIGHTOP);
              int32_t numberRHS;
              numberRHS = bitToFixed (bitRHS);
              putFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI,
                        numberRHS);
              bitRHS->inUse = 0;
            }
          // ELSE (4600)
          else
            // IF OP = RIGHTOP THEN (4601)
            if (1
                & (xEQ (COREHALFWORD (
                            mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP),
                        COREHALFWORD (mRIGHTOP))))
              // I = LEFTOP; (4602)
              {
                descriptor_t *bitRHS = getBIT (16, mLEFTOP);
                int32_t numberRHS;
                numberRHS = bitToFixed (bitRHS);
                putFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI,
                          numberRHS);
                bitRHS->inUse = 0;
              }
        es1s1:;
        } // End of DO block
      // ELSE (4603)
      else
        // IF (INST& 15) =  0 THEN (4604)
        if (1
            & (xEQ (
                xAND (COREHALFWORD (mGENERATExGUARANTEE_ADDRESSABLExINST), 15),
                0)))
          // IF OP = LEFTOP THEN (4605)
          if (1
              & (xEQ (COREHALFWORD (
                          mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP),
                      COREHALFWORD (mLEFTOP))))
            // I = CONST(OP); (4606)
            {
              int32_t numberRHS = (int32_t)(getFIXED (
                  getFIXED (mIND_STACK)
                  + 73
                        * (COREHALFWORD (
                            mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExOP))
                  + 0 + 4 * (0)));
              putFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI,
                        numberRHS);
            }
      // IF I > 0 THEN (4607)
      if (1
          & (xGT (getFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI),
                  0)))
        // IF FORM(I) = SYM THEN (4608)
        if (1
            & (xEQ (
                COREHALFWORD (
                    getFIXED (mIND_STACK)
                    + 73
                          * (getFIXED (
                              mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI))
                    + 32 + 2 * (0)),
                BYTE0 (mSYM))))
          // IF SYT_BASE(LOC(I)) = CURRENT_BASE THEN (4609)
          if (1
              & (xEQ (
                  COREHALFWORD (
                      getFIXED (mP2SYMS)
                      + 12
                            * (COREHALFWORD (
                                getFIXED (mIND_STACK)
                                + 73
                                      * (getFIXED (
                                          mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI))
                                + 40 + 2 * (0)))
                      + 4 + 2 * (0)),
                  COREHALFWORD (
                      mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExCURRENT_BASE))))
            // IF CHECK_SRS(MAKE_INST(LOAD,TYPE(I),RX),INX(I),SYT_BASE(LOC(I)),
            // SYT_DISP(LOC(I))+INX_CON(I)) = SRSTYPE THEN (4610)
            if (1
                & (xEQ (
                    bitToFixed ((
                        putBITp (
                            16, mCHECK_SRSxINST,
                            (putBITp (16, mGENERATExMAKE_INSTxOPCODE,
                                      getBIT (16, mGENERATExLOAD)),
                             putBITp (
                                 16, mGENERATExMAKE_INSTxOPTYPE,
                                 getBIT (
                                     16,
                                     getFIXED (mIND_STACK)
                                         + 73
                                               * (getFIXED (
                                                   mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI))
                                         + 50 + 2 * (0))),
                             putBITp (16, mGENERATExMAKE_INSTxOPFORM,
                                      getBIT (16, mGENERATExRX)),
                             GENERATExMAKE_INST (0))),
                        putBITp (
                            16, mCHECK_SRSxIX,
                            getBIT (
                                16,
                                getFIXED (mIND_STACK)
                                    + 73
                                          * (getFIXED (
                                              mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI))
                                    + 34 + 2 * (0))),
                        putBITp (
                            16, mCHECK_SRSxBASE,
                            getBIT (
                                16,
                                getFIXED (mP2SYMS)
                                    + 12
                                          * (COREHALFWORD (
                                              getFIXED (mIND_STACK)
                                              + 73
                                                    * (getFIXED (
                                                        mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI))
                                              + 40 + 2 * (0)))
                                    + 4 + 2 * (0))),
                        putFIXED (
                            mCHECK_SRSxDISP,
                            xadd (
                                COREHALFWORD (
                                    getFIXED (mP2SYMS)
                                    + 12
                                          * (COREHALFWORD (
                                              getFIXED (mIND_STACK)
                                              + 73
                                                    * (getFIXED (
                                                        mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI))
                                              + 40 + 2 * (0)))
                                    + 6 + 2 * (0)),
                                getFIXED (
                                    getFIXED (mIND_STACK)
                                    + 73
                                          * (getFIXED (
                                              mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI))
                                    + 4 + 4 * (0)))),
                        CHECK_SRS (0))),
                    BYTE0 (mSRSTYPE))))
              // RETURN 1; (4611)
              {
                reentryGuard = 0;
                return fixedToBit (32, (int32_t)(1));
              }
      // LOOK_COUNT = CTR+NUMOP; (4612)
      {
        int32_t numberRHS
            = (int32_t)(xadd (COREHALFWORD (mCTR), COREHALFWORD (mNUMOP)));
        putFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExLOOK_COUNT,
                  numberRHS);
      }
      // IF SPAREBASE = R3 THEN (4613)
      if (1
          & (xEQ (COREHALFWORD (mGENERATExGUARANTEE_ADDRESSABLExSPAREBASE),
                  BYTE0 (mR3))))
        // LOADED_BASE = R_VAR(BASE_POSSIBLE); (4614)
        {
          descriptor_t *bitRHS = getBIT (
              16,
              mR_VAR
                  + 2
                        * COREHALFWORD (
                            mGENERATExGUARANTEE_ADDRESSABLExBASE_POSSIBLE));
          putBIT (16,
                  mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExLOADED_BASE,
                  bitRHS);
          bitRHS->inUse = 0;
        }
      // ELSE (4615)
      else
        // LOADED_BASE = 0; (4616)
        {
          int32_t numberRHS = (int32_t)(0);
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16,
                  mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExLOADED_BASE,
                  bitRHS);
          bitRHS->inUse = 0;
        }
      // DO I = 1 TO 4; (4617)
      {
        int32_t from62, to62, by62;
        from62 = 1;
        to62 = 4;
        by62 = 1;
        for (putFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI,
                       from62);
             getFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI)
             <= to62;
             putFIXED (
                 mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI,
                 getFIXED (mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExI)
                     + by62))
          {
          // RESTART: (4618)
          RESTART:
            // LOOK_COUNT=LOOK_COUNT+1; (4619)
            {
              int32_t numberRHS = (int32_t)(xadd (
                  getFIXED (
                      mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExLOOK_COUNT),
                  1));
              putFIXED (
                  mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExLOOK_COUNT,
                  numberRHS);
            }
            // HMAT_WD=OPR(LOOK_COUNT); (4620)
            {
              int32_t numberRHS = (int32_t)(getFIXED (
                  getFIXED (mFOR_ATOMS)
                  + 4
                        * (getFIXED (
                            mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExLOOK_COUNT))
                  + 0 + 4 * (0)));
              descriptor_t *bitRHS;
              bitRHS = fixedToBit (32, (int32_t)(numberRHS));
              putBIT (32,
                      mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExHMAT_WD,
                      bitRHS);
              bitRHS->inUse = 0;
            }
            // IF ~HMAT_WD THEN (4621)
            if (1
                & (xNOT (COREWORD (
                    mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExHMAT_WD))))
              // IF (SHR(HMAT_WD,4)& 4095) >= 100 THEN (4622)
              if (1
                  & (xGE (
                      xAND (
                          SHR (
                              COREWORD (
                                  mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExHMAT_WD),
                              4),
                          4095),
                      100)))
                // GO TO RESTART; (4623)
                goto RESTART;
              // ELSE (4624)
              else
                // IF NOSTOP(SHR(HMAT_WD,4) &  4095) THEN (4625)
                if (1
                    & (bitToFixed (getBIT (
                        1,
                        mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExNOSTOP
                            + 1
                                  * xAND (
                                      SHR (
                                          COREWORD (
                                              mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExHMAT_WD),
                                          4),
                                      4095)))))
                  // GO TO RESTART; (4626)
                  goto RESTART;
                // ELSE (4627)
                else
                  // RETURN 0; (4628)
                  {
                    reentryGuard = 0;
                    return fixedToBit (32, (int32_t)(0));
                  }
            // IF (SHR(HMAT_WD,4) &  15) ~= 1 THEN (4629)
            if (1
                & (xNEQ (
                    xAND (
                        SHR (
                            COREWORD (
                                mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExHMAT_WD),
                            4),
                        15),
                    1)))
              // GO TO RESTART; (4630)
              goto RESTART;
            // IF OPMODE(SYT_TYPE(SHR(HMAT_WD,16))) = 4 THEN (4631)
            if (1
                & (xEQ (
                    BYTE0 (
                        mOPMODE
                        + 1
                              * BYTE0 (
                                  getFIXED (mSYM_TAB)
                                  + 34
                                        * (SHR (
                                            COREWORD (
                                                mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExHMAT_WD),
                                            16))
                                  + 32 + 1 * (0))),
                    4)))
              // GO TO RESTART; (4632)
              goto RESTART;
            // B_REG= SYT_BASE(SHR(HMAT_WD,16)); (4633)
            {
              descriptor_t *bitRHS = getBIT (
                  16,
                  getFIXED (mP2SYMS)
                      + 12
                            * (SHR (
                                COREWORD (
                                    mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExHMAT_WD),
                                16))
                      + 4 + 2 * (0));
              putBIT (16, mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExB_REG,
                      bitRHS);
              bitRHS->inUse = 0;
            }
            // IF B_REG< 0 THEN (4634)
            if (1
                & (xLT (
                    COREHALFWORD (
                        mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExB_REG),
                    0)))
              // IF B_REG=CURRENT_BASE THEN (4635)
              if (1
                  & (xEQ (
                      COREHALFWORD (
                          mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExB_REG),
                      COREHALFWORD (
                          mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExCURRENT_BASE))))
                // RETURN 1; (4636)
                {
                  reentryGuard = 0;
                  return fixedToBit (32, (int32_t)(1));
                }
              // ELSE (4637)
              else
                // IF B_REG = LOADED_BASE THEN (4638)
                if (1
                    & (xEQ (
                        COREHALFWORD (
                            mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExB_REG),
                        COREHALFWORD (
                            mGENERATExGUARANTEE_ADDRESSABLExSRS_DESIRABLExLOADED_BASE))))
                  // DO; (4639)
                  {
                  rs1s2s1:;
                    // OTHER_BASE_REFS = OTHER_BASE_REFS + 1; (4640)
                    {
                      int32_t numberRHS = (int32_t)(xadd (
                          COREHALFWORD (
                              mGENERATExGUARANTEE_ADDRESSABLExOTHER_BASE_REFS),
                          1));
                      descriptor_t *bitRHS;
                      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                      putBIT (16,
                              mGENERATExGUARANTEE_ADDRESSABLExOTHER_BASE_REFS,
                              bitRHS);
                      bitRHS->inUse = 0;
                    }
                    // GO TO RESTART; (4641)
                    goto RESTART;
                  es1s2s1:;
                  } // End of DO block
                // ELSE (4642)
                else
                  // RETURN 0; (4643)
                  {
                    reentryGuard = 0;
                    return fixedToBit (32, (int32_t)(0));
                  }
          }
      } // End of DO for-loop block
    es1:;
    } // End of DO block
  // RETURN 0; (4644)
  {
    reentryGuard = 0;
    return fixedToBit (32, (int32_t)(0));
  }
}