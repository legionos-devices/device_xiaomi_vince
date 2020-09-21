/*
   Copyright (c) 2016, The CyanogenMod Project
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

#include "vendor_init.h"
#include "log/log.h"

char const *heapstartsize;
char const *heapgrowthlimit;
char const *heapsize;
char const *heaptargetutilization;
char const *heapminfree;
char const *heapmaxfree;
int property_set(const char *key, const char *value) {
    return __system_property_set(key, value);
}

void check_device()
{
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram > 3072ull * 1024 * 1024) {
        // from - xxhdpi-4096-dalvik-heap.mk
        heapstartsize = "16m";
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.75";
        heapminfree = "4m";
        heapmaxfree = "8m";
    } else {
        // from - xxhdpi-3072-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit= "288m";
        heapsize = "768m";
        heaptargetutilization = "0.75";
        heapminfree = "2m";
        heapmaxfree = "8m";
   }
}

void vendor_load_properties()
{
    check_device();

    SetProperty("dalvik.vm.heapstartsize", heapstartsize);
    SetProperty("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    SetProperty("dalvik.vm.heapsize", heapsize);
    SetProperty("dalvik.vm.heaptargetutilization", heaptargetutilization);
    SetProperty("dalvik.vm.heapminfree", heapminfree);
    SetProperty("dalvik.vm.heapmaxfree", heapmaxfree);
}
