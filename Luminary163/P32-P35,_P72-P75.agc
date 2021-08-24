### FILE="Main.annotation"
## Copyright:   Public domain.
## Filename:    P32-P35,_P72-P75.agc
## Purpose:     A section of Luminary revision 163.
##              It is part of the reconstructed source code for the first
##              (unflown) release of the flight software for the Lunar
##              Module's (LM) Apollo Guidance Computer (AGC) for Apollo 14.
##              The code has been recreated from a reconstructed copy of
##              Luminary 173, as well as Luminary memos 157 amd 158.
##              It has been adapted such that the resulting bugger words
##              exactly match those specified for Luminary 163 in NASA
##              drawing 2021152N, which gives relatively high confidence
##              that the reconstruction is correct.
## Reference:   pp. 616-648
## Assembler:   yaYUL
## Contact:     Ron Burkey <info@sandroid.org>.
## Website:     www.ibiblio.org/apollo/index.html
## Mod history: 2019-08-21 MAS  Created from Luminary 173.
##              2021-05-30 ABS  TTPIO -> TTPI0
##                              K10RK2 -> K1ORK2

## Page 616
# COELLIPTIC SEQUENCE INITIATION (CSI) PROGRAMS (P32 AND P72)

# MOD NO -1       LOG SECTION - P32-P35, P72-P75
# MOD BY WHITE.P  DATE  1JUNE67

# PURPOSE

#       (1) TO CALCULATE PARAMETERS ASSOCIATED WITH THE FOLLOWING
#           CONCENTRIC FLIGHT PLAN MANEUVERS - THE CO-ELLIPTIC SEQUENCE
#           INITIATION (CSI) MANEUVER AND THE CONSTANT DELTA ALTITUDE
#           (CDH) MANEUVER.

#       (2) TO CALCULATE THESE PARAMETERS BASED UPON MANEUVER DATA
#           APPROVED AND KEYED INTO THE DSKY BY THE ASTRONAUT.

#       (3) TO DISPLAY TO THE ASTRONAUT AND THE GROUND DEPENDENT VARIABLES
#           ASSOCIATED WITH THE CONCENTRIC FLIGNT PLAN MANEUVERS FOR
#           APPROVAL BY THE ASTRONAUT/GROUND.

#       (4) TO STORE THE CSI TARGET PARAMETERS FOR USE BY THE DESIRED
#           THRUSTING PROGRAM.

# ASSUMPTIONS

#       (1) AT A SELECTED TPI TIME THE LINE OF SIGHT BETWEEN THE ACTIVE
#           AND PASSIVE VEHICLES IS SELECTED TO BE A PRESCRIBED ANGLE (E)
#           FROM THE HORIZONTAL PLANE DEFINED BY THE ACTIVE VEHICLE
#           POSITION.

#       (2) THE TIME BETWEEN CSI IGNITION AND CDH IGNITION MUST BE
#           COMPUTED TO BE GREATER THAN 10 MINUTES FOR SUCCESSFUL
#           COMPLETION OF THE PROGRAM.

#       (3) THE TIME BETWEEN CDH IGNITION AND TPI IGNITION MUST BE
#           COMPUTED TO BE GREATER THAN 10 MINUTES FOR SUCCESSFUL
#           COMPLETION OF THE PROGRAM.

#       (4) CDH DELTA V IS SELECTED TO MINIMIZE THE VARIATION OF THE
#           ALTITUDE DIFFERENCE BETWEEN THE ORBITS.

#       (5) CSI BURN IS DEFINED SUCH THAT THE IMPULSIVE DELTA V IS IN THE
#           HORIZONTAL PLANE DEFINED BY THE ACTIVE VEHICLE POSITION AT CSI
#           IGNITION.

#       (6) THE PERICENTER ALTITUDE OF THE ORBIT FOLLOWING CSI AND CDH
#           MUST BE GREATER THAN 35,000 FT (LUNAR ORBIT) OR 85 NM (EARTH
#           ORBIT) FOR SUCCESSFUL COMPLETION OF THIS PROGRAM.

#       (7) THE CSI AND CDH MANEUVERS ARE ORIGINALLY ASSUMED TO BE
#           PARALLEL TO THE PLANE OF THE CSM ORBIT.  HOWEVER CREW
## Page 617
#           MODIFICATION OF DELTA V (LV) COMPONENTS MAY RESULT IN AN
#           OUT-OF-PLANE CSI MANEUVER.

#       (8) STATE VECTOR UPDATES BY P27 ARE DISALLOWED DURING AUTOMATIC
#           STATE VECTOR UPDATING INITIATED BY P20 (SEE ASSUMPTION 10).

#       (9) COMPUTED VARIABLES MAY BE STORED FOR LATER VERIFICATION BY
#           THE GROUND.  THESE STORAGE CAPABILITIES ARE NORMALLY LIMITED
#           ONLY TO THE PARAMETERS FOR ONE THRUSTING MANEUVER AT A TIME
#           EXCEPT FOR CONCENTRIC FLIGHT PLAN MANEUVER SEQUENCES.

#      (10) THE RENDEZVOUS RADAR MAY OR MAY NOT BE USED TO UPDATE THE LM
#           OR CSM STATE VECTORS FOR THIS PROGRAM.  IF RADAR USE IS
#           DESIRED THE RADAR WAS TURNED ON AND LOCKED ON THE CSM BY
#           PREVIOUS SELECTION OF P20.  RADAR SIGHTING MARKS WILL BE MADE
#           AUTOMATICALLY APPROXIMATELY ONCE A MINUTE WHEN ENABLED BY THE
#           TRACK AND UPDATE FLAGS (SEE P20).  THE RENDEZVOUS TRACKING
#           MARK COUNTER IS ZEROED BY THE SELECTION OF P20 AND AFTER EACH
#           THRUSTING MANEUVER.

