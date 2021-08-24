### FILE="Main.annotation"
## Copyright:   Public domain.
## Filename:    TVCEXECUTIVE.agc
## Purpose:     A section of Artemis revision 071.
##              It is part of the reconstructed source code for the first
##              release of the flight software for the Command Module's
##              (CM) Apollo Guidance Computer (AGC) for Apollo 15 through
##              17. The code has been recreated from a copy of Artemis 072.
##              It has been adapted such that the resulting bugger words
##              exactly match those specified for Artemis 071 in NASA
##              drawing 2021154-, which gives relatively high confidence
##              that the reconstruction is correct.
## Reference:   950
## Assembler:   yaYUL
## Contact:     Ron Burkey <info@sandroid.org>.
## Website:     www.ibiblio.org/apollo/index.html
## Mod history: 2019-08-14 MAS  Created from Artemis 072.

## Page 950
# PROGRAM NAME.... TVCEXECUTIVE, CONSISTING OF TVCEXEC, NEEDLEUP, VARGAINS
#		   1SHOTCHK, REPCHEK, CG.CORR, COPYCYCLES, ETC.
# LOG SECTION...TVCEXECUTIVE			SUBROUTINE...DAPCSM
# MODIFIED BY SCHLUNDT				21 OCTOBER 1968
# MODIFIED BY BEALS TO ELIMINATE CSMMASS UPDATE LOGIC (NOW DONE IN S40.8)
# FUNCTIONAL DESCRIPTION....
#
#      *A SELF-PERPETUATING WAITLIST TASK AT 1/2 SECOND INTERVALS WHICH:
#	PREPARES THE ROLL DAP WITH OGA (CDUX)
#	PREPARES THE ROLL FDAI NEEDLE (FLY-TO  OGA ERROR)
#	PREPARES THE ROLL PHASE PLANE  OGAERR  (FLY-FROM  OGA ERROR)
#	PREPARES THE TVC ROLLDAP TASK WAITLIST CALL (3 CS DELAY)
#	UPDATES THE NEEDLES DISPLAY
#	CALLS MASSPROP TO UPDATE INERTIA DATA
#	UPDATES PITCH, YAW, AND ROLL DAP GAINS FROM MASSPROP DATA
#	PERFORMS ONE-SHOT CORRECTION FOR TMC LOOP 0-3 SEC AFTER IGNITION
#	PERFORMS REPETITIVE UPDATES FOR TMC LOOP AFTER THE ONE-SHOT CORR.
#
# CALLING SEQUENCE....
#
#      *TVCEXEC CALLED AS A WAITLIST TASK, IN PARTICULAR BY TVCINIT4 AND BY
#	ITSELF, BOTH AT 1/2 SECOND INTERVALS
#
# NORMAL EXIT MODE.... TASKOVER
#
# ALARM OR ABORT EXIT MODES.... NONE
#
# SUBROUTINES CALLED....NEEDLER, S40.15, MASSPROP, TASKOVER, IBNKCALL
#
# OTHER INTERFACES....
#
#      *TVCRESTART PACKAGE FOR RESTARTS
#      *PITCHDAP, YAWDAP FOR VARIABLE GAINS AND ENGINE TRIM ANGLES
# ERASABLE INITIALIZATION REQUIRED....
#
#      *SEE TVCDAPON....TVCINIT4
#      *VARK AND 1/CONACC (S40.15 OF TVCINITIALIZE)
#      *PAD LOAD EREPFRAC
#      *BITS 15,14 OF FLAGWRD6 (T5 BITS)
#      *TVCEXPHS FOR RESTARTS
#      *ENGINE-ON BIT (11.13) FOR RESTARTS
#      *CDUX, OGAD
#
# OUTPUT....
#
#      *ROLL DAP OGANOW, FDAI NEEDLE (AK). AND PHASE PLANE OGAERR
#      *VARIABLE GAINS FOR PITCH/YAW AND ROLL TVC DAPS
#      *SINGLE-SHOT AND REPETITIVE CORRECTIONS TO ENGINE TRIM ANGLES
#	PACTOFF AND YACTOFF
# DEBRIS.... MUCH, BUT SHAREABLE WITH RCS/ENTRY, ALL IN EBANK6

## Page 951
		SETLOC	DAPROLL
		BANK
		EBANK=	CNTR
		COUNT*	$$/TVCX


TVCEXEC		CS	FLAGWRD6	# CHECK FOR TERMINATION (BITS 15,14 READ
		MASK	DPCONFIG	# 10 FROM TVCDAPON TO RCSDAPON
		EXTEND
		BZMF	TVCEXFIN	# TERMINATE

		CAF	.5SEC		# W.L. CALL TO PERPETUATE TVCEXEC
		TC	TWIDDLE
		ADRES	TVCEXEC
ROLLPREP	CAE	CDUX		# UPDATE ROLL LADDERS (NO NEED TO RESTART-
		XCH	OGANOW		#	PROTECT, SINCE ROLL DAPS RE-START)
		XCH	OGAPAST

		CAE	OGAD		# PREPARE ROLL FDAI NEEDLE  WITH FLY-TO
		EXTEND			#	ERROR (COMMAND - MEASURED)
		MSU	OGANOW
		TS	AK		# FLY-TO OGA ERROR, SC.AT B-1 REVS

		EXTEND			# PREPARE ROLL DAP PHASE PLANE  OGAERR
		MP	-BIT14
		TS	OGAERR		# PHASE-PLANE (FLY-FROM) OGAERROR,
					#	SC.AT B+0 REVS

		CAF	THREE		# SET UP ROLL DAP TASK (ALLOW SOME TIME)
		TC	TWIDDLE
		ADRES	ROLLDAP		
