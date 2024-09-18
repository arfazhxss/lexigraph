#!/usr/bin/env python3

import sys
import concord4

def main():
    saved_stdout, saved_stderr = sys.stdout, sys.stderr
    sys.stdout, sys.stderr = None, None
    cc = concord4.concord(sys.stdin)
    results = cc.full_concordance() 
    sys.stdout, sys.stderr = saved_stdout, saved_stderr
    # print("0000000001111111111222222222233333333334444444444555555555566666666667")
    # print("1234567890123456789012345678901234567890123456789012345678901234567890")
    if results != []:
        print("\n".join(results))

if __name__ == "__main__":
    main()
