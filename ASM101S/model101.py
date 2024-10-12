'''
License:    This program is declared by its author, Ronald Burkey, to be the 
            U.S. Public Domain, and may be freely used, modifified, or 
            distributed for any purpose whatever.
Filename:   model101.py
Purpose:    This object-code generation for ASM101S, specific to the assembly 
            language of the IBM AP-101S computer.
Contact:    info@sandroid.org
Refer to:   https://www.ibiblio.org/apollo/ASM101S.html
History:    2024-09-05 RSB  Began.
'''

import copy
import random
from expressions import error, unroll, astFlattenList, evalArithmeticExpression
from fieldParser import parserASM

'''
A unique but "random" 28-bit "random", excluding all 0's and all 1's, 
left-shifted by 36 bits, is assigned as a hashcode to each CSECT (or DSECT) and 
each EXTRN symbol. These are explicitly seeded, so as to make the sequence 
repeatable, but the exact seed isn't significant.

The purpose of this sequence of random numbers is to provide a workable (if 
unfortunately not theoretically perfect) means of computing arithmetical 
expressions optionally involving addresses of symbols.  Addresses are limited
to 24 bits in AP-101S, but prior to linking we don't know the actual addresses
but only the offsets within control sections.  And for EXTRN symbols, we don't
even know that much.  The values we use in computing arithmetical expressions
are 64-bit signed integers like so:
    hashcode + 32-bit offset For local symbols
    hashcode                 For EXTRN symbols
    32-bit number            For plain number
For correctly-formed expressions (i.e., those not involving illegal combinations
of address symbols), this always produces the correct results.  (Note that 
"pairing" of EXTRN symbols in expressions is not allowed.)  In particular, we're
concerned about producing the correct results for expressions like:
    symbol + number
    symbol1 - symbol2        where both symbols are in the same control section.

The hashed addresses are stored directly in the `symtab` dictionary,
so that they're easily accessed by the expression evaluator when presented with
a symbol.  At the end of the recursive evaluation of such an expression, the 
final hashcode can be extracted from the result and looked up in the
`hashcodeLookup` dictionary to determine what CSECT or EXTRN symbol it relates
to, if any.  Here's an example, involving an EXTRN symbol, two local symbols in
the same control section (thus having the same hashcode in their hashed 
addresses) and a few literal numbers:
    LOCAL1 + NUMBER1 + EXTERN - LOCAL2 + NUMBER2 * NUMBER3 
In the computation, the symbols are represented by the numerical values
    EXTERN = hashcode1
    LOCAL1 = hashcode2 + offset1
    LOCAL2 = hashcode2 + offset2
Since hashcode2-hashcode2 cancels out, the result of the calculation is
    result = hashcode1 + (offset1 + NUMBER1 - offset2 + NUMBER2 * NUMBER3)
or just
    result = hashcode1 + NUMBER4
which can be separated by the operations:
    NUMBER4  = result & 0x00000000FFFFFFFF
    buffer   = result & 0x0000000F00000000
    hashcode = result & 0xFFFFFFF000000000
`buffer` is an unused area between the 32-bit numerical value and the 28-bit
`hashcode`.

But (you ask), what if the NUMBER4 part of the calculation overflows?  If there
is positive overflow, it can almost always be detected by the value of the 
`buffer`, but in extreme cases it results in a `hashcode` which is illegal
and fails lookup.  If there's negative overflow, then in almost all cases
`hashcode` will be all 1's, but since all 1's is not a legal hashcode, we can
use it as an indication that the result is purely numerical, without a 
hashcode.
'''
random.seed(16134176201611561415)
hashcodeLookup = {}
def getHashcode(symbol):
    hashcode = random.randint(1, (1 << 28) - 1) << 36
    hashcodeLookup[hashcode] = symbol
    return hashcode
# Reverses the hashing of a computed result of an arithmetic expression.
# returns
#    sect,number
# where sect==None for a pure numerical result, or is the name of an EXTRN
# or CSECT for an address result.  In case of error None,None is returned.
def unhash(result):
    offset   = result & 0x00000000FFFFFFFF
    buffer   = result & 0x0000000F00000000
    hashcode = result & 0xFFFFFFF000000000
    if hashcode in [0, 0xFFFFFFF000000000]:
        # A purely-numerical value
        return None, result
    if buffer == 0 and hashcode in hashcodeLookup:
        return hashcodeLookup[hashcode], offset
    return None, None

#=============================================================================
# Various tables or the instruction set.

ap101 = True
system390 = False

# First, the CPU instructions, categorized by instruction types, accompanied
# by opcodes.  When the opcode is given as -1, it's a special case in terms
# of how the code is generated.  (There are other special cases, though, which
# are not so-marked, such as almost all conditional branches..)

# The 6-bit numerical codes are the 5-bit OP field, suffixed by the 1-bit OPX
# field.  Though technically considered RR instructions, the mnemonics
# LFXI, LFLI, SPM, BR, and NOPR are special, in that they either
# are encoded slightly differently or else are aliases and accept an altered 
# syntax from the others.
argsRR = {   "AR": 0b000000,   "CR": 0b000100,   "CBL": 0b000011,   
             "DR": 0b010010,  "XUL": 0b000001,    "LR": 0b000110,  
            "LCR": 0b111011, "LFXI": 0b101110,    "MR": 0b010000,    
             "SR": 0b000010, "BALR": 0b111000,   "BCR": 0b110000, 
           "BCRE": 0b110001, "BCTR": 0b110100,  "BVCR": 0b110010, 
            "NCT": 0b111001,   "NR": 0b001000,    "XR": 0b011100,   
             "OR": 0b001010,  "SUM": 0b100111,  "AEDR": 0b010101,  
            "AER": 0b010100, "CEDR": 0b000111,   "CER": 0b010011, 
           "CVFX": 0b001110, "CVFL": 0b001111,  "DEDR": 0b000101, 
            "DER": 0b011010,  "LER": 0b011110,  "LECR": 0b011111, 
           "LFXR": 0b001001, "LFLI": 0b100010,  "LFLR": 0b001011,  
           "MEDR": 0b001101,  "MER": 0b011000,  "SEDR": 0b010111, 
            "SER": 0b010110,  "MVH": 0b011011,   "SPM": 0b110011, 
           "SRET": 0b100101, "LXAR": 0b010001, "STXAR": 0b101001, 
            "ICR": 0b110110,   "BR": 0b110000,  "NOPR": 0b110000,  
           "LACR": 0b111011,   "PC": 0b011011 }

# The 10-bit numerical codes are the codes in encoded positions 0-4 (in both
# the RS and SRS forms of the instructin) suffixed by the bits in positions
# 8-12 (of the RS form, but are unused in the SRS forms.
argsSRSandRS = {
   "A": 0b0000011110, "AH": 0b1000011110,   "C": 0b0001011110, 
  "CH": 0b1001011110,  "D": 0b0100111110, "IAL": 0b1110011111, 
   "L": 0b0001111110, "LA": 0b1110111110,  "LH": 0b1001111110, 
   "M": 0b0100011110, "MH": 0b1010111110,  "ST": 0b0011011110, 
 "STH": 0b1011111110,  "S": 0b0000111110,  "SH": 0b1000111110, 
  "TD": 0b1010011110, "BC": 0b1100011110,   "N": 0b0010011110, 
   "X": 0b0111011110,  "O": 0b0010111110, "SHW": 0b1010011110,
  "TH": 0b1010011110, "ZH": 0b1010011110,  "AE": 0b0101011110, 
  "DE": 0b0110111110, "LE": 0b0111111110,  "ME": 0b0110011110,  
  "SE": 0b0101111110,
 }