#      (11) THE ISS NEED NOT BE ON TO COMPLETE THIS PROGRAM.

#      (12) THE OPERATION OF THE PROGRAM UTILIZES THE FOLLOWING FLAGS -

#               ACTIVE VEHICLE FLAG - DESIGNATES THE VEHICLE WHICH IS
#               DOING RENDEZVOUS THRUSTING MANEUVERS TO THE PROGRAM WHICH
#               CALCULATES THE MANEUVER PARAMETERS.  SET AT THE START OF
#               EACH RENDEZVOUS PRE-THRUSTING PROGRAM.

#               FINAL FLAG - SELECTS FINAL PROGRAM DISPLAYS AFTER CREW HAS
#               COMPLETED THE FINAL MANEUVER COMPUTATION AND DISPLAY
#               CYCLE.

#               EXTERNAL DELTA V STEERING FLAG - DESIGNATES THE TYPE OF
#               STEERING REQUIRED FOR EXECUTION OF THIS MANEUVER BY THE
#               THRUSTING PROGRAM SELECTED AFTER COMPLETION OF THIS
#               PROGRAM.

#      (13) IT IS NORMALLY REQUIRED THAT THE ISS BE ON FOR 1 HOUR PRIOR TO
#           A THRUSTING MANEUVER.

#      (14) THIS PROGRAM IS SELECTED BY THE ASTRONAUT BY DSKY ENTRY -

#               P32 IF THIS VEHICLE IS ACTIVE VEHICLE.

#               P72 IF THIS VEHICLE IS PASSIVE VEHICLE.

# INPUT

#       (1) TCSI     TIME OF THE CSI MANEUVER

## Page 618
#       (2) NN       NUMBER OF APSIDAL CROSSINGS THRU WHICH THE ACTIVE
#                    VEHICLE ORBIT CAN BE ADVANCED TO OBTAIN THE CDH
#                    MANEUVER POINT
#       (3) ELEV     DESIRED LOS ANGLE AT TPI
#       (4) TTPI     TIME OF THE TPI MANEUVER
# OUTPUT

#       (1) TRKMKCNT NUMBER OF MARKS
#       (2) TTOGO    TIME TO GO
#       (3) +MGA     MIDDLE GIMBAL ANGLE
#       (4) DIFFALT  DELTA ALTITUDE AT CDH
#       (5) T1TOT2   DELTA TIME FROM CSI TO CDH
#       (6) T2TOT3   DELTA TIME FROM CDH TO TPI
#       (7) DELVLVC  DELTA VELOCITY AT CSI - LOCAL VERTICAL COORDINATES
#       (8) DELVLVC  DELTA VELOCITY AT CDH - LOCAL VERTICAL COORDINATES

# DOWNLINK

#       (1) TCSI     TIME OF THE CSI MANEUVER
#       (2) TCDH     TIME OF THE CDH MANEUVER
#       (3) TTPI     TIME OF THE TPI MANEUVER
#       (4) TIG      TIME OF THE CSI MANEUVER
#       (5) DELVEET1 DELTA VELOCITY AT CSI - REFERENCE COORDINATES
#       (6) DELVEET2 DELTA VELOCITY AT CDH - REFERENCE COORDINATES
#       (7) DIFFALT  DELTA ALTITUDE AT CDH
#       (8) NN       NUMBER OF APSIDAL CROSSINGS THRU WHICH THE ACTIVE
#                    VEHICLE ORBIT CAN BE ADVANCED TO OBTAIN THE CDH
#                    MANEUVER POINT
#       (9) ELEV     DESIRED LOS ANGLE AT TPI

# COMMUNICATION TO THRUSTING PROGRAMS

#       (1) TIG      TIME OF THE CSI MANEUVER
#       (2) RTIG     POSITION OF ACTIVE VEHICLE AT CSI - BEFORE ROTATION
#                    INTO PLANE OF PASSIVE VEHICLE
#       (3) VTIG     VELOCITY OF ACTIVE VEHICLE AT CSE - BEFORE ROTATION
#                    INTO PLANE OF PASSIVE VEHICLE
#       (4) DELVSIN  DELTA VELOCITY AT CSI - REFERENCE COORDINATES
#       (5) DELVSAB  MAGNITUDE OF DELTA VELOCITY AT CSI
#       (6) XDELVFLG SET TO INDICATE EXTERNAL DELTA V VG COMPUTATION

# SUBROUTINES USED

#       AVFLAGA
#       AVFLAGP
#       P20FLGON
#       VARALARM
#       BANKCALL
#       GOFLASH
#       GOTOPOOH
## Page 619
#       VNPOOH
#       GOFLASHR
#       BLANKET
#       ENDOFJOB
#       SELECTMU
#       ADVANCE
#       INTINT
#       PASSIVE
#       CSI/A
#       S32/33.1
#       DISDVLVC
#       VN1645

                BANK            35
                SETLOC          CSI/CDH
                BANK
                EBANK=          SUBEXIT
                COUNT*          $$/P3272
P32             TC              AVFLAGA
                TC              P32STRT
P72             TC              AVFLAGP
P32STRT         EXTEND
                DCA             P30ZERO
                DXCH            CENTANG
                TC              P32/P72A
ALMXITA         SXA,2
                                CSIALRM
ALMXIT          LXC,1
                                CSIALRM
                SLOAD*          EXIT
                                ALARM/TB -1,1
                CA              MPAC
                TC              VARALARM
                CAF             V05N09
                TC              BANKCALL
                CADR            GOFLASH
                TC              GOTOPOOH
                TC              -4
P32/P72A        TC              P20FLGON
                CAF             P30ZERO
                TS              NN              +1
                TS              TCSI
                TS              TCSI            +1
VN0611          CAF             V06N11                  # TCSI
                TC              VNPOOH
                TC              INTPRET
                DLOAD           DCOMP
                                TCSI
                BMN             DLOAD
                                VN0655
