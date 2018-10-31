#!/bin/sh

umsservernum=$(ps | grep umsserver | grep -v grep | wc -l)

echo "umsservernum" is $umsservernum
