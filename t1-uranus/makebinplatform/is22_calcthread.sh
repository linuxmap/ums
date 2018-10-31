#!/bin/sh

umssipadapternum=$(ps | grep umssipadapter | grep -v grep | wc -l)
umsmediatransnum=$(ps | grep umsmediatrans | grep -v grep | wc -l)
umsnetbufnum=$(ps | grep umsnetbuf | grep -v grep | wc -l)

echo "umssipadapternum" is $umssipadapternum
echo "umsmediatransnum" is $umsmediatransnum
echo "umsnetbufnum" is $umsnetbufnum
