### FILE="Main.annotation"
## Copyright:   Public domain.
## Filename:    DOWNLINK_LISTS.agc
## Purpose:     A section of Luminary revision 178.
##              It is part of the reconstructed source code for the final
##              release of the flight software for the Lunar Module's
##              (LM) Apollo Guidance Computer (AGC) for Apollo 14. The
##              code has been recreated from copies of Zerlina 56, Luminary
##              210, and Luminary 131, as well as many Luminary memos.
##              It has been adapted such that the resulting bugger words
##              exactly match those specified for Luminary 178 in NASA
##              drawing 2021152N, which gives relatively high confidence
##              that the reconstruction is correct.
## Reference:   pp. 199-212
## Assembler:   yaYUL
## Contact:     Ron Burkey <info@sandroid.org>.
## Website:     www.ibiblio.org/apollo/index.html
## Mod history: 2019-08-14 MAS  Created from Zerlina 56.
##              2019-08-31 MAS  Restored the LMREND07 downlist to what
##                              it was in Luminary 131, deleted the
##                              LMREND08 sublist, reverted the leadin
##                              for RENDEZVU, deleted all of the DLxxx
##                              tags, and replaced LRTIMEDL with MKTIME.

## Page 199
                BANK            22
                SETLOC          DOWNTELM
                BANK

                EBANK=          DNTMBUFF

# SPECIAL DOWNLINK OP CODES
#                                                   OP CODE ADDRESS(EXAMPLE) SENDS..     BIT 15  BITS 14-12 BITS 11
#                                                                                                                -0
#                                                   ------ ----------      ----------    ------  ---------- -------
#                                                                                                                --
#                                                   1DNADR TIME2           (2 AGC WDS)     0         0      ECADR
#                                                   2DNADR TEPHEM          (4 AGC WDS)     0         1      ECADR
#                                                   3DNADR VGBODY          (6 AGC WDS)     0         2      ECADR
#                                                   4DNADR STATE           (8 AGC WDS)     0         3      ECADR
#                                                   5DNADR UPBUFF          (10AGC WDS)     0         4      ECADR
#                                                   6DNADR DSPTAB          (12AGC WDS)     0         5      ECADR
#                                                   DNCHAN 30              CHANNELS        0         7      CHANNEL
#                                                                                                           ADDRESS
#                                                   DNPTR  NEXTLIST        POINTS TO NEXT  0         6      ADRES
#                                                                           LIST.

# DOWNLIST FORMAT DEFINITIONS AND RULES-
# 1. END OF A LIST = -XDNADR (X = 1 TO 6), -DNPTR, OR -DNCHAN.
# 2. SNAPSHOT SUBLIST = LIST WHICH STARTS WITH A -1DNADR.
# 3. SNAPSHOT SUBLIST CAN ONLY CONTAIN 1DNADRS.
# 4. TIME2 1DNADR MUST BE LOCATED IN THE CONTROL LIST OF A DOWNLIST.
# 5. ERASABLE DOWN TELEMETRY WORDS SHOULD BE GROUPED IN SEQUENTIAL
#    LOCATIONS AS MUCH AS POSSIBLE TO SAVE STORAGE USED BY DOWNLINK LISTS.

                COUNT*          $$/DLIST
ERASZERO        EQUALS          7
UNKNOWN         EQUALS          ERASZERO
SPARE           EQUALS          ERASZERO                # USE SPARE TO INDICATE AVAILABLE SPACE
LOWIDCOD        OCT             77340                   # LOW ID CODE


NOMDNLST        EQUALS          COSTALIN                # FRESH START AND POST P27 DOWNLIST
AGSLIST         EQUALS          AGSI/UPD
UPDNLIST        EQUALS          AGSI/UPD                # UPDATE PROGRAM (P27) DOWNLIST

## Page 200
# LM ORBITAL MANEUVERS LIST

#     -----------------  CONTROL LIST  --------------------------

