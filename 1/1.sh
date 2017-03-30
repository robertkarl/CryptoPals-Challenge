#! /bin/sh
../hex --decode < 1.in | ../b64 > 1.out
cat 1.out
diff expected.out 1.out

