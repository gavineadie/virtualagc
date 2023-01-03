#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Copyright:      None - the author (Ron Burkey) declares this software to
                be in the Public Domain, with no rights reserved.
Filename:       executePALMAT.py
Purpose:        This is a VM (admittedly, and inefficient one) for 
                running PALMAT code generated by compilation of 
                HAL/S source code.
History:        2023-01-01 RSB  Began.
"""

import re
import math
import random
from decimal import Decimal, ROUND_HALF_UP

# This is a replacement for Python's round() function.
# Python's round() function uses a method apparently called 
# "banker's rounding", in which everything rounds just as you'd
# expect except that numbers which are *exactly* integer+1/2
# round (from my perspective) very oddly: they round to the
# nearest *even* integer.  For example, 1.5 and 2.5 both round
# to 2, 3.5 and 4.5 both round to 4, and so on. As far as HAL/S
# is concerned, the documentation isn't 100% explicit in this
# regard, but the explanations on p. 3-4 (PDF p. 42) of 
# "Programming in HAL/S" make it pretty clear that banker's 
# rounding is *not* what was envisaged; 0.5 is supposed to round
# to 1, 3.5 is supposed to round to 4.  (What's left undiscussed
# are cases like -1.5 or -2.5.  Oh well!)  Therefore, the following
# function is provided to account for rounding that's closer to
# what's needed.  I think!
def hround(x):
    return int(Decimal(x).to_integral_value(rounding=ROUND_HALF_UP))

# Categorization of the HAL/S built-in functions by the number of arguments
# they take.
builtIns = [
    # No arguments
    ["CLOCKTIME", "DATE", "ERRGRP", "ERRNUM", "PRIO", "RANDOM", "RANDOMG", 
     "RUNTIME"],
    # One argument
    ["ABS", "CEILING", "FLOOR", "ODD", "ROUND", "SIGN", "SIGNUM", "TRUNCATE",
     "ARCCOS", "ARCCOSH", "ARCSIN", "ARCSINH", "ARCTAN", "ARCTANH", "COS",
     "COSH", "EXP", "LOG", "SIN", "SINH", "SQRT", "TAN", "TANH",
     "ABVAL", "DET", "INVERSE", "TRACE", "TRANSPOSE", "UNIT",
     "MAX", "MIN", "PROD", "SUM", "LENGTH", "TRIM", "NEXTIME", "SIZE"],
    # Two arguments
    ["DIV", "MOD", "REMAINDER", "ARCTAN2", "XOR", "INDEX", "LJUST", "RJUST",
     "SHL", "SHR"],
    # Three arguments
    ["MIDVAL"]
]

def executePALMAT(PALMAT, trace = False, indent=0):
    scopes = PALMAT["scopes"]
    scopeNumber = len(scopes) - 1
    scope = scopes[scopeNumber]
    identifiers = scope["identifiers"]
    instructions = scope["instructions"]
    if len(instructions) < 1:
        return
    computationStack = []
    for instruction in instructions:
        if trace:
            print("\t==>", computationStack, instruction)
        stackSize = len(computationStack)
        if "string" in instruction:
            computationStack.append(instruction["string"])
        elif "number" in instruction:
            stringifiedNumber = instruction["number"]
            multiplier = 1.0
            # Recall that HAL/S literal numbers can include modifiers like
            # "B-12" or "H7" in addition to the usual "E23".  Python
            # has no knowledge of these additional funky modifiers, so
            # we have to handle them explicitly.  Unfortunately this 
            # can make the numerical version inexact compared to the 
            # stringified version, and not inexact in the same way as 
            # the original IBM 360 or AP-101S representations were. 
            # At some point I'll probably make the compiler do this work
            # for the sake of efficiency, but right now I'm going for 
            # correctness and leaving efficiency optimizations for later.
            while True:
                match = re.search("[BH][-]?[0-9]+$", stringifiedNumber)
                if match == None:
                    break
                modifier = match.group()
                stringifiedNumber = stringifiedNumber[:match.span()[0]]
                if modifier[0] == "B":
                    multiplier *= 2 ** (int(modifier[1:]))
                else: # modifier[0] == "H":
                    multiplier *= 16 ** (int(modifier[1:]))
            computationStack.append(float(stringifiedNumber) * multiplier)   
        elif "operator" in instruction:
            operator = instruction["operator"]
            if operator in ["U-"]: # Unary operators.
                if stackSize < 1:
                    print("Implementation error, not enough operands for operator \"%s\"" % operator)
                    break
                operand = computationStack[-1]
                if operator == "U-":
                    result = -operand
                else:
                    print("Implementation error, unary operator \"%s\" not yet implemented" % operator)
                    break
                computationStack[-1] = result
            elif operator in ["+", "-", "", "/", "**", ".", "*", "C||"]: # binary operators.
                if stackSize < 2:
                    print("Implementation error, not enough operands for operator \"%s\"" % operator)
                    break
                operand1 = computationStack[-1]
                operand2 = computationStack[-2]
                computationStack.pop()
                if operator == "+":
                    result = operand1 + operand2
                elif operator == "-":
                    result = operand1 - operand2
                elif operator == "":
                    result = operand1 * operand2
                elif operator == "/":
                    result = operand1 / operand2
                elif operator == "**":
                    result = operand1 ** operand2
                elif operator == "C||": # string concatenation.
                    result = operand1 + operand2
                else:
                    print("Implementation error, binary operator \"%s\" not yet implemented" % operator)
                computationStack[-1] = result
            else:
                print("Implementation error, unknown binary operator \"%s\"" % operator)
                break
        elif "fetch" in instruction or "store" in instruction:
            erroredUp = False
            if "fetch" in instruction:
                identifier = instruction["fetch"]
                fetch = True
            else:
                identifier = instruction["store"]
                fetch = False
            identifier = "^" + identifier + "^"
            for s in reversed(scopes):
                if identifier in s["identifiers"]:
                    erroredUp = True
                    if fetch:
                        if "value" not in s["identifiers"][identifier]:
                            print("Identifier %s uninitialized" % identifier)
                            break
                        computationStack.append(s["identifiers"][identifier]["value"])
                    else: # store
                        if len(computationStack) < 1:
                            print("Implementation error, stack empty for STORE instruction")
                            break
                        value = computationStack[-1]
                        attributes = s["identifiers"][identifier]
                        if isinstance(value, str):
                            if "character" not in attributes:
                                print("Cannot store string in non-CHARACTER variable.")
                                break
                            maxlen = attributes["character"]
                            value = value[:maxlen]
                        elif isinstance(value, bool):
                            if "bit" not in attributes:
                                print("Cannot store bit/boolean in non-bit/boolean variable.")
                                break
                        elif isinstance(value, (float, int)):
                            if "scalar" not in attributes and "integer" not in attributes:
                                print("Cannot store arithmetic value in non-integer/scalar variable.")
                                break
                            if "integer" in attributes:
                                value = hround(value)
                            elif "scalar" in attributes:
                                value = float(value)
                        else:
                            print("Implementation error, non-boolean/character/arithmetic not yet implemented.")
                            break
                        attributes["value"] = value
                    break
            if not erroredUp:
                print("Identifier %s not in any accessible scope" % identifier)
                break
        elif "pop" in instruction:
            value = instruction["pop"]
            if value <= stackSize:
                while value > 0:
                    computationStack.pop()
                    value -= 1
            else:
                print("Implementation error, too many POPs: %d vs %d" \
                      % (value, stackSize))
                break
        elif "write" in instruction:
            lun = instruction["write"]
            if lun == '6':
                print("%*s" % (indent, ""), end="")
                while len(computationStack) > 0:
                    value = computationStack.pop()
                    if isinstance(value, bool):
                        if value:
                            print(" TRUE ", end="")
                        else:
                            print(" FALSE ", end="")
                    elif isinstance(value, (int, float)):
                        print(" %s " % str(value), end="")
                    else:
                        print(value, end="")
                print()
        elif "function" in instruction:
            function = instruction["function"]
            # First check all of the no-argument functions.
            if function in builtIns[0]:
                if function == "RANDOM":
                    # Note that this returns a number in the range [0, 1),
                    # and therefore cannot return exactly 1.  The HAL/S
                    # documentation isn't entirely clear whether values
                    # that are *exactly* 0 or 1 should be returned.
                    computationStack[-1] = random.random()
                if function == "RANDOMG":
                    computationStack[-1] = random.gauss()
                else:
                    print("Implemented HAL/S built-in function", function)
                    break
            # Now all of the one-argument functions.
            elif function in builtIns[1]:
                if stackSize < 1:
                    print("Not enough arguments on stack for function", function)
                    break
                operand = computationStack[-1]
                if function == "ABS":
                    computationStack[-1] = abs(operand)
                elif function == "CEILING":
                    computationStack[-1] = math.ceil(operand)
                elif function == "FLOOR":
                    computationStack[-1] = math.floor(operand)
                elif function == "ROUND":
                    operand = hround(operand)
                    computationStack[-1] = hround(operand)
                elif function == "SIGN":
                    if operand >= 0:
                        computationStack[-1] = 1
                    else:
                        computationStack[-1] = -1
                elif function == "SIGNUM":
                    if operand > 0:
                        computationStack[-1] = 1
                    elif operand < 0:
                        computationStack[-1] = -1
                    else:
                        computationStack[-1] = 0
                elif function == "TRUNCATE":
                    if operand >= 0:
                        computationStack[-1] = math.floor(operand)
                    else:
                        computationStack[-1] = math.ceil(operand)
                elif function == "ARCCOS":
                    computationStack[-1] = math.acos(operand)
                elif function == "ARCCOSH":
                    computationStack[-1] = math.acosh(operand)
                elif function == "ARCSIN":
                    computationStack[-1] = math.asin(operand)
                elif function == "ARCSINH":
                    computationStack[-1] = math.asinh(operand)
                elif function == "ARCTAN":
                    computationStack[-1] = math.atan(operand)
                elif function == "ARCTANH":
                    computationStack[-1] = math.atanh(operand)
                elif function == "COS":
                    computationStack[-1] = math.cos(operand)
                elif function == "COSH":
                    computationStack[-1] = math.cosh(operand)
                elif function == "SIN":
                    computationStack[-1] = math.sin(operand)
                elif function == "SINH":
                    computationStack[-1] = math.sinh(operand)
                elif function == "TAN":
                    computationStack[-1] = math.tan(operand)
                elif function == "TANH":
                    computationStack[-1] = math.tanh(operand)
                elif function == "EXP":
                    computationStack[-1] = math.exp(operand)
                elif function == "LOG":
                    computationStack[-1] = math.log(operand)
                elif function == "SQRT":
                    computationStack[-1] = math.sqrt(operand)
                elif function == "LENGTH":
                    # The operand is a string.
                    computationStack[-1] = len(operand)
                elif function == "TRIM":
                    computationStack[-1] = operand.strip()
                elif function == "ODD":
                    # Note that this function returns a boolean.
                    operand = hround(operand)
                    if (operand & 1) == 0:
                        computationStack[-1] = False
                    else:
                        computationStack[-1] = True
                else:
                    print("Implemented HAL/S built-in function", function)
                    break
            # Now all of the two-argument functions.
            elif function in builtIns[2]:
                if stackSize < 2:
                    print("Not enough arguments on stack for function", function)
                    break
                operand1 = computationStack.pop()
                operand2 = computationStack[-1]
                if function == "DIV":
                    computationStack[-1] = hround(operand1) // hround(operand2)
                elif function == "REMAINDER":
                    operand1 = hround(operand1)
                    operand2 = hround(operand2)
                    computationStack[-1] = operand1 % operand2 
                    if operand1 * operand2 < 0:
                        computationStack[-1] -= operand2
                elif function == "MOD":
                    value = operand1 % operand2
                    if operand2 < 0:
                        value -= operand2
                    computationStack[-1] = value
                elif function == "ARCTAN2":
                    computationStack[-1] = math.atan2(operand2, operand1)
                elif function == "XOR":
                    computationStack[-1] = operand1 ^ operand2
                elif function == "SHL":
                    operand1 = hround(operand1)
                    operand2 = hround(operand2)
                    computationStack[-1] = operand1 << operand2
                elif function == "SHR":
                    operand1 = hround(operand1)
                    operand2 = hround(operand2)
                    computationStack[-1] = operand1 >> operand2
                elif function == "INDEX":
                    # So operand1 and operand2 are strings here.  In Python,
                    # the character positions within the string are numbered
                    # from 0 (with -1 being "not present"), while in HAL/S
                    # they are numbered from 1 (with 0 being "not present").
                    computationStack[-1] = 1 + operand1.find(operand2)
                elif function == "LJUST":
                    # operand1 is a string, operand2 is a positive integer.
                    if operand2 < len(operand1):
                        computationStack[-1] = operand1[:operand2]
                        # This is also supposed to signal an error, which
                        # I have no idea about right now, so I'll have to come
                        # back to it later.
                        # TBD
                    else:
                        computationalStack[-1] = "%*s" % (-operand2, operand1)
                elif function == "RJUST":
                    # operand1 is a string, operand2 is a positive integer.
                    if operand2 < len(operand1):
                        computationStack[-1] = operand1[:operand2]
                        # This is also supposed to signal an error, which
                        # I have no idea about right now, so I'll have to come
                        # back to it later.
                        # TBD
                    else:
                        computationalStack[-1] = "%*s" % (operand2, operand1)
                else:
                    print("Implemented HAL/S built-in function", function)
                    break
            # Now all of the two-argument functions.
            elif function in builtIns[3]:
                if stackSize < 3:
                    print("Not enough arguments on stack for function", function)
                    break
                operand1 = computationStack.pop()
                operand2 = computationStack.pop()
                operand3 = computationStack[-1]
                if function == "MIDVAL":
                    if operand1 > operand2:
                        operand1, operand2 = operand2, operand1
                    # We now have operand1 <= operand2.
                    if operand3 <= operand1:
                        computationStack[-1] = operand1
                    elif operand3 >= operand2:
                        computationStack[-1] = operand2
                    else:
                        computationStack[-1] = operand3
                else:
                    print("Implemented HAL/S built-in function", function)
                    break
            else:
                print("Implementation error, function", function)
                break
        else:
            print("Implementation error, unknown PALMAT:", instruction)
            break
    if trace:
        print("\t==>", computationStack, "(end)")