## Page 620
                                TETLEM
                STCALL          TDEC1
                                PRECSET
                VLOAD           VSR*
                                RACT3
                                0,2
                STOVL           RVEC
                                VACT3
                VSR*            SET
                                0,2
                                RVSW
                STODL           VVEC
                                DPPOSMAX
                STCALL          RDESIRED
                                TIMERAD
                DAD
                                TDEC2
                STORE           TCSI
                EXIT
                TC              VN0611
VN0655          EXIT
                CAF             V06N55                  # NN, ELEV(RGLOS)
                TC              BANKCALL
                CADR            GOFLASH
                TC              GOTOPOOH
                TC              +2
                TC              -5
                CAF             V06N37                  # TTPI
                TC              VNPOOH
                TC              INTPRET
                DLOAD
                                TCSI
                STCALL          TIG
                                SELECTMU
P32/P72B        CALL
                                ADVANCE
                SETPD           VLOAD
                                0D
                                VPASS1
                PDVL            PDDL
                                RPASS1
                                TCSI
                PDDL            PDDL
                                TTPI
                                TWOPI
                PUSH            CALL
                                INTINT
                CALL
                                PASSIVE
                CALL

## Page 621
                                CSI/A
P32/P72C        BON             SET
                                FINALFLG
                                P32/P72D
                                UPDATFLG
P32/P72D        DLOAD
                                T1TOT2
P32/P72E        STORE           T1TOT2
                DSU             BPL
                                60MIN
                                P32/P72E
                DLOAD
                                T2TOT3
P32/P72F        STORE           T2TOT3
                DSU             BPL
                                60MIN
                                P32/P72F
                EXIT
                CAF             V06N75
                TC              VNPOOH
                TC              INTPRET
                VLOAD           CALL
                                DELVEET1
                                S32/33.1
                STOVL           DELVEET1
                                RACT2
                STOVL           RACT1
                                DELVEET2
                AXT,1           CALL
                VN              0682
                                DISDVLVC
                DLOAD
                                TTPI
                STCALL          TTPI0
                                VN1645
                GOTO
                                P32/P72B

## Page 622
# CONSTANT DELTA HEIGHT (CDH) PROGRAMS (P33 AND P73)

# MOD NO -1       LOG SECTION - P32-P35, P72-P75
# MOD BY WHITE.P  DATE  1JUNE67
# PURPOSE

#       (1) TO CALCULATE PARAMETERS ASSOCIATED WITH THE CONSTANT DELTA
#           ALTITUDE MANEUVER (CDH).

#       (2) TO CALCULATE THESE PARAMETERS BASED UPON MANEUVER DATA
#           APPROVED AND KEYED INTO THE DSKY BY THE ASTRONAUT.

#       (3) TO DISPLAY TO THE ASTRONAUT AND THE GROUND DEPENDENT VARIABLES
#           ASSOCIATED WITH THE CDH MANEUVER FOR APPROVAL BY THE
#           ASTRONAUT/GROUND.

#       (4) TO STORE THE CDH TARGET PARAMETERS FOR USE BY THE DESIRED
#           THRUSTING PROGRAM.

# ASSUMPTIONS

#       (1) THIS PROGRAM IS BASED UPON PREVIOUS COMPLETION OF THE
#           CO-ELLIPTIC SEQUENCE INITIATION (CSI) PROGRAM (P32/P72).
#           THERFORE -

#           (A) AT A SELECTED TPI TIME (NOW IN STORAGE) THE LINE OF SIGHT
#               BETWEEN THE ACTIVE AND PASSIVE VEHICLES WAS SELECTED TO BE
#               A PRESCRIBED ANGLE (E) (NOW IN STORAGE) FROM THE
#               HORIZONTAL PLANE DEFINED BY THE ACTIVE VEHICLE POSITION.

#           (B) THE TIME BETWEEN CSI IGNITION AND CDH IGNITION WAS
#               COMPUTED TO BE GREATER THAN 10 MINUTES.

#           (C) THE TIME BETWEEN CDH IGNITION AND TPI IGNITION WAS
#               COMPUTED TO BE GREATER THAN 10 MINUTES.
#
#           (D) THE VARIATION OF THE ALTITUDE DIFFERENCE BETWEEN THE
#               ORBITS WAS MINMIZED.
#
#           (E) CSI BURN WAS DEFINED SUCH THAT THE IMPULSIVE DELTA V WAS
#               IN THE HORIZONTAL PLANE DEFINED BY ACTIVE VEHICLE

#               POSITION AT CSI IGNITION.

#           (F) THE PERICENTER ALTITUDES OF THE ORBITS FOLLOWING CSI AND
#               CDH WERE COMPUTED TO BE GREATER THAN 35,000 FT FOR LUNAR
#               ORBIT OR 85 NM FOR EARTH ORBIT.

#           (G) THE CSI AND CDH MANEUVERS WERE ASSUMED TO BE PARALLEL TO
#               THE PLANE OF THE PASSIVE VEHICLE ORBIT.  HOWEVER, CREW

## Page 623
#               MODIFICATION OF DELTA V (LV) COMPONENTS MAY HAVE RESULTED
#               IN AN OUT-OF-PLANE MANEUVER.

#       (2) STATE VECTOR UPDATES BY P27 ARE DISALLOWED DURING AUTOMATIC
#           STATE VECTOR UPDATING INITIATED BY P20 (SEE ASSUMPTION 4).

#       (3) COMPUTED VARIABLES MAY BE STORED FOR LATER VERIFICATION BY
#           THE GROUND.  THESE STORAGE CAPABILITES ARE NORMALLY LIMITED
#           ONLY TO THE PARAMETERS FOR ONE THRUSTING MANEUVER AT A TIME
#           EXCEPT FOR CONCENTRIC FLIGHT PLAN MANEUVER SEQUENCES.

