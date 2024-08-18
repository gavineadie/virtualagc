/*
  File OBJECT_CONDENSERxBRANCH_DELETE.c generated by XCOM-I, 2024-08-09
  12:39:31.
*/

#include "runtimeC.h"

int32_t
OBJECT_CONDENSERxBRANCH_DELETE (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "OBJECT_CONDENSERxBRANCH_DELETE");
  // IF BRANCH_DEL = FIRSTBRANCH(CURRENT_ESDID) THEN (14684)
  if (1
      & (xEQ (COREHALFWORD (mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL),
              COREHALFWORD (mFIRSTBRANCH + 2 * getFIXED (mCURRENT_ESDID)))))
    // DO; (14685)
    {
    rs1:;
      // FIRSTBRANCH(CURRENT_ESDID) = BRANCH_FLINK(BRANCH_DEL); (14686)
      {
        descriptor_t *bitRHS = getBIT (
            16, getFIXED (mBRANCH_TBL)
                    + 14
                          * (COREHALFWORD (
                              mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                    + 10 + 2 * (0));
        putBIT (16, mFIRSTBRANCH + 2 * (getFIXED (mCURRENT_ESDID)), bitRHS);
        bitRHS->inUse = 0;
      }
      // BRANCH_BLINK(BRANCH_FLINK(BRANCH_DEL))= 0; (14687)
      {
        int32_t numberRHS = (int32_t)(0);
        putBIT (
            16,
            getFIXED (mBRANCH_TBL)
                + 14
                      * (COREHALFWORD (
                          getFIXED (mBRANCH_TBL)
                          + 14
                                * (COREHALFWORD (
                                    mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                          + 10 + 2 * (0)))
                + 12 + 2 * (0),
            fixedToBit (16, numberRHS));
      }
      // IF BRANCH_DEL = LASTBRANCH(CURRENT_ESDID) THEN (14688)
      if (1
          & (xEQ (COREHALFWORD (mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL),
                  COREHALFWORD (mLASTBRANCH + 2 * getFIXED (mCURRENT_ESDID)))))
        // LASTBRANCH(CURRENT_ESDID) = 0; (14689)
        {
          int32_t numberRHS = (int32_t)(0);
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16, mLASTBRANCH + 2 * (getFIXED (mCURRENT_ESDID)), bitRHS);
          bitRHS->inUse = 0;
        }
    es1:;
    } // End of DO block
  // ELSE (14690)
  else
    // IF BRANCH_DEL = LASTBRANCH(CURRENT_ESDID) THEN (14691)
    if (1
        & (xEQ (COREHALFWORD (mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL),
                COREHALFWORD (mLASTBRANCH + 2 * getFIXED (mCURRENT_ESDID)))))
      // DO; (14692)
      {
      rs2:;
        // LASTBRANCH(CURRENT_ESDID) = BRANCH_BLINK(BRANCH_DEL); (14693)
        {
          descriptor_t *bitRHS = getBIT (
              16, getFIXED (mBRANCH_TBL)
                      + 14
                            * (COREHALFWORD (
                                mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                      + 12 + 2 * (0));
          putBIT (16, mLASTBRANCH + 2 * (getFIXED (mCURRENT_ESDID)), bitRHS);
          bitRHS->inUse = 0;
        }
        // BRANCH_FLINK(BRANCH_BLINK(BRANCH_DEL)) = 0; (14694)
        {
          int32_t numberRHS = (int32_t)(0);
          putBIT (
              16,
              getFIXED (mBRANCH_TBL)
                  + 14
                        * (COREHALFWORD (
                            getFIXED (mBRANCH_TBL)
                            + 14
                                  * (COREHALFWORD (
                                      mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                            + 12 + 2 * (0)))
                  + 10 + 2 * (0),
              fixedToBit (16, numberRHS));
        }
      es2:;
      } // End of DO block
    // ELSE (14695)
    else
      // DO; (14696)
      {
      rs3:;
        // BRANCH_FLINK(BRANCH_BLINK(BRANCH_DEL)) = BRANCH_FLINK(BRANCH_DEL);
        // (14697)
        {
          descriptor_t *bitRHS = getBIT (
              16, getFIXED (mBRANCH_TBL)
                      + 14
                            * (COREHALFWORD (
                                mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                      + 10 + 2 * (0));
          putBIT (
              16,
              getFIXED (mBRANCH_TBL)
                  + 14
                        * (COREHALFWORD (
                            getFIXED (mBRANCH_TBL)
                            + 14
                                  * (COREHALFWORD (
                                      mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                            + 12 + 2 * (0)))
                  + 10 + 2 * (0),
              bitRHS);
          bitRHS->inUse = 0;
        }
        // BRANCH_BLINK(BRANCH_FLINK(BRANCH_DEL)) = BRANCH_BLINK(BRANCH_DEL);
        // (14698)
        {
          descriptor_t *bitRHS = getBIT (
              16, getFIXED (mBRANCH_TBL)
                      + 14
                            * (COREHALFWORD (
                                mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                      + 12 + 2 * (0));
          putBIT (
              16,
              getFIXED (mBRANCH_TBL)
                  + 14
                        * (COREHALFWORD (
                            getFIXED (mBRANCH_TBL)
                            + 14
                                  * (COREHALFWORD (
                                      mOBJECT_CONDENSERxBRANCH_DELETExBRANCH_DEL))
                            + 10 + 2 * (0)))
                  + 12 + 2 * (0),
              bitRHS);
          bitRHS->inUse = 0;
        }
      es3:;
      } // End of DO block
  {
    reentryGuard = 0;
    return 0;
  }
}