ORBMANUV        EQUALS                                  # SEND ID BY SPECIAL CODING
                DNPTR           LMORBM01                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                1DNADR          DELLT4                  # DELLT4,+1
                3DNADR          RTARG                   # RTARG,+1...+5
                1DNADR          ELEV                    # ELEV,+1
                1DNADR          TEVENT                  # TEVENT,+1
                6DNADR          REFSMMAT                # REFSMMAT+0...+11D
                1DNADR          TCSI                    # TCSI,+1
                3DNADR          DELVEET1                # DELVEET1+0...+5
                3DNADR          VGTIG                   # VGTIG+0...+5
                1DNADR          DNLRVELZ                # DNLRVELZ,DNLRALT
                1DNADR          TPASS4                  # TPASS4,+1
                DNPTR           LMORBM02                # COMMON DATA
                1DNADR          TIME2                   # TIME2/1
                DNPTR           LMORBM03                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMORBM04                # COMMON DATA
                2DNADR          POSTORKU                # POSTORKU,NEGTORKU,POSTORKV,NEGTORKV
                1DNADR          SERVDURN                # SERVDURN,DUMLOOPS
                1DNADR          TCDH                    # TCDH,+1
                3DNADR          DELVEET2                # DELVEET2+0...+5
                1DNADR          TTPI                    # TTPI,+1
                3DNADR          DELVEET3                # DELVEET3+0...+5
                1DNADR          DNRRANGE                # DNRRANGE,DNRRDOT
                2DNADR          DNLRVELX                # DNLRVELX,DNLRVELY,DNLRVELZ,DNLRALT
                1DNADR          DIFFALT                 # DIFFALT,+1
                1DNADR          LEMMASS                 # LEMMASS,CSMMASS
                1DNADR          IMODES30                # IMODES30,IMODES33
                1DNADR          TIG                     # TIG,+1
                DNPTR           LMORBM05                # COMMON DATA
                DNPTR           LMORBM06                # COMMON DATA
                1DNADR          SPARE                   # FORMERLY PIF
               -1DNADR          TGO                     # TGO,+1

#     -----------------  SUB-LISTS  ----------------------------

LMORBM01       -1DNADR          R-OTHER         +2      # R-OTHER+2,+3             SNAPSHOT
                1DNADR          R-OTHER         +4      # R-OTHER+4,+5
                1DNADR          V-OTHER                 # V-OTHER,+1
                1DNADR          V-OTHER         +2      # V-OTHER+2,+3
                1DNADR          V-OTHER         +4      # V-OTHER+4,+5
                1DNADR          T-OTHER                 # T-OTHER,+1
               -1DNADR          R-OTHER                 # R-OTHER+0,+1

LMORBM02        2DNADR          REDOCTR                 # REDOCTR,THETAD,+1,+2     COMMON DATA

## Page 201
                1DNADR          RSBBQ                   # RSBBQ,+1
                2DNADR          OMEGAP                  # OMEGAP,OMEGAQ,OMEGAR,GARBAGE
                2DNADR          CDUXD                   # CDUXD,CDUYD,CDUZD,GARBAGE
                2DNADR          CDUX                    # CDUX,CDUY,CDUZ,CDUT
                6DNADR          STATE                   # STATE+0...+11D (FLAGWORDS)
               -6DNADR          DSPTAB                  # DSPTAB TABLES

LMORBM03       -1DNADR          RN              +2      # RN +2,+3                 SNAPSHOT
                1DNADR          RN              +4      # RN +4,+5
                1DNADR          VN                      # VN,+1
                1DNADR          VN              +2      # VN +2,+3
                1DNADR          VN              +4      # VN +4,+5
                1DNADR          PIPTIME                 # PIPTIME,+1
               -1DNADR          RN                      # RN,+1

LMORBM04        2DNADR          OMEGAPD                 # OMEGAPD,OMEGAQD,OMEGARD,GARBAGE
                DNCHAN          76                      # GARBAGE,CHANNEL77
                2DNADR          CADRFLSH        +2      # CADRFLSH +2,FAILREG,+1,+2
               -1DNADR          RADMODES                # RADMODES,DAPBOOLS        COMMON DATA

LMORBM05        2DNADR          OMEGAP                  # OMEGAP,OMEGAQ,OMEGAR,GARBAGE
                2DNADR          CDUXD                   # CDUXD,CDUXD,CDUZD,GARBAGE
                2DNADR          CDUX                    # CDUX,CDUY,CDUZ,CDUT
                1DNADR          ALPHAQ                  # ALPHAQ,ALPHAR            COMMON DATA
                1DNADR          POSTORKP                # POSTORKP,NEGTORKP
