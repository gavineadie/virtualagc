#!/usr/bin/env python3
'''
License:    The author, Ron Burkey, declares this program to be in the Public
            Domain, and may be used or modified in any way desired.
Filename:   xplBuiltins.py
Purpose:    This is part of the port of the original XPL source code for 
            HAL/S-FC into Python.  It contains what might be thought of as the
            global variables accessible by all other source files.
Contact:    The Virtual AGC Project (www.ibiblio.org/apollo).
History:    2023-09-07 RSB  Split the former g.py into two files, this one
                            (xplBuiltins.py) containing just functions, and g.py
                            (which continues to contain all of the variables
                            and constants).
'''

import sys
from time import time_ns
from datetime import datetime
from decimal import Decimal, ROUND_HALF_UP
import json
import math
import ebcdic

sourceFile = None  # Use stdin by default for HAL/S source-code file.
outUTF8 = True
for parm in sys.argv[1:]:
    if parm.startswith("--hal="):
        sourceFile = parm[6:]
    elif parm == "--ascii":
        outUTF8 = False
    elif parm == "--utf8":
        outUTF8 = True


# Python's native round() function uses a silly method (in the sense that it is
# unlike the expectation of every programmer who ever lived) called 'banker's
# rounding', wherein half-integers sometimes round up and sometimes
# round down.  Good for bankers, I suppose, because rounding errors tend to
# sum to zero, but no help whatever for us.  Instead, hround() rounds
# half-integers upward.  Returns None on error.
def hround(x):
    try:
        i = int(Decimal(x).to_integral_value(rounding=ROUND_HALF_UP))
    except:
        # x wasn't a number.
        return None
    return i


'''
The following stuff is for converting back and forth from Python
numerical values to System/360 double-precision (64-bit) floating 
point.

The IBM documentation I've seen for the floating-point format
is pure garbage.  Fortunately, wikipedia ("IBM hexadecimal 
floating-point") explains it very simply.  Here's what it looks 
like in terms of 8 groups of 8 bits each:
    SEEEEEEE FFFFFFFF FFFFFFFF ... FFFFFFFF
where S is the sign, E is the exponent, and F is the fraction.
Single precision (32-bit) is the same, but with only 3 F-groups. 
The exponent is a power of 16, biased by 64, and thus represents
16**-64 through 16**63. The fraction is an unsigned number, of
which the leftmost bit represents 1/2, the next bit represents
1/4, and so on. 

As a special case, 0 is encoded as all zeroes.

E.g., the 64-bit hexadecimal pair 0x42640000 0x00000000 parses as:
    S = 0 (i.e., positive)
    Exponent = 16**(0x42-0x40) = 16**2 = 2**8.
    Fraction = 0.0110 0100 ...
or in total, 1100100 (binary), or 100 decimal.
'''
twoTo56 = 2 ** 56
twoTo52 = 2 ** 52


# Convert a Python integer or float to IBM double-precision float.  
# Returns as a pair (msw,lsw), each of which are 32-bit integers,
# or (0xff000000,0x00000000) on error.
def toFloatIBM(x):
    d = float(x)
    if d == 0:
        return 0x00000000, 0x00000000
    # Make x positive but preserve the sign as a bit flag.
    if d < 0:
        s = 1
        d = -d
    else:
        s = 0
    # Shift left by 24 bits.
    d *= twoTo56
    # Find the exponent (biased by 64) as a power of 16:
    e = 64
    while d < twoTo52:
        e -= 1
        d *= 16
    while d >= twoTo56:
        e += 1
        d /= 16
    if e < 0:
        e = 0
    if e > 127:
        return 0xff000000, 0x00000000
    # x should now be in the right range, so lets just turn it into an integer.
    f = hround(d)
    # Convert to a more-significant and less-significant 32-word:
    msw = (s << 31) | (e << 24) | (f >> 32)
    lsw = f & 0xffffffff
    return msw, lsw