#       (4) THE RENDEZVOUS RADAR MAY OR MAY NOT BE USED TO UPDATE THE LM
#           OR CSM STATE VECTORS FOR THIS PROGRAM.  IF RADAR USE IS
#           DESIRED THE RADAR WAS TURNED ON AND LOCKED ON THE CSM BY
#           PREVIOUS SELECTION OF P20.  RADAR SIGHTING MARKS WILL BE MADE
#           AUTOMATICALLY APPROXIMATELY ONCE A MINUTE WHEN ENABLED BY THE
#           TRACK AND UPDATE FLAGS (SEE P20).  THE RENDEZVOUS TRACKING
#           MARK COUNTER IS ZEROED BY THE SELECTION OF P20 AND AFTER EACH
#           THRUSTING MANEUVER.

#       (5) THE ISS NEED NOT BE ON TO COMPLETE THIS PROGRAM.

#       (6) THE OPERATION OF THE PROGRAM UTILIZES THE FOLLOWING FLAGS -

#               ACTIVE VEGICLE FLAG - DESIGNATES THE VEHICLE WHICH IS
#               DOING RENDEZVOUS THRUSTING MANEUVERS TO THE PROGRAM WHICH
#               CALCULATES THE MANEUVER PARAMETERS.  SET AT THE START OF
#               EACH RENDEZVOUS PRE-THRUSTING PROGRAM.

#               FINAL FLAG - SELECTS FINAL PROGRAM DISPLAYS AFTER CREW HAS
#               COMPLETED THE FINAL MANEUVER COMPUTATION AND DISPLAY
#               CYCLE.

#               EXTERNAL DELTA V STEERING FLAG - DESIGNATES THE TYPE OF
#               STEERING REQUIRED FOR EXECUTION OF THIS MANEUVER BY THE
#               THRUSTING PROGRAM SELECTED AFTER COMPLETION OF THIS
#               PROGRAM.

#       (7) IT IS NORMALLY REQUIRED THAT THE ISS BE ON FOR 1 HOUR PRIOR TO
#           A THRUSTING MANEUVER.

#       (8) THIS PROGRAM IS SELECTED BY THE ASTRONAUT BY DSKY ENTRY -

#               P33 IF THIS VEHICLE IS ACTIVE VEHICLE.

#               P73 IF THIS VEHICLE IS PASSIVE VEHICLE.

# INPUT

#       (1) TTPI0    TIME OF THE TPI MANEUVER - SAVED FROM P32/P72

## Page 624
#       (2) ELEV     DESIRED LOS ANGLE AT TPI - SAVED FROM P32/P72
#       (3) TCDH     TIME OF THE CDH MANEUVER

# OUTPUT

#       (1) TRKMKCNT NUMBER OF MARKS
#       (2) TTOGO    TIME TO GO
#       (3) +MGA     MIDDLE GIMBAL ANGLE
#       (4) DIFFALT  DELTA ALTITUDE AT CDH
#       (5) T2TOT3   DELTA TIME FROM CDH TO COMPUTED TPI
#       (6) NOMTPI   DELTA TIME FROM NOMINAL TPI TO COMPUTED TPI
#       (7) DELVLVC  DELTA VELOCITY AT CDH - LOCAL VERTICAL COORDINATES

# DOWNLINK

#       (1) TCDH     TIME OF THE CDH MANEUVER
#       (2) TTPI     TIME OF THE TPI MANEUVER
#       (3) TIG      TIME OF THE CDH MANEUVER
#       (4) DELVEET2 DELTA VELOCITY AT CDH - REFERENCE COORDINATES
#       (5) DIFFALT  DELTA ALTITUDE AT CDH
#       (6) ELEV     DESIRED LOS ANGLE AT TPI
# COMMUNICATION TO THRUSTING PROGRAMS

#       (1) TIG      TIME OF THE CDH MANEUVER
#       (2) RTIG     POSITION OF ACTIVE VEHICLE AT CDH - BEFORE ROTATION
#                    INTO PLANE OF PASSIVE VEHICLE
#       (3) VTIG     VELOCITY OF ACTIVE VEHICLE AT CDH - BEFORE ROTATION
#                    INTO PLANE OF PASSIVE VEHICLE
#       (4) DELVSIN  DELTA VELOCITY AT CDH - REFERENCE COORDINATES
#       (5) DELVSAB  MAGNITUDE OF DELTA VELOCITY AT CDH
#       (6) XDELVFLG SET TO INDICATE EXTERNAL DELTA V VG COMPUTATION

# SUBROUTINES USED

#       AVFLAGA
#       AVFLAGP
#       P20FLGON
#       VNPOOH
#       SELECTMU
#       ADVANCE
#       CDHMVR
#       INTINT3P
#       ACTIVE
#       PASSIVE
#       S33/34.1
#       ALARM
#       BANKCALL
#       GOFLASH
#       GOTOPOOH
#       S32/33.1
## Page 625
#       VN1645

                COUNT*          $$/P3373
P33             TC              AVFLAGA
                TC              P33/P73A
P73             TC              AVFLAGP
P33/P73A        TC              P20FLGON
                CAF             V06N13                  # TCDH
                TC              VNPOOH
                TC              INTPRET
                DLOAD
                                TTPI0
                STODL           TTPI
                                TCDH
                STCALL          TIG
                                SELECTMU
P33/P73B        CALL
                                ADVANCE
                CALL
                                CDHMVR
                SETPD           VLOAD
                                0D
                                VACT3
                PDVL            CALL
                                RACT2
                                INTINT3P
                CALL
                                ACTIVE
                SETPD           VLOAD
                                0D
                                VPASS2
                PDVL            CALL
                                RPASS2
                                INTINT3P
                CALL
                                PASSIVE
                DLOAD           SET
                                P30ZERO
                                ITSWICH
                STCALL          NOMTPI
                                S33/34.1
                BZE             EXIT
                                P33/P73C
                TC              ALARM
                OCT             611
                CAF             V05N09
                TC              BANKCALL
                CADR            GOFLASH
                TC              GOTOPOOH
                TC              +2

