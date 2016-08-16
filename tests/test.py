#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
import threading
import logging

import pylogging

from pylogging import LogLevel
from pyformat import Format as F


handler = pylogging.StdLogHandler()
fhandler = pylogging.FileHandler('bla')

logger = pylogging.Logger()

logger.add_handler(fhandler)

#logging.basicConfig(level=logging.INFO, format='%(message)s')


def runThread(i):
    fmt = F(u'thread ščřž %||: %||')

    def thread():
        for x in range(1000):
            #logging.info('thread %s: %s', i, x )
            #print('thread %s: %s' % (i, x ) )
            #print(fmt % i % x)
            logger.info(fmt % i % x)


    return thread


threads = []

for i in range(10):
    t = threading.Thread(target=runThread(i))
    t.start()

    threads.append(t)


for t in threads:
    t.join()

    
