#!/bin/sh

umsmediatransnum=$(ps | grep umsmediatrans | grep -v grep | wc -l)

echo "umsmediatransnum" is $umsmediatransnum