# Inverse of toFloatIBM(): Converts more-significant and less-significant 
# 32-bit words of an IBM DP float to a Python float.
def fromFloatIBM(msw, lsw):
    s = (msw >> 31) & 1
    e = ((msw >> 24) & 0x7f) - 64
    f = ((msw & 0x00ffffff) << 32) | (lsw & 0xffffffff)
    x = f * (16 ** e) / twoTo56
    if s != 0:
        x = -x
    return x

'''
# Test of the IBM float conversions.  Note that aside from showing that
# toFloatIBM() and fromFloatIBM() are inverses, it also reproduces the 
# known value 100 -> 0x42640000,0x00000000.
for s in range(-1, 2, 2):
    for e in range(-10, 11):
        x = s * 10 ** e
        msw, lsw = toFloatIBM(x)
        y = fromFloatIBM(msw, lsw)
        print(x, "0x%08x,0x%08x" % (msw, lsw), y)
'''

#------------------------------------------------------------------------------
# Here's some stuff intended to functionally replace some of XPL's 'implicitly
# declared' functions and variables while retaining roughly the same syntax.

# Here's are lists of all open "devices", by their "device number". If the 
# device isn't open, then the entry in the inputDevices[] and/or outputDevices[] 
# array(s) is a Python None.  Note that the behavior of output devices 0 and 1
# (both stdout) are hard-coded in the OUTPUT function and bypass the 
# inputDevices[] list entirely.
#
# When there is Python file associated with the device, the value will be a
# Python dictionary structured as follows:
#    {
#        "file":   The associated Python file object,
#        "open":   Boolean (True if open, False if closed),
#        "blob":   If an input file, the entire contents as a list of strings.
#                  If an output file, just None, since output is written 
#                  directly to the file without any buffering.
#        "pds":    If an input file the file contents as a dictionary.
#                  If an output file, just None, since output is written 
#                  directly to the file without any buffering.
#        "random": The file contents as a list of fixed-length Python bytearray
#                  objects.  "Random" files are treated as input/output, and
#                  their contents are both buffered and written to the 
#                  associated file.
#        "reclen": The record length (in bytes) for "random" files.
#        "mem":    For a "pds", the member name last found by MONITOR(2);
#                  not used for a "blob",
#        "ptr":    The index of the last line returned by an INPUT();
#                  for a "blob" it's the index within the file as a whole,
#                  while for a "pds" it's the index within the member,
#        "was":    Set of PDS keys from most-recent read or write to file.
#    }
# The keys "blob", "pds", and "random" are mutually exclusive; one and only one
# of them is present.  For a "pds" dictionary, the dictionary keys are  
# "member names", each of which is precisely 8 characters long (including 
# padding by spaces on the right).  The value associated with a member key is 
# the entire contents of that member as a list of strings.
#
# NOTE: It took me a good long time to figure this out, but the
# input and output "devices" which are accessed via the INPUT and OUTPUT
# statements are *separate* from the random-access files accessed by READ
# and WRITE statements.  What really puzzled me was that device 2 is used for
# outputting LISTING2, whereas file 2 is used for inputting and outputting to
# the LITFILE.  But finally I did figure it out, fortunately.  If you look at
# sample JCL, you'll see that all of these have separate DD cards defining
# them.  We simply open 6 random-access files called "HAL-S-FC.file1" through
# "HAL-S-FC.file2" and then wash our hands of the matter.

# The entries of the files[] array are 3-lists of the open random-access file 
# pointer, the record size, and the current file size (in bytes).
files = [None]
for i in range(1, 7):
    f = open("FILE%d.bin" % i, "w+b")
    f.seek(2, 0)
    files.append([f, 7200, f.tell()])

inputDevices = [None] * 10
outputDevices = [None] * 10

# Open the files that we need, other than output files 0 and 1 (whose behavior
# is hard-coded separately), and buffer their contents where appropriate.
if sourceFile == None:  # HAL/S source code.
    f = sys.stdin
    sourceFile = "stdin"