LMORBM09        DNCHAN          11                      # CHANNEL11 ,12
                DNCHAN          13                      # CHANNELS13,14
                DNCHAN          30                      # CHANNELS30,31
               -DNCHAN          32                      # CHANNELS32,33

LMORBM06        1DNADR          PIPTIME1                # PIPTIME,+1               COMMON DATA
               -3DNADR          DELV                    # DELV+0...+5

## Page 203
# LM COAST AND ALIGNMENT DOWNLIST

#     -----------------  CONTROL LIST  --------------------------

COSTALIN        EQUALS                                  # SEND ID BY SPECIAL CODING
                DNPTR           LMCSTA01                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                1DNADR          AGSK                    # AGSK,+1
                1DNADR          TALIGN                  # TALIGN,+1
                2DNADR          POSTORKU                # POSTORKU,NEGTORKU,POSTORKV,NEGTORKV
                1DNADR          DNRRANGE                # DNRRANGE,DNRRDOT
                1DNADR          TEVENT                  # TEVENT,+1
                6DNADR          REFSMMAT                # REFSMMAT+0...+11D
                1DNADR          AOTCODE                 # AOTCODE,GARBAGE
                3DNADR          RLS                     # RLS+0...+5
                2DNADR          DNLRVELX                # DNLRVELX,DNLRVELY,DNLRVELZ,DNLRALT
                3DNADR          VGTIG                   # VGTIGX,Y,Z
                DNPTR           LMCSTA02                # COMMON DATA
                1DNADR          TIME2                   # TIME2/1
                DNPTR           LMCSTA03                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMCSTA04                # COMMON DATA
                DNPTR           LMCSTA07                # COMMON DATA
                1DNADR          SERVDURN                # SERVDURN,DUMLOOPS
                1DNADR          TET                     # TET,+1
                2DNADR          CDUS                    # CDUS,PIPAX,PIPAY,PIPAZ
                1DNADR          LASTYCMD                # LASTYCMD,LASTXCMD
                1DNADR          LEMMASS                 # LEMMASS,CSMMASS
                1DNADR          IMODES30                # IMODES30,IMODES33
                1DNADR          TIG                     # TIG,+1
                DNPTR           LMCSTA05                # COMMON DATA
               -6DNADR          DSPTAB                  # DSPTAB+0...+11D TABLE

#     -----------------  SUB-LISTS  ----------------------------

LMCSTA01        EQUALS          LMORBM01                # COMMON DOWNLIST DATA

LMCSTA02        EQUALS          LMORBM02                # COMMON DOWNLIST DATA

LMCSTA03        EQUALS          LMORBM03                # COMMON DOWNLIST DATA

LMCSTA04        EQUALS          LMORBM04                # COMMON DOWNLIST DATA

LMCSTA05        EQUALS          LMORBM05                # COMMON DOWNLIST DATA

LMCSTA06        2DNADR          X789                    # X789+0...+3              COMMON DATA
               -1DNADR          LASTYCMD                # LASTYCMD,LASTXCMD

LMCSTA07        3DNADR          OGC                     # OGC,+1,IGC,+1,MGC,+1     COMMON DATA
                1DNADR          BESTI                   # BESTI,BESTJ
# Page 204                
                3DNADR          STARSAV1                # STARSAV1+0...+5
               -3DNADR          STARSAV2                # STARSAV2+0...+5

## Page 205
# LM RENDEZVOUS AND PRE-THRUST DOWNLIST

#     -----------------  CONTROL LIST  --------------------------

