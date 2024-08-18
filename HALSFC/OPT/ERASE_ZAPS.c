/*
  File ERASE_ZAPS.c generated by XCOM-I, 2024-08-09 12:38:53.
*/

#include "runtimeC.h"

int32_t
ERASE_ZAPS (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard, "ERASE_ZAPS");
  // IF STACK_TRACE THEN (3258)
  if (1 & (bitToFixed (getBIT (8, mSTACK_TRACE))))
    // OUTPUT = 'ERASE_ZAPS:  '||STT#; (3259)
    {
      descriptor_t *stringRHS;
      stringRHS = xsCAT (cToDescriptor (NULL, "ERASE_ZAPS:  "),
                         bitToCharacter (getBIT (16, mSTTp)));
      OUTPUT (0, stringRHS);
      stringRHS->inUse = 0;
    }
  // DO FOR K = 0 TO VAL_SIZE - 1; (3260)
  {
    int32_t from78, to78, by78;
    from78 = 0;
    to78 = xsubtract (COREHALFWORD (mVAL_SIZE), 1);
    by78 = 1;
    for (putBIT (16, mERASE_ZAPSxK, fixedToBit (16, from78));
         bitToFixed (getBIT (16, mERASE_ZAPSxK)) <= to78; putBIT (
             16, mERASE_ZAPSxK,
             fixedToBit (16, bitToFixed (getBIT (16, mERASE_ZAPSxK)) + by78)))
      {
        // ZAPS(K) = 0; (3261)
        {
          int32_t numberRHS = (int32_t)(0);
          putFIXED (getFIXED (mOBPS) + 4 * (COREHALFWORD (mZAP_LEVEL)) + 0
                        + 4 * (COREHALFWORD (mERASE_ZAPSxK)),
                    numberRHS);
        }
      }
  } // End of DO for-loop block
  {
    reentryGuard = 0;
    return 0;
  }
}