else:
    # Get the source-file name from the compiler's --hal switch.
    # If the file turns out to not be in the current folder, try several others.
    # This is just a convenience for me in debugging, based on the notion that
    # the compiler is being run from the yaShuttle/ported/ folder in the source 
    # tree.  The other folders don't need to be checked in a production version
    # of the compiler, since they most likely don't even exist.
    folders = (
        ".",
        "../Source Code/Programming in HAL-S",
        "../Source Code/HAL-S-360 Users Manual"
        )
    f = None
    i = 0
    while f == None and i < len(folders):
        try:
            s = folders[i] + "/" + sourceFile
            f = open(s, "r")
            sourceFile = s
            break
        except:
            f = None
            i += 1
    if f == None:
        print("Couldn't find the source file (%s)" % sourceFile, \
              file=sys.stderr)
        sys.exit(1)
dummy = f.readlines()  # Source code.
for i in range(len(dummy)):
    dummy[i] = dummy[i].rstrip('\n\r').replace("¬", "~")\
                        .replace("^", "~").replace("¢", "`").expandtabs(8)\
                        .ljust(80)
inputDevices[0] = {
    "file": f,
    "open": True,
    "ptr":-1,
    "blob": dummy
    }
f = open("LISTING2.hal", "w")  # Secondary output listing
outputDevices[2] = {
    "file": f,
    "open": True,
    "blob": []
    }
f = open("ERRORLIB.json", "r")  # File of error message types.
dummy = json.load(f)
inputDevices[5] = {
    "file": f,
    "open": True,
    "ptr":-1,
    "mem": "",
    "pds": dummy,
    "was": set(dummy.keys())
    }
inputDevices[6] = {  # File of module access rights.
    "file": None,
    "open": False,
    "ptr":-1,
    "mem": "",
    "pds": {},
    "was": set()
    }
f = open("SOURCECO.txt", "w")  # Source-comparision output.
outputDevices[9] = {
    "file": f,
    "open": True,
    "blob": []
    }


def SHL(a, b):
    return a << b


def SHR(a, b):
    return a >> b


# Some of the MONITOR calls are listed beginning on PDF p. 826 of the "HAL/S-FC
# & HAL/S-360 Compiler System Program Description" (IR-182-1).  Note that the
# only function numbers actually appearing in the source code are:
#    0-10, 12, 13, 15-18, 21-23, 31-32
# The latter two aren't mentioned in the documentation.
compilerStartTime = time_ns()
dwArea = None
compilationReturnBits = 0
namePassedToCompiler = ""