## Page 626
                TC              P33/P73A
                TC              INTPRET
                DLOAD
                                P30ZERO
                STORE           NOMTPI
P33/P73C        BON             SET
                                FINALFLG
                                P33/P73D
                                UPDATFLG
P33/P73D        DLOAD           DAD
                                NOMTPI
                                TTPI
                STORE           TTPI
                DSU
                                TCDH
P33/P73E        DSU             BPL
                                60MIN
                                P33/P73E
                DAD
                                60MIN
                STODL           T1TOT2
                                TTPI
                DSU             PUSH
                                TTPI0
P33/P73F        ABS             DSU
                                60MIN
                BPL             DAD
                                P33/P73F
                                60MIN
                SIGN            STADR
                STORE           T2TOT3
                EXIT
                CAF             V06N75
                TC              VNPOOH
                TC              INTPRET
                VLOAD           CALL
                                DELVEET2
                                S32/33.1
                STCALL          DELVEET2
                                VN1645
                GOTO
                                P33/P73B

## Page 627
# ..... AVFLAGA/P .....

# SUBROUTINES USED

#          UPFLAG
#          DOWNFLAG

AVFLAGA         EXTEND                                  # AVFLAG = LEM
                QXCH            SUBEXIT
                TC              UPFLAG
                ADRES           AVFLAG
                TC              SUBEXIT
AVFLAGP         EXTEND                                  # AVFLAG = CSM
                QXCH            SUBEXIT
                TC              DOWNFLAG
                ADRES           AVFLAG
                TC              SUBEXIT
P20FLGON        EXTEND
                QXCH            SUBEXIT
                TC              UPFLAG
                ADRES           UPDATFLG                # SET UPDATFLG
                TC              UPFLAG
                ADRES           TRACKFLG                # SET TRACKFLG
                TC              SUBEXIT

## Page 628
# ..... DISDVLVC  .....

# SUBROUTINES USED

#       S32/33.X
#        VNPOOH

DISDVLVC        STORE           DELVLVC
                STQ             CALL
                                NORMEX
                                S32/33.X
                VLOAD           MXV
                                DELVLVC
                                0D
                VSL1            SXA,1
                                VERBNOUN
                STORE           DELVLVC
                EXIT
                CA              VERBNOUN
                TC              VNPOOH
                TC              INTPRET
                GOTO
                                NORMEX

## Page 629
# ..... CONSTANTS .....

V06N11          VN              0611
V06N13          VN              0613
V06N75          VN              0675
SN359+          2DEC            -.000086601
CS359+          2DEC            +.499999992
P30ZERO         2DEC            0
60MIN           2DEC            360000

ALARM/TB        OCT             00600                   # NO 1
                OCT             00601                   #    2
                OCT             00602                   #    3
                OCT             00603                   #    4
                OCT             00604                   #    5
                OCT             00605                   #    6
                OCT             00606                   #    7

## Page 630
# ..... CSI/A     .....

# SUBROUTINES USED

#       VECSHIFT
#       TIMETHET
#       PERIAPO
#       SHIFTR1
#       INTINT2C
#       CDHMVR
#       PERIAPO1
#       INTINT
#       ACTIVE

                BANK            34
                SETLOC          CSI/CDH1
                BANK
                EBANK=          SUBEXIT
                COUNT*          $$/CSI
LOOPMX          2DEC            16
INITST          2DEC            .03048          B-7     #      INITIAL DELDV = 10 FPS
DVMAX1          2DEC            3.0480          B-7     #      MAXIMUM DV1 = 1000 FPS
DVMAX2          2DEC            3.014472        B-7     #                     989 FPS
1DPB2           2DEC            1.0             B-2
1DPB28          2DEC            1
PMINE           2DEC            157420          B-29    # 85 NM    - MUST BE 8 WORDS BEFORE PMINM
EPSILN1         2DEC            .0003048        B-7     #      .1 FPS
NICKELDP        2DEC            .021336         B-7     # 7 FPS (CHANGED FROM .05 FPS)
FIFPSDP         2DEC            -.152400        B-7     #      50  FPS
PMINM           2DEC            10668           B-29    # 35000 FT - MUST BE 8 WORDS AFTER PMINE
DELMAX1         2DEC            .6096000        B-7     #      200 FPS
ONETHTH         2DEC            .0001           B-3
TMIN            2DEC            60000                   # 10 MIN

CSI/A           CLEAR           SET                     # INITIALIZE INDICATORS
                                S32.1F1                 # DVT1 HAS EXCEEDED MAX INDICATOR
                                S32.1F2                 # FIRST PASS FOR NEWTON ITERATION INDICATR

## Page 631
                CLEAR           SET
                                S32.1F3A                # 00=1ST 2 PASSES 2ND CYCLE 01=FIRST CYCLE
                                S32.1F3B                # 10=2ND CYCLE 11=50FPS STAGE 2ND CYCLE
                DLOAD
                                P30ZERO
                STORE           LOOPCT
                STORE           CSIALRM
CSI/B           SETPD           VLOAD
                                0D
                                RACT1
                ABVAL           PUSH                    # RA1                           B29 PL02D
                NORM            SR1
                                X2                      #                        B29-N2+ B1 PL04D
                PDVL            ABVAL
                                RPASS3
                NORM            BDDV                    # RA1/RP3                        B1 PL02D
                                X1
                XSU,2           SR*                     #                                B2
                                X1
                                1,2
                DAD             DMP                     # (1+(RA1/RP3))RA1       B29+B2=B31 PL00D
                                1DPB2
                NORM            PDDL                    #                                   PL02D
                                X1
                                RTMU
                SR1             DDV                     #                       B38-B31= B7 PL00D
                SL*             SQRT                    #                                B7
                                0 -7,1
                PDVL            UNIT                    #                                   PL02D
                                RACT1
                PDVL            VXV
                                UP1
                UNIT                                    # UNIT(URP1 X UVP1 X URA1) = UH1
                DOT             SL1                     # VA1 . UH1                      B7
                                VACT1
                BDSU            STADR                   #                                   PL00D
                STODL           DELVCSI
                                INITST                  # 10 FPS
                STORE           DELDV