NEEDLEUP	TC	IBNKCALL	# DO A NEEDLES UPDATE (RETURNS AFTER CADR)
		CADR	NEEDLER		#	(NEEDLES RESTARTS ITSELF)

VARGAINS	CCS	VCNTR		# TEST FOR GAIN UPDATE TIME
		TCF	EXECCOPY	# NOT YET			
GAINCHNG	TC	IBNKCALL	# UPDATE IXX, IAVG, IAVG/TLX
		CADR	FIXCW		# MASSPROP ENTRY  (ALREADY INITIALIZED)
		TC	IBNKCALL	# UPDATE 1/CONACC, VARK
		CADR	S40.15		#	(S40.15 IS IN TVCINITIALIZE)
		CAF	NINETEEN	# RESET THE VARIABLE-GAIN UPDATE COUNTER
EXECCOPY	TS	VCNTR
1SHOTCHK	CCS	CNTR		# CHECK TIME FOR ONE-SHOT OR REPCORR
		TCF	+4		#	NOT YET
		TCF	1SHOTOK		#	NOW
		TCF	REPCHEK		#	ONE-SHOT OVER, ON TO REPCORR
		TCF	1SHOTOK		#	NOW  (ONE-SHOT ONLY, NO REPCORR)

 +4		TS	CNTRTMP		# COUNT DOWN
		CAF	FOUR		# SET UP TVCEXPHS FOR ENTRY AT CNTRCOPY
## Page 952
		TS	TVCEXPHS
		TCF	CNTRCOPY

REPCHEK		CAE	REPFRAC		# CHECK FOR REPETITIVE UPDATES
		EXTEND
		BZMF	TVCEXFIN	#	NO, OVER-AND-OUT
		TS	TEMPDAP +1	#	YES, SET UP CORRECTION FRACTION
		CAF	TWO		# SET UP TVCEXPHS FOR ENTRY AT CORSETUP
		TS	TVCEXPHS
		TCF	CORSETUP	

1SHOTOK		CAF	ENGONBIT	
		MASK	FLAGWRD5
		CCS	A
		TCF	+2		#	ONE-SHOT OK
		TCF	TVCEXFIN	#	NO, TERMINATE

		INCR	TVCEXPHS	#					(1)
TEMPSET		CAF	FCORFRAC	#	SET UP CORRECTION FRACTION
		TS	TEMPDAP +1

		INCR	TVCEXPHS	# ENTRY FROM REPCHECK AT NEXT LOCATION	(2)
CORSETUP	CAE	DAPDATR1	# CHECK FOR LEM-OFF/ON
		MASK	BIT13		# (NOTE, SHOWS LEM-OFF)
		EXTEND
		BZF	+2		# LEM IS ON,  PICK UP   TEMPDAP+1
		CAE	TEMPDAP +1	# LEM IS OFF, PICK UP 2(TEMPDAP+1)
		AD	TEMPDAP +1
		TS	TEMPDAP		# CG.CORR USES TEMPDAP

		CAF	NEGONE		# SET UP FOR CNTR = -1 (ONE-SHOT DONE)
		TS	CNTRTMP		#	(COPYCYCLE AT .CNTRCOPY.)

CG.CORR		EXTEND			# PITCH TMC LOOP
		DCA	PDELOFF
		DXCH	PACTTMP
		EXTEND
		DCS	PDELOFF
		DDOUBL
		DDOUBL
		DXCH	TTMP1
		EXTEND
		DCA	DELPBAR
		DDOUBL
		DDOUBL
		DAS	TTMP1
		EXTEND
		DCA	TTMP1
		EXTEND
		MP	TEMPDAP
## Page 953
		DAS	PACTTMP

		EXTEND			# YAW TMC LOOP
		DCA	YDELOFF
		DXCH	YACTTMP
		EXTEND
		DCS	YDELOFF
		DDOUBL		
		DDOUBL
		DXCH	TTMP1
		EXTEND
		DCA	DELYBAR
		DDOUBL
		DDOUBL
		DAS	TTMP1
		EXTEND
		DCA	TTMP1
		EXTEND
		MP	TEMPDAP
		DAS	YACTTMP

CORCOPY		INCR	TVCEXPHS	# RESTART PROTECT THE COPYCYCLE		(3)
		EXTEND			# TRIM-ESTIMATES, AND
		DCA	PACTTMP
		TS	PACTOFF		#	TRIMS
		DXCH	PDELOFF

		EXTEND
		DCA	YACTTMP
		TS	YACTOFF
		DXCH	YDELOFF

		INCR	TVCEXPHS	# ENTRY FROM 1SHOTCHK AT NEXT LOCATION	(4)
CNTRCOPY	CAE	CNTRTMP		# UPDATE CNTR (RESTARTS OK, FOLLOWS CPYCY)
		TS	CNTR

TVCEXFIN	CAF	ZERO		# RESET TVCEXPHS
		TS	TVCEXPHS		
		TCF	TASKOVER	# TVCEXECUTIVE FINISHED


FCORFRAC	=	BIT13		# ONE-SHOT CORRECTION FRACTION	