def MONITOR(function, arg2=None, arg3=None):
    global inputDevices, outputDevices, dwArea, compilationReturnBits, \
            namePassedToCompiler, files
    
    def error(msg=''):
        if len(msg) > 0:
            msg = '(' + msg + ') '
        print("Error %sin MONITOR(%s,%s,%s)" % \
              (msg, str(function), str(arg2), str(arg3)), file=sys.stderr)
        sys.exit(1)
    
    def close(n):
        global outputDevices
        device = outputDevices[n]
        if isinstance(device, list) and "open" in device and device["open"]: 
            device["file"].close()
            device["open"] = False
        else:
            # print("\nTrying to close device %d, which is not open" % n)
            pass
    
    if function == 0: 
        n = arg2
        close(n)
        
    elif function == 1:
        n = arg2
        member = arg3
        msg = ''
        try:
            msg = "no file"
            device = outputDevices[n]
            file = device["file"]
            msg = "not PDS"
            pds = device["pds"]
            msg = "other"
            was = device["was"]
            if member in was:
                returnValue = 1
            else:
                returnValue = 0
            was.clear()
            was[0:0] = pds.keys()
            file.seek(0)
            j = json.dump(pds, file)
            file.truncate()
            close(n)
            return returnValue
        except: 
            error(msg)
    
    elif function == 2:
        n = arg2
        member = arg3
        msg = ''
        try:
            msg = "not PDS"
            if member in inputDevices[n]["pds"]:
                inputDevices[n]["mem"] = member
                inputDevices[n]["ptr"] = -1
                return 0
            '''
            if n in (4, 7):
                if member in inputDevices[6]["pds"]:
                    inputDevices[6]["mem"] = member
                    return 0
            '''
            return 1
        except:
            error(msg)
        
    elif function == 3: 
        n = arg2
        close(n)
    
    elif function == 4:
        # Change block size of a random-access file.
        files[arg2][1] = arg3
    
    elif function == 5:
        # arg2 must be an array of 32-bit integers.
        dwArea = arg2
    
    elif function == 6:
        # This won't be right if the based variable is anything other than 
        # FIXED ... say if it's strings or multiple fields.  But it does add
        # at least as many array elements as needed.  Any other errors will 
        # have to be caught downstream, since there's simply not enough info
        # supplied to take care of it here.
        array = arg2
        n = arg3
        try:
            while len(array) < n:
                array.append(0)
            return 0
        except:
            error()
    
    elif function == 7:
        array = arg2
        n = arg3
        try:
            while n > 0:
                array.pop(-1)
        except:
            error()
    
    elif function == 8:
        error()
    
    elif function == 9:
        '''
        This is a bit confusing, so let me try to summarize my understanding of
        it.  There are no built-in floating-point operations in XPL nor 
        (apparently) in the 360 CPU, so they're handled in a roundabout way via
        the MONITOR(5,...) and MONITOR(9,...) calls.  MONITOR(5) sets ups a 
        working array in which to hold floating-point operands and results.
        The values are stored in IBM DP floating-point format, each of which
        requires 2 32-bit words, 1 for the most-significant part and 1 for the 
        less-significant part.  The first two entries in the working area
        specified by MONITOR(5) comprise operand0 (and the result), while the 
        second two entries comprise operand1 (if needed). 
        '''
        if dwArea == None:
            print("\nNo MONITOR(5) prior to MONITOR(9)", file=sys.stderr)
            exit(1)
        op = arg2
        try:
            # Get operands from the defined working area, and convert them
            # from IBM floating point to Python floats.
            value0 = fromFloatIBM(dwArea[0], dwArea[1])
            value1 = fromFloatIBM(dwArea[2], dwArea[3])
            # Perform the binary operations.
            if op == 1:
                value0 += value1
            elif op == 2:
                value0 -= value1
            elif op == 3:
                value0 *= value1
            elif op == 4:
                value0 /= value1
            elif op == 5:
                value0 = pow(value0, value1)
            # Or perform the unary operations, which are all trig functions.
            # Unfortunately, the documentation doesn't specify the angular 
            # units.  I assume they're radians.
            elif op == 6:
                value0 = math.sin(value0)
            elif op == 7:
                value0 = math.cos(value0)
            elif op == 8:
                value0 = math.tan(value0)
            elif op == 9:
                value0 = math.exp(value0)
            elif op == 10:
                value0 = math.log(value0)
            elif op == 11:
                value0 = math.sqrt(value0)
            else:
                return 1
            # Convert the result back to IBM floats, and store in working area.
            dwArea[0],dwArea[1] = toFloatIBM(value0)
            return 0
        except:
            return 1
    
    elif function == 10:
        if dwArea == None:
            print("\nNo MONITOR(5) prior to MONITOR(10)", file=sys.stderr)
            exit(1)
        s = arg2
        try:
            dwArea[0],dwArea[1] = toFloatIBM(float(s))
            return 0
        except:
            return 1
    
    elif function == 12:
        p = arg2 # 0 for SP, 8 for DP
        value = fromFloatIBM(dwArea[0], dwArea[1])
        '''
        The "standard" HAL format for floating-point numbers is described on 
        p. 8-3 of "Programming in HAL/S", though unfortunately the number of
        significant digits provided for SP vs DP is not specified and is simply
        said to be implementation dependent.  To summarize the format:
            0.0:        Printed as " 0.0" (notice the leading space.
            Positive:   Printed as " d.ddd...E±ee"
            Negative:   Printed as "-d.ddd...E±ee"
        Given that 2**24 = 16777216 (8 digits) and 2**56 = 72057594037927936
        (17 digits), it should be the case that SP and DP are *fully* accurate
        only to 7 digits and 16 digits respectively.  Moreover, there is always
        exactly 1 digit (non-zero) to the left of the decimal point.  Therefore,
        for SP and DP, it would be reasonable to have 6 and 15 digits to the
        right of the decimal point respectively. (See also yaHAL-S/palmatAux.py.)
        '''
        if value == 0.0:
            return " 0.0"
        if p == 0:
            fpFormat = "%+2.6e"
        else:
            fpFormat = "%+2.15e"
        value = fpFormat % value
        if value[:1] == "+":
            value = " " + value[1:]
        value = value.replace("e", "E")
        return value
    
    elif function == 13:
        # Unneeded
        return 0
    
    elif function == 15:
        # The documented explanation is sheerest gobbledygook.  I think perhaps
        # it's saying that the so-called template library maintains a revision
        # code for each structure template stored in it, and that this function
        # can be used to retrieve that revision code.  All of which is as
        # meaningless to us as it can possibly be.  I return a nonsense value.
        return 32 * 65536 + 0
        
    elif function == 16:
        try:
            orFlag = 0x80 & arg2
            code = 0x7F & arg2
            if orFlag:
                compilationReturnBits |= code
            else:
                compilationReturnBits = code
        except:
            error()
        
    elif function == 17:
        namePassedToCompiler = arg2
        
    elif function == 18:
        return (time_ns() - compilerStartTime) // 10000000
    
    elif function == 21:
        return 1000000000
        
    elif function == 22:
        pass
        
    elif function == 23:
        return "REL32V0   "
    
    elif function == 31:
        # This appears to be related somehow to control of virtual memory,
        # something of which we have no need.
        pass
        
    elif function == 32:  # Returns the 'storage increment', whatever that may be.
        return 16384

