/*
  File STREAMxD_TOKEN.c generated by XCOM-I, 2024-08-09 12:38:15.
*/

#include "runtimeC.h"

descriptor_t *
STREAMxD_TOKEN (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (descriptor_t *)0;
    }
  reentryGuard = guardReentry (reentryGuard, "STREAMxD_TOKEN");
// BLANKS: (3410)
BLANKS:
  // DO FOREVER; (3411)
  while (1 & (1))
    {
      // DO WHILE (BYTE(CURRENT_CARD,D_INDEX) = BYTE(' ')) & (D_INDEX <=
      // TEXT_LIMIT); (3412)
      while (1
             & (xAND (xEQ (BYTE (getCHARACTER (mCURRENT_CARD),
                                 COREHALFWORD (mSTREAMxD_INDEX)),
                           BYTE1 (cToDescriptor (NULL, " "))),
                      xLE (COREHALFWORD (mSTREAMxD_INDEX),
                           COREHALFWORD (mTEXT_LIMIT)))))
        {
          // D_INDEX = D_INDEX + 1; (3413)
          {
            int32_t numberRHS
                = (int32_t)(xadd (COREHALFWORD (mSTREAMxD_INDEX), 1));
            descriptor_t *bitRHS;
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (16, mSTREAMxD_INDEX, bitRHS);
            bitRHS->inUse = 0;
          }
        } // End of DO WHILE block
      // IF D_INDEX <= TEXT_LIMIT THEN (3414)
      if (1
          & (xLE (COREHALFWORD (mSTREAMxD_INDEX), COREHALFWORD (mTEXT_LIMIT))))
        // ESCAPE BLANKS; (3415)
        goto es1;
      // IF D_CONTINUATION_OK THEN (3416)
      if (1 & (bitToFixed (getBIT (1, mSTREAMxD_CONTINUATION_OK))))
        // DO; (3417)
        {
        rs1s2:;
          // CALL NEXT_RECORD; (3418)
          NEXT_RECORD (0);
          // IF CARD_TYPE(BYTE(CURRENT_CARD)) ~= CARD_TYPE(BYTE('D')) THEN
          // (3419)
          if (1
              & (xNEQ (
                  COREHALFWORD (mCARD_TYPE
                                + 2 * BYTE1 (getCHARACTER (mCURRENT_CARD))),
                  COREHALFWORD (mCARD_TYPE
                                + 2 * BYTE1 (cToDescriptor (NULL, "D"))))))
            // DO; (3420)
            {
            rs1s2s1:;
              // LOOKED_RECORD_AHEAD = TRUE; (3421)
              {
                int32_t numberRHS = (int32_t)(1);
                descriptor_t *bitRHS;
                bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                putBIT (1, mLOOKED_RECORD_AHEAD, bitRHS);
                bitRHS->inUse = 0;
              }
              // D_CONTINUATION_OK = FALSE; (3422)
              {
                int32_t numberRHS = (int32_t)(0);
                descriptor_t *bitRHS;
                bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                putBIT (1, mSTREAMxD_CONTINUATION_OK, bitRHS);
                bitRHS->inUse = 0;
              }
              // RETURN ''; (3423)
              {
                reentryGuard = 0;
                return cToDescriptor (NULL, "");
              }
            es1s2s1:;
            } // End of DO block
          // BYTE(CURRENT_CARD) = BYTE('D'); (3424)
          {
            int32_t numberRHS = (int32_t)(BYTE1 (cToDescriptor (NULL, "D")));
            lBYTEb (ADDR (NULL, 0, "CURRENT_CARD", 0), 0,
                    BYTE1 (cToDescriptor (NULL, "D")));
          }
          // CALL PRINT_COMMENT(TRUE); (3425)
          {
            putBITp (1, mSTREAMxPRINT_COMMENTxPRINT,
                     fixedToBit (32, (int32_t)(1)));
            STREAMxPRINT_COMMENT (0);
          }
          // D_INDEX = 1; (3426)
          {
            int32_t numberRHS = (int32_t)(1);
            descriptor_t *bitRHS;
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (16, mSTREAMxD_INDEX, bitRHS);
            bitRHS->inUse = 0;
          }
          // REPEAT BLANKS; (3427)
          goto rs1;
        es1s2:;
        } // End of DO block
      // ELSE (3428)
      else
        // RETURN ''; (3429)
        {
          reentryGuard = 0;
          return cToDescriptor (NULL, "");
        }
      if (0)
        {
        rs1:
          continue;
        es1:
          break;
        } // block labeled BLANKS
    }     // End of DO WHILE block
  // DO I = 1 TO #SPECIALS; (3430)
  {
    int32_t from63, to63, by63;
    from63 = 1;
    to63 = 3;
    by63 = 1;
    for (putBIT (16, mSTREAMxD_TOKENxI, fixedToBit (16, from63));
         bitToFixed (getBIT (16, mSTREAMxD_TOKENxI)) <= to63;
         putBIT (16, mSTREAMxD_TOKENxI,
                 fixedToBit (16, bitToFixed (getBIT (16, mSTREAMxD_TOKENxI))
                                     + by63)))
      {
        // IF BYTE(CURRENT_CARD, D_INDEX) = BYTE(SPECIALS, I) THEN (3431)
        if (1
            & (xEQ (BYTE (getCHARACTER (mCURRENT_CARD),
                          COREHALFWORD (mSTREAMxD_INDEX)),
                    BYTE (getCHARACTER (mSTREAMxD_TOKENxSPECIALS),
                          COREHALFWORD (mSTREAMxD_TOKENxI)))))
          // DO; (3432)
          {
          rs2s1:;
            // D_INDEX = D_INDEX + 1; (3433)
            {
              int32_t numberRHS
                  = (int32_t)(xadd (COREHALFWORD (mSTREAMxD_INDEX), 1));
              descriptor_t *bitRHS;
              bitRHS = fixedToBit (32, (int32_t)(numberRHS));
              putBIT (16, mSTREAMxD_INDEX, bitRHS);
              bitRHS->inUse = 0;
            }
            // RETURN SUBSTR(CURRENT_CARD, D_INDEX-1, 1); (3434)
            {
              reentryGuard = 0;
              return SUBSTR (getCHARACTER (mCURRENT_CARD),
                             xsubtract (COREHALFWORD (mSTREAMxD_INDEX), 1), 1);
            }
          es2s1:;
          } // End of DO block
      }
  } // End of DO for-loop block
  // I = D_INDEX; (3435)
  {
    descriptor_t *bitRHS = getBIT (16, mSTREAMxD_INDEX);
    putBIT (16, mSTREAMxD_TOKENxI, bitRHS);
    bitRHS->inUse = 0;
  }
