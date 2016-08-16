#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
import threading
import logging

import pylogging

from pylogging import LogLevel
from pyformat import Format as F


f = F('test log %||')



handler = pylogging.StdErrHandler()
logger = pylogging.Logger()

logger.add_handler(handler)

logging.basicConfig(level=logging.INFO, format='%(message)s')


def runThread(i):
    fmt = F('thread ščřž %||: %||')

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