RENDEZVU        EQUALS                                  # SEND ID BY SPECIAL CODING
                DNPTR           LMREND01                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMREND07                # COLLECT SNAPSHOT
                4DNADR          DNTMBUFF                # SEND SNAPSHOT
                1DNADR          DELLT4                  # DELLT4,+1
                3DNADR          RTARG                   # RTARG +0...+5
                3DNADR          DELVSLV                 # DELVSLV+0...+5
                1DNADR          TCSI                    # TCSI,+1
                3DNADR          DELVEET1                # DELVEET+0...+5
                1DNADR          SERVDURN                # SERVDURN,DUMLOOPS
                1DNADR          TPASS4                  # TPASS4,+1
                DNPTR           LMREND06                # COMMON DATA
                DNPTR           LMREND02                # COMMON DATA
                1DNADR          TIME2                   # TIME2/1
                DNPTR           LMREND03                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMREND04                # COMMON DATA
                2DNADR          POSTORKU                # POSTORKU,NEGTORKU,POSTORKV,NEGTORKV
                1DNADR          SPARE
                1DNADR          TCDH                    # TCDH,+1
                3DNADR          DELVEET2                # DELVEET2+0...+5
                1DNADR          TTPI                    # TTPI,+1
                3DNADR          DELVEET3                # DELVEET3+0...+5
                1DNADR          ELEV                    # ELEV,+1
                2DNADR          CDUS                    # CDUS,PIPAX,PIPAY,PIPAZ
                1DNADR          LASTYCMD                # LASTYCMD,LASTXCMD
                1DNADR          LEMMASS                 # LEMMASS,CSMMASS
                1DNADR          IMODES30                # IMODES30,IMODES33
                1DNADR          TIG                     # TIG,+1
                DNPTR           LMREND05                # COMMON DATA
                1DNADR          TET                     # TET,+1
                1DNADR          CENTANG                 # CENTANG,+1
                1DNADR          NN                      # NN,+1
                1DNADR          DIFFALT                 # DIFFALT,+1
                1DNADR          DELVTPF                 # DELVTPF,+1
               -1DNADR          SPARE

#     -----------------  SUB-LISTS  ----------------------------

LMREND01        EQUALS          LMORBM01                # COMMON DOWNLIST DATA

LMREND02        EQUALS          LMORBM02                # COMMON DOWNLIST DATA

LMREND03        EQUALS          LMORBM03                # COMMON DOWNLIST DATA

LMREND04        EQUALS          LMORBM04                # COMMON DOWNLIST DATA
## Page 206

LMREND05        EQUALS          LMORBM05                # COMMON DOWNLIST DATA

LMREND06        EQUALS          LMCSTA06                # COMMON DOWNLIST DATA

LMREND07       -1DNADR          AIG                     # AIG,AMG       SNAPSHOT
                1DNADR          AOG                     # AOG,TRKMKCNT
                1DNADR          TANGNB                  # TANGNB,+1
                1DNADR          MKTIME                  # MKTIME,+1
               -1DNADR          RANGRDOT                # DNRRANGE,DNRRDOT

## Page 207
# LM DESCENT AND ASCENT DOWNLIST

#     -----------------  CONTROL LIST  --------------------------

DESC/ASC        EQUALS                                  # SEND ID BY SPECIAL CODING
                1DNADR          SPARE
                1DNADR          SPARE
                1DNADR          SPARE
                DNPTR           LMDSAS08                # COLLECT SNAPSHOT
                1DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMDSAS07                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                1DNADR          TEVENT                  # TEVENT,+1
                3DNADR          UNFC/2                  # UNFC/2+0...+5
                3DNADR          VGVECT                  # VGVECT+0...+5
                1DNADR          TTF/8                   # TTF/8,+1
                1DNADR          DELTAH                  # DELTAH,+1
                3DNADR          RLS                     # RLS+0...+5
                1DNADR          ZDOTD                   # ZDOTD,+1
                DNPTR           LMDSAS09                # COMMON DATA
                DNPTR           LMDSAS02                # COMMON DATA
                1DNADR          TIME2                   # TIME2/1
                DNPTR           LMDSAS03                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMDSAS04                # COMMON DATA
                2DNADR          POSTORKU                # POSTORKU,NEGTORKU,POSTORKV,NEGTORKV
                3DNADR          RGU                     # RGU+0...+5
                3DNADR          VGU                     # VGU+0...+5
                3DNADR          LAND                    # LAND+0...+5
                1DNADR          AT                      # AT,+1
                1DNADR          TLAND                   # TLAND,+1
                1DNADR          DVTOTAL                 # DVTOTAL,+1
                1DNADR          LASTYCMD                # LASTYCMD,LASTXCMD
                1DNADR          LEMMASS                 # LEMMASS,CSMMASS
                1DNADR          IMODES30                # IMODES30,IMODES33
                1DNADR          TIG                     # TIG,+1
                DNPTR           LMDSAS05                # COMMON DATA
                DNPTR           LMDSAS06                # COMMON DATA
                1DNADR          PSEUDO55                # PSEUDO55,GARBAGE
               -1DNADR          TTOGO                   # TTOGO,+1