argsSRSonly = {
  "BCB": 0b1101100000,  "BCF": 0b1101100000, "BCTB": 0b1101100000, 
 "BVCF": 0b1101100000,  "SLL": 0b1111000000, "SLDL": 0b1111100000, 
  "SRA": 0b1111000000, "SRDA": 0b1111100000, "SRDL": 0b1111100000,  
  "SRL": 0b1111000000,  "SRR": 0b1111000000, "SRDR": 0b1111100000,
    "B": 0b1100000000,  "NOP": 0b1100000000,   "BH": 0b1100000000,   
   "BL": 0b1100000000,   "BE": 0b1100000000,  "BNH": 0b1100000000, 
  "BNL": 0b1100000000,  "BNE": 0b1100000000,   "BO": 0b1100000000,   
   "BP": 0b1100000000,   "BM": 0b1100000000,   "BZ": 0b1100000000,  
  "BNP": 0b1100000000,  "BNM": 0b1100000000,  "BNZ": 0b1100000000,  
  "BNO": 0b1100000000,  "BLE": 0b1100000000,   "BN": 0b1100000000, 
 }


argsRSonly = { 
   "AST": 0b0000011111,    "IHL": 0b1000011111,     "LM": 0b1100111111, 
   "MIH": 0b1001111111,    "STM": 0b1100111111,    "SST": 0b0000111111, 
   "BAL": 0b1110011110,    "BIX": 0b1101111110,    "BCT": 0b1101011110, 
   "BCV": 0b1100111110,    "NST": 0b0010011111,    "XST": 0b0111011111, 
   "OST": 0b0010111111,    "AED": 0b0101011111,    "CED": 0b0001111111, 
    "CE": 0b0100111111,    "DED": 0b0001011111,    "LED": 0b0111111111, 
   "MVS": 0b0110011111,    "MED": 0b0011011111,    "SED": 0b0101111111, 
  "STED": 0b0011111111,    "STE": 0b0011111110,   "DIAG": 0b1100011111, 
  "ISPB": 0b1110111111,    "LPS": 0b1100111111,    "SSM": 0b1000111111, 
  "SCAL": 0b1101011111,    "SVC": 0b1100111111,     "TS": 0b1011111111, 
   "LXA": 0b0100011111,    "LDM": 0b0110111111,   "STXA": 0b1010011111, 
  "STDM": 0b1001011111,     "A@": 0b0000011110,    "A@#": 0b0000011110, 
    "A#": 0b0000011110,    "AE@": 0b0101011110,   "AE@#": 0b0101011110, 
   "AE#": 0b0101011110,   "AED@": 0b0101011111,  "AED@#": 0b0101011111, 
  "AED#": 0b0101011111,    "AH@": 0b1000011110,   "AH@#": 0b1000011110, 
   "AH#": 0b1000011110,   "AST@": 0b0000011111,  "AST@#": 0b0000011111, 
  "AST#": 0b0000011111,     "B@": 0b1100000000,    "B@#": 0b1100000000, 
    "B#": 0b1100000000,   "BAL@": 0b1110011110,  "BAL@#": 0b1110011110, 
  "BAL#": 0b1110011110,    "BC@": 0b1100011110,   "BC@#": 0b1100011110, 
   "BC#": 0b1100011110,   "BCT@": 0b1101011110,  "BCT@#": 0b1101011110, 
  "BCT#": 0b1101011110,   "BCV@": 0b1100111110,  "BCV@#": 0b1100111110, 
  "BCV#": 0b1100111110,    "BE@": 0b1100000000,   "BE@#": 0b1100000000, 
   "BE#": 0b1100000000,    "BH@": 0b1100000000,   "BH@#": 0b1100000000, 
   "BH#": 0b1100000000,   "BIX@": 0b1101111110,  "BIX@#": 0b1101111110, 
  "BIX#": 0b1101111110,    "BL@": 0b1100000000,   "BL@#": 0b1100000000, 
   "BL#": 0b1100000000,   "BLE@": 0b1100000000,  "BLE@#": 0b1100000000, 
  "BLE#": 0b1100000000,    "BM@": 0b1100000000,   "BM@#": 0b1100000000, 
   "BM#": 0b1100000000,    "BN@": 0b1100000000,   "BN@#": 0b1100000000, 
   "BN#": 0b1100000000,   "BNE@": 0b1100000000,  "BNE@#": 0b1100000000, 
  "BNE#": 0b1100000000,   "BNH@": 0b1100000000,  "BNH@#": 0b1100000000, 
  "BNH#": 0b1100000000,   "BNL@": 0b1100000000,  "BNL@#": 0b1100000000, 
  "BNL#": 0b1100000000,   "BNM@": 0b1100000000,  "BNM@#": 0b1100000000, 
  "BNM#": 0b1100000000,   "BNO@": 0b1100000000,  "BNO@#": 0b1100000000, 
  "BNO#": 0b1100000000,   "BNP@": 0b1100000000,  "BNP@#": 0b1100000000, 
  "BNP#": 0b1100000000,   "BNZ@": 0b1100000000,  "BNZ@#": 0b1100000000, 
  "BNZ#": 0b1100000000,    "BO@": 0b1100000000,   "BO@#": 0b1100000000, 
   "BO#": 0b1100000000,    "BP@": 0b1100000000,   "BP@#": 0b1100000000, 
   "BP#": 0b1100000000,    "BZ@": 0b1100000000,   "BZ@#": 0b1100000000, 
   "BZ#": 0b1100000000,     "C@": 0b0001011110,    "C@#": 0b0001011110, 
    "C#": 0b0001011110,    "CE@": 0b0100111111,   "CE@#": 0b0100111111, 
   "CE#": 0b0100111111,   "CED@": 0b0001111111,  "CED@#": 0b0001111111, 
  "CED#": 0b0001111111,    "CH@": 0b1001011110,   "CH@#": 0b1001011110, 
   "CH#": 0b1001011110,     "D@": 0b0100111110,    "D@#": 0b0100111110, 
    "D#": 0b0100111110,    "DE@": 0b0110111110,   "DE@#": 0b0110111110, 
   "DE#": 0b0110111110,   "DED@": 0b0001011111,  "DED@#": 0b0001011111, 
  "DED#": 0b0001011111,  "DIAG@": 0b1100011111, "DIAG@#": 0b1100011111, 
 "DIAG#": 0b1100011111,   "IAL@": 0b1110011111,  "IAL@#": 0b1110011111, 
  "IAL#": 0b1110011111,   "IHL@": 0b1000011111,  "IHL@#": 0b1000011111, 
  "IHL#": 0b1000011111,  "ISPB@": 0b1110111111, "ISPB@#": 0b1110111111, 
 "ISPB#": 0b1110111111,     "L@": 0b0001111110,    "L@#": 0b0001111110, 
    "L#": 0b0001111110,    "LA@": 0b1110111110,   "LA@#": 0b1110111110, 
   "LA#": 0b1110111110,   "LDM@": 0b0110111111,  "LDM@#": 0b0110111111, 
  "LDM#": 0b0110111111,    "LE@": 0b0111111110,   "LE@#": 0b0111111110, 
   "LE#": 0b0111111110,   "LED@": 0b0111111111,  "LED@#": 0b0111111111, 
  "LED#": 0b0111111111,    "LH@": 0b1001111110,   "LH@#": 0b1001111110, 
   "LH#": 0b1001111110,    "LM@": 0b1100111111,   "LM@#": 0b1100111111, 
   "LM#": 0b1100111111,   "LPS@": 0b1100111111,  "LPS@#": 0b1100111111, 
  "LPS#": 0b1100111111,   "LXA@": 0b0100011111,  "LXA@#": 0b0100011111, 
  "LXA#": 0b0100011111,     "M@": 0b0100011110,    "M@#": 0b0100011110, 
    "M#": 0b0100011110,    "ME@": 0b0110011110,   "ME@#": 0b0110011110, 
   "ME#": 0b0110011110,   "MED@": 0b0011011111,  "MED@#": 0b0011011111, 
  "MED#": 0b0011011111,    "MH@": 0b1010111110,   "MH@#": 0b1010111110, 
   "MH#": 0b1010111110,   "MIH@": 0b1001111111,  "MIH@#": 0b1001111111, 
  "MIH#": 0b1001111111,   "MVS@": 0b0110011111,  "MVS@#": 0b0110011111, 
  "MVS#": 0b0110011111,     "N@": 0b0010011110,    "N@#": 0b0010011110, 
    "N#": 0b0010011110,   "NOP@": 0b1100000000,  "NOP@#": 0b1100000000, 
  "NOP#": 0b1100000000,   "NST@": 0b0010011111,  "NST@#": 0b0010011111, 
  "NST#": 0b0010011111,     "O@": 0b0010111110,    "O@#": 0b0010111110, 
    "O#": 0b0010111110,   "OST@": 0b0010111111,  "OST@#": 0b0010111111, 
  "OST#": 0b0010111111,     "S@": 0b0000111110,    "S@#": 0b0000111110, 
    "S#": 0b0000111110,  "SCAL@": 0b1101011111, "SCAL@#": 0b1101011111, 
 "SCAL#": 0b1101011111,    "SE@": 0b0101111110,   "SE@#": 0b0101111110, 
   "SE#": 0b0101111110,   "SED@": 0b0101111111,  "SED@#": 0b0101111111, 
  "SED#": 0b0101111111,    "SH@": 0b1000111110,   "SH@#": 0b1000111110, 
   "SH#": 0b1000111110,   "SHW@": 0b1010011110,  "SHW@#": 0b1010011110, 
  "SHW#": 0b1010011110,   "SSM@": 0b1000111111,  "SSM@#": 0b1000111111, 
  "SSM#": 0b1000111111,   "SST@": 0b0000111111,  "SST@#": 0b0000111111, 
  "SST#": 0b0000111111,    "ST@": 0b0011011110,   "ST@#": 0b0011011110, 
   "ST#": 0b0011011110,  "STDM@": 0b1001011111, "STDM@#": 0b1001011111, 
 "STDM#": 0b1001011111,   "STE@": 0b0011111110,  "STE@#": 0b0011111110, 
  "STE#": 0b0011111110,  "STED@": 0b0011111111, "STED@#": 0b0011111111, 
 "STED#": 0b0011111111,   "STH@": 0b1011111110,  "STH@#": 0b1011111110, 
  "STH#": 0b1011111110,   "STM@": 0b1100111111,  "STM@#": 0b1100111111, 
  "STM#": 0b1100111111,  "STXA@": 0b1010011111, "STXA@#": 0b1010011111, 
 "STXA#": 0b1010011111,   "SVC@": 0b1100111111,  "SVC@#": 0b1100111111, 
  "SVC#": 0b1100111111,    "TD@": 0b1010011110,   "TD@#": 0b1010011110, 
   "TD#": 0b1010011110,    "TH@": 0b1010011110,   "TH@#": 0b1010011110, 
   "TH#": 0b1010011110,    "TS@": 0b1011111111,   "TS@#": 0b1011111111, 
   "TS#": 0b1011111111,     "X@": 0b0111011110,    "X@#": 0b0111011110, 
    "X#": 0b0111011110,   "XST@": 0b0111011111,  "XST@#": 0b0111011111, 
  "XST#": 0b0111011111,    "ZH@": 0b1010011110,   "ZH@#": 0b1010011110, 
   "ZH#": 0b1010011110    
   }

