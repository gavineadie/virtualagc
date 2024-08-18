/*
  File DISCONNECT.c generated by XCOM-I, 2024-08-09 12:40:41.
*/

#include "runtimeC.h"

int32_t
DISCONNECT (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "DISCONNECT");
  // IF BLOCK_MODE(NEST) = CMPL_MODE THEN (1410)
  if (1
      & (xEQ (BYTE0 (mBLOCK_MODE + 1 * getFIXED (mNEST)), BYTE0 (mCMPL_MODE))))
    // SYT_NEST(LOC) = 0; (1411)
    {
      int32_t numberRHS = (int32_t)(0);
      putBIT (8,
              getFIXED (mSYM_TAB) + 34 * (COREHALFWORD (mDISCONNECTxLOC)) + 28
                  + 1 * (0),
              fixedToBit (8, numberRHS));
    }
  // ELSE (1412)
  else
    // DO; (1413)
    {
    rs1:;
      // I = HASH(CLOSE_BCD, SYT_HASHSIZE); (1414)
      {
        int32_t numberRHS
            = (int32_t)((putCHARACTERp (mHASHxBCD, getCHARACTER (mCLOSE_BCD)),
                         putFIXED (mHASHxHASHSIZE, 997), HASH (0)));
        putFIXED (mDISCONNECTxI, numberRHS);
      }
      // IF SYT_HASHSTART(I) = LOC THEN (1415)
      if (1
          & (xEQ (COREHALFWORD (mSYT_HASHSTART + 2 * getFIXED (mDISCONNECTxI)),
                  COREHALFWORD (mDISCONNECTxLOC))))
        // SYT_HASHSTART(I) = SYT_HASHLINK(LOC); (1416)
        {
          descriptor_t *bitRHS = getBIT (
              16, getFIXED (mLINK_SORT) + 4 * (COREHALFWORD (mDISCONNECTxLOC))
                      + 0 + 2 * (0));
          putBIT (16, mSYT_HASHSTART + 2 * (getFIXED (mDISCONNECTxI)), bitRHS);
          bitRHS->inUse = 0;
        }
      // ELSE (1417)
      else
        // DO; (1418)
        {
        rs1s1:;
          // I = SYT_HASHSTART(I); (1419)
          {
            descriptor_t *bitRHS
                = getBIT (16, mSYT_HASHSTART + 2 * getFIXED (mDISCONNECTxI));
            int32_t numberRHS;
            numberRHS = bitToFixed (bitRHS);
            putFIXED (mDISCONNECTxI, numberRHS);
            bitRHS->inUse = 0;
          }
          // DO WHILE I ~= LOC; (1420)
          while (1
                 & (xNEQ (getFIXED (mDISCONNECTxI),
                          COREHALFWORD (mDISCONNECTxLOC))))
            {
              // J = I; (1421)
              {
                int32_t numberRHS = (int32_t)(getFIXED (mDISCONNECTxI));
                putFIXED (mDISCONNECTxJ, numberRHS);
              }
              // I = SYT_HASHLINK(I); (1422)
              {
                descriptor_t *bitRHS = getBIT (
                    16, getFIXED (mLINK_SORT) + 4 * (getFIXED (mDISCONNECTxI))
                            + 0 + 2 * (0));
                int32_t numberRHS;
                numberRHS = bitToFixed (bitRHS);
                putFIXED (mDISCONNECTxI, numberRHS);
                bitRHS->inUse = 0;
              }
            } // End of DO WHILE block
          // SYT_HASHLINK(J) = SYT_HASHLINK(LOC); (1423)
          {
            descriptor_t *bitRHS = getBIT (
                16, getFIXED (mLINK_SORT)
                        + 4 * (COREHALFWORD (mDISCONNECTxLOC)) + 0 + 2 * (0));
            putBIT (16,
                    getFIXED (mLINK_SORT) + 4 * (getFIXED (mDISCONNECTxJ)) + 0
                        + 2 * (0),
                    bitRHS);
            bitRHS->inUse = 0;
          }
        es1s1:;
        } // End of DO block
      // SYT_FLAGS(LOC) = SYT_FLAGS(LOC) | INACTIVE_FLAG; (1424)
      {
        int32_t numberRHS = (int32_t)(xOR (
            getFIXED (getFIXED (mSYM_TAB)
                      + 34 * (COREHALFWORD (mDISCONNECTxLOC)) + 8 + 4 * (0)),
            32768));
        putFIXED (getFIXED (mSYM_TAB) + 34 * (COREHALFWORD (mDISCONNECTxLOC))
                      + 8 + 4 * (0),
                  numberRHS);
      }
    es1:;
    } // End of DO block
  {
    reentryGuard = 0;
    return 0;
  }
}