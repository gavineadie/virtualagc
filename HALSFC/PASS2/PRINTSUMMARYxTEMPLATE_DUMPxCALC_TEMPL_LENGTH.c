/*
  File PRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTH.c generated by XCOM-I,
  2024-08-09 12:39:31.
*/

#include "runtimeC.h"

int32_t
PRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTH (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard = guardReentry (reentryGuard,
                               "PRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTH");
  // NUM = SYT_LINK1(OP2); (14579)
  {
    descriptor_t *bitRHS = getBIT (
        16, getFIXED (mSYM_TAB) + 34 * (COREHALFWORD (mOP2)) + 24 + 2 * (0));
    putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM, bitRHS);
    bitRHS->inUse = 0;
  }
  // L = 0; (14580)
  {
    int32_t numberRHS = (int32_t)(0);
    descriptor_t *bitRHS;
    bitRHS = fixedToBit (32, (int32_t)(numberRHS));
    putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxL, bitRHS);
    bitRHS->inUse = 0;
  }
  // DO WHILE NUM ~= 0; (14581)
  while (1
         & (xNEQ (
             COREHALFWORD (mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM),
             0)))
    {
      // IF SYT_LINK1(NUM) ~= 0 THEN (14582)
      if (1
          & (xNEQ (
              COREHALFWORD (
                  getFIXED (mSYM_TAB)
                  + 34
                        * (COREHALFWORD (
                            mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM))
                  + 24 + 2 * (0)),
              0)))
        // NUM = SYT_LINK1(NUM); (14583)
        {
          descriptor_t *bitRHS = getBIT (
              16,
              getFIXED (mSYM_TAB)
                  + 34
                        * (COREHALFWORD (
                            mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM))
                  + 24 + 2 * (0));
          putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM,
                  bitRHS);
          bitRHS->inUse = 0;
        }
      // ELSE (14584)
      else
        // DO; (14585)
        {
        rs1s1:;
          // L = L + 1; (14586)
          {
            int32_t numberRHS = (int32_t)(xadd (
                COREHALFWORD (mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxL),
                1));
            descriptor_t *bitRHS;
            bitRHS = fixedToBit (32, (int32_t)(numberRHS));
            putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxL,
                    bitRHS);
            bitRHS->inUse = 0;
          }
          // DO ; (14587)
          {
          rs1s1s1:;
            // IF COREWORD ( ADDR ( SORT_TAB ) + 12 ) >= COREWORD ( ADDR (
            // SORT_TAB ) + 8 ) THEN (14588)
            if (1
                & (xGE (COREWORD (xadd (ADDR ("PRINTSUMMARYxSORT_TAB",
                                              0x80000000, NULL, 0),
                                        12)),
                        COREWORD (xadd (ADDR ("PRINTSUMMARYxSORT_TAB",
                                              0x80000000, NULL, 0),
                                        8)))))
              // CALL _NEEDMORE_SPACE ( ADDR ( SORT_TAB )  ) ; (14589)
              {
                putFIXED (m_NEEDMORE_SPACExDOPE,
                          ADDR ("PRINTSUMMARYxSORT_TAB", 0x80000000, NULL, 0));
                _NEEDMORE_SPACE (0);
              }
            // COREWORD ( ADDR ( SORT_TAB ) + 12 ) = COREWORD ( ADDR ( SORT_TAB
            // ) + 12 ) + 1 ; (14590)
            {
              int32_t numberRHS = (int32_t)(xadd (
                  COREWORD (xadd (
                      ADDR ("PRINTSUMMARYxSORT_TAB", 0x80000000, NULL, 0),
                      12)),
                  1));
              COREWORD2 (
                  xadd (ADDR ("PRINTSUMMARYxSORT_TAB", 0x80000000, NULL, 0),
                        12),
                  numberRHS);
            }
          es1s1s1:;
          } // End of DO block
          // T_SORT(L) = NUM; (14591)
          {
            descriptor_t *bitRHS = getBIT (
                16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM);
            putBIT (
                16,
                getFIXED (mPRINTSUMMARYxSORT_TAB)
                    + 5
                          * (COREHALFWORD (
                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxL))
                    + 3 + 2 * (0),
                bitRHS);
            bitRHS->inUse = 0;
          }
          // NUM = SYT_LINK2(NUM); (14592)
          {
            descriptor_t *bitRHS = getBIT (
                16,
                getFIXED (mSYM_TAB)
                    + 34
                          * (COREHALFWORD (
                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM))
                    + 26 + 2 * (0));
            putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM,
                    bitRHS);
            bitRHS->inUse = 0;
          }
        es1s1:;
        } // End of DO block
      // DO WHILE NUM < 0; (14593)
      while (1
             & (xLT (COREHALFWORD (
                         mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM),
                     0)))
        {
          // NUM = SYT_LINK2(-NUM); (14594)
          {
            descriptor_t *bitRHS = getBIT (
                16,
                getFIXED (mSYM_TAB)
                    + 34
                          * (xminus (COREHALFWORD (
                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM)))
                    + 26 + 2 * (0));
            putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxNUM,
                    bitRHS);
            bitRHS->inUse = 0;
          }
        } // End of DO WHILE block
    }     // End of DO WHILE block
  // IF (SYT_FLAGS(OP2) & RIGID_FLAG) = 0 THEN (14595)
  if (1
      & (xEQ (xAND (getFIXED (getFIXED (mSYM_TAB) + 34 * (COREHALFWORD (mOP2))
                              + 8 + 4 * (0)),
                    getFIXED (mRIGID_FLAG)),
              0)))
    // DO; (14596)
    {
    rs2:;
      // DO INDX = 1 TO (L-1); (14597)
      {
        int32_t from145, to145, by145;
        from145 = 1;
        to145 = xsubtract (
            COREHALFWORD (mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxL), 1);
        by145 = 1;
        for (putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX,
                     fixedToBit (16, from145));
             bitToFixed (getBIT (
                 16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
             <= to145;
             putBIT (
                 16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX,
                 fixedToBit (
                     16,
                     bitToFixed (getBIT (
                         16,
                         mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
                         + by145)))
          {
            // DO I = 1 TO (L-INDX); (14598)
            {
              int32_t from146, to146, by146;
              from146 = 1;
              to146 = xsubtract (
                  COREHALFWORD (
                      mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxL),
                  COREHALFWORD (
                      mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX));
              by146 = 1;
              for (
                  putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxI,
                          fixedToBit (16, from146));
                  bitToFixed (getBIT (
                      16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxI))
                  <= to146;
                  putBIT (
                      16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxI,
                      fixedToBit (
                          16,
                          bitToFixed (getBIT (
                              16,
                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxI))
                              + by146)))
                {
                  // IF SYT_ADDR(T_SORT(INDX)) > SYT_ADDR(T_SORT(INDX+I)) THEN
                  // (14599)
                  if (1
                      & (xGT (
                          getFIXED (
                              getFIXED (mSYM_TAB)
                              + 34
                                    * (COREHALFWORD (
                                        getFIXED (mPRINTSUMMARYxSORT_TAB)
                                        + 5
                                              * (COREHALFWORD (
                                                  mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
                                        + 3 + 2 * (0)))
                              + 4 + 4 * (0)),
                          getFIXED (
                              getFIXED (mSYM_TAB)
                              + 34
                                    * (COREHALFWORD (
                                        getFIXED (mPRINTSUMMARYxSORT_TAB)
                                        + 5
                                              * (xadd (
                                                  COREHALFWORD (
                                                      mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX),
                                                  COREHALFWORD (
                                                      mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxI)))
                                        + 3 + 2 * (0)))
                              + 4 + 4 * (0)))))
                    // DO; (14600)
                    {
                    rs2s1s1s1:;
                      // TEMP = T_SORT(INDX); (14601)
                      {
                        descriptor_t *bitRHS = getBIT (
                            16,
                            getFIXED (mPRINTSUMMARYxSORT_TAB)
                                + 5
                                      * (COREHALFWORD (
                                          mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
                                + 3 + 2 * (0));
                        putBIT (
                            16,
                            mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxTEMP,
                            bitRHS);
                        bitRHS->inUse = 0;
                      }
                      // T_SORT(INDX) = T_SORT(INDX+I); (14602)
                      {
                        descriptor_t *bitRHS = getBIT (
                            16,
                            getFIXED (mPRINTSUMMARYxSORT_TAB)
                                + 5
                                      * (xadd (
                                          COREHALFWORD (
                                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX),
                                          COREHALFWORD (
                                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxI)))
                                + 3 + 2 * (0));
                        putBIT (
                            16,
                            getFIXED (mPRINTSUMMARYxSORT_TAB)
                                + 5
                                      * (COREHALFWORD (
                                          mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
                                + 3 + 2 * (0),
                            bitRHS);
                        bitRHS->inUse = 0;
                      }
                      // T_SORT(INDX+I) = TEMP; (14603)
                      {
                        descriptor_t *bitRHS = getBIT (
                            16,
                            mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxTEMP);
                        putBIT (
                            16,
                            getFIXED (mPRINTSUMMARYxSORT_TAB)
                                + 5
                                      * (xadd (
                                          COREHALFWORD (
                                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX),
                                          COREHALFWORD (
                                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxI)))
                                + 3 + 2 * (0),
                            bitRHS);
                        bitRHS->inUse = 0;
                      }
                    es2s1s1s1:;
                    } // End of DO block
                }
            } // End of DO for-loop block
          }
      } // End of DO for-loop block
    es2:;
    } // End of DO block
  // IF (SYT_FLAGS(T_SORT(1)) & NAME_FLAG) ~= 0 THEN (14604)
  if (1
      & (xNEQ (xAND (getFIXED (getFIXED (mSYM_TAB)
                               + 34
                                     * (COREHALFWORD (
                                         getFIXED (mPRINTSUMMARYxSORT_TAB)
                                         + 5 * (1) + 3 + 2 * (0)))
                               + 8 + 4 * (0)),
                     getFIXED (mNAME_FLAG)),
               0)))
    // DO; (14605)
    {
    rs3:;
      // IF (SYT_FLAGS(T_SORT(1)) & REMOTE_FLAG) ~= 0 THEN (14606)
      if (1
          & (xNEQ (xAND (getFIXED (getFIXED (mSYM_TAB)
                                   + 34
                                         * (COREHALFWORD (
                                             getFIXED (mPRINTSUMMARYxSORT_TAB)
                                             + 5 * (1) + 3 + 2 * (0)))
                                   + 8 + 4 * (0)),
                         getFIXED (mREMOTE_FLAG)),
                   0)))
        // LENGTHI = 2; (14607)
        {
          int32_t numberRHS = (int32_t)(2);
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI, bitRHS);
          bitRHS->inUse = 0;
        }
      // ELSE (14608)
      else
        // LENGTHI = 1; (14609)
        {
          int32_t numberRHS = (int32_t)(1);
          descriptor_t *bitRHS;
          bitRHS = fixedToBit (32, (int32_t)(numberRHS));
          putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI, bitRHS);
          bitRHS->inUse = 0;
        }
    es3:;
    } // End of DO block
  // ELSE (14610)
  else
    // LENGTHI = EXTENT(T_SORT(1)); (14611)
    {
      int32_t numberRHS = (int32_t)(getFIXED (
          getFIXED (mSYM_TAB)
          + 34
                * (COREHALFWORD (getFIXED (mPRINTSUMMARYxSORT_TAB) + 5 * (1)
                                 + 3 + 2 * (0)))
          + 12 + 4 * (0)));
      descriptor_t *bitRHS;
      bitRHS = fixedToBit (32, (int32_t)(numberRHS));
      putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI, bitRHS);
      bitRHS->inUse = 0;
    }
  // DO INDX = 1 TO (L-1); (14612)
  {
    int32_t from147, to147, by147;
    from147 = 1;
    to147 = xsubtract (
        COREHALFWORD (mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxL), 1);
    by147 = 1;
    for (putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX,
                 fixedToBit (16, from147));
         bitToFixed (
             getBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
         <= to147;
         putBIT (
             16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX,
             fixedToBit (
                 16,
                 bitToFixed (getBIT (
                     16, mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
                     + by147)))
      {
        // IF (SYT_FLAGS(T_SORT(INDX+1)) & NAME_FLAG) ~= 0 THEN (14613)
        if (1
            & (xNEQ (
                xAND (
                    getFIXED (
                        getFIXED (mSYM_TAB)
                        + 34
                              * (COREHALFWORD (
                                  getFIXED (mPRINTSUMMARYxSORT_TAB)
                                  + 5
                                        * (xadd (
                                            COREHALFWORD (
                                                mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX),
                                            1))
                                  + 3 + 2 * (0)))
                        + 8 + 4 * (0)),
                    getFIXED (mNAME_FLAG)),
                0)))
          // DO; (14614)
          {
          rs4s1:;
            // IF (SYT_FLAGS(T_SORT(INDX+1)) & REMOTE_FLAG) ~= 0 THEN (14615)
            if (1
                & (xNEQ (
                    xAND (
                        getFIXED (
                            getFIXED (mSYM_TAB)
                            + 34
                                  * (COREHALFWORD (
                                      getFIXED (mPRINTSUMMARYxSORT_TAB)
                                      + 5
                                            * (xadd (
                                                COREHALFWORD (
                                                    mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX),
                                                1))
                                      + 3 + 2 * (0)))
                            + 8 + 4 * (0)),
                        getFIXED (mREMOTE_FLAG)),
                    0)))
              // LENGTHI = LENGTHI + 2; (14616)
              {
                int32_t numberRHS = (int32_t)(xadd (
                    COREHALFWORD (mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI), 2));
                descriptor_t *bitRHS;
                bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI, bitRHS);
                bitRHS->inUse = 0;
              }
            // ELSE (14617)
            else
              // LENGTHI = LENGTHI + 1; (14618)
              {
                int32_t numberRHS = (int32_t)(xadd (
                    COREHALFWORD (mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI), 1));
                descriptor_t *bitRHS;
                bitRHS = fixedToBit (32, (int32_t)(numberRHS));
                putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI, bitRHS);
                bitRHS->inUse = 0;
              }
          es4s1:;
          } // End of DO block
        // ELSE (14619)
        else
          // IF SYT_ADDR(T_SORT(INDX)) ~= SYT_ADDR(T_SORT(INDX+1)) THEN (14620)
          if (1
              & (xNEQ (
                  getFIXED (
                      getFIXED (mSYM_TAB)
                      + 34
                            * (COREHALFWORD (
                                getFIXED (mPRINTSUMMARYxSORT_TAB)
                                + 5
                                      * (COREHALFWORD (
                                          mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX))
                                + 3 + 2 * (0)))
                      + 4 + 4 * (0)),
                  getFIXED (
                      getFIXED (mSYM_TAB)
                      + 34
                            * (COREHALFWORD (
                                getFIXED (mPRINTSUMMARYxSORT_TAB)
                                + 5
                                      * (xadd (
                                          COREHALFWORD (
                                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX),
                                          1))
                                + 3 + 2 * (0)))
                      + 4 + 4 * (0)))))
            // LENGTHI = LENGTHI + EXTENT(T_SORT(INDX+1)); (14621)
            {
              int32_t numberRHS = (int32_t)(xadd (
                  COREHALFWORD (mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI),
                  getFIXED (
                      getFIXED (mSYM_TAB)
                      + 34
                            * (COREHALFWORD (
                                getFIXED (mPRINTSUMMARYxSORT_TAB)
                                + 5
                                      * (xadd (
                                          COREHALFWORD (
                                              mPRINTSUMMARYxTEMPLATE_DUMPxCALC_TEMPL_LENGTHxINDX),
                                          1))
                                + 3 + 2 * (0)))
                      + 12 + 4 * (0))));
              descriptor_t *bitRHS;
              bitRHS = fixedToBit (32, (int32_t)(numberRHS));
              putBIT (16, mPRINTSUMMARYxTEMPLATE_DUMPxLENGTHI, bitRHS);
              bitRHS->inUse = 0;
            }
      }
  } // End of DO for-loop block
  {
    reentryGuard = 0;
    return 0;
  }
}