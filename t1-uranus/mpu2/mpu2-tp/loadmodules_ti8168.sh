#
#  Copyright (c) 2008, Texas Instruments Incorporated
#  All rights reserved.
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
# 
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
rmmod cmemk.ko
rmmod syslink.ko
# insert cmemk, tell it to occupy physical 120MB-128MB, create .reference serverplatforms.xs!!!
# 20 4K buffers, 10 128K buffers  and two 1MB buffers

insmod syslink.ko
insmod cmemk.ko  allowOverlap=1 phys_start=0x99C00000 phys_end=0x9CC00000 pools=3x6291456,1x4123648,3x3110400,3x1966080,10x524288,4x65536,30x13824,160x16384,50x8192,384x4096
#rgb24: 3x(1920x1080x3) yuyv:3x1920x1080x2 3x1280x720x2...
# insert DSP/BIOS Link driver
#
#insmod syslink.ko TRACE=1 TRACEFAILURE=1 TRACEENTER=1
#insmod syslink.ko
#insmod TI81xx_HDMI.ko hdmi_mode=2
# make /dev/dsplink
#rm -f /dev/syslink
#mknod /dev/syslink c `awk "\\$2==\"dsplink\" {print \\$1}" /proc/devices` 0
mkdir /dev/syslinkipc/ 
mknod /dev/syslinkipc/ProcMgr         c 254  0
mknod /dev/syslinkipc/Notify          c 254  1
mknod /dev/syslinkipc/NameServer      c 254  2
mknod /dev/syslinkipc/SharedRegion    c 254  3
mknod /dev/syslinkipc/HeapBufMP       c 254  4
mknod /dev/syslinkipc/HeapMemMP       c 254  5
mknod /dev/syslinkipc/HeapMultiBuf    c 254  6
mknod /dev/syslinkipc/ListMP          c 254  7
mknod /dev/syslinkipc/GateMP          c 254  8
mknod /dev/syslinkipc/MessageQ        c 254  9
mknod /dev/syslinkipc/MultiProc       c 254  10
mknod /dev/syslinkipc/Ipc             c 254  11
mknod /dev/syslinkipc/Osal            c 254  12
mknod /dev/syslinkipc/SyslinkMemMgr   c 254  13
mknod /dev/syslinkipc/ClientNotifyMgr c 254  14
mknod /dev/syslinkipc/FrameQBufMgr    c 254  15
mknod /dev/syslinkipc/FrameQ          c 254  16
mknod /dev/syslinkipc/RingIO          c 254  17

./prcm_config_app s