#     -----------------  SUB-LISTS   ----------------------------

LMDSAS02        EQUALS          LMORBM02                # COMMON DOWNLIST DATA

LMDSAS03        EQUALS          LMORBM03                # COMMON DOWNLIST DATA

LMDSAS04        EQUALS          LMORBM04                # COMMON DOWNLIST DATA

LMDSAS05        EQUALS          LMORBM05                # COMMON DOWNLIST DATA
## Page 208

LMDSAS06        EQUALS          LMORBM06                # COMMON DOWNLIST DATA

LMDSAS07       -1DNADR          HMEASDL                 # HMEASDL,+1
                1DNADR          VMEAS                   # VMEAS,+1
                1DNADR          AIG                     # AIG,AMG
                1DNADR          AOG                     # AOG,VSELECT
                1DNADR          LATVMETR                # LATVMETR,FORVMETR
                1DNADR          SERVDURN                # SERVDURN,DUMLOOPS
               -1DNADR          MKTIME                  # MKTIME,+1

LMDSAS08       -1DNADR          GTCTIME                 # GTCTIME,+1
               -1DNADR          FC                      # FC, GARBAGE
LMDSAS09        EQUALS          LMCSTA06                # COMMON DOWNLIST DATA

## Page 209
# LM LUNAR SURFACE ALIGN DOWNLIST

#     -----------------  CONTROL LIST  --------------------------

SURFALIN        EQUALS                                  # SEND ID BY SPECIAL CODING
                DNPTR           LMLSAL01                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMLSAL07                # COLLECT SNAPSHOT
                4DNADR          DNTMBUFF                # SEND SHAPSHOT
                1DNADR          TALIGN                  # TALIGN,+1
                6DNADR          REFSMMAT                # REFSMMAT+0...+11D
                6DNADR          YNBSAV                  # YNBSAV+0...+5,ZNBSAV+0...+5
                1DNADR          X789                    # X789,+1
                1DNADR          TET                     # TET,+1
                1DNADR          LASTYCMD                # LASTYCMD,LASTXCMD
                DNPTR           LMLSAL02                # COMMON DATA
                1DNADR          TIME2                   # TIME/1
                DNPTR           LMLSAL03                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SHAPSHOT
                DNPTR           LMLSAL04                # COMMON DATA
                DNPTR           LMLSAL08                # COMMON DATA
                3DNADR          GSAV                    # GSAV +0...+5
                1DNADR          AGSK                    # AGSK,+1
                1DNADR          LASTYCMD                # LASTYCMD,LASTXCMD
                1DNADR          LEMMASS                 # LEMMASS,CSMMASS
                1DNADR          IMODES30                # IMODES30,IMODES33
                1DNADR          TIG                     # TIG,+1
                2DNADR          OMEGAP                  # OMEGAP,OMEGAQ,OMEGAR,GARBAGE
                2DNADR          CDUXD                   # CDUXD,CDUYD,CDUZD,GARBAGE
                2DNADR          CDUX                    # CDUX,CDUY,CDUZ,CDUT
                1DNADR          ALPHAQ                  # ALPHAQ,ALPHAR            COMMON DATA
                1DNADR          AOTCODE                 # AOTCODE,GARBAGE
                DNPTR           LMLSAL09                # COMMON DATA
                DNPTR           LMLSAL06                # COMMON DATA
                1DNADR          TSIGHT                  # TSIGHT,TSIGHT +1
               -1DNADR          CURSOR                  # AOT CURSOR,SPIRAL
#     -----------------  SUB-LISTS  ----------------------------

