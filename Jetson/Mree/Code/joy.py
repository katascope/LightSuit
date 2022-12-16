#!/usr/bin/env python
import fcntl
import os
import struct
import logging
import threading
import time

infile_path = "/dev/input/js0"
EVENT_SIZE = struct.calcsize("LhBB")
f = open(infile_path, "rb")

def thread_function(name):
 logging.info("Thread %s: starting", name)
 while True:
  event = f.read(EVENT_SIZE)
  if event:
    try:
      print(struct.unpack("LhBB",event))
      (tv_msec, value, type, number)= struct.unpack("LhBB", event)
    except:
      q = 1

if __name__ == "__main__":
  format = "%(asctime)s: %(message)s"
  logging.basicConfig(format=format, level=logging.INFO,
  datefmt="%H:%M:%S")

  logging.info("Main : before creating thread")
  x = threading.Thread(target=thread_function, args=(1,))
  logging.info("Main : before running thread")
  x.start()
  logging.info("Main : wait for the thread to finish")
  # x.join()
  logging.info("Main : all done")
               
while True:
  print("Loop..")
  time.sleep(0.5)
