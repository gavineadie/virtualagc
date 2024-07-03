{
  // File:      patch52p.c
  // For:       SAVE_LITERAL.c
  // Notes:     1. Page references are from IBM "ESA/390 Principles of
  //               Operation", SA22-7201-08, Ninth Edition, June 2003.
  //            2. Labels are of the form p%d_%d, where the 1st number
  //               indicates the leading patch number of the block, and
  //               the 2nd is the byte offset of the instruction within
  //               within the block.
  //            3. Known-problematic translations are marked with the
  //               string  "* * * F I X M E * * *" (without spaces).
  // History:   2024-06-26 RSB  Auto-generated by XCOM-I --guess-inlines.
  //                            Checked and changed "guess" to "patch".

p52_0: ;
  // (52)             CALL INLINE("58",1,0,VAL);              /* L    1,VAL        */     
  address360B = 56620;
  // Type RX, p. 7-7:		L	1,56620(0,0)
  GR[1] = COREWORD(address360B);

p52_4: ;
  // (53)             CALL INLINE("58",2,0,LIT_CHAR_AD);      /* L    2,LIT_CHAR_AD */    
  address360B = 2200;
  // Type RX, p. 7-7:		L	2,2200(0,0)
  GR[2] = COREWORD(address360B);

p52_8: ;
  // (54)             CALL INLINE("58",3,0,SIZE);             /* L    3,SIZE        */    
  address360B = 56624;
  // Type RX, p. 7-7:		L	3,56624(0,0)
  GR[3] = COREWORD(address360B);

  /*
   * CALL INLINE statements #55 and #56 (see patch56p.c) do not operate as
   * XCOM-I --guess expects.  This pair is *self-modifying* code.  `VAL` (the
   * 2nd parameter of this `SAVE_LITERAL` procedure) is a string descriptor.
   * Inline  #55 copies the length field from `VAL` into the length field of
   * the MVC instruction in inline #56.  This is different from an EX operation,
   * because the change is persistent and inline #56 is executed in-place when
   * the instruction counter gets to it.  We can handle it by just letting
   * #56 read `VAL` itself.
   */
p52_12: ;
  // (55)             CALL INLINE("D2",0,0,3,1,VAL);          /* MVC  1(0,3),VAL    */
  /*
  address360A = GR[3] + 1;
  address360B = 56620;
  // Type SS, p. 7-83:		MVC	1(0,3),56620(0)
  mvc(address360A, address360B, 0);
  */

p52_18: ;
}