CSI/B1          DLOAD           DAD                     # IF LOOPCT = 16
                                LOOPCT
                                1DPB28
                STORE           LOOPCT
                DSU             AXT,2
                                LOOPMX
                                6
                BPL
                                SCNDSOL
CSI/B2          SETPD
                                0D

## Page 632
                DLOAD           ABS
                                DELVCSI
                DSU             BMN
                                DVMAX1
                                CSI/B23
                AXT,2           BON
                                7
                                S32.1F1
                                SCNDSOL
                BOFF            BON
                                S32.1F3A
                                CSI/B22                 # FLAG 3 NEQ 3
                                S32.1F3B
                                SCNDSOL
CSI/B22         SET             DLOAD
                                S32.1F1
                                DVMAX2
                SIGN
                                DELVCSI
                STORE           DELVCSI
CSI/B23         VLOAD           PUSH
                                RACT1
                UNIT            PDVL
                                UP1
                VXV             UNIT                    # UNIT (URP1 X UVP1 X URA1) = UH1
                VXSC            VSL1
                                DELVCSI
                STORE           DELVEET1
                VAD             BOV
                                VACT1
                                CSI/B23D
CSI/B23D        STCALL          VACT4
                                VECSHIFT
                STOVL           VVEC
                SET
                                RVSW
                STOVL           RVEC
                                SN359+
                STCALL          SNTH                    # ALSO CSTH
                                TIMETHET
                SR1             LXA,1
                                RTX1
                STCALL          HAFPA1
                                PERIAPO
                CALL
                                SHIFTR1
                STODL           POSTCSI
                                CENTANG
                BZE             GOTO
                                +2

## Page 633
                                CIRCL
                DLOAD
                                ECC
                DSU             BMN
                                ONETHTH
                                CIRCL
                DLOAD           CALL
                                R1
                                SHIFTR1
                SETPD           NORM
                                2D
                                X1
                PDVL            DOT                     #                                       PL04D
                                RACT1
                                VACT4
                ABS             DDV
                                02D                     # (/RDOTV/)/R1              B36-B29= B7
                SL*             DSU
                                0,1
                                NICKELDP
                BMN             DLOAD
                                CIRCL
                                P
                SL2             DSU
                                1DPB2
                STODL           14D
                                RTSR1/MU
                SR1             DDV                     # (1/ROOTMU)/R1         B-16-B29 = B-45 PL02D
                PDDL            DMP
                                P
                                R1
                CALL
                                SHIFTR1
                SL4             SL1
                SQRT            DMP                     # ((P/MU)**.5)/R1       B14+B-45 = B-31 PL02D
                BOFF            SL3
                                CMOONFLG
                                CSI/B3
CSI/B3          PDVL            DOT
                                RACT1
                                VACT4
                STORE           RDOTV
                ABS
                NORM            DMP                     # ((P/MU)**.5)RDOTV/R1                  PL02D
                                X2
                XSU,1           SL*                     #                  B-31+B36-B3 = B2
                                X2
                                3,1
                STODL           12D
                                P30ZERO

## Page 634
                STORE           16D
                VLOAD           UNIT
                                12D
                STOVL           SNTH                    # ALSO STORES CSTH AND 0
                                RACT1
                PDVL            SIGN
                                VACT4
                                RDOTV
                VCOMP           CALL
                                VECSHIFT
                STOVL           VVEC
                SET
                                RVSW
                STCALL          RVEC
                                TIMETHET
                PDDL            BPL
                                RDOTV
                                NTP/2
                DLOAD           DSU
                                HAFPA1
                PUSH            GOTO
                                NTP/2
CIRCL           SETPD           DLOAD
                                00D
                                P30ZERO
                PUSH
NTP/2           DLOAD           DMP
                                NN
                                HAFPA1
                SL              DSU
                                14D
                DAD
                                TCSI
                STORE           TCDH
                BDSU            AXT,2
                                TTPI
                                5D
                BMN             SETPD
                                SCNDSOL
                                0D
                VLOAD           PDVL
                                VACT4
                                RACT1
                CALL
                                INTINT2C
                STOVL           RACT2
                                VATT
                STOVL           VACT2
                                VPASS1
                SETPD           PDVL

## Page 635
                                0D
                                RPASS1
                CALL
                                INTINT2C
                STOVL           RPASS2
                                VATT
                STCALL          VPASS2
                                CDHMVR
                VLOAD           SETPD
                                RACT2
                                0D
                PDVL            CALL
                                VACT3
                                PERIAPO1
                CALL
                                SHIFTR1
                STOVL           POSTCDH
                                VACT3
                SETPD           PDVL
                                0D
                                RACT2
                PDDL            PDDL
                                TCDH
                                TTPI
                PDDL            PUSH
                                TWOPI
                CALL
                                INTINT
                CALL
                                ACTIVE
                DLOAD
                                ELEV
                SETPD           SINE
                                6D
                PDVL            UNIT
                                RACT3
                STORE           00D                     # URA3 AT 00D
                PDVL            VXV                     # PL14D,PL08D
                                UP1
                UNIT
                PDDL            COSINE                  # UNIT(URA3XUVA3XURA3) = UH3       B1 PL14D
                                ELEV
                VXSC            STADR                   # (COSLOS)(UH3)                    B2 PL08D
                STORE           18D                     #     PLUS
                DLOAD           VXSC                    # (SINLOS)(URA3) = U               B2 PL00D
                VAD             VSL1
                                18D                     #                                  B1
                PUSH            DOT                     #                                     PL06D
                                RACT3                   # (U . RA3) = TEMP1     B1 +B29 = B30
                SL1             PUSH                    #                                 B29 PL08D

