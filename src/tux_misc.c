/*
 * Tux Droid - Misc
 * Copyright (C) 2008 C2ME Sa <Acness : remi.jocaille@c2me.be>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <stdio.h>
#include <string.h>

#include "tux_misc.h"

#ifdef WIN32
#   include <time.h>
#   include <windows.h>
#else
#   include <sys/time.h>
#endif

#ifdef WIN32
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
#   define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
#   define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

#ifndef WIN32
struct timezone
{
    int  tz_minuteswest; /* minutes W of Greenwich */
    int  tz_dsttime;     /* type of dst correction */
};
#endif

/**
 *
 */
static int
gettimeofday(struct timeval *tv, struct timezone *tz)
{
    FILETIME ft;
    unsigned __int64 tmpres = 0;
    static int tzflag;

    if (NULL != tv)
    {
        GetSystemTimeAsFileTime(&ft);

        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

        /*converting file time to unix epoch*/
        tmpres -= DELTA_EPOCH_IN_MICROSECS;
        tmpres /= 10;  /*convert into microseconds*/
        tv->tv_sec = (long)(tmpres / 1000000UL);
        tv->tv_usec = (long)(tmpres % 1000000UL);
    }

    if (NULL != tz)
    {
        if (!tzflag)
        {
            _tzset();
            tzflag++;
        }
        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
    }

    return 0;
}
#endif /* WIN32 */

/**
 *
 */
LIBEXPORT double
get_time(void)
{
    double result;
    struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv, &tz);
    result = ((double)tv.tv_usec / 1000000) + (double)tv.tv_sec;

    return result;
}

LIBLOCAL bool
str_to_uint8(const char *str, unsigned char *dest)
{
    int r, val;

    r = sscanf(str, "%d", &val);

    if (r == 1)
    {
        if ((val >= 0) && (val <= 255))
        {
            *dest = val;
            return true;
        }
    }

    return false;
}

LIBLOCAL bool
str_to_int8(const char *str, char *dest)
{
    int r, val;

    r = sscanf(str, "%d", &val);

    if (r == 1)
    {
        if ((val >= -128) && (val <= 127))
        {
            *dest = val;
            return true;
        }
    }

    return false;
}

LIBLOCAL bool
str_to_int(const char *str, int *dest)
{
    int r, val;

    r = sscanf(str, "%d", &val);

    if (r == 1)
    {
        *dest = val;
        return true;
    }

    return false;
}

LIBLOCAL bool
str_to_bool(const char *str, bool *dest)
{
    if (!strcmp(str, "True"))
    {
        *dest = true;
        return true;
    }
    else
    {
        if (!strcmp(str, "False"))
        {
            *dest = false;
            return true;
        }
    }

    return false;
}

LIBLOCAL bool
str_to_float(const char *str, float *dest)
{
    int r;
    float val;

    r = sscanf(str, "%f", &val);

    if (r == 1)
    {
        *dest = val;
        return true;
    }

    return false;
}

LIBLOCAL bool
hex_to_uint8(const char *str, unsigned char *dest)
{
    int r;
    int val;

    r = sscanf(str, "0x%2x", &val);

    if (r == 1)
    {
        if ((val >= 0) && (val <= 255))
        {
            *dest = val;
            return true;
        }
    }

    return false;
}
