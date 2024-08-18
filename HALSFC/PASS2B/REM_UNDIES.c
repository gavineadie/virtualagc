/*
  File REM_UNDIES.c generated by XCOM-I, 2024-08-09 12:41:32.
*/

#include "runtimeC.h"

descriptor_t *
REM_UNDIES (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (descriptor_t *)0;
    }
  reentryGuard = guardReentry (reentryGuard, "REM_UNDIES");
  // TEMP_STRING = HAL_NAME; (1409)
  {
    descriptor_t *stringRHS;
    stringRHS = getCHARACTER (mREM_UNDIESxHAL_NAME);
    putCHARACTER (mREM_UNDIESxTEMP_STRING, stringRHS);
    stringRHS->inUse = 0;
  }
  // WORK1 = CHAR_INDEX(TEMP_STRING, UNDERSCORE); (1410)
  {
    descriptor_t *bitRHS
        = (putCHARACTERp (mCHAR_INDEXxSTRING1,
                          getCHARACTER (mREM_UNDIESxTEMP_STRING)),
           putCHARACTERp (mCHAR_INDEXxSTRING2,
                          getCHARACTER (mREM_UNDIESxUNDERSCORE)),
           CHAR_INDEX (0));
    int32_t numberRHS;
    numberRHS = bitToFixed (bitRHS);
    putFIXED (mWORK1, numberRHS);
    bitRHS->inUse = 0;
  }
  // DO WHILE WORK1 > 0; (1411)
  while (1 & (xGT (getFIXED (mWORK1), 0)))
    {
      // TEMP_STRING = SUBSTR(TEMP_STRING, 0, WORK1) || SUBSTR(TEMP_STRING,
      // WORK1 + 1); (1412)
      {
        descriptor_t *stringRHS;
        stringRHS = xsCAT (SUBSTR (getCHARACTER (mREM_UNDIESxTEMP_STRING), 0,
                                   getFIXED (mWORK1)),
                           SUBSTR2 (getCHARACTER (mREM_UNDIESxTEMP_STRING),
                                    xadd (getFIXED (mWORK1), 1)));
        putCHARACTER (mREM_UNDIESxTEMP_STRING, stringRHS);
        stringRHS->inUse = 0;
      }
      // WORK1 = CHAR_INDEX(TEMP_STRING, UNDERSCORE); (1413)
      {
        descriptor_t *bitRHS
            = (putCHARACTERp (mCHAR_INDEXxSTRING1,
                              getCHARACTER (mREM_UNDIESxTEMP_STRING)),
               putCHARACTERp (mCHAR_INDEXxSTRING2,
                              getCHARACTER (mREM_UNDIESxUNDERSCORE)),
               CHAR_INDEX (0));
        int32_t numberRHS;
        numberRHS = bitToFixed (bitRHS);
        putFIXED (mWORK1, numberRHS);
        bitRHS->inUse = 0;
      }
    } // End of DO WHILE block
  // RETURN TEMP_STRING; (1414)
  {
    reentryGuard = 0;
    return getCHARACTER (mREM_UNDIESxTEMP_STRING);
  }
}