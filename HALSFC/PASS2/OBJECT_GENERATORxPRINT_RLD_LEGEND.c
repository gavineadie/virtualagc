/*
  File OBJECT_GENERATORxPRINT_RLD_LEGEND.c generated by XCOM-I, 2024-08-09
  12:39:31.
*/

#include "runtimeC.h"

int32_t
OBJECT_GENERATORxPRINT_RLD_LEGEND (int reset)
{
  static int reentryGuard = 0;
  if (reset)
    {
      reentryGuard = 0;
      return (int32_t)0;
    }
  reentryGuard
      = guardReentry (reentryGuard, "OBJECT_GENERATORxPRINT_RLD_LEGEND");
  // ABSLIST_COUNT = LINE_LIM; (16173)
  {
    descriptor_t *bitRHS = getBIT (16, mOBJECT_GENERATORxLINE_LIM);
    putBIT (16, mOBJECT_GENERATORxABSLIST_COUNT, bitRHS);
    bitRHS->inUse = 0;
  }
  // OUTPUT(1) = AHEAD(3); (16174)
  {
    descriptor_t *stringRHS;
    stringRHS = getCHARACTER (mOBJECT_GENERATORxAHEAD + 4 * 3);
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = '1'; (16175)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "1");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = AHEAD(2); (16176)
  {
    descriptor_t *stringRHS;
    stringRHS = getCHARACTER (mOBJECT_GENERATORxAHEAD + 4 * 2);
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = ' RLD INFORMATION'; (16177)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, " RLD INFORMATION");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = ''; (16178)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = ' POS.ID (P) IS THE ESDID OF SD FOR THE CONTROL '; (16179)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL, " POS.ID (P) IS THE ESDID OF SD FOR THE CONTROL ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = S1||'SECTION THAT CONTAINS THE ADDRESS CONSTANT'; (16180)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (
        getCHARACTER (mOBJECT_GENERATORxS1),
        cToDescriptor (NULL, "SECTION THAT CONTAINS THE ADDRESS CONSTANT"));
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = S1; (16181)
  {
    descriptor_t *stringRHS;
    stringRHS = getCHARACTER (mOBJECT_GENERATORxS1);
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = ' REL.ID (R) IS THE ESDID OF ESD ENTRY FOR THE '; (16182)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL, " REL.ID (R) IS THE ESDID OF ESD ENTRY FOR THE ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = S1||'SYMBOL BEING REFERRED TO'; (16183)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (getCHARACTER (mOBJECT_GENERATORxS1),
                       cToDescriptor (NULL, "SYMBOL BEING REFERRED TO"));
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = S1; (16184)
  {
    descriptor_t *stringRHS;
    stringRHS = getCHARACTER (mOBJECT_GENERATORxS1);
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = ''; (16185)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = '  FLAG        TYPE'; (16186)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "  FLAG        TYPE");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = 'ACTION PERFORMED'; (16187)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "ACTION PERFORMED");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||S1||SUBSTR(X72,0,32)||S2; (16188)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                                     getCHARACTER (mOBJECT_GENERATORxS1)),
                              SUBSTR (getCHARACTER (mX72), 0, 32)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = ''; (16189)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = 'V00000ST      YCON      RELOCATION FACTOR IS ADDED TO ADDRESS ';
  // (16190)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL,
        "V00000ST      YCON      RELOCATION FACTOR IS ADDED TO ADDRESS ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = 'CONSTANT.  IF ADDRESS IS GREATER THAN 15 BITS, SET BIT "0" ON.';
  // (16191)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL,
        "CONSTANT.  IF ADDRESS IS GREATER THAN 15 BITS, SET BIT \"0\" ON.");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||S1||S2; (16192)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = '000001ST      ACON      RELOCATION FACTOR IS ADDED TO ADDRESS ';
  // (16193)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL,
        "000001ST      ACON      RELOCATION FACTOR IS ADDED TO ADDRESS ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = 'CONSTANT.'; (16194)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "CONSTANT.");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||S1||S2; (16195)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = 'V00100ST      ZCON      ADD RELOCATION FACTOR TO FIRST HALFWORD.';
  // (16196)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL,
        "V00100ST      ZCON      ADD RELOCATION FACTOR TO FIRST HALFWORD.");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = '  IF GREATER THAN 15 BITS, UPDATE BSR FIELD.'; (16197)
  {
    descriptor_t *stringRHS;
    stringRHS
        = cToDescriptor (NULL, "  IF GREATER THAN 15 BITS, UPDATE BSR FIELD.");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||S1||S2; (16198)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,32)||'(BRANCH RELOCATION FOR 32-BIT BRANCH)';
  // (16199)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (
        SUBSTR (getCHARACTER (mX72), 0, 32),
        cToDescriptor (NULL, "(BRANCH RELOCATION FOR 32-BIT BRANCH)"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = 'V10000ST      ZCON      UPDATE DSR FIELD WITH HIGH ORDER 4 BITS ';
  // (16200)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL,
        "V10000ST      ZCON      UPDATE DSR FIELD WITH HIGH ORDER 4 BITS ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = 'OF THE 19-BIT RELOCATION FACTOR.'; (16201)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "OF THE 19-BIT RELOCATION FACTOR.");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||S1||S2; (16202)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,32)||'(DATA RELOCATION FOR 32-BIT BRANCH)';
  // (16203)
  {
    descriptor_t *stringRHS;
    stringRHS
        = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 32),
                 cToDescriptor (NULL, "(DATA RELOCATION FOR 32-BIT BRANCH)"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = 'V01000ST      ZCON      UPDATE BSR FIELD WITH HIGH ORDER 4 BITS ';
  // (16204)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL,
        "V01000ST      ZCON      UPDATE BSR FIELD WITH HIGH ORDER 4 BITS ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = 'OF THE 19-BIT RELOCATION FACTOR.'; (16205)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "OF THE 19-BIT RELOCATION FACTOR.");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||S1||S2; (16206)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,32)||'(BRANCH RELOCATION FOR 32-BIT DATA)';
  // (16207)
  {
    descriptor_t *stringRHS;
    stringRHS
        = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 32),
                 cToDescriptor (NULL, "(BRANCH RELOCATION FOR 32-BIT DATA)"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = 'V10100ST      ZCON      ADD RELOCATION FACTOR TO FIRST HALFWORD.';
  // (16208)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL,
        "V10100ST      ZCON      ADD RELOCATION FACTOR TO FIRST HALFWORD.");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = '  IF GREATER THAN 15-BITS, UPDATE DSR FIELD.'; (16209)
  {
    descriptor_t *stringRHS;
    stringRHS
        = cToDescriptor (NULL, "  IF GREATER THAN 15-BITS, UPDATE DSR FIELD.");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||S1||S2; (16210)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,32)||'(DATA RELOCATION FOR 32-BIT DATA)'; (16211)
  {
    descriptor_t *stringRHS;
    stringRHS
        = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 32),
                 cToDescriptor (NULL, "(DATA RELOCATION FOR 32-BIT DATA)"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = ''; (16212)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||'V = SIGN OF THE YCON IN THE TEXT RECORD';
  // (16213)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (
        SUBSTR (getCHARACTER (mX72), 0, 8),
        cToDescriptor (NULL, "V = SIGN OF THE YCON IN THE TEXT RECORD"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,13)||'0 = THE YCON IS POSITIVE'; (16214)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 13),
                       cToDescriptor (NULL, "0 = THE YCON IS POSITIVE"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = '1 = THE YCON IS THE ABSOLUTE VALUE OF A NEGATIVE NUMBER'; (16215)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL, "1 = THE YCON IS THE ABSOLUTE VALUE OF A NEGATIVE NUMBER");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,13)||S1; (16216)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 13),
                       getCHARACTER (mOBJECT_GENERATORxS1));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||'S = DIRECTION OF RELOCATION'; (16217)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                       cToDescriptor (NULL, "S = DIRECTION OF RELOCATION"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,13)||'0 = POSITIVE'; (16218)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 13),
                       cToDescriptor (NULL, "0 = POSITIVE"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,13)||'1 = NEGATIVE'; (16219)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 13),
                       cToDescriptor (NULL, "1 = NEGATIVE"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,8)||'T = TYPE OF NEXT RLD ITEM'; (16220)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (SUBSTR (getCHARACTER (mX72), 0, 8),
                       cToDescriptor (NULL, "T = TYPE OF NEXT RLD ITEM"));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = '0 = NEXT RLD ITEM HAS DIFFERENT R OR P POINTERS; THEY ARE '; (16221)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL, "0 = NEXT RLD ITEM HAS DIFFERENT R OR P POINTERS; THEY ARE ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = 'IN THE NEXT ITEM'; (16222)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "IN THE NEXT ITEM");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,13)||S1||S2; (16223)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 13),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S1 = '1 = NEXT RLD ITEM HAS SAME R AND P POINTERS; HENCE THEY ARE ';
  // (16224)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (
        NULL, "1 = NEXT RLD ITEM HAS SAME R AND P POINTERS; HENCE THEY ARE ");
    putCHARACTER (mOBJECT_GENERATORxS1, stringRHS);
    stringRHS->inUse = 0;
  }
  // S2 = 'OMITTED'; (16225)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "OMITTED");
    putCHARACTER (mOBJECT_GENERATORxS2, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = SUBSTR(X72,0,13)||S1||S2; (16226)
  {
    descriptor_t *stringRHS;
    stringRHS = xsCAT (xsCAT (SUBSTR (getCHARACTER (mX72), 0, 13),
                              getCHARACTER (mOBJECT_GENERATORxS1)),
                       getCHARACTER (mOBJECT_GENERATORxS2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = ''; (16227)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = X2||SUBSTR(AHEAD(2),2); (16228)
  {
    descriptor_t *stringRHS;
    stringRHS
        = xsCAT (getCHARACTER (mX2),
                 SUBSTR2 (getCHARACTER (mOBJECT_GENERATORxAHEAD + 4 * 2), 2));
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  // OUTPUT(1) = ''; (16229)
  {
    descriptor_t *stringRHS;
    stringRHS = cToDescriptor (NULL, "");
    OUTPUT (1, stringRHS);
    stringRHS->inUse = 0;
  }
  {
    reentryGuard = 0;
    return 0;
  }
}