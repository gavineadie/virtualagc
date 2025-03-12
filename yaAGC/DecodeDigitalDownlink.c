 /*
  Copyright 2005,2009-2010 Ronald S. Burkey <info@sandroid.org>
  
  This file is part of yaAGC.

  yaAGC is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  yaAGC is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with yaAGC; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  
  In addition, as a special exception, Ronald S. Burkey gives permission to
  link the code of this program with the Orbiter SDK library (or with 
  modified versions of the Orbiter SDK library that use the same license as 
  the Orbiter SDK library), and distribute linked combinations including 
  the two. You must obey the GNU General Public License in all respects for 
  all of the code used other than the Orbiter SDK library. If you modify 
  this file, you may extend this exception to your version of the file, 
  but you are not obligated to do so. If you do not wish to do so, delete 
  this exception statement from your version. 
 
  Filename:	DecodeDownlinkList.c
  Purpose:	The DecodeDigitalDownlink function can be used to print out
		a downlink list.  Simply keep feeding it data from channel
		013, 034, and 035 as the data arrives.
  Compiler:	GNU gcc.
  Contact:	Ron Burkey <info@sandroid.org>
  Ref:		http://www.ibiblio.org/apollo/index.html
  Mods:		06/27/05 RSB.	Began.
		06/28/05 RSB.	Rewrote a lot to base the printing on
				arrays of specifications.
		06/30/05 RSB	Now completely configurable at runtime.
		07/01/05 RSB	Now *even more* completely configurable at
				runtime.  Finished LM Coast/Align.
		07/03/05 RSB	Removed the LeftShift and Mask table
				parameters, and replaced with a user-
				definable formatting function.  Completed
				the LM Orbital Maneuvers downlist.
				Completed LM Surface Align downlist.
				Completed LM Rendezvous/Prethrust downlist.
				Completed LM Descent/Ascent downlist.
		07/26/05 RSB	Corrected scaling for all SP quantities.
				(Oops!)  Added CM Powered List..
		07/27/05 RSB	Added CM Program 22 list.
		07/28/05 RSB	Added remainder of CM downlink lists.
		04/07/09 RSB	Added ProcessDownlinkList for overriding
				PrintDownlinkList.  The idea is that its
				default is NULL, in which case PrintDownlinkList
				is used.  If non-NULL, then whateverit points
				to is used in place of PrintDownlinkList.
		11/22/10 RSB    Eliminated a compiler warning I suddenly
				encountered in Ubuntu 10.04.
		03/03/25 RSB	Added `dddConfigure`.
		03/06/25 RSB	Some corrections (or at least changes) to the
				hard-coded downlist specifications.
				Changed interpretation of { -1 } spacers in
				downlists.
		03/08/25 RSB	Increased the width of displayed fields from 20
				to 24.  (See `DISPLAYED_FIELD_WIDTH`.)  The
				new `USE_COLONS` constant can be used to switch
				between the formats VARIABLE=VALUE and
				VARIABLE: VALUE at compile time.
		03/11/25 RSB	Altered on the basis of SHOW_WORD_NUMBERS in
				agc_engine.h.
  
*/

#define DECODE_DIGITAL_DOWNLINK_C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "agc_engine.h"

#define DEBUG_DOWNLIST_SPEC_FILES

//#define FLOAT_SCALE (1.0 / 0x10000000)
#define FLOAT_SCALE (1.0 / 02000000000)
#define S_FLOAT_SCALE (1.0 / 040000)
#define US_FLOAT_SCALE (1.0 / 0100000)
#define PRINT_CSM 1
#define PRINT_LM 2
#define B0 0x1
#define B1 0x2
#define B2 0x4
#define B3 0x8
#define B4 0x10
#define B5 0x20
#define B6 0x40
#define B7 0x80
#define B8 0x100
#define B9 0x200
#define B10 0x400
#define B11 0x800
#define B12 0x1000
#define B13 0x2000
#define B14 0x4000
#define B15 0x8000
#define B16 0x10000
#define B17 0x20000
#define B18 0x40000
#define B19 0x80000
#define B20 0x100000
#define B21 0x200000
#define B22 0x400000
#define B23 0x800000
#define B24 0x1000000
#define B25 0x2000000
#define B26 0x4000000
#define B27 0x8000000
#define B28 0x10000000
#define B29 0x20000000

//--------------------------------------------------------------------------
// Some specific formatting functions for wacky fields.

static char DefaultFormatBuffer[33];

