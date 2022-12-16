import select
import sys

def kbfunc():
    input = select.select([sys.stdin], [], [], 1)[0]
    if input:
        value = sys.stdin.readline().rstrip() 
        if (value is not None and len(value) > 0):
            print("Got value " + str(value))
        return value
