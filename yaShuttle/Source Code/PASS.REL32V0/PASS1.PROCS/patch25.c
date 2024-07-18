{
  // File:      patch25.c
  // For:       BLANK.c
  // Notes:     1. Page references are from IBM "ESA/390 Principles of
  //               Operation", SA22-7201-08, Ninth Edition, June 2003.
  //            2. Labels are of the form p%d_%d, where the 1st number
  //               indicates the leading patch number of the block, and
  //               the 2nd is the byte offset of the instruction within
  //               within the block.
  //            3. Known-problematic translations are marked with the
  //               string  "* * * F I X M E * * *" (without spaces).
  // History:   2024-07-17 RSB  Auto-generated by XCOM-I --guess=....
  //                            Fixed the FIXME.

p25_0: ;
  // (25)       CALL INLINE("58", 1, 0, STRING);      /* L   1,DESCRIPTOR      */         
  address360B = (mBLANKxSTRING) & 0xFFFFFF;
  // Type RX, p. 7-7:		L	1,mBLANKxSTRING(0,0)
  detailedInlineBefore(25, "L	1,mBLANKxSTRING(0,0)");
  GR[1] = COREWORD(address360B);
  detailedInlineAfter();

p25_4: ;
  // (26)       CALL INLINE("41", 1, 0, 1, 0);        /* LA  1,0(0,1)          */         
  address360B = (GR[1] + 0) & 0xFFFFFF;
  // Type RX, p. 7-78:		LA	1,0(0,1)
  detailedInlineBefore(26, "LA	1,0(0,1)");
  GR[1] = address360B & 0xFFFFFF;
  detailedInlineAfter();

p25_8: ;
  // (27)       CALL INLINE("4A", 1, 0, START);       /* AH  1,START           */         
  address360B = (mBLANKxSTART) & 0xFFFFFF;
  // Type RX, p. 7-12:		AH	1,mBLANKxSTART(0,0)
  detailedInlineBefore(27, "AH	1,mBLANKxSTART(0,0)");
  scratch = GR[1] + COREHALFWORD(address360B);
  setCC();
  GR[1] = scratch;
  detailedInlineAfter();

p25_12: ;
  // (28)       CALL INLINE("92", 4, 0, 1, 0);        /* MVI X'40',0(1)        */         
  address360A = (GR[1] + 0) & 0xFFFFFF;
  // Type SI, p. 7-83:		MVI	0(1),64
  detailedInlineBefore(28, "MVI	0(1),64");
  memory[address360A] = 64;
  detailedInlineAfter();

p25_16: ;
  // (29)       CALL INLINE("48", 2, 0, COUNT);       /* LH  2,COUNT           */         
  address360B = (mBLANKxCOUNT) & 0xFFFFFF;
  // Type RX, p. 7-80:		LH	2,mBLANKxCOUNT(0,0)
  detailedInlineBefore(29, "LH	2,mBLANKxCOUNT(0,0)");
  GR[2] = COREHALFWORD(address360B);
  detailedInlineAfter();

p25_20: ;
  // (30)       CALL INLINE("58", 3, 0, J);           /* L   3,J               */         
  address360B = (mBLANKxJ) & 0xFFFFFF;
  // Type RX, p. 7-7:		L	3,mBLANKxJ(0,0)
  detailedInlineBefore(30, "L	3,mBLANKxJ(0,0)");
  GR[3] = COREWORD(address360B);
  detailedInlineAfter();

p25_24: ;
  // (31)       CALL INLINE("44", 2, 0, 3, 0);        /* EX  2,0(0,3)          */         
  address360B = (GR[3] + 0) & 0xFFFFFF;
  // Type RX, p. 7-74:		EX	2,0(0,3)
  detailedInlineBefore(31, "EX	2,0(0,3)");
  // Unsupported opcode EX.  Refer to patch32.c.
  // (32)       CALL INLINE("D2", 0, 0, 1, 1, 1, 0);  /* MVC 1(0,1),0(1)       */
  address360A = (GR[1] + 1) & 0xFFFFFF;
  address360B = (GR[1] + 0) & 0xFFFFFF;
  // Type SS, p. 7-83:          MVC     1(0,1),0(1)
  mvc(address360A, address360B, GR[2]);
  detailedInlineAfter();

p25_28: ;
}