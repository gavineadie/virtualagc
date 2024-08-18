/*
  File GENERATExRETURN_COLUMN_STACK.c generated by XCOM-I, 2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
GENERATExRETURN_COLUMN_STACK (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "GENERATExRETURN_COLUMN_STACK");
  // IF SYMFORM(FORM(PTR)) THEN (2928)
  if (1
      & (bitToFixed (getBIT (
          1, mSYMFORM
                 + 1
                       * COREHALFWORD (
                           getFIXED (mIND_STACK)
                           + 73
                                 * (COREHALFWORD (
                                     mGENERATExRETURN_COLUMN_STACKxPTR))
                           + 32 + 2 * (0))))))
    // DO; (2929)
    {
    rs1:;
      // IF BIT_FLAG & ( (SYT_TYPE(LOC2(PTR)) = BITS) | (SYT_TYPE(LOC2(PTR)) =
      // FULLBIT) ) THEN (2930)
      if (1
          & (xAND (
              BYTE0 (mGENERATExRETURN_COLUMN_STACKxBIT_FLAG),
              xOR (
                  xEQ (
                      BYTE0 (
                          getFIXED (mSYM_TAB)
                          + 34
                                * (COREHALFWORD (
                                    getFIXED (mIND_STACK)
                                    + 73
                                          * (COREHALFWORD (
                                              mGENERATExRETURN_COLUMN_STACKxPTR))
                                    + 42 + 2 * (0)))
                          + 32 + 1 * (0)),
                      BYTE0 (mBITS)),
                  xEQ (
                      BYTE0 (
                          getFIXED (mSYM_TAB)
                          + 34
                                * (COREHALFWORD (
                                    getFIXED (mIND_STACK)
                                    + 73
                                          * (COREHALFWORD (
                                              mGENERATExRETURN_COLUMN_STACKxPTR))
                                    + 42 + 2 * (0)))
                          + 32 + 1 * (0)),
                      BYTE0 (mFULLBIT))))))
        // DO; (2931)
        {
        rs1s1:;
          // CALL RETURN_STACK_ENTRY(COLUMN(PTR)); (2932)
          {
            putBITp (
                16, mGENERATExRETURN_STACK_ENTRYxP,
                getBIT (16, getFIXED (mIND_STACK)
                                + 73
                                      * (COREHALFWORD (
                                          mGENERATExRETURN_COLUMN_STACKxPTR))
                                + 24 + 2 * (0)));
            GENERATExRETURN_STACK_ENTRY (0);
          }
          // COLUMN(PTR) = 0; (2933)
          {
            int32_t numberRHS = (int32_t)(0);
            putBIT (
                16,
                getFIXED (mIND_STACK)
                    + 73 * (COREHALFWORD (mGENERATExRETURN_COLUMN_STACKxPTR))
                    + 24 + 2 * (0),
                fixedToBit (16, numberRHS));
          }
        es1s1:;
        } // End of DO block
      // ELSE (2934)
      else
        // DO; (2935)
        {
        rs1s2:;
          // IF (SYT_TYPE(LOC2(PTR)) = EVENT) THEN (2936)
          if (1
              & (xEQ (
                  BYTE0 (
                      getFIXED (mSYM_TAB)
                      + 34
                            * (COREHALFWORD (
                                getFIXED (mIND_STACK)
                                + 73
                                      * (COREHALFWORD (
                                          mGENERATExRETURN_COLUMN_STACKxPTR))
                                + 42 + 2 * (0)))
                      + 32 + 1 * (0)),
                  BYTE0 (mEVENT))))
            // DO; (2937)
            {
            rs1s2s1:;
              // CALL RETURN_STACK_ENTRY(COLUMN(PTR)); (2938)
              {
                putBITp (
                    16, mGENERATExRETURN_STACK_ENTRYxP,
                    getBIT (16,
                            getFIXED (mIND_STACK)
                                + 73
                                      * (COREHALFWORD (
                                          mGENERATExRETURN_COLUMN_STACKxPTR))
                                + 24 + 2 * (0)));
                GENERATExRETURN_STACK_ENTRY (0);
              }
              // COLUMN(PTR) = 0; (2939)
              {
                int32_t numberRHS = (int32_t)(0);
                putBIT (16,
                        getFIXED (mIND_STACK)
                            + 73
                                  * (COREHALFWORD (
                                      mGENERATExRETURN_COLUMN_STACKxPTR))
                            + 24 + 2 * (0),
                        fixedToBit (16, numberRHS));
              }
            es1s2s1:;
            } // End of DO block
        es1s2:;
        } // End of DO block
    es1:;
    } // End of DO block
  // BIT_FLAG = FALSE; (2940)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (1, mGENERATExRETURN_COLUMN_STACKxBIT_FLAG, bitRHS);
    bitRHS->inUse = 0;
  }
  {
    reentryGuard = 0;
    return 0;
  }
}