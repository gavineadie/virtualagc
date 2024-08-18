/*
  File FINDER.c generated by XCOM-I, 2024-08-09 12:40:41.
*/

#include "runtimeC.h"

descriptor_t *
FINDER (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (descriptor_t *)0;
    }
  reentryGuard = guardReentry (reentryGuard, "FINDER");
  // DO I = START TO MAXLIBFILES; (2544)
  {
    int32_t from51, to51, by51;
    from51 = bitToFixed (getBIT (16, mFINDERxSTART));
    to51 = 2;
    by51 = 1;
    for (putBIT (16, mFINDERxI, fixedToBit (16, from51));
         bitToFixed (getBIT (16, mFINDERxI)) <= to51;
         putBIT (16, mFINDERxI,
                 fixedToBit (16, bitToFixed (getBIT (16, mFINDERxI)) + by51)))
      {
        // IF ~FILENODD(I) THEN (2545)
        if (1
            & (xNOT (BYTE0 (mFINDERxFILENODD + 1 * COREHALFWORD (mFINDERxI)))))
          // DO; (2546)
          {
          rs1s1:;
            // CALL MONITOR(8, FILENO, FILENUM(I)); (2547)
            MONITOR8 (
                COREHALFWORD (mFINDERxFILENO),
                getFIXED (mFINDERxFILENUM + 4 * COREHALFWORD (mFINDERxI)));
            // RETCODE = MONITOR(2, FILENO, NAME); (2548)
            {
              int32_t numberRHS = (int32_t)(MONITOR2 (
                  COREHALFWORD (mFINDERxFILENO), getCHARACTER (mFINDERxNAME)));
              descriptor_t *bitRHS;
              bitRHS = fixedToBit (32, (int32_t)(numberRHS));
              putBIT (16, mFINDERxRETCODE, bitRHS);
              bitRHS->inUse = 0;
            }
            // IF RETCODE = 0 THEN (2549)
            if (1 & (xEQ (COREHALFWORD (mFINDERxRETCODE), 0)))
              // DO; (2550)
              {
              rs1s1s1:;
                // INCLUDE_FILE# = FILENUM(I); (2551)
                {
                  int32_t numberRHS = (int32_t)(getFIXED (
                      mFINDERxFILENUM + 4 * COREHALFWORD (mFINDERxI)));
                  descriptor_t *bitRHS;
                  bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                  putBIT (16, mINCLUDE_FILEp, bitRHS);
                  bitRHS->inUse = 0;
                }
                // RETURN FALSE; (2552)
                {
                  reentryGuard = 0;
                  return fixedToBit (32, (int32_t)(0));
                }
              es1s1s1:;
              } // End of DO block
            // FILENODD(I) = SHR(RETCODE, 1); (2553)
            {
              int32_t numberRHS
                  = (int32_t)(SHR (COREHALFWORD (mFINDERxRETCODE), 1));
              descriptor_t *bitRHS;
              bitRHS = fixedToBit (32, (int32_t)(numberRHS));
              putBIT (1, mFINDERxFILENODD + 1 * (COREHALFWORD (mFINDERxI)),
                      bitRHS);
              bitRHS->inUse = 0;
            }
          es1s1:;
          } // End of DO block
      }
  } // End of DO for-loop block
  // RETURN TRUE; (2554)
  {
    reentryGuard = 0;
    return fixedToBit (32, (int32_t)(1));
  }
}