## Page 636
                DSQ             TLOAD                   # TEMP1**2                        B58
                                MPAC
                PDVL            DOT                     #                                     PL11D
                                RACT3
                                RACT3
                TLOAD           DCOMP                   # RA3.RA3
                                MPAC
                PDVL            DOT                     # RP3.RP3                         B58 PL14D
                                RPASS3
                                RPASS3                  #                                       PL11D
                TAD             TAD                     # TEMP1**2+RA3.RA3+RP3.RP3=TEMP2        PL08D
                BPL             DLOAD
                                K1ORK2
                                LOOPCT
                DSU             AXT,2
                                1DPB28
                                1D
                BZE
                                ALMXITA
                DLOAD           SR1
                                DELDV
                STORE           DELDV
                BDSU
                                DVPREV
                STCALL          DELVCSI
                                CSI/B1
K1ORK2          SQRT            PUSH                    # TEMP3 = TEMP2**.5                B29 PL10D
                DCOMP           DSU
                                06D                     # -TEMP1-TEMP3 =K2 AT 10D
                STODL           10D                     #                                      PL08D
                DSU             STADR                   #                                      PL06D
                STORE           12D                     # -TEMP1+TEMP3 =K1 AT 12D
                ABS
                STODL           14D
                                10D
                ABS             DSU
                                14D
                BMN             DLOAD
                                K2.
                                12D
                STORE           10D                     # K=K1
K2.             DLOAD
                                10D
                VXSC            VSL1
                VAD             UNIT                    # V=RA3+KU UNIT                    B1
                                RACT3
                PDVL            UNIT
                                RPASS3                  #                                      PL06D
                PDVL            UNIT
                                VPASS3                  #                                      PL12D

## Page 637
                VXV             PDVL                    # UVP3 X URP3                          PL18D
                                06D
                                06D
                VXV             DOT
                                00D
                STADR                                   #                                     PL12D
                STOVL           12D                     # (URP3XV).(UVP3XURP3)=TEMP           PL06D
                DOT             SL1                     #                                     PL00D
                ARCCOS          SIGN
                                12D                     #                                 B0
                SR1             PUSH                    # GAMMA=SIGN(TEMP)ARCOS(UNITV.URP3)   PL02D
                BON             DLOAD
                                S32.1F2
                                FRSTPAS
                                00D                     # NOT THE FIRST PASS OF A CYCLE
                DSU             PDDL                    # GAMMA-GAMPREV                    B1 PL04D
                                GAMPREV
                                DELVCSI
                DSU             NORM                    #                                  B7
                                DVPREV
                                X1
                BDDV            PDDL                    # (GAM-GAMPREV)/(DV-DVPREV)    B-6+N1 PL06D
                                02D                     #         = SLOPE
                                DELVCSI
                STORE           DVPREV
                BOFF            BOFF
                                S32.1F3A
                                THRDCHK
                                S32.1F3B
                                THRDCHK
                DLOAD           DMP
                                02D
                                GAMPREV
                BPL             DLOAD
                                FIFTYFPS
                                INITST
                SIGN
                                DELDV
                STORE           DELDV
                SET             CLEAR
                                S32.1F3A
                                S32.1F3B
FRSTPAS         DLOAD
                                00D
                STODL           GAMPREV
                                DELVCSI
                STORE           DVPREV
                DSU             CLEAR
                                DELDV
                                S32.1F2

## Page 638
                STCALL          DELVCSI
                                CSI/B1
THRDCHK         BON             BON
                                S32.1F3A
                                NEWTN
                                S32.1F3B
                                NEWTN
FIFTYFPS        DLOAD           SIGN
                                FIFPSDP
                                04D
                SIGN
                                GAMPREV
                STORE           DELDV
                DCOMP           DAD
                                DELVCSI
                STODL           DELVCSI
                                00D
                SET             SET
                                S32.1F3B
                                S32.1F3A
                STCALL          GAMPREV
                                CSI/B2
NEWTN           DLOAD           NORM
                                04D
                                X2
                BDDV            XSU,1
                                00D
                                X2
                SR*
                                0,1
                STODL           DELDV
                                00D
                STORE           GAMPREV
                DLOAD           ABS
                                DELDV
                PUSH            DSU		#					PL08D
                                EPSILN1
                BMN             DLOAD
                                CSI/SOL
                DSU             BMN
                                DELMAX1
                                CSISTEP
                DLOAD           SIGN
                                DELMAX1
                                DELDV
                STORE           DELDV
CSISTEP         DLOAD           DSU
                                DELVCSI
                                DELDV
                STCALL          DELVCSI

## Page 639
                                CSI/B1
CSI/SOL         DLOAD           AXT,2
                                POSTCSI
                                2
                LXA,1
                                RTX1
                DSU*            BMN
                                PMINE -2,1
                                SCNDSOL
                AXT,2           DLOAD
                                3
                                POSTCDH
                DSU*            BMN
                                PMINE -2,1
                                SCNDSOL
                DLOAD           DSU
                                TCDH
                                TCSI
                STORE           T1TOT2
                AXT,2           DSU
                                4
                                TMIN
                BMN             AXT,2
                                SCNDSOL
                                5
                DLOAD           DSU
                                TTPI
                                TCDH
                STORE           T2TOT3
                DSU             BPL
                                TMIN
                                P32/P72C
SCNDSOL         BON             BOFF
                                S32.1F3A
                                ALMXIT
                                S32.1F3B
                                ALMXIT
                SXA,2           DLOAD
                                CSIALRM
                                P30ZERO
                CLEAR           SET
                                S32.1F1
                                S32.1F2
                CLEAR           CLEAR
                                S32.1F3A
                                S32.1F3B
                STCALL          LOOPCT
                                CSI/B