'''
The following function replaces the XPL constructs
    OUTPUT(fileNumber) = string
    OUTPUT = string                which is shorthand for OUTPUT(0)=string.
Interpretations:
    fileNumber 0    The assembly listing, on stdout
    fileNumber 1    Same as 0, but the leading character of string is used for 
                    carriage control.
    fileNumber 2    Unformatted source listing (LISTING2).
    fileNumber 3    HALMAT object-file.
    fileNumber 4    For punching duplicate card deck (Pass 4)
    fileNumber 5    SDF (Simulation Data File), a PDS
    fileNumber 6    Structure-template library, a PDS
    fileNumber 8    TBD
    fileNumber 9    Patch from one source version to another, a PDS.
The carriage-control characters mentioned above (for fileNumber 1) may be
the so-called ANSI control characters:
    '_'    Single space the line and print
    '0'    Double space the line and print
    '-'    Triple space the line and print
    '+'    Do not space the line and print (but does return carriage to left!)
    '1'    Form feed
    'H'    Heading line.
    '2'    Subheading line.
    ...    Others
'''
headingLine = ''
subHeadingLine = ''
pageCount = 0
LINE_COUNT = 0
linesPerPage = 59  # Should get this from LINECT parameter.


def OUTPUT(fileNumber, string):
    global headingLine, subHeadingLine, pageCount, LINE_COUNT
    if fileNumber == 0:
        string = ' ' + string
        fileNumber = 1
    if fileNumber == 1:
        ansi = string[:1]
        queue = []
        if ansi == ' ': 
            queue.append('')
        elif ansi == '0': 
            queue.append('')
            queue.append('')
        elif ansi == '-':
            queue.append('')
            queue.append('')
            queue.append('')
        elif ansi == '+':
            # This would overstrike the line.  I.e., it's like a carriage return
            # without a line feed.  But I have no actual way to do that, so we 
            # need to advance to the next line.
            queue.append('')
            pass
        elif ansi == '1':
            LINE_COUNT = linesPerPage
        elif ansi == 'H':
            headingLine = string[1:]
            return
        elif ansi == '2':
            subHeadingLine = string[1:]
            return
        if outUTF8:
            queue.append(string[1:].replace("`", "¢").replace("~", "¬"))
        else:
            queue.append(string[1:])
        for i in range(len(queue)):
            if LINE_COUNT == 0 or LINE_COUNT >= linesPerPage:
                if pageCount > 0:
                    print('\n\f', end='')
                pageCount += 1
                LINE_COUNT = 0
                if len(headingLine) > 0:
                    print(headingLine)
                    LINE_COUNT += 1
                if len(subHeadingLine) > 0:
                    print(subHeadingLine)
                    LINE_COUNT += 1
                if LINE_COUNT > 0:
                    print()
                    LINE_COUNT += 1
            if i < len(queue) - 1:
                print(queue[i])
            else:
                print(queue[i], end='')
    elif fileNumber == 6:
        pass
    elif fileNumber == 8:
        pass
    elif fileNumber in [2, 9]:
        if outputDevices[fileNumber]["open"] and \
                "blob" in outputDevices[fileNumber]:
            f = outputDevices[fileNumber]["file"]
            if outUTF8:
                string = string.replace("`", "¢").replace("~", "¬")
            f.write(string + '\n')
            f.flush()

