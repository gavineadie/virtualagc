         MACRO                                                          00000010
&L       IDEDR &R0,&R2,&R4,&R6                                          00000020
&L       LER   &R4,&R0                                                  00000022
         LER   &R4+1,&R0+1                                              00000024
         DER   &R0,&R2                                                  00000030
         LER   &R6,&R0                                                  00000050
         LER   &R6+1,&R0+1                                              00000060
         MEDR  &R6,&R2                                                  00000070
         SEDR  &R6,&R4                                                  00000080
         DER   &R6,&R2                                                  00000090
         SEDR  &R0,&R6                                                  00000100
         MEND                                                           00000110