LMLSAL01        EQUALS          LMORBM01                # COMMON DOWNLIST DATA

LMLSAL02        EQUALS          LMORBM02                # COMMON DOWNLIST DATA

LMLSAL03        EQUALS          LMORBM03                # COMMON DOWNLIST DATA

LMLSAL04        EQUALS          LMORBM04                # COMMON DOWNLIST DATA

LMLSAL05        EQUALS          LMCSTA05                # COMMON DOWNLIST DATA

LMLSAL06        EQUALS          LMORBM06                # COMMON DOWNLIST DATA
## Page 210

LMLSAL07        EQUALS          LMREND07                # COMMON DOWNLIST DATA

LMLSAL08        EQUALS          LMCSTA07                # COMMON DOWNLIST DATA
LMLSAL09        EQUALS          LMORBM09                # COMMON DOWNLIST DATA

## Page 211
# LM AGS INITIALIZATION AND UPDATE DOWNLIST

#     -----------------  CONTROL LIST  --------------------------

AGSI/UPD        EQUALS                                  # SEND IO BY SPECIAL CODING
                3DNADR          AGSBUFF         +0      # AGSBUFF+0...+5
                1DNADR          AGSBUFF         +12D    # AGSBUFF+12D,GARBAGE
                3DNADR          AGSBUFF         +1      # AGSBUFF+1...+6
                1DNADR          AGSBUFF         +13D    # AGSBUFF+13D, GARBAGE
                3DNADR          AGSBUFF         +6      # AGSBUFF+6...+11
                1DNADR          AGSBUFF         +12D    # AGSBUFF+12,GARBAGE
                3DNADR          AGSBUFF         +7      # AGSBUFF+7...+12D
                1DNADR          AGSBUFF         +13D    # AGSBUFF+13D,GARBAGE
                6DNADR          COMPNUMB                # COMPNUMB,UPOLDMOD,UPVERB,UPCOUNT,
                                                        # UPBUFF+0...+7
                6DNADR          UPBUFF          +8D     # UPBUFF +8D...+19D
                DNPTR           LMAGSI02                # COMMON DATA
                1DNADR          TIME2                   # TIME2/1
                DNPTR           LMAGSI03                # COLLECT SNAPSHOT
                6DNADR          DNTMBUFF                # SEND SNAPSHOT
                DNPTR           LMAGSI04                # COMMON DATA
                2DNADR          POSTORKU                # POSTORKU,NEGTORKU,POSTORKV,NEGTORKV
                1DNADR          SERVDURN                # SERVDURN,DUMLOOPS
                1DNADR          SPARE
                1DNADR          AGSK                    # AGSK,+1
                6DNADR          UPBUFF                  # UPBUFF+0...+11D
                4DNADR          UPBUFF          +12D    # UPBUFF+12D...+19D
                1DNADR          LEMMASS                 # LEMMASS,CSMMASS
                1DNADR          IMODES30                # IMODES30,IMODES33
                1DNADR          SPARE
                DNPTR           LMAGSI05                # COMMON DATA
               -6DNADR          DSPTAB                  # DSPTAB+0...+11D

#     -----------------  SUB-LISTS  ----------------------------

LMAGSI02        EQUALS          LMORBM02                # COMMON DOWNLIST DATA

LMAGSI03        EQUALS          LMORBM03                # COMMON DOWNLIST DATA

LMAGSI04        EQUALS          LMORBM04                # COMMON DOWNLIST DATA

LMAGSI05        EQUALS          LMORBM05                # COMMON DOWNLIST DATA

# -------------------------------------------------------------------
DNTABLE         GENADR          COSTALIN                # LM COAST AND ALIGN DOWNLIST
                GENADR          AGSI/UPD                # LM AGS INITIALIZATION/UPDATE DOWNLIST
                GENADR          RENDEZVU                # LM RENDEZVOUS AND PRETHRUST DOWNLIST
                GENADR          ORBMANUV                # LM ORBITAL MANEUVERS DOWNLIST
                GENADR          DESC/ASC                # LM DESCENT AND ASCENT DOWNLIST
                GENADR          SURFALIN                # LM LUNAR SURFACE ALIGN DOWNLIST
# ----------------------------------------------------------     