argsSRSorRS = argsSRSandRS | argsSRSonly | argsRSonly

'''
i = 0
for key in argsRSonly:
    i += 1
    value = format(argsSRSorRS[key.replace("@","").replace("#","")], "#012b")
    print('%8s: %s, ' % ('"'+key+'"', value), end="")
    if i % 3 == 0:
            print()
print()
sys.exit(1)
'''

# The 14-bit numerical codes are what's encoded in bits 0-12
# LHI and SHI are special and must be specially handled.
argsRI = { "AHI": 0b1011000011100, "CHI": 0b1011010111100, 
           "MHI": 0b1011011111100, "NHI": 0b1011011011100, 
           "XHI": 0b1011010011100, "OHI": 0b1011001011100, 
           "TRB": 0b1011001111100, "ZRB": 0b1011000111100, 
           "LHI": 0b0000000000000, "SHI": 0b1011000011100 }

# The 8-bit numerical codes are the OP+OPX fields of the encoded instruction.
argsSI = { "CIST": 0b10110101, "MSTH": 0b10110000, "NIST": 0b10110110, 
           "XIST": 0b10110100,   "SB": 0b10110010,   "TB": 0b10110011, 
             "ZB": 0b10110001,  "TSB": 0b10110111 }

# Now, the MSC instructions.
argsMSC = { "@A": -1, "@B": -1, "@BN": -1, "@BNN": -1, "@BNP": -1, "@BNZ": -1, "@BU": -1, "@BU@": -1, "@BXN": -1,
         "@BXNN": -1, "@BXNP": -1, "@BXNZ": -1, "@BXP": -1, "@BXZ": -1, "@BZ": -1, "@C": -1, "@CI": -1, 
         "@CNOP": -1, "@DLY": -1, "@INT": -1, "@L": -1, "@LAR": -1, "@LF": -1, "@LH": -1, "@LI": -1, "@LMS": -1, 
         "@LXI": -1, "@N": -1, "@NIX": -1, "@RAI": -1, "@RAW": -1, "@RBI": -1, "@REC": -1, "@RFD": -1, "@RNI": -1, 
         "@RNW": -1, "@SAI": -1, "@SEC": -1, "@SFD": -1, "@SIO": -1, "@ST": -1, "@STF": -1, "@STH": -1, "@STP": -1, 
         "@TAX": -1, "@TI": -1, "@TM": -1, "@TMI": -1, "@TSZ": -1, "@TXA": -1, "@TXI": -1, "@WAT": -1, "@X": -1, 
         "@XAX": -1, "@BC": -1, "@BXC" "@CALL": -1, "@CALL@": -1, "@LBB": -1, "@LBB@": -1, "@LBP": -1, 
         "@LBP@": -1 }

