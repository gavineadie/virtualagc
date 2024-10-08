{
  /*
   * File:      patch19.c
   * For:       ZEROu256.c
   * Notes:     1. Page references are from IBM "ESA/390 Principles of
   *               Operation", SA22-7201-08, Ninth Edition, June 2003.
   *            2. Labels are of the form p%d_%d, where the 1st number
   *               indicates the leading patch number of the block, and
   *               the 2nd is the byte offset of the instruction within
   *               within the block.
   *            3. Known-problematic translations are marked with the
   *               string  "* * * F I X M E * * *" (without spaces).
   * History:   2024-07-18 RSB  Auto-generated by XCOM-I --guess=....
   *                            Fixed the EX FIXME.
   */

p19_0: ;
  // (19)          CALL INLINE("58", 1, 0, COREuADDR);  /* L   1,COREuADDR              */
  address360B = (mZEROu256xCOREuADDR) & 0xFFFFFF;
  // Type RX, p. 7-7:		L	1,mZEROu256xCOREuADDR(0,0)
  detailedInlineBefore(19, "L	1,mZEROu256xCOREuADDR(0,0)");
  GR[1] = COREWORD(address360B);
  detailedInlineAfter();

p19_4: ;
  // (20)          CALL INLINE("92", 0, 0, 1, 0);       /* MVI 0(1),X'00'               */
  address360A = (GR[1] + 0) & 0xFFFFFF;
  // Type SI, p. 7-83:		MVI	0(1),0
  detailedInlineBefore(20, "MVI	0(1),0");
  memory[address360A] = 0;
  detailedInlineAfter();

p19_8: ;
  // (21)          CALL INLINE("48", 2, 0, COUNT);      /* LH  2,COUNT                  */
  address360B = (mZEROu256xCOUNT) & 0xFFFFFF;
  // Type RX, p. 7-80:		LH	2,mZEROu256xCOUNT(0,0)
  detailedInlineBefore(21, "LH	2,mZEROu256xCOUNT(0,0)");
  GR[2] = COREHALFWORD(address360B);
  detailedInlineAfter();

p19_12: ;
  // (22)          CALL INLINE("58", 3, 0, MVCTEMP);    /* L   3,MVCTEMP                */
  address360B = (mZEROu256xMVCTEMP) & 0xFFFFFF;
  // Type RX, p. 7-7:		L	3,mZEROu256xMVCTEMP(0,0)
  detailedInlineBefore(22, "L	3,mZEROu256xMVCTEMP(0,0)");
  GR[3] = COREWORD(address360B);
  detailedInlineAfter();

p19_16: ;
  // (23)          CALL INLINE("44", 2, 0, 3, 0);       /* EX  2,0(0,3)                 */
  address360B = (GR[3] + 0) & 0xFFFFFF;
  // Type RX, p. 7-74:		EX	2,0(0,3)
  detailedInlineBefore(23, "EX	2,0(0,3)");
  // Unsupported opcode EX.  See patch24.c.
  // (24)       CALL INLINE("D2", 0, 0, 1, 1, 1, 0);    /* MVC 1(0,1),0(1)              */
  address360A = (GR[1] + 1) & 0xFFFFFF;
  address360B = (GR[1] + 0) & 0xFFFFFF;
  // Type SS, p. 7-83:          MVC     1(0,1),0(1)
  mvc(address360A, address360B, GR[2]);
  detailedInlineAfter();

p19_20: ;
}