'''
    fileNumber 0,1  stdin, presumably the source code.
    fileNumber 4    Apparently, includable source consists of members of a
                    PDS, and this device number is attached to such a PDS.
    fileNumber 5    Error library (a PDS).
    fileNumber 6    An access-control PDS, providing acceptable language subsets
    fileNumber 7    For reading in structure templates from PDS.
    
The available documentation doesn't tell us what INPUT() is supposed to return
at the end-of-file or end-of-member, though the XPL code I've looked at 
indicates the following:

    End of PDS member           A zero-length string.  E.g., INTERPRE sets
                                a flag called EOF_FLAG upon encountering such a
                                string.
    
    End of sequential file      A zero-length string.  At least, that's what
                                I see in the READ_CARD procedure, which is 
                                what reads the HAL/S source-code files.  
                                However, it's possible for a sequential file to
                                contain zero-length strings other than at the
                                end, so at least for device 0 (source code),
                                I replace zero-length strings by strings which
                                contain a single blank

'''
asciiEOT = 0x04


def INPUT(fileNumber):
    try:
        file = inputDevices[fileNumber]
        index = file['ptr'] + 1
        if 'blob' in file:
            data = file['blob']
        else:
            mem = file["mem"]
            data = file['pds'][mem]
        if index < len(data):
            file['ptr'] = index
            line = data[index]
            if len(line) == 0:
                line = ' '
            return line[:]
        else:
            return ''
    except:
        return None


# This function either reads a block from a random-access file, or else 
# writes one.  In either case, that data is a bytearray object.  Unfortunately,
# the original XPL used FILE() in one of two forms that give us some 
# problems duplicating the function in Python:
#    FILE(...) = array        # For output
#    array = FILE(...)        # For input
# Realize that in the latter form, we want to overwrite the array in place,
# so just returning the input data as a bytearray isn't going to do that.  
# Our workaround is to call the FILE() function in either of two forms, 
# recognizing the types of the parameters to distinguish between the
# input vs output cases:
#    FILE(fileNumber, recordNumber, array)    # For output
#    FILE(array, fileNumber, recordNumber)    # For input.
# In either case, array must be a bytearray of length equal to reclen, where
# reclen is the record length specified in files[fileNumber] when the file
# was opened, but no check is performed for that or any other error condition.
def FILE(arg1, arg2, arg3):
    global files
    
    if isinstance(arg1, bytearray):
        isInput = True
        inputArray = arg1
        fileNumber = arg2
        recordNumber = arg3
    else:
        isInput = False
        fileNumber = arg1
        recordNumber = arg2
        outputArray = arg3
    
    f = files[fileNumber][0]
    reclen = files[fileNumber][1]
    size = files[fileNumber][2]
    f.seek(recordNumber * reclen, 0)
    if isInput:
        data = bytearray(f.read(reclen))
        for i in range(reclen):
            inputArray[i] = data[i]
        return
    f.write(outputArray)
    if f.tell() > size:
        files[fileNumber][2] = f.tell()

# For XPL's DATE and TIME 'variables'.  DATE = (1000*(year-1900))+DayOfTheYear,
# while TIME=NumberOfCentisecondsSinceMidnight.  The timezone isn't specified
# by the definitions (as far as I know), so we just maintain consistency between
# the DATE and TIME, and use whatever TZ is the default.