// LM Coast Align -- RR Range.
static char *
FormatRrRange (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  int Radmodes;
  x = GetSP (&DownlinkListBuffer[IndexIntoList], 1);
  Radmodes = DownlinkListBuffer[126];
  if (04 & Radmodes)		// high scale
    x *= 75.04;
  else
    x *= 9.38;
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// LM Coast Align -- RR Range Rate.
static char *
FormatRrRangeRate (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = (DownlinkListBuffer[IndexIntoList] - 017000) * (-0.6278);
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// LM Coast Align -- LR Vx
static char *
FormatLrVx (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = (DownlinkListBuffer[IndexIntoList] - 12288.2) * (-0.6440);
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// LM Coast Align -- LR Vy
static char *
FormatLrVy (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = (DownlinkListBuffer[IndexIntoList] - 12288.2) * (1.212);
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// LM Coast Align -- LR Vz
static char *
FormatLrVz (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = (DownlinkListBuffer[IndexIntoList] - 12288.2) * (0.8668);
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// LM Coast Align -- LR Range.
static char *
FormatLrRange (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  int Radmodes;
  x = GetSP (&DownlinkListBuffer[IndexIntoList], 1);
  Radmodes = DownlinkListBuffer[126];
  if (0400 & Radmodes)		// high scale
    x *= 5.395;
  else
    x *= 1.079;
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// LM AGS Initialization -- LM & CM Epoch
static char *
FormatEpoch (int IndexIntoList, int Scale, Format_t Format)
{
  int Data[2];
  double x;
  Data[0] = DownlinkListBuffer[IndexIntoList];
  Data[1] = DownlinkListBuffer[IndexIntoList + 4];
  x = GetDP (Data, Scale);
  sprintf (DefaultFormatBuffer, "%.10g", x);
  return (DefaultFormatBuffer);
}

// LM AGS Initialization -- Adjust SP scaling depending on 
// Earth vs. Moon.  Assumes that Scale is set for Earth-orbit,
// and adjusts it downward for Moon-orbit.  This is the usual
// situation where there is a difference in earth-moon scaling,
// so this function can be used in a number of cases.
static char *
FormatEarthOrMoonSP (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  int Flagword0;
  Flagword0 = DownlinkListBuffer[76];
  if (04000 & Flagword0)	// MOONFLAG
    Scale /= 4;
  x = GetSP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// Similar, but different flag is used for earth vs. moon
static char *
FormatEarthOrMoonDP (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  int Flagword8;
  Flagword8 = DownlinkListBuffer[84];
  if (02000 & Flagword8)	// LMOONFLG
    Scale /= 4;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.10g", x);
  return (DefaultFormatBuffer);
}

// LM Descent/Ascent --- HMEAS (LR RANGE)
static char *
FormatHMEAS (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.10g", 1.079 * x);
  return (DefaultFormatBuffer);
}

// LM Descent/Ascent --- FC
static char *
FormatGtc (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.10g", 2.817 * x);
  return (DefaultFormatBuffer);
}

// CM (all) -- ADOT vs. OGARATE/OMEGAB, or WBODY vs. OMEGAC
static char *
FormatAdotsOrOga (int IndexIntoList, int Scale, Format_t Format)
{
  static char Unknown[] = "(unknown)";
  int Flagword6, Dapdatr1, Flagword9;
  double fScale, x;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], 1);
  Flagword6 = 060000 & DownlinkListBuffer[84];
  Flagword9 = 0400 & DownlinkListBuffer[87];
  Dapdatr1 = 070000 & DownlinkListBuffer[162];
  if (Flagword6 == 020000)	// RCS DAP
    fScale = 450.0;
  else if (Flagword6 == 040000)	// TVC DAP
    {
      if (IndexIntoList == 20)	// OGARATE
        fScale = 16.0;
      else 			// OMEGAB pitch, yaw, or OMEGAC
        {
	  if (Dapdatr1 == 010000)
	    fScale = 12.5;
	  else if ((Dapdatr1 & 030000) != 020000)
	    return (Unknown);
	  else if (Flagword9 == 0)
	    fScale = 1.0;	// Scaling here relies on data we don't have.
	  else
	    fScale = 6.25;
	}
    }
  else				// No DAP
    return (Unknown);
  sprintf (DefaultFormatBuffer, "%.10g", fScale * x);
  return (DefaultFormatBuffer);
}

// CM CDUT
static char *
FormatCDUT (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.10g", x + 19.7754);
  return (DefaultFormatBuffer);
}

// CM Powered list -- DELVs
static char *
FormatDELV (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.10g", 5.85 * x);
  return (DefaultFormatBuffer);
}

// CM Powered list -- PACTOFF or YACTOFF
static char *
FormatXACTOFF (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = GetSP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.5g", 85.41 * x);
  return (DefaultFormatBuffer);
}

// CM Program 22 -- optics trunnion angle
static char *
FormatOTRUNNION (int IndexIntoList, int Scale, Format_t Format)
{
  int twos;
  double x;
  // Fetch the value, which is in 2's complement.
  twos = DownlinkListBuffer[IndexIntoList];
  if (040000 & twos)
    twos |= ~077777;
  x = twos * S_FLOAT_SCALE * 45 + 19.7754;
  sprintf (DefaultFormatBuffer, "%.5g", x);
  return (DefaultFormatBuffer);
}

// Scales by half.
static char *
FormatHalfDP (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], Scale);
  sprintf (DefaultFormatBuffer, "%.10g", x / 2);
  return (DefaultFormatBuffer);
}

// CM Entry/Update -- RDOT..
static char *
FormatRDOT (int IndexIntoList, int Scale, Format_t Format)
{
  double x;
  x = GetDP (&DownlinkListBuffer[IndexIntoList], 1);
  sprintf (DefaultFormatBuffer, "%.10g", x * 2 * 25766.1973);
  return (DefaultFormatBuffer);
}

//--------------------------------------------------------------------------

// Write the screen buffer to the terminal.

static void
SwriteDefault (void)
{
  int i;
  printf ("\x1b[0;0H");		// ANSI move to top of screen.
  for (i = 0; i < Sheight; i++)
    puts (Sbuffer[i]);
}

// The idea here is that by default, the downlink data is displayed using the
// SwriteDefault function.  However, at runtime this pointer could be replaced
// by any other appropriate function, and the data would be displayed some other
// way.
Swrite_t *SwritePtr = SwriteDefault;

static void
Swrite (void)
{
  int i, j;
  for (i = 0; i < Sheight; i++)
    {
      for (j = 0; j < Swidth; j++)
        if (0 == Sbuffer[i][j])
	  Sbuffer[i][j] = ' ';
      Sbuffer[i][Swidth] = 0;
    }
  (*SwritePtr) ();
}

// Clear the screen buffer.
static int LastRow = 1, LastCol = 1;
static void
Sclear (void)
{
  int i, j;
  LastRow = 1;
  LastCol = 1;
  for (i = 0; i < Sheight; i++)
    for (j = 0; j < Swidth; j++)
      Sbuffer[i][j] = ' ';  
}

//---------------------------------------------------------------------------
// Specifications for the DEFAULT downlink lists.  Originally these hard-coded
// structures of type `DownlinkListSpec_t` were internal to the present
// source-code file, but they have been removed to a separate file for easier
// maintenance.
#include "DecodeDigitalDownlinkHardcodes.c"

// The ACTUAL downlink lists used.  The following array can be modified
// at runtime to get different lists.  Or, the array can be used to get
// pointers to the default lists, which could be modified in-place
// (for example, to have different row,col coordinates).

// The following array entries must correspond to the numerical order
// of the DL_xxx constants.
DownlinkListSpec_t *DownlinkListSpecs[11] = {
  &CmPoweredListSpec, &LmOrbitalManeuversSpec,
  &CmCoastAlignSpec, &LmCoastAlignSpec,
  &CmRendezvousPrethrustSpec, &LmRendezvousPrethrustSpec,
  &CmProgram22Spec, &LmDescentAscentSpec,
  &LmLunarSurfaceAlignSpec, &CmEntryUpdateSpec,
  &LmAgsInitializationUpdateSpec
};

//---------------------------------------------------------------------------
/*
 * Perform certain manipulations on a `DownlinkListSpec_t` structure to
 * improve the viewing experience.  The potential cleanups are as follows,
 * though in the sober light of day, I realize that not all of them make
 * good sense and thus have either not implemented them or else disabled them
 * after implementing them:
 *
 *   1.	Remove all "spacer" elements.  Those were created manually, were never
 *   	thoroughly checked, and are difficult to maintain.  Not to mention, they
 *   	conflict with some of the operations below.
 *   2.	Whenever a set of variables like VARIABLE and VARIABLE+n are found,
 *   	bubble them around so that they're both contiguous and in order of
 *   	increasing n (where VARIABLE is treated like VARIABLE+0).
 *   3.	Whenever a set of at least two (possibly change this later to 3)
 *   	consecutive variables VARIABLE, VARIABLE+n are found, insert a spacer
 *   	element prior to the first one.
 *   4.	Convert all spaces in variable names to underscores.
 */

// Pop a `FieldSpec_t` at a given index in a `DownlinkListSpec_t` structure.
// The return structure for the FieldSpec_t must have been pre-allocated.
void
dddPop(DownlinkListSpec_t *dls, int index, FieldSpec_t *fs)
{
  memcpy(fs, &(dls->FieldSpecs[index]), sizeof(FieldSpec_t));
  if (index < MAX_DOWNLINK_LIST - 1)
    memmove(&(dls->FieldSpecs[index]), &(dls->FieldSpecs[index + 1]),
	sizeof(FieldSpec_t) * (MAX_DOWNLINK_LIST - 1 - index));
  memset(&(dls->FieldSpecs[MAX_DOWNLINK_LIST - 1]), 0, sizeof(FieldSpec_t));
}

// Push a `FieldSpec_t` into a given index in a `DownlinkListSpec_t` structure.
void
dddPush(DownlinkListSpec_t *dls, int index, FieldSpec_t *fs)
{
  if (index < MAX_DOWNLINK_LIST - 1)
    memmove(&(dls->FieldSpecs[index + 1]), &(dls->FieldSpecs[index]),
	sizeof(FieldSpec_t) * (MAX_DOWNLINK_LIST - 1 - index));
  memcpy(&(dls->FieldSpecs[index]), fs, sizeof(FieldSpec_t));
}

// A comparison function for sorting the field-spec names.
typedef struct {
  char name[DISPLAYED_FIELD_WIDTH];
  int index;
} dddName_t;
int
dddCmp (const void *e1, const void *e2)
{
  dddName_t *s1 = (dddName_t *) e1, *s2 = (dddName_t *) e2;
  int i;

  i = strcmp(s1->name, s2->name);
  if (i != 0)
    return i;
  return s1->index - s2->index;
}

void
dddNormalize(DownlinkListSpec_t *dls)
{
#ifdef SHOW_WORD_NUMBERS
  int skip = 1;
#else
  int skip = 0;
#endif
  int i, j;
  FieldSpec_t *FieldSpecs, fs;
#ifdef DO_DDD_NORMALIZATION
  int numNames;
  FieldSpec_t *Fifs;
  dddName_t names[MAX_DOWNLINK_LIST];
#endif

#if defined(DO_DDD_NOORMALIZATION) || defined(SHOW_WORD_NUMBERS)
  // Step 1:  Eliminate all spacers.
  FieldSpecs = dls->FieldSpecs;
  for (i = 0; i < MAX_DOWNLINK_LIST; i++)
    if (FieldSpecs[i].IndexIntoList == -1)
      {
	dddPop(dls, i, &fs);
	i--;
      }
#endif

#ifdef DO_DDD_NORMALIZATION
  // Step 2:  Group stuff like VARIABLE, VARIABLE+n together.  A preliminary
  // step is to sort the variable names, so that we can even find out if there
  // are any sets of names like this.  This is done into the `names` array.
  for (i = 0; i < MAX_DOWNLINK_LIST; i++)
    {
      int n, length;
      char *plus, *Name;
      FieldSpecName_t name;

      Name = FieldSpecs[i].Name;
      plus = strstr(Name, "+");
      if (plus == NULL)
	{
	  n = 0;
	  length = strlen(Name) - 1;
	}
      else
	{
	  n = atoi(plus + 1);
	  length = plus - Name;
	}
      if (length < 0)
	break;
      strncpy(name, Name, length);
      name[length] = 0;
      strcpy(names[i].name, name);
      names[i].index = n;
    }
  numNames = i;
  qsort(names, numNames, sizeof(dddName_t), dddCmp);
  /*
  for (i = 0; i < numNames; i++)
    if (names[i].index)
      fprintf(stderr, "%3d: %s+%d\n", i, names[i].name, names[i].index);
    else
      fprintf(stderr, "%3d: %s\n", i, names[i].name);
  exit(1);
  */
  // TBD ... do the actual rearrangements.

  // Step 3:  Insert spacers as necessary.
  for (i = 0; i < MAX_DOWNLINK_LIST - 1; i++)
    {
      FieldSpec_t *fs, *fs1, fsSpacer = { -1 };
      int length;
      fs = &FieldSpecs[i];
      length = strlen(fs->Name);
      if (length == 0)
	break;
      fs1 = &FieldSpecs[i + 1];
      if (NULL == strstr(fs->Name, "+") &&
	  !strncmp(fs->Name, fs1->Name, length - 1) &&
	  fs1->Name[length - 1] == '+')
	{
	  dddPush(dls, i, &fsSpacer);
	  i++;
	}
    }
#endif // DO_DDD_NORMALIZATION

  // Step 4:  Convert spaces to underscores.
  for (i = 0; i < MAX_DOWNLINK_LIST; i++)
    {
      char *s;
      FieldSpecs = dls->FieldSpecs;
      if (FieldSpecs[i].IndexIntoList < 0)
	continue;
      for (s = FieldSpecs[i].Name, j = skip; *s; s++)
	if (*s == ' ')
	  {
	    j--;
	    if (j >= 0)
	      continue;
	    *s = '_';
	  }
    }
}

//---------------------------------------------------------------------------
// The `dddConfigure` function can be called at startup to modify the default
// downlist specifications given above, so that they instead contain
// mission-specific data obtained from files in the filesystem.  The input
// parameter is the name of an AGC software version, and the return value is
// 1 if that software corresponds to a CM or 0 for an LM.  Any files not found
// transparently leave the corresponding default downlist specification unchanged,
// though an info message is output to the console.
DownlinkListSpec_t *cmIdToSpec[] = {
    NULL, // 77772
    &CmProgram22Spec, // 77773
    &CmPoweredListSpec, // 77774
    &CmRendezvousPrethrustSpec, // 77775
    &CmEntryUpdateSpec, // 77776
    &CmCoastAlignSpec // 77777
};
DownlinkListSpec_t *lmIdToSpec[] = {
    &LmLunarSurfaceAlignSpec, // 77772
    &LmDescentAscentSpec, // 77773
    &LmOrbitalManeuversSpec, // 77774
    &LmRendezvousPrethrustSpec, // 77775
    &LmAgsInitializationUpdateSpec, // 77776
    &LmCoastAlignSpec // 77777
};

// Print a selected table of specs (either `cmIdToSpec` or `lmIdToSpec`) to
// a file.
static void
printSpecs(const char *filename, DownlinkListSpec_t **specs)
{
#ifdef DEBUG_DOWNLIST_SPEC_FILES
  FILE *f;
  int i, j;
  FieldSpec_t *fieldSpec;
  f = fopen(filename, "wt");
  if (f == NULL)
    {
      fprintf(stderr, "Could not open %s\n", filename);
      exit(1);
    }
  for (i = 0; i < 6; i++, specs++)
    {
      fprintf(f, "%05o:\n", 077772 + i);
      if (*specs == NULL)
	{
	  fprintf(f, "\tNULL\n");
	  continue;
	}
      fprintf(f, "\t%s\n", (*specs)->Title);
      fieldSpec = (*specs)->FieldSpecs;
      for (j = 0; j < MAX_DOWNLINK_LIST; j++, fieldSpec++)
	{
	  fprintf(f, "\t%d: %d, %s, %08X, %d, %p, %s\n", j,
		  fieldSpec->IndexIntoList,
		  fieldSpec->Name,
		  fieldSpec->Scale,
		  fieldSpec->Format,
		  fieldSpec->Formatter,
		  fieldSpec->Unit
		  );
	}

    }
  fclose(f);
#endif
}

static int
isUnsigned (char *s)
{
  if (*s == 0)
    return 0;
  for (; *s != 0; s++)
    if (*s < '0' || *s > '9')
      return 0;
  return 1;
}

#ifdef DO_FLEXIBLE_FALLBACK
// The following function is like `fopen`, but specifically tailored to files
// with names of the form
//	ddd-ID_SSSVVV.tsv
// where ddd is literal, ID is a 5-digit octal number, SSS is an alphabetic
// string, VVV is a decimal number, and tsv is literal.  The idea is that
// SSSVVV is the name of an AGC software version, such as Luminary099 or
// Comanche055.  If a file with the specified name isn't found, then VVV is
// decremented until a matching file is found.
char filenameFlexible[100];
FILE *
fopenFlexibly(char *filename, char *options)
{
  FILE *fp;
  char *s, *ss, format[32];
  int vvv, vvvLength;

  strcpy(filenameFlexible, filename);

  // If the specified file exists, then just return it!
  fp = fopen(filenameFlexible, options);
  if (fp != NULL)
    return fp;

  // We need to parse the filename, so that we can alter it and try again.
  int parsed = 0;
  if (strncmp(filenameFlexible, "ddd-", 4))
    return NULL;  // Doesn't start with "ddd-".
  ss = strstr(filenameFlexible, ".tsv");
  if (ss == NULL)
    return NULL;  // Doesn't end with ".tsv"
  for (s = ss; isdigit(s[-1]); s--); // Find VVV.
  if (s == ss)
    return NULL;  // No digits found.
  vvvLength = ss - s;
  sprintf(format, "%%0%dd.tsv", vvvLength);
  vvv = atoi(s);
  for (vvv--; vvv >= 0; vvv--)
    {
      sprintf(s, format, vvvLength, vvv);
      fp = fopen(filenameFlexible, options);
      if (fp != NULL)
	return fp;
    }

  return NULL;
}
#endif // FLEXIBLE_FALLBACK

int
dddConfigure (char *agcSoftware)
{
  int id;
  DownlinkListSpec_t **IdToSpec;
  printSpecs("before.txt", lmIdToSpec);
  // Software is assumed to be for the LM unless its name begins with one of the
  // known CM programs.
  CmOrLm = 0;
  if (!strncmp(agcSoftware, "Artemis", 7) ||
      !strncmp(agcSoftware, "Colossus", 8) ||
      !strncmp(agcSoftware, "Comanche", 8) ||
      !strncmp(agcSoftware, "Manche", 6) ||
      !strncmp(agcSoftware, "Skylark", 7) ||
      !strncmp(agcSoftware, "CM", 2))
    CmOrLm = 1;
  if (CmOrLm)
    IdToSpec = cmIdToSpec;
  else
    IdToSpec = lmIdToSpec;
  for (id = 077772; id <= 077777; id++)
    {
      char filename[64];
      DownlinkListSpec_t *dls;
      FieldSpec_t *fieldSpec;
      FILE *fp;
      int i;
      dls = IdToSpec[id - 077772];
      if (dls == NULL)
	continue;
      sprintf(filename, "ddd-%05o-%s.tsv", id, agcSoftware);
      fp = fopen(filename, "rt");
      if (fp == NULL)
	{
	  fprintf(stderr, "Using default configuration because file %s not found.\n", filename);
	  dddNormalize(dls);
	  continue;
	}
      fprintf(stderr, "Opening %s\n", filename);
      for (i = 0; i < MAX_DOWNLINK_LIST; i++)
	{
	  // Note that we cannot use `fscanf` to read lines from these files,
	  // because in a tab-delimited file it's fine for fields to be empty,
	  // but %s will simply skip right past them.  So we have to read entire
	  // lines an find the tab delimiters ourself.
	  int n, offset;
	  char *s, *ss, line[200], *offsetField, *varField, *scalerField, *formatField,
	    *formatterField, *unitField;
	  if (NULL == fgets(line, sizeof(line), fp))
	    {
	      fprintf(stderr, "Records read from %s:  %d\n", filename, i);
	      memset(&(dls->FieldSpecs[i]), 0, sizeof(FieldSpec_t) * (MAX_DOWNLINK_LIST - i));
	      break;
	    }
	  if (strlen(line) > 0 && line[0] == '#')
	    {
	      i--;
	      continue;
	    }
	  //fprintf(stderr, "\tParsing line: %s", line);
	  // Detect a couple of special cases.
	  line[strcspn(line, "\r\n")] = 0; // remove trailing CR or LF.
	  if (strstr(line, "\t") == NULL) // No tabs?
	    {
	      if (!strncmp(line, "http", 4))
		strcpy(dls->URL, line);
	      else
		strcpy(dls->Title, line);
	      i--;
	      continue;
	    }
	  for (s = line, n = 0; n < 6; s = ss + 1, n++)
	    {
	      for (ss = s; *ss != 0; ss++)
		if (*ss == '\t')
		  break;
	      if (*ss == 0 && n < 5)
		{
		  fprintf(stderr, "Ill-formed line %d in %s\n", i, filename);
		  exit(1);
		}
	      *ss = 0;
	      if (n == 0)
		offsetField = s;
	      else if (n == 1)
		varField = s;
	      else if (n == 2)
		scalerField = s;
	      else if (n == 3)
		formatField = s;
	      else if (n == 4)
		formatterField = s;
	      else if (n == 5)
		unitField = s;
	    }
	  if (!isUnsigned(offsetField) &&
	      !(offsetField[0] == '-' && isUnsigned(&offsetField[1])))
	    {
	      fprintf(stderr, "Non-numeric field %s at line %d in %s\n",
		      offsetField, i, filename);
	      exit(1);
	    }
	  offset = atoi(offsetField);
	  fieldSpec = &(dls->FieldSpecs[i]);
	  fieldSpec->IndexIntoList = offset;
	  fieldSpec->Name[0] = 0;
	  fieldSpec->Scale = 0;
	  fieldSpec->Format = FMT_SP;
	  fieldSpec->Formatter = NULL;
	  fieldSpec->Unit[0] = 0;
	  if (offset == -1)
	    continue;
	  // For the scaler field, at the moment I only recognize items of the
	  // form %u or B%u.
	  if (isUnsigned(scalerField))
	    fieldSpec->Scale = atoi(scalerField);
	  else if (scalerField[0] == 'B' && isUnsigned(&scalerField[1]))
	    fieldSpec->Scale = 1 << atoi(&scalerField[1]);
	  else
	    fprintf(stderr, "Unrecognized scaler field in %s: %s\n", filename, scalerField);
	  // Only the formats in `enum Format_t` are recognized.
	  if (!strcmp(formatField, "FMT_SP"))
	    fieldSpec->Format = FMT_SP;
	  else if (!strcmp(formatField, "FMT_DP"))
	    fieldSpec->Format = FMT_DP;
	  else if (!strcmp(formatField, "FMT_OCT"))
	    fieldSpec->Format = FMT_OCT;
	  else if (!strcmp(formatField, "FMT_2OCT"))
	    fieldSpec->Format = FMT_2OCT;
	  else if (!strcmp(formatField, "FMT_DEC"))
	    fieldSpec->Format = FMT_DEC;
	  else if (!strcmp(formatField, "FMT_2DEC"))
	    fieldSpec->Format = FMT_2DEC;
	  else if (!strcmp(formatField, "FMT_USP"))
	    fieldSpec->Format = FMT_USP;
	  else
	    fprintf(stderr, "Unrecognized format field in %s: %s\n", filename, formatField);
	  // Similarly for the formatter field.
	  if (strlen(formatterField) == 0)
	    ;
	  else if (!strcmp(formatterField, "FormatUnknown"))
	    ;
	  else if (!strcmp(formatterField, "FormatRequired"))
	    ;
	  else if (!strcmp(formatterField, "FormatOTRUNNION"))
	    fieldSpec->Formatter = &FormatOTRUNNION;
	  else if (!strcmp(formatterField, "FormatEarthOrMoonSP"))
	    fieldSpec->Formatter = &FormatEarthOrMoonSP;
	  else if (!strcmp(formatterField, "FormatEarthOrMoonDP"))
	    fieldSpec->Formatter = &FormatEarthOrMoonDP;
	  else if (!strcmp(formatterField, "FormatEpoch"))
	    fieldSpec->Formatter = &FormatEpoch;
	  else if (!strcmp(formatterField, "FormatAdotsOrOga"))
	    fieldSpec->Formatter = &FormatAdotsOrOga;
	  else if (!strcmp(formatterField, "FormatCDUT"))
	    fieldSpec->Formatter = &FormatCDUT;
	  else if (!strcmp(formatterField, "FormatDELV"))
	    fieldSpec->Formatter = &FormatDELV;
	  else if (!strcmp(formatterField, "FormatRDOT"))
	    fieldSpec->Formatter = &FormatRDOT;
	  else if (!strcmp(formatterField, "FormatHalfDP"))
	    fieldSpec->Formatter = &FormatHalfDP;
	  else if (!strcmp(formatterField, "FormatGtc"))
	    fieldSpec->Formatter = &FormatGtc;
	  else if (!strcmp(formatterField, "FormatHMEAS"))
	    fieldSpec->Formatter = &FormatHMEAS;
	  else if (!strcmp(formatterField, "FormatXACTOFF"))
	    fieldSpec->Formatter = &FormatXACTOFF;
	  else if (!strcmp(formatterField, "FormatLrRange"))
	    fieldSpec->Formatter = &FormatLrRange;
	  else if (!strcmp(formatterField, "FormatLrVz"))
	    fieldSpec->Formatter = &FormatLrVz;
	  else if (!strcmp(formatterField, "FormatLrVy"))
	    fieldSpec->Formatter = &FormatLrVy;
	  else if (!strcmp(formatterField, "FormatLrVx"))
	    fieldSpec->Formatter = &FormatLrVx;
	  else if (!strcmp(formatterField, "FormatRrRange"))
	    fieldSpec->Formatter = &FormatRrRange;
	  else if (!strcmp(formatterField, "FormatRrRangeRate"))
	    fieldSpec->Formatter = &FormatRrRangeRate;
	  else
	    fprintf(stderr, "Unrecognized formatter field in %s: %s\n", filename, formatterField);
	  // Units.
	  if (!strcmp(unitField, "TBD"))
	    unitField[0] = 0;
	  strcpy(fieldSpec->Unit, unitField);
#ifdef SHOW_WORD_NUMBERS
	  if (fieldSpec->Format == FMT_DP ||
	      fieldSpec->Format == FMT_2OCT ||
	      fieldSpec->Format == FMT_2DEC)
	    sprintf(fieldSpec->Name, "%d ", (offset / 2) + 1);
	  else
	    sprintf(fieldSpec->Name, "%d%c ", (offset / 2) + 1,
		    (offset % 2) ? 'b' : 'a');
	  strcat(fieldSpec->Name, varField);
#else
	  strcpy(fieldSpec->Name, varField);
#endif
	  strcat(fieldSpec->Name, "=");
	}
      fclose(fp);
      dddNormalize(dls);
    }

  printSpecs("after.txt", lmIdToSpec);
  return CmOrLm;
}

//---------------------------------------------------------------------------
// Print a double-precision number.  I cut-and-pasted this from CheckDec.c,
// and modified trivially;

double
GetDP (int *Ptr, int Scale)
{
  int i, Sign, Oct1, Oct2;
  double x;
  Oct1 = *Ptr++;
  Oct2 = *Ptr;
  if (0 != (040000 & Oct1))
    {
      Oct1 = ~Oct1;
      Oct2 = ~Oct2;
      Sign = -1;
    }
  else
    {
      Sign = 1;
    }
  i = ((Oct1 & 037777) << 14) | (Oct2 & 037777);
  x = Sign * i * FLOAT_SCALE * Scale;
  return (x);
}

void
PrintDP (int *Ptr, int Scale, int row, int col)
{
  sprintf (&Sbuffer[row][col], "%.10g", GetDP (Ptr, Scale));
}

double
GetSP (int *Ptr, int Scale)
{
  int i, Sign, Oct;
  double x;
  Oct = *Ptr;
  if (0 != (040000 & Oct))
    {
      Oct = ~Oct;
      Sign = -1;
    }
  else
    {
      Sign = 1;
    }
  i = (Oct & 037777);
  x = Sign * i * S_FLOAT_SCALE * Scale;
  return (x);
}

void
PrintSP (int *Ptr, int Scale, int row, int col)
{
  sprintf (&Sbuffer[row][col], "%.5g", GetSP (Ptr, Scale));
}

double
GetUSP (int *Ptr, int Scale)
{
  unsigned Oct;
  double x;
  Oct = 077777 & *Ptr;
  x = Oct * US_FLOAT_SCALE * Scale;
  return (x);
}

void
PrintUSP (int *Ptr, int Scale, int row, int col)
{
  sprintf (&Sbuffer[row][col], "%.5g", GetUSP (Ptr, Scale));
}

//--------------------------------------------------------------------------
// Stuff for printing fields.

// Print a field.
static void
PrintField (const FieldSpec_t *FieldSpec)
{
  int row, col, *Ptr, nameLength;
  FieldSpecName_t fsn;

  strcpy(fsn, FieldSpec->Name);
  nameLength = strlen(fsn);
#define USE_COLONS
#ifdef USE_COLONS
  strcpy(&fsn[nameLength-1], ": ");
  nameLength += 1;
#endif

  row = FieldSpec->Row;
  col = FieldSpec->Col;
  if (row == 0 && col == 0)
    {
      row = LastRow;
      col = LastCol;
    }
  if (FieldSpec->IndexIntoList < 0)
    {
      if (col > 1)
	{
	  LastCol = 1;
	  LastRow = row + 1;
	}
      return;
    }
  LastCol = col + DISPLAYED_FIELD_WIDTH;
  if (LastCol < Swidth)
    LastRow = row;
  else
    {
      LastCol = 1;
      LastRow = row + 1;
    }
  if (FieldSpec->IndexIntoList < 0)
    return;
  if (FieldSpec->Formatter != NULL)
    {
      char *s;
      s = (*FieldSpec->Formatter) (FieldSpec->IndexIntoList,
      				   FieldSpec->Scale, FieldSpec->Format);
      if (s != NULL)
        sprintf (&Sbuffer[row][col], "%s%s", fsn, s);
    }
  else
    {
      sprintf (&Sbuffer[row][col], "%s", fsn);
      col += nameLength;
      Ptr = &DownlinkListBuffer[FieldSpec->IndexIntoList];
      switch (FieldSpec->Format)
	{
	case FMT_SP:
	  PrintSP (Ptr, FieldSpec->Scale, row, col);
	  break;
	case FMT_DP:
	  PrintDP (Ptr, FieldSpec->Scale, row, col);
	  break;
	case FMT_OCT:
	  sprintf (&Sbuffer[row][col], "%05o", Ptr[0]);
	  break;
	case FMT_2OCT:
	  sprintf (&Sbuffer[row][col], "%05o%05o", Ptr[0], Ptr[1]);
	  break;
	case FMT_DEC:
	  sprintf (&Sbuffer[row][col], "%+d", Ptr[0]);
	  break;
	case FMT_2DEC:
	  sprintf (&Sbuffer[row][col], "%+d", 0100000 * Ptr[0] + Ptr[1]);
	  break;
	case FMT_USP:		
	  PrintUSP (Ptr, FieldSpec->Scale, row, col);
	  break;
	}
    }
}

// Print an entire downlink list.

char *DocumentationURL = (char *) DEFAULT_URL;
void
PrintDownlinkList (const DownlinkListSpec_t *Spec)
{
  // This is a global pointer to a function which can override PrintDownlinkList().
  // The idea is that PrintDownlinkList() is the default processor, and can be
  // used for printing "raw" downlink data, but it can be overridden if the buffered
  // downlink list needs to be processed differently, for example to be printed on 
  // a simulated MSK CRT.
  DocumentationURL = (char *) Spec->URL;
  if (ProcessDownlinkList != NULL)
    {
      (*ProcessDownlinkList) (Spec);
    }
  else
    {
      int i;
      Sclear ();
      sprintf (&Sbuffer[0][0], "%s", Spec->Title);
      for (i = 0; i < MAX_DOWNLINK_LIST; i++)
	{
	  if (i && !Spec->FieldSpecs[i].IndexIntoList)
	    break;		// End of field-list.
	  PrintField (&Spec->FieldSpecs[i]);
	}
      Swrite ();
    }
}

//---------------------------------------------------------------------------
// Print an "erasable dump" downlink list.

static void
DecodeErasableDump (char *Title)
{
  int i, j, row, col;
  Sclear ();
  DocumentationURL = (char *) DEFAULT_URL;
  sprintf (&Sbuffer[0][0], "%s", Title);
  sprintf (&Sbuffer[1][0], "ID=%05o  SYNC=%05o  PASS=%o  EBANK=%o  TIME1=%05o",
           DownlinkListBuffer[0], DownlinkListBuffer[1],
	   (DownlinkListBuffer[2] >> 11) & 1,
	   (DownlinkListBuffer[2] >> 8) & 7,
	   DownlinkListBuffer[3]);
  for (i = 1, j = 0, row = 2, col = 0; i <= 128; i++, j += 2)
    {
      if (1 == (i & 3))
        {
          sprintf (&Sbuffer[row][col], "%03o:", j);
	  col += 4;
	}
      sprintf (&Sbuffer[row][col], " %05o %05o", DownlinkListBuffer[j + 4],
	       DownlinkListBuffer[j + 5]);
      col += 12;
      if (0 == (i & 3))
        {
	  row++;
	  col = 0;
	}
    }
  Swrite ();
}

//----------------------------------------------------------------------------
// If you want to print digital downlinks to stdout, just keep feeding 
// DecodeDigitalDownlink the data read from output channels 013, 034, and 035
// as it arrives.  (Actually, you can just feed it data for all AGC output
// channels, if you like.)  The function takes care of buffering the data and
// parsing it out, so there's nothing else you have to do.

void
DecodeDigitalDownlink (int Channel, int Value, int CmOrLm)
{
  static int WordOrderBit = 0, Any = 0;
  
  // Parse the incoming data.  Detect unexpected stuff and restart the packet
  // if found.
  if (Channel == 013)
    {
      WordOrderBit = (Value & 0100);
      return;
    }
  else if (Channel == 034)
    {
      if (0 != (DownlinkListCount & 1))
        goto AbortList;
      if (DownlinkListCount == 0)
        {
	  if (WordOrderBit)
	    goto AbortList;
	  // Interpret the ID.
	Retry:
	  //printf ("ID=%05o\n", Value);
	  DownlinkListZero = 100;
	  if (Value == 01776)		// LM erasable dump.
	    {
	      DownlinkListExpected = 260;
	      DownlinkListZero = -1;
	    }
	  else if (Value == 01777)	// CM erasable dump.
	    {
	      DownlinkListExpected = 260; 
	      DownlinkListZero = -1;
	    }
	  else if (Value == 077772)	// Lunar surface align
	    DownlinkListExpected = 200;
	  else if (Value == 077773)	// LM descent/ascent, CM program 22 list
	    DownlinkListExpected = 200;
	  else if (Value == 077774)	// LM orbital maneuvers, CM powered list.
	    DownlinkListExpected = 200;
	  else if (Value == 077775)	// LM or CM rendezvous/prethrust
	    DownlinkListExpected = 200;
	  else if (Value == 077776)	// LM AGS initialization/update, CM entry/update
	    DownlinkListExpected = 200;
	  else if (Value == 077777)	// LM or CM coast align
	    DownlinkListExpected = 200;
	  else
	    goto AbortList;
	  //printf ("Started downlink of type 0%o\n", Value);
	}
      else
        {
	  if (!WordOrderBit && DownlinkListCount != DownlinkListZero)
	    {
	      DownlinkListCount = 0;
	      goto Retry;
	    }
	}
    }
  else if (Channel == 035)
    {
      if (0 == (DownlinkListCount & 1))
        goto AbortList;
      if (DownlinkListCount == 1)
        { 
	  if (Value != 077340)	// sync word
            goto AbortList;
	  if (WordOrderBit)
	    goto AbortList;
	}
      else
        {
	  if (!WordOrderBit && DownlinkListCount != DownlinkListZero + 1)
	    goto AbortList;
	}
    }
  else
    return;
  
  // Buffer the incoming data.
  if (DownlinkListCount < MAX_DOWNLINK_LIST)
    DownlinkListBuffer[DownlinkListCount++] = Value;
    
  // End of the list!  Do something with the data.
  if (DownlinkListCount >= DownlinkListExpected)
    {
      static char LMdump[] = "LM erasable dump downlinked.";
      static char CMdump[] = "CM erasable dump downlinked.";
      switch (DownlinkListBuffer[0])
        {
	case 01776:
	  DecodeErasableDump (LMdump);
	  break;
	case 01777:
	  DecodeErasableDump (CMdump);
	  break;
	case 077774:
	  if (CmOrLm)
	    PrintDownlinkList (DownlinkListSpecs[DL_CM_POWERED_LIST]);
	  else
	    PrintDownlinkList (DownlinkListSpecs[DL_LM_ORBITAL_MANEUVERS]);
	  break;
	case 077777:
	  if (CmOrLm)
	    PrintDownlinkList (DownlinkListSpecs[DL_CM_COAST_ALIGN]);
	  else
	    PrintDownlinkList (DownlinkListSpecs[DL_LM_COAST_ALIGN]);
	  break;
	case 077775:
	  if (CmOrLm)
	    PrintDownlinkList (DownlinkListSpecs[DL_CM_RENDEZVOUS_PRETHRUST]);
	  else
	    PrintDownlinkList (DownlinkListSpecs[DL_LM_RENDEZVOUS_PRETHRUST]);
	  break;
	case 077773:
	  if (CmOrLm)
	    PrintDownlinkList (DownlinkListSpecs[DL_CM_PROGRAM_22]);
	  else
	    PrintDownlinkList (DownlinkListSpecs[DL_LM_DESCENT_ASCENT]);
	  break;
	case 077772:
	  PrintDownlinkList (DownlinkListSpecs[DL_LM_LUNAR_SURFACE_ALIGN]);
	  break;
	case 077776:
	  if (CmOrLm)
	    PrintDownlinkList (DownlinkListSpecs[DL_CM_ENTRY_UPDATE]);
	  else
	    PrintDownlinkList (DownlinkListSpecs[DL_LM_AGS_INITIALIZATION_UPDATE]);
	  break;
	default:
	  Sclear ();
	  sprintf (&Sbuffer[0][0], "Unknown list type downlinked.");
	  Swrite ();
	  break;
	}
      Any = 1;
      DownlinkListCount = 0;
    }
    
  return;
AbortList:
  if (Any && DownlinkListCount != 0)
    {
      Sclear ();
      sprintf (&Sbuffer[0][0], "Downlink list of type 0%o aborted at word-count %d", 
              DownlinkListBuffer[0], DownlinkListCount);
      Swrite ();
      Any = 0;
    }
  DownlinkListCount = 0;
  return;
}