## Page 640
# ..... ADVANCE    .....

# SUBROUTINES USED

#       PRECSET
#       ROTATE

ADVANCE         STQ             DLOAD
                                SUBEXIT
                                TIG
                STCALL          TDEC1
                                PRECSET
                SET             VLOAD
                                XDELVFLG
                                VPASS3
                STORE           VPASS2
                STOVL           VPASS1
                                RPASS3
                STORE           RPASS2
                STORE           RPASS1
                UNIT            VXV
                                VPASS1
                UNIT
                STOVL           UP1
                                RACT3
                STCALL          RTIG
                                ROTATE
                STORE           RACT2
                STOVL           RACT1
                                VACT3
                STCALL          VTIG
                                ROTATE
                STORE           VACT2
                STCALL          VACT1
                                SUBEXIT

## Page 641
# ..... ROTATE     .....

ROTATE          PUSH            PUSH
                DOT             VXSC
                                UP1
                                UP1
                VSL2            BVSU
                UNIT            PDVL
                ABVAL           VXSC
                VSL1            RVQ

## Page 642
# ..... INTINTNA   .....

INTINT2C        PDDL            PDDL
                                TCSI
                                TCDH
                PDDL            PUSH
                                TWOPI
                GOTO
                                INTINT
INTINT3P        PDDL            PDDL
                                TCDH
                                TTPI
                PDDL            PUSH
                                P30ZERO
                GOTO
                                INTINT

## Page 643
# ..... S32/33.1  .....

# SUBROUTINES USED

#       S32/33.X

S32/33.1        STQ             AXT,1
                                SUBEXIT
                VN              0681
                CALL
                                DISDVLVC
                CALL
                                S32/33.X
                VLOAD           VXM
                                DELVLVC
                                0D
                VSL1
                STORE           DELVSIN
                PUSH            ABVAL
                STOVL           DELVSAB
                GOTO
                                SUBEXIT

## Page 644
# ..... S32/33.X  .....

S32/33.X        SETPD           VLOAD
                                6D
                                UP1
                VCOMP           PDVL
                                RACT1
                UNIT            VCOMP
                PUSH            VXV
                                UP1
                VSL1
                STORE           0D
                RVQ

## Page 645
# ..... CDHMVR     .....

# SUBROUTINES USED

#       VECSHIFT
#       TIMETHET
#       SHIFTR1

CDHMVR          STQ             VLOAD
                                SUBEXIT
                                RACT2
                PUSH            UNIT
                STOVL           UNVEC                   # UR SUB A
                                RPASS2
                UNIT            DOT
                                UNVEC
                PUSH            SL1
                STODL           CSTH
                DSQ             PDDL
                                DP1/4TH
                SR2             DSU
                SQRT            SL1
                PDVL            VCOMP
                VXV
                                RPASS2
                DOT             PDDL
                                UP1
                SIGN            STADR
                STOVL           SNTH
                                RPASS2
                PDVL            CALL
                                VPASS2
                                VECSHIFT
                STOVL           VVEC
                CLEAR
                                RVSW
                STCALL          RVEC
                                TIMETHET
                LXA,2           VSL*
                                RTX2
                                0,2
                STORE           18D
                DOT             SL1R
                                UNVEC
                PDVL            ABVAL                   # 0D = V SUB PV
                SL*             PDVL
                                0,2
                                RACT2
                ABVAL           PDDL                    # 2D = LENGTH OF R SUB A
                DSU

## Page 646
                                02D
                STODL           DIFFALT                 # DELTA H IN METERS             B+29
                                R1A
                NORM            PDDL                    # 2 - R V**/MU                          04D
                                X1
                                R1
                CALL
                                SHIFTR1
                SR1R            DDV
                SL*             PUSH
                                0 -5,1
                DSU             PDDL                    # A SUB A                       B+29    04D
                                DIFFALT
                SR2             DDV                     # A SUB P                      B+31
                                04D                     #                              B+2
                PUSH            SQRT                    #    A SUB P/A SUB A             06D
                DMPR            DMP
                                06D
                                00D
                SL3R            PDDL                    # V SUB A V METERS/CS           B+7     08D
                                02D                     # R SUB A MAGNITUDE    B+29
                NORM            PDDL
                                X1
                                RTMU
                SR1             DDV                     # 2MU  B+38
                SL*             PDDL                    #    2 MU/R SUBAA      B+14       10D
                                0 -5,1
                                04D                     # ASUBA                        B+29
                NORM            PDDL
                                X2
                                RTMU
                SR1             DDV
                SL*             BDSU
                                0 -6,2                  # 2U/R - U/A    B+14 (METERS/CS)SQ
                PDDL            DSQ                     #                                       10D
                                08D
                BDSU            SQRT
                PDVL            VXV                     # SQRT(MU(2/R SUB A-1/A SUB A)-VSUBA2)10D
                                UP1
                                UNVEC
                UNIT            VXSC
                                10D
                PDVL            VXSC
                                UNVEC
                                08D
                VAD             VSL1
                STADR
                STORE           VACT3
                VSU
                                VACT2
## Page 647
                STCALL          DELVEET2                # DELTA VCDH - REFERENCE COORDINATES
                                SUBEXIT

## Page 648
# ..... COMPTGO   .....

# SUBROUTINES USED

#          CLOKTASK
#          2PHSCHNG

                BANK            35
                SETLOC          CSI/CDH
                BANK

                EBANK=          RTRN

                COUNT*          $$/P3575

COMPTGO         EXTEND
                QXCH            RTRN
                CAF             ZERO
                TS              DISPDEX
                CAF             BIT2
                INHINT
                TC              WAITLIST
                EBANK=          WHICH
                2CADR           CLOKTASK

                TC              2PHSCHNG
                OCT             40036
                OCT             05024
                OCT             13000
                TC              RTRN