# And BCE instructions.
argsBCE = { "#@#DEC": -1, "#@#HEX": -1, "#@#SCN": -1, "#BU": -1, "#BU@": -1, "#CMD": -1, "#CMDI": -1, 
           "#CNOP": -1, "#DLY": -1, "#DLYI": -1, "#LBR": -1, "#LBR@": -1, "#LTO": -1, "#LTOI": -1, "#MIN": -1,
           "#MIN@": -1, "#MINC": -1, "#MOUT": -1, "#MOUT@": -1, "#MOUTC": -1, "#ORG": -1, "#RDL": -1, 
           "#RDLI": -1, "#RDS": -1, "#RIB": -1, "#SIB": -1, "#SPLIT": -1, "#SSC": -1, "#SST": -1, "#STP": -1, 
           "#TDL": -1, "#TDLI": -1, "#TDS": -1, "#WAT": -1, "#WIX": -1
       }

instructionsWithoutOperands = argsBCE
instructionsWithOperands = argsRR | argsSRSorRS | argsRSonly | argsSRSonly | \
                           argsSI | argsMSC
knownInstructions = instructionsWithoutOperands | instructionsWithOperands

# The field values are the masks.
branchAliases = {"B": 7, "BR": 7, "NOP": 0, "NOPR": 0, "BH": 1, "BL": 2, 
                 "BE": 4, "BNH": 6, "BNL": 5, "BNE": 3, "BO": 1, "BP": 1, 
                 "BM": 2, "BZ": 4, "BNP": 6, "BNM": 5, "BNZ": 3, "BNO": 6,
                 "BLE": 6, "BN": 2}

# Floating-point RS/SRS mnemonics. 
fpOperations = { "AED", "AE", "CE", "CED", "DED", "DE", "LED", "LE", 
                 "MED", "ME", "SED", "SE", "STED", "STE" }

sects = {} # CSECTS and DSECTS.
entries = set() # For `ENTRY`.
extrns = set() # For `EXTRN`.
symtab = {}
metadata = {
    "sects": sects,
    "entries": entries,
    "extrns": extrns,
    "symtab": symtab,
    "passCount": 0
    }

#=============================================================================
# `optimizeScratch` analyzes the "scratch" structures created during the 
# "collect" pass, to resolve ambiguities in how those mnemonics which could be
# either SRS instructions or RS instructions are coded.

def optimizeScratch():
    global symtab, sects
    
    for sect in sects:
        scratch = sects[sect]["scratch"]
        previouslyDefined = {}
        for i in range(len(scratch)):
            entry = scratch[i]
            entry["properties"]["length"] = entry["length"]
            if "name" in entry:
                previouslyDefined[entry["name"]] = i
            if not entry["ambiguous"]:
                continue
            # We've found an ambiguous instruction (i.e., SRS vs RS) that we
            # must resolve.  First thing is that we have to parse the operand
            # to determine the target address we want to reach.
            ast = parserASM(entry["operand"], "rsAll")
            if ast == None or "X2" in ast or "B2" in ast:
                entry["ambiguous"] = False
                continue
            d2 = evalArithmeticExpression(ast["D2"], {}, entry["properties"], \
                                          symtab, \
                                          symtab[sect]["value"] + entry["pos1"] // 2, \
                                          severity=0)
            if d2 == None:
                entry["ambiguous"] = False
                continue
            section, value = unhash(d2)
            if section == None:
                entry["ambiguous"] = False
                continue
            # Check for the case `OPCODE R1,D2`, where `D2` is a location in
            # a CSECT currently in `USING`.
            b = None
            d = 10000000
            for u in entry["using"]:
                if u != None and section == u[1]:
                    if u[2] < d:
                        d = u[2]
                        b = u[1]
            if b != None and d < 56:
                entry["length"] = 2
                entry["properties"]["length"] = entry["length"]
                entry["ambiguous"] = False
                for j in range(i+1, len(scratch)):
                    entry2 = scratch[j]
                    if sect == entry2["sect"]:
                        entry2["pos1"] -= 2
                        entry2["pos2"] -= 1
                        entry2["debug"] = "%05X" % entry2["pos2"]
                        if "name" in entry2:
                            sym2 = symtab[entry2["name"]]
                            if sym2["address"] > entry["pos2"]:
                                sym2["address"] -= 1
                                sym2["value"] -= 1
                                sym2["debug"] = "%05X" % sym2["address"]
                continue
    return

#=============================================================================
# Generate object code for AP-101S.

'''
Work is done in place on the `source` array, which is a list of "property"
structures, one for each line if source code, including all of the macro
definitions from the macro library.  However, all manipulations of symbolic
variables and expansion of macros has been performed, so only the lines of
pure assembly-language code (i.e., CPU instructions and related pseudo-ops)
are processed.  Moreover, while continuation lines are present, all after the
first in any sequence have been merged into the first line of the sequence.
The `macros` argument is provided merely to have a list of operations which
can be ignored.

The only manipulations done to any particular entry of `source` are:
    1. The `errors` field may be augmented via the `error` function.
    2. Non-previously-existing fields may be added to hold object-code data.
I.e., no existing fields other than `errors` are affected.

Additionally, the function returns a dictionary of non-line-by-line info about
the assembly.

Note that addresses are in units of bytes.
'''
ignore = { "TITLE", 
           "GBLA", "GBLB", "GBLC", "LCLA", "LCLB",
           "LCLC", "SETA", "SETB", "SETC", "AIF",
           "AGO", "ANOP", "SPACE", "MEXIT", "MNOTE" }
hexDigits = "0123456789ABCDEF"

'''
Data for the compilation that isn't on a line-by-line basis.  Regarding the
`symtab` dictionary, there's an entry for each symbol, and each entry is 
itself a dictionary.  Each of those dictionaries has a "type" key to indicate 
the general category it falls into, chosen from among the following:

   "EXTERNAL"    Indicates an `EXTRN` symbol.
   "DATA"        Indicates `DS` or `DC`.
   "INSTRUCTION" Indicates a program label.
   "ENTRY"       Indicates an `ENTRY` point, but otherwise identical to an
                 "INSTRUCTION".
   "CSECT"       Indicates `CSECT`, `DSECT`, or `START`.
   "EQU"         Indicates `EQU`.
   "LITERAL"     Indicates an integer, boolean, or string constant value.
   ... presumably, more later ...
   
Besides the "type" key, there could be one or more of following keys:
   "section"     (string) Name of the control section containg the symbol.
   "address"     (integer) Halfword ddress of the symbol within the control section.
   "value"       Tricky, so see explanatin that follows.

Regarding "value", this is what's used in computing the value of arithmetic 
expressions involving the symbol.  There are four cases:

1. For symbols which cannot be used in arithmetic expressions, there is no 
   "value" field.
2. For symbols representing addresses ("EXTERNAL", "DATA", "INSTRUCTION", 
   "ENTRY", "CSECT"), this is a 64-bit integer pseudo-address that combines the
   "section" and "address" fields into a single number.
3. For symbols representing constant values rather than addresses ("LITERAL"),
   is the actual integer, boolean, or string value of the constant.
4. "EQU" symbols may represent any of the cases mentioned above, and the "value"
   field will also match those cases accordingly.

The `unhash` function can be used to return any "value"-type integer into 
its constituent "section"/"address", or to determine that it's just an integer
value rather than an address at all.
'''