// TOKEN: (3436)
TOKEN:
  // DO WHILE D_INDEX <= TEXT_LIMIT; (3437)
  while (1
         & (xLE (COREHALFWORD (mSTREAMxD_INDEX), COREHALFWORD (mTEXT_LIMIT))))
    {
      // DO J = 0 TO #SPECIALS; (3438)
      {
        int32_t from64, to64, by64;
        from64 = 0;
        to64 = 3;
        by64 = 1;
        for (putBIT (16, mSTREAMxD_TOKENxJ, fixedToBit (16, from64));
             bitToFixed (getBIT (16, mSTREAMxD_TOKENxJ)) <= to64; putBIT (
                 16, mSTREAMxD_TOKENxJ,
                 fixedToBit (16, bitToFixed (getBIT (16, mSTREAMxD_TOKENxJ))
                                     + by64)))
          {
            // IF BYTE(CURRENT_CARD, D_INDEX) = BYTE(SPECIALS, J) THEN (3439)
            if (1
                & (xEQ (BYTE (getCHARACTER (mCURRENT_CARD),
                              COREHALFWORD (mSTREAMxD_INDEX)),
                        BYTE (getCHARACTER (mSTREAMxD_TOKENxSPECIALS),
                              COREHALFWORD (mSTREAMxD_TOKENxJ)))))
              // ESCAPE TOKEN; (3440)
              goto es3;
          }
      } // End of DO for-loop block
      // D_INDEX = D_INDEX + 1; (3441)
      {
        int32_t numberRHS
            = (int32_t)(xadd (COREHALFWORD (mSTREAMxD_INDEX), 1));
        descriptor_t *bitRHS;
        bitRHS = fixedToBit (32, (int32_t)(numberRHS));
        putBIT (16, mSTREAMxD_INDEX, bitRHS);
        bitRHS->inUse = 0;
      }
      if (0)
        {
        rs3:
          continue;
        es3:
          break;
        } // block labeled TOKEN
    }     // End of DO WHILE block
  // RETURN SUBSTR(CURRENT_CARD, I, D_INDEX - I); (3442)
  {
    reentryGuard = 0;
    return SUBSTR (getCHARACTER (mCURRENT_CARD),
                   COREHALFWORD (mSTREAMxD_TOKENxI),
                   xsubtract (COREHALFWORD (mSTREAMxD_INDEX),
                              COREHALFWORD (mSTREAMxD_TOKENxI)));
  }
}