def DATE():
    timetuple = datetime.now().timetuple()
    return 1000 * (timetuple.tm_year - 1900) + timetuple.tm_yday


def TIME():
    now = datetime.now()
    return  now.hour * 360000 + \
            now.minute * 6000 + \
            now.second * 100 + \
            now.microsecond // 10000


def SUBSTR(de, ne, ne2=None):
    if ne2 == None:
        return de[ne:]
    return de[ne: ne + ne2]


def STRING(s):
    return str(s)


def LENGTH(s):
    return len(s)


def LEFT_PAD(s, n):
    return s.rjust(n, ' ')

'''
# Replaced by function of same name in HALINCL/COMROUT.
def PAD(s, n):
    if isinstance(s, int):
        s = str(s)
    return s.ljust(n, ' ')
'''


def MIN(a, b):
    return min(a, b)


def MAX(a, b):
    return max(a, b)

# For BYTE() and STRING_GT(), the ebcdic module is used to interconvert between
# strings and EBCDIC bytearrays.

# If s is a string (in our case, always encoded as ASCII), i an integer, and
# b a byte-code, then BYTE() has the following usages:
#    BYTE(s)                Returns byte-value of s[0].
#    BYTE(s,i)              Returns byte-value of s[i].
#    BYTE(s,i,b)            Sets byte-value of s[i] to b.
# Even though our strings are always encoded as ASCII, the byte-values 
# we associate with the individual characters are always EBCDIC.  We 
# therefore have to convert freely back and forth between EBCDIC and ASCII.
# The documentation doesn't recognize the possibility that the string s is 
# empty, and thus doesn't say what is supposed to be returned in that case.
# However, this does sometimes occur.


def BYTE(s, index=0, value=None):
    if not isinstance(s, str):
        print("Implementation error: BYTE called with non-string argument:", \
              s, file = sys.stderr)
        if False:
            0/0 # Just my way of triggering an error for the debugger.
        sys.exit(1)
    if value == None:
        try:
            c = s[index]
            if c == '`':  # Replacement for cent sign
                return 0x4A
            elif c == '~':  # Replacement for logical-not sign
                return 0x5F
            elif c == '\x04':  # Replacement for EOF.
                return 0xFE
            else:  # Everything else.
                return c.encode('cp1140')[0]  # Get EBCDIC byte code.
        except:
            return 0
    if value == 0x4A:  # Replacement for cent sign.
        c = '`'
    elif value == 0x5F:  # Replacement for logical-not sign.
        c = '~' 
    elif value == 0xFE:  # Replacement for EOF.
        c = '\x04'
    else:  # Everything else.
        c = bytearray([value]).decode('cp1140')
    return s[:index] + c + s[index + 1:]

    dummy[i] = dummy[i].rstrip('\n\r').replace("¬", "~")\
                        .replace("^", "~").replace("¢", "`").expandtabs(8)\
                        .ljust(80)


# STRING_GT() is completely undocumented, as far as I know.  I'm going to 
# assume it's a string-comparison operation.  As to whether the particular
# collation sequence is significant or not ...
def STRING_GT(s1, s2):
    return s1.encode('cp1140') > s2.encode('cp1140')


# The following is supposed to give the address in memory of the variable that's
# it's parameter.  Of course, that's specific to the IBM implementation, and
# (perhaps) utterly meaningless to us, so at least for now I'm simply providing
# it as a dummy.  Each "variable" is simply assigned a unique number, from 0
# upward.  This assumes that the variables are simple ... i.e., not arrays.
ADDResses = []


def ADDR(variable):
    global ADDResses
    if variable not in ADDResses:
        ADDResses.append(variable)
    return ADDResses.index(variable)
    
    return 0


# Inserts inline BAL instructions.  Obviously less than useless to us.  
# I'm not sure what to do with it.
def INLINE(arg1=None, arg2=None, arg3=None, arg4=None, arg5=None, \
           arg6=None, arg7=None, arg8=None, arg9=None, arg10=None):
    return