# `dcBuffer` is used for assembling a single `DC` pseudo-op.  I don't know the
# maximum amount of data a single `DC` can generate ... but it's a *lot*.
# I've simply chosen a number here that while far less than the maximum, should
# be overkill for Shuttle flight software.
dcBuffer = bytearray(1024)
def generateObjectCode(source, macros):
    global dcBuffer
    
    #-----------------------------------------------------------------------
    # Setup
    
    collect = False
    compile = False
    sect = None # Current section.
    for key in macros:
        ignore.add(key)
    properties = {}
    
    name = ""
    operation = ""
    using = [None]*8
    hashMask = 0xFFFFFFF000000000

    #-----------------------------------------------------------------------
    
    # If a single `USING` is defined, get it.
    def onlyOneUsing():
        found = None
        for i in range(len(using)):
            if using[i] != None:
                if found == None:
                    found = i
                else:
                    return None
        return found
    
    # A function for writing to memory or allocating it without writing to
    # it, as appropriate, though in this case "not writing to it" means 
    # zeroing it.  This occurs in the current CSECT or DSECT
    #    `bytes`        Is either a number (for DS) indicating how much memory
    #                   to allocate, or else a `bytearray` (for DC) of the
    #                   actual bytes to store.
    # Alignment must have been done prior to entry.
    memoryChunkSize = 4096
    def toMemory(bytes):
        nonlocal collect, compile, properties, name, operation
        pos1 = sects[sect]["pos1"]
        if collect:
            pos2 = pos1 // 2
            newScratch = {}
            if name != "":
                newScratch["name"] = name
            if isinstance(bytes, int):
                newScratch["length"] = bytes
            else:
                newScratch["length"] = len(bytes)
            newScratch = newScratch | {
                "ambiguous": (operation in argsSRSandRS),
                "debug": "%05X" % pos2,
                "pos1": pos1,
                "pos2": pos2,
                "sect": sect,
                "operation": operation,
                "operand": operand,
                "properties": properties,
                "using": copy.copy(using)
                }
            sects[sect]["scratch"].append(newScratch)
        properties["section"] = sect
        properties["pos1"] = pos1
        if isinstance(bytes, bytearray):
            end = pos1 + len(bytes)
            if cVsD and compile:
                memory = sects[sect]["memory"]
                if end > len(memory):
                    chunks = (end - len(memory) + memoryChunkSize - 1) \
                                // memoryChunkSize
                    memory.extend([0]*(chunks * memoryChunkSize - len(memory)))
                for i in range(len(bytes)):
                    memory[pos1 + i] = bytes[i]
            properties["assembled"] = bytes
            sects[sect]["pos1"] = end
        else:
            sects[sect]["pos1"] += bytes
        if sects[sect]["pos1"] > sects[sect]["used"]:
            sects[sect]["used"] = sects[sect]["pos1"]

    # Common processing for all instructions. The `alignment` argument is one
    # of 1 (byte), 2 (halfword), 4 (word), 8 (doubleword).
    # The memory added for padding is 0-filled if `zero` is `True`, or left
    # unchanged if `False`.
    def commonProcessing(alignment=1, zero=False):
        nonlocal cVsD, sect, name, operation
        
        # Make sure we're in *some* CSECT or DSECT
        if sect == None:
            cVsD = True
            sect = ""
            if sect not in sects:
                sects[sect] = {
                    "pos1": 0,
                    "used": 0,
                    "memory": bytearray(memoryChunkSize),
                    "scratch": []
                    }
        
        # Perform alignment.
        if alignment > 1:
            rem = sects[sect]["pos1"] % alignment
            if rem != 0:
                if zero:
                    toMemory(bytearray(alignment - rem))
                else:
                    toMemory(alignment - rem)
        
        # Add `name` (if any) to the symbol table.
        if collect and name != "":
            pos1 = sects[sect]["pos1"]
            if name in symtab: # This can't happen.
                oldSect = symtab[name]["section"]
                oldPos = symtab[name]["address"]
                if oldSect != sect or oldPos != pos1:
                    error(properties, 
                          "Symbol %s address has changed: (%s,%d) -> (%s,%d)" \
                          % (name, oldSect, oldPos, sect, pos1 ))
            else:
                pos2 = pos1 // 2
                symtab[name] = { "section": sect,  "address": pos2,
                                 "value": symtab[sect]["value"] + pos2,
                                 "debug": "%05X" % pos2 }
                if operation in ["DC", "DS"]:
                    symtab[name]["type"] = "DATA"
                elif name in entries:
                    symtab[name]["type"] = "ENTRY"
                else:
                    symtab[name]["type"] = "INSTRUCTION"
    
    # Gets the hashed address of the current program counter.
    def currentHash():
        return symtab[sect]["value"] + sects[sect]["pos1"] // 2
    
    # Evaluate a single suboperand of the operand of an instruction like 
    # RR, RS, SRS, SI, RI.  Returns a pair (err,value).  The `err` is 
    # boolean and is True on error.  The value is an integer, or None if the
    # desired subfield isn't present.  The possible subfields are strings like
    # "R1", "R2", "D2", "X2", "B2", and so on.
    def evalInstructionSubfield(properties, subfield, ast, symtab={}):
        nonlocal sect
        if subfield not in ast:
            return False, None
        expression = ast[subfield]
        value = evalArithmeticExpression(expression, {}, properties, symtab, \
                                         currentHash(), severity=0)
        if value == None:
            error(properties, "Could not evaluate %s subfield" % subfield, \
                  severity=0)
            return True, None
        return False, value
    
    # For an instruction in which there's a nominal suboperand D2(B2) [or
    # D2(X2,B2)], but which is given in the source code simply as D2, determine
    # a suitable B2 and adjusted D2 from among the registers specified by 
    # `USING`.  The argument `d2` is given in hashed form.  The return value 
    # is B2,D2 where the base has been subtracted from the given d2, or else 
    # None,None if no candidates were found. As far as the `findB2D2` function 
    # is concerned, there's no actual upper limit on the returned D2; the 
    # calling code must determine for itself whether or not D2 is small enough.
    def findB2D2(d2):
        if (d2 & hashMask) in [0, hashMask]:
            return None, (d2 & 0xFFFFFF)
        D2 = None
        B2 = None
        for i in range(len(using)):
            e = using[i]
            if e == None:
                continue
            d = d2 - e[0]
            if d >= 0 and d < 4096:
                # Note that "<=" is required in this test, rather than "<",
                # because the assembler manual states that if two candidate
                # registers result in the same D2, the higher-number register
                # is used.
                if D2 == None or d <= D2:
                    D2 = d
                    B2 = i
        return B2, D2
    
    #-----------------------------------------------------------------------
    # Process source code in a series of passes.
    #    passCount == 0         Determine the number of bytes needed by each
    #                           CPU instruction or DC/DS, and the addresses
    #                           of all symbols.
    #    passCount == 1         Compile to memory.
    # Pass 0 isn't actually as straightforward as it sounds, because of the
    # ambiguity in terms of size of all of the instructions whose mnemonics
    # are in `argsSRSorRC` and all of the branch instructions aliased to 
    # instruction `BC` (which itself is in `argsSRSorRC`).  So pass 0 collects
    # a lot of data regarding such memory alignments into a work structure
    # that's extensively analyzed in between passes 0 and 1 to resolve the
    # ambiguity as best ti can.
    
    for passCount in range(2):
        metadata["passCount"] = passCount
        collect = (passCount == 0)
        compile = (passCount == 1)
        continuation = False
        for sect in sects:
            sects[sect]["pos1"] = 0
        sect = None
        using = [None]*8
        # Process shource code, line-by-line
        for properties in source:
            
            #******** Should this line be processed or discarded? ********
            if properties["inMacroDefinition"] or properties["fullComment"] or \
                    properties["dotComment"] or properties["empty"]:
                continue
            # We only need to look at the first line of any sequence of continued
            # lines.
            if continuation:
                continuation = properties["continues"]
                continue
            continuation = properties["continues"]
            # Various types of lines we can immediately discard by looking at 
            # their `operation` fields
            operation = properties["operation"]
            if operation in ignore:
                continue
            
            name = properties["name"]
            if name.startswith("."):
                name = ""
            operand = properties["operand"].rstrip()
            
            #******** Most pseudo-ops ********
            # Take care of pseudo-ops that don't add anything to AP-101S memory.
            # Each one of these should either `continue` or `break`, so as not to
            # fall through to instruction processing.
            if operation in ["CSECT", "DSECT"]:
                # The current section name starts as `None`, meaning none has been
                # assigned.  `START` or `CSECT` changes that to either "" (the
                # "unnamed" section) or an identifier. Code that must be assembled
                # when the section name is still `None` automatically switches to
                # the unnamed section.  I *could* check here that the name given
                # to the section is a valid identifier name, but I'm not bothering
                # with that just yet.
                cVsD = (operation == "CSECT")
                if name == "" and not cVsD:
                    error(properties, "Unnamed DSECT not allowed.")
                sect = name
                if sect not in sects:
                    sects[sect] = {
                        "pos1": 0,
                        "used": 0,
                        "memory": bytearray(memoryChunkSize),
                        "scratch": []
                        }
                    symtab[sect] = { 
                        "section": sect, 
                        "address": 0, 
                        "type": "CSECT",
                        "value": getHashcode(sect) 
                        }
                properties["section"] = sect
                properties["pos1"] = sects[sect]["pos1"]
                continue
            elif operation == "END":
                break
            elif operation in ["ENTRY", "EXTRN"]:
                ast = parserASM(operand, "identifierList")
                if ast == None:
                    error(properties, "Cannot parse operand of %s" % operation)
                else:
                    ast = unroll(ast)
                    symbols = []
                    if isinstance(ast, str):
                        symbols.append(ast)
                    else:
                        symbols.append(ast[0])
                        for e in ast[1]:
                            symbols.append(e[1])
                    for symbol in symbols:
                        if operation == "ENTRY":
                            entries.add(symbol)
                        else:
                            extrns.add(symbol)
                            symtab[symbol] = {
                                "type": "EXTERNAL",
                                "value": getHashcode(symbol)
                                }
                continue
            elif operation == "EQU":
                if name == "":
                    error(properties, "EQU has no name field")
                    continue
                oldValue = None
                if name in symtab:
                    if symtab[name]["type"] != "EQU":
                        error(properties, "EQU name already in use: %s" % name)
                        continue
                    oldValue = symtab[name]["value"]
                ast = parserASM(operand, "equOperand")
                if ast == None:
                    error(properties, "Cannot parse operand of EQU")
                    continue
                err, v = evalInstructionSubfield(properties, "v", ast, symtab)
                if err:
                    error(properties, "Cannot evaluate EQU")
                    continue
                if oldValue not in [None, v]:
                    error(properties, "EQU value of %s changed: %d -> %d" % \
                          (name, oldValue, value))
                    continue
                symtab[name] = {
                    "type": "EQU",
                    "value": v
                    }
                continue
            # For EXTRN see ENTRY.
            elif operation == "LTORG":
                commonProcessing(8)
                continue
            elif operation in ["USING", "DROP"]:
                ast = parserASM(operand, "expressions")
                if ast == None or "r" not in ast or not isinstance(ast["r"], list):
                    error(properties, "Cannot parse operand of " + operation)
                    continue
                rlist = ast["r"]
                for i in range(len(rlist)):
                    rlist[i] = evalArithmeticExpression(rlist[i], {}, \
                                                        properties, \
                                                        symtab, currentHash())
                if operation == "USING":
                    if len(rlist) < 1 or rlist[0] == None:
                        error(properties, "Bad location")
                        continue
                    else:
                        h = rlist.pop(0)
                section, address = unhash(h)
                for r in rlist:
                    if r == None or r < 0 or r > 7:
                        error(properties, "Bad register number")
                    elif operation == "USING":
                        using[r] = (h, section, address)
                        h += 4096
                        address += 4096
                    else: # DROP
                        using[r] = None
                continue
            
            #******** Partial Alignment ********
            # The System/360 assembly-language manual claims that *some* data
            # (such as C'...' and X'...' data in `DC` pseudo-ops) is 
            # unaligned ... i.e., aligned to byte boundaries.  This is misleading.  
            # All `DC`, `DS`, and all instructions must minimally be aligned
            # halfword boundaries.  We know this if only because the 
            # addresses printed in assembly listings are all halfword addresses
            # rather than byte addresses.  I presume that the manual's claim
            # is really referring to suboperands beyond the first suboperand
            # when a single `DC` or `DS` has multiple suboperands in its 
            # operand.  Regardless, we should align to the halfword now.
            sects[sect]["pos1"] += sects[sect]["pos1"] & 1
            
            #******** Process instruction ********
            
            # For our purposes, pseudo-ops like `DS` and `DC` that can have labels,
            # modify memory, and move the instruction pointer are "instructions".
            
            if operation in ["DC", "DS"]:
                ast = parserASM(operand, operation.lower() + "Operands")
                if ast == None:
                    error(properties, "Cannot parse %s operand" % operation)
                    continue
                flattened = astFlattenList(ast)
                dcBufferPtr = 0
                # At this point, `flattened` should be a list with one entry for
                # each suboperand.  Those suboperands are in the form of 
                # dicts with the keys:
                #    'd'    duplication factor
                #    't'    type
                #    'l'    length modifier
                #    'v'    value
                # Each of these fields will itself be an AST.  The descriptions
                # of how these things are supposed to be interpreted is in the
                # length section "DC -- DEFINE CONSTANT" (pdf p. 46, numbered
                # p. 36) of the assembly-language manual (GC28-6514-8).
                for suboperand in flattened:
                    if suboperand["d"] == []:
                        duplicationFactor = 1
                    else:
                        duplicationFactor = \
                            evalArithmeticExpression(suboperand["d"], {}, \
                                                     properties)
                        if duplicationFactor == None:
                            error(properties, "Could not evaluate duplication factor")
                            continue
                    try:
                        suboperandType = suboperand["t"][0]
                    except:
                        error(properties, "Suboperand type not specified")
                        continue
                    if suboperand["l"] == []:
                        lengthModifier = None
                    else:
                        lengthModifier = \
                            evalArithmeticExpression(suboperand["l"], {}, \
                                                     properties)
                        if lengthModifier == None:
                            error(properties, "Count not evaluate length modifier")
                            continue
                    astValue = suboperand["v"]
                    if suboperandType == "C":
                        commonProcessing(1)
                        
                        pass
                    elif suboperandType == "X":
                        commonProcessing(1)
                        # Adjust the string to have an even number of digits,
                        # 0-padded or truncated to the length modifier, if any.
                        try:
                            hexString = flattened[0]["v"][0][1]
                            if lengthModifier == None:
                                count = len(hexString)
                                count += (count % 1)
                            else:
                                count = lengthModifier * 2
                            while len(hexString) < count:
                                hexString = "0" + hexString
                            hexString = hexString[-count:]
                        except:
                            error(properties, "Cannot parse X value")
                            continue
                        # Deal with memory.
                        if operation == "DC":
                            bytes = bytearray()
                            for i in range(0, count, 2):
                                b = hexString[i:i+2]
                                bytes.append(int(b, 16))
                            toMemory(bytes)
                        else:
                            toMemory(count // 2)
                    elif suboperandType == "B":
                        commonProcessing(1)
                        
                        pass
                    elif suboperandType in ["F", "H"]:
                        if suboperandType == "H":
                            length = 2
                            mask = 0xFFFF
                        else:
                            length = 4
                            mask = 0xFFFFFFFF
                        if lengthModifier != None:
                            commonProcessing(1)
                        else:
                            commonProcessing(length)
                        if lengthModifier != None:
                            pass
                        if operation == "DC":
                            for exp in suboperand["v"]:
                                v = int(exp[1]) & mask
                                j = (length - 1) * 8
                                for i in range(length):
                                    dcBuffer[dcBufferPtr] = (v >> j) & 0xFF
                                    dcBufferPtr += 1
                                    j -= 8
                            length = dcBufferPtr
                            while duplicationFactor > 1:
                                for i in range(length):
                                    dcBuffer[dcBufferPtr] = dcBuffer[i]
                                    dcBufferPtr += 1
                            toMemory(dcBuffer[:dcBufferPtr])
                            continue
                        toMemory(duplicationFactor * length)
                    elif suboperandType == "E":
                        commonProcessing(1)
                        if lengthModifier != None:
                            pass
                        if operation == "DC":
                            pass
                        
                        toMemory(duplicationFactor * 4)
                    elif suboperandType == "D":
                        commonProcessing(1)
                        if lengthModifier != None:
                            pass
                        if operation == "DC":
                            pass
                        
                        toMemory(duplicationFactor * 8)
                    elif suboperandType == "A":
                        commonProcessing(1)
                        if lengthModifier != None:
                            pass
                        if operation == "DC":
                            pass
                        
                        toMemory(duplicationFactor * 4)
                    elif suboperandType == "Y":
                        if lengthModifier != None:
                            commonProcessing(1)
                        else:
                            commonProcessing(2)
                        if lengthModifier != None:
                            pass
                        if operation == "DC":
                            for exp in suboperand["v"]:
                                v = evalArithmeticExpression(exp, {}, \
                                                             properties, \
                                                             symtab, \
                                                             currentHash())
                                if v == None:
                                    error(properties, "Cannot evaluate Y-type constant")
                                    v = 0
                                dcBuffer[dcBufferPtr] = (v >> 8) & 0xFF
                                dcBufferPtr += 1
                                dcBuffer[dcBufferPtr] = v & 0xFF
                                dcBufferPtr += 1
                            length = dcBufferPtr
                            while duplicationFactor > 1:
                                for i in range(length):
                                    dcBuffer[dcBufferPtr] = dcBuffer[i]
                                    dcBufferPtr += 1
                            toMemory(dcBuffer[:dcBufferPtr])
                            continue
                        toMemory(duplicationFactor * 2)
                    else:
                        error(properties, 
                              "Unsupported DC/DS type %s" % suboperandType)
                        continue
                continue
            
            if operation in argsRR:
                commonProcessing(2)
                if not compile:
                    toMemory(2)
                    continue
                data = bytearray(2)
                ast = parserASM(operand, "rrAll")
                if ast != None:
                    # Make sure we trap some special mnemonics:
                    if operation in ["SPM", "NOPR"]:
                        err = "R1" in ast
                        r1 = 0
                    elif operation == "BR":
                        err = "R1" in ast
                        r1 = 7
                    else:
                        err, r1 = evalInstructionSubfield(properties, "R1", \
                                                          ast, symtab)
                    if not err and r1 >= 0 and r1 <= 7:
                        err, r2 = evalInstructionSubfield(properties, "R2", ast, symtab)
                        limit = 7
                        if operation in ["LFXI", "LFLI"]:
                            limit = 15
                        if not err and r2 >= 0 and r2 <= limit:
                            op = argsRR[operation]
                            data[0] = ((op & 0b111110) << 2) | r1
                            data[1] = 0b11100000 | ((op & 1) << 3) | r2
                toMemory(data)
                continue
                
            if operation in argsSRSorRS:
                commonProcessing(2)
                '''
                We have a conundrum here.  For the mnemonics in argsSRSandRS
                there is both an RS version of the instruction
                (2 halfwords) and an SRS version of the instruction (1 halfword).
                All of the SRS versions could be encoded as the RS version 
                without functional difficulty, I think, but aren't (presumably
                to save a little memory).  There's no syntactic difference.
                The old assembler decided, I guess, based on the size of D2:
                    0 <= DS < 56         -> SRS
                    56 <= DS             -> RS
                But we can't always determine the size of DS in earlier passes, 
                because it may involve unresolved forward references.
                Or in other words, we often cannot determine the size of the
                instruction without already knowing the size of the instruction.
                ***FIXME***
                '''
                if collect:
                    dataSize = 4
                else:
                    dataSize = properties["length"]
                if operation in branchAliases or operation in argsSRSonly:
                    dataSize = 2
                if not compile:
                    toMemory(dataSize)
                    continue
                data = bytearray(dataSize)
                ast = parserASM(operand, "rsAll")
                if ast != None:
                    err, r1 = evalInstructionSubfield(properties, "R1", ast, symtab)
                    if r1 == None:
                        # R1 is syntatically omitted for various instructions,
                        # and an implied R1 is used instead.
                        if operation == "SVC":
                            r1 = 1
                        elif operation in ["SSM", "TS", "LDM", "STDM"]:
                            r1 = 0
                        elif operation in branchAliases:
                            r1 = branchAliases[operation]
                        else:
                            # No matches, fall through to other types of instsructions.
                            pass
                    if r1 != None:
                        err, d2 = evalInstructionSubfield(properties, "D2", ast, symtab)
                        if not err: 
                            if d2 != None:
                                properties["adr1"] = d2 & 0xFFFF
                            err, b2 = evalInstructionSubfield(properties, "B2", ast, symtab)
                            if not err: 
                                err, x2 = evalInstructionSubfield(properties, "X2", ast, symtab)
                                if not err:
                                    done = False
                                    forceRS = (operation in argsRSonly)
                                    if operation == "CE":
                                        print("***DEBUG***")
                                    if operation in branchAliases:
                                        d = d2 - (currentHash() + 1)
                                        if d >= 0 and d < 0b111000:
                                            opcode = argsSRSonly["BCF"]
                                            data[0] = ((opcode & 0b1111100000) >> 2) | r1
                                            d = d & 0b111111
                                            data[1] = (d << 2) | 0b00
                                            if "adr1" in properties and \
                                                    properties["adr1"] != d:
                                                properties["adr2"] = d
                                            done = True
                                        elif d < 0 and d >= -0b111000:
                                            opcode = argsSRSonly["BCB"]
                                            data[0] = ((opcode & 0b1111100000) >> 2) | r1
                                            d = (-d & 0b111111)
                                            if "adr1" in properties and \
                                                    properties["adr1"] != d:
                                                properties["adr2"] = d
                                            data[1] = (d << 2) | 0b10
                                            done = True
                                        else:
                                            operation = "BC"
                                            forceRS = True
                                    if not done:
                                        if b2 == None:
                                            b2,newd2 = findB2D2(d2)
                                            if b2 == None:
                                                if (d2 & hashMask) == symtab[sect]["value"]:
                                                    b2 = 3
                                                    forceRS = True
                                            else:
                                                d2 = newd2
                                        opcode = argsSRSorRS[operation]
                                        hd2 = d2
                                        if (opcode & 0b1000000000) == 0 and \
                                                operation not in fpOperations \
                                                and d2 != None:
                                            # I believe (undocumented, I think)
                                            # that the most-significant bit of the
                                            # opcode determines whether it's a
                                            # "fullword instruction" (0) or a 
                                            # "halfword instruction" (1).  In the
                                            # former case, the displacement is in
                                            # units of fullwords, whereas we've
                                            # provided it in terms of halfwords.
                                            d2 = (d2 & hashMask) | ((d2 & 0xFFFFFFFF) // 2)
                                        if b2 == None and d2 == None:
                                            error(properties, "Cannot determine D2(B2)")
                                        elif not forceRS and b2 != None and \
                                                b2 >= 0 and b2 <= 3 and \
                                                (d2 < 56 or len(data) == 2):
                                            data = data[:2]
                                            data[0] = ((argsSRSorRS[operation] & 0b1111100000) >> 2) | r1
                                            data[1] = 0xFF & ((d2 << 2) | b2)
                                            if "adr1" in properties and \
                                                    properties["adr1"] != hd2:
                                                properties["adr2"] = hd2
                                        else:
                                            if b2 == None:
                                                b2 = 3
                                            elif b2 == 3:
                                                d2 -= currentHash() + 2
                                            data[0] = ((opcode & 0b1111100000) >> 2) | r1
                                            data[1] = ((opcode & 0b11111) << 3) | b2
                                            # I notice that the original assembler
                                            # sometimes encoded with AM=1, whereas
                                            # I would use AM=0 (because no X2 was
                                            # specified in the source code).  This
                                            # is okay behaviorally as long as no
                                            # @ or # is in the mnemonic and D2
                                            # is small enough to fit in 11 bits.
                                            # As near as I can see, this happens
                                            # with floating-point instructions, 
                                            # though I have no rational for it.
                                            ia = "@" in operation
                                            i =  "#" in operation
                                            if x2 == None and not ia and not i \
                                                    and d2 <= 0b11111111111 and \
                                                    operation in fpOperations:
                                                x2 = 0
                                            if x2 == None:
                                                data[2] = (d2 & 0xFF00) >> 8
                                            else:
                                                if x2 < 0 or x2 > 7:
                                                    error(properties, "X2 out of range")
                                                else:
                                                    data[1] |= 0b100
                                                    data[2] = (x2 << 5) | \
                                                              (ia << 4) | \
                                                              (i << 3) | \
                                                              ((d2 & 0x700) >> 8)
                                            data[3] = d2 & 0xFF
                                            d2 &= 0xFFFF
                                            if "adr1" in properties and \
                                                    properties["adr1"] != d2:
                                                properties["adr2"] = d2
                toMemory(data)
                continue
                
            if operation in argsRI:
                commonProcessing(2)
                if not compile:
                    toMemory(4)
                    continue
                data = bytearray(4)
                ast = parserASM(operand, "riAll")
                if ast != None:
                    err, r2 = evalInstructionSubfield(properties, "R2", ast, symtab)
                    if not err and r2 >= 0 and r2 <= 7: 
                        err, i1 = evalInstructionSubfield(properties, "I1", ast, symtab)
                        if not err: 
                            if i1 != None:
                                properties["adr2"] = i1 & 0xFFFF
                            if operation == "SHI":
                                i1 = -i1
                                operation = "AHI"
                            if operation == "LHI":
                                # LHI is not actually an RI instruction, though
                                # it is RI syntactically, but
                                # rather an alias for LA (an RS instruction)
                                # with special field values.
                                op = argsSRSorRS["LA"]
                                data[0] = (op << 3) | r2
                                data[1] = 0b11110011 # AM=0, B2=11
                                
                            else:
                                op = argsRI[operation]
                                data[0] = (op & 0b1111111100000) >> 5
                                data[1] = ((op & 0b11111) << 3) | r2
                            i1 &= 0xFFFF
                            data[2] = i1 >> 8
                            data[3] = i1 & 0xFF
                toMemory(data)
                continue
                
            if operation in argsSI:
                commonProcessing(2)
                if not compile:
                    toMemory(4)
                    continue
                data = bytearray(4)
                ast = parserASM(operand, "siAll")
                if ast != None:
                    err, d2 = evalInstructionSubfield(properties, "D2", ast, symtab)
                    if not err:
                        if d2 != None:
                            properties["adr1"] = d2 & 0xFFFF
                        err, b2 = evalInstructionSubfield(properties, "B2", ast, symtab)
                        if not err and b2 >= 0 and b2 <= 3:
                            err, i1 = evalInstructionSubfield(properties, "I1", ast, symtab)
                            i1 &= 0xFFFF
                            properties["adr2"] = i1
                            d2 &= 0b111111
                            op = argsSI[operation]
                            data[0] = op
                            data[1] = (d2 << 2) | b2
                            data[2] = i1 >> 8
                            data[3] = i1 & 0xFF
                toMemory(data)
                continue
                
            if operation in argsMSC:
                # MSC operations are really standardized enough for there to be
                # any advantage in segregating them this way, but it might provide
                # some clarity in maintenance to do so.
                commonProcessing(2)
                ast = parserASM(operand, "mscAll")
                if ast != None:
                    toMemory(bytearray(4))
                    continue
                
            if operation in argsBCE:
                # BCE operations are really standardized enough for there to be
                # any advantage in segregating them this way, but it might provide
                # some clarity in maintenance to do so.
                commonProcessing(2)
                ast = parserASM(operand, "bceAll")
                if ast != None:
                    toMemory(bytearray(4))
                    continue
                
            error(properties, "Unrecognized line")
            continue
        
        if collect:
            for sect in sects:
                optimizeScratch()
    
    return metadata
