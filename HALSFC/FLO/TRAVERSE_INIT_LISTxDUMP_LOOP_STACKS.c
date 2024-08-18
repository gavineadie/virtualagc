/*
  File TRAVERSE_INIT_LISTxDUMP_LOOP_STACKS.c generated by XCOM-I, 2024-08-09
  12:38:39.
*/

#include "runtimeC.h"

int32_t
TRAVERSE_INIT_LISTxDUMP_LOOP_STACKS (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard
      = guardReentry (reentryGuard, "TRAVERSE_INIT_LISTxDUMP_LOOP_STACKS");
  // IF LOOP_INX = 0 THEN (1969)
  if (1 & (xEQ (COREHALFWORD (mTRAVERSE_INIT_LISTxLOOP_INX), 0)))
    // RETURN; (1970)
    {
      reentryGuard = 0;
      return 0;
    }
  // OUTPUT = '#  START  INCR  REPEAT  OFFSET  PASS  PERIOD  CELL INCR  CELL
  // REPEAT'; (1971)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "#  START  INCR  REPEAT  OFFSET  PASS  "
                                     "PERIOD  CELL INCR  CELL REPEAT");
    OUTPUT (0, stringRHS);
    stringRHS->inUse = 0;
  }
  // DO J = 1 TO LOOP_INX; (1972)
  {
    int32_t from45, to45, by45;
    from45 = 1;
    to45 = bitToFixed (getBIT (16, mTRAVERSE_INIT_LISTxLOOP_INX));
    by45 = 1;
    for (putBIT (16, mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ,
                 fixedToBit (16, from45));
         bitToFixed (getBIT (16, mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))
         <= to45;
         putBIT (
             16, mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ,
             fixedToBit (16, bitToFixed (getBIT (
                                 16, mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))
                                 + by45)))
      {
        // OUTPUT = J||X3||FORMAT(LOOP_START(J),4)||'
        // '||FORMAT(LOOP_INCR(J),4)||
        // X3||FORMAT(LOOP_REPEAT(J),5)||X3||FORMAT(LOOP_OFFSET(J),5)
        // ||X1||FORMAT(LOOP_PASS(J),5)||X3||FORMAT(LOOP_PERIOD(J),5)|| '
        // '||FORMAT(CELL_LOOP_INCR(J),4)||'        '||
        // FORMAT(CELL_LOOP_REPEAT(J),5); (1973)
        {
          descriptor_t *stringRHS;
          stringRHS = xsCAT (
              xsCAT (
                  xsCAT (
                      xsCAT (
                          xsCAT (
                              xsCAT (
                                  xsCAT (
                                      xsCAT (
                                          xsCAT (
                                              xsCAT (
                                                  xsCAT (
                                                      xsCAT (
                                                          xsCAT (
                                                              xsCAT (
                                                                  xsCAT (
                                                                      xsCAT (
                                                                          bitToCharacter (getBIT (
                                                                              16,
                                                                              mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ)),
                                                                          getCHARACTER (
                                                                              mX3)),
                                                                      (putFIXED (
                                                                           mFORMATxIVAL,
                                                                           COREHALFWORD (
                                                                               mTRAVERSE_INIT_LISTxLOOP_START
                                                                               + 2
                                                                                     * COREHALFWORD (
                                                                                         mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
                                                                       putFIXED (
                                                                           mFORMATxN,
                                                                           4),
                                                                       FORMAT (
                                                                           0))),
                                                                  cToDescriptor (
                                                                      NULL,
                                                                      "  ")),
                                                              (putFIXED (
                                                                   mFORMATxIVAL,
                                                                   COREHALFWORD (
                                                                       mTRAVERSE_INIT_LISTxLOOP_INCR
                                                                       + 2
                                                                             * COREHALFWORD (
                                                                                 mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
                                                               putFIXED (
                                                                   mFORMATxN,
                                                                   4),
                                                               FORMAT (0))),
                                                          getCHARACTER (mX3)),
                                                      (putFIXED (
                                                           mFORMATxIVAL,
                                                           COREHALFWORD (
                                                               mTRAVERSE_INIT_LISTxLOOP_REPEAT
                                                               + 2
                                                                     * COREHALFWORD (
                                                                         mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
                                                       putFIXED (mFORMATxN, 5),
                                                       FORMAT (0))),
                                                  getCHARACTER (mX3)),
                                              (putFIXED (
                                                   mFORMATxIVAL,
                                                   COREHALFWORD (
                                                       mTRAVERSE_INIT_LISTxLOOP_OFFSET
                                                       + 2
                                                             * COREHALFWORD (
                                                                 mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
                                               putFIXED (mFORMATxN, 5),
                                               FORMAT (0))),
                                          getCHARACTER (mX1)),
                                      (putFIXED (
                                           mFORMATxIVAL,
                                           COREHALFWORD (
                                               mTRAVERSE_INIT_LISTxLOOP_PASS
                                               + 2
                                                     * COREHALFWORD (
                                                         mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
                                       putFIXED (mFORMATxN, 5), FORMAT (0))),
                                  getCHARACTER (mX3)),
                              (putFIXED (
                                   mFORMATxIVAL,
                                   COREHALFWORD (
                                       mTRAVERSE_INIT_LISTxLOOP_PERIOD
                                       + 2
                                             * COREHALFWORD (
                                                 mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
                               putFIXED (mFORMATxN, 5), FORMAT (0))),
                          cToDescriptor (NULL, "       ")),
                      (putFIXED (
                           mFORMATxIVAL,
                           COREHALFWORD (
                               mTRAVERSE_INIT_LISTxCELL_LOOP_INCR
                               + 2
                                     * COREHALFWORD (
                                         mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
                       putFIXED (mFORMATxN, 4), FORMAT (0))),
                  cToDescriptor (NULL, "        ")),
              (putFIXED (
                   mFORMATxIVAL,
                   COREHALFWORD (
                       mTRAVERSE_INIT_LISTxCELL_LOOP_REPEAT
                       + 2
                             * COREHALFWORD (
                                 mTRAVERSE_INIT_LISTxDUMP_LOOP_STACKSxJ))),
               putFIXED (mFORMATxN, 5), FORMAT (0)));
          OUTPUT (0, stringRHS);
          stringRHS->inUse = 0;
        }
      }
  } // End of DO for-loop block
  {
    reentryGuard = 0;
    return 0;
  }
}