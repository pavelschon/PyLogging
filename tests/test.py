#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import unicode_literals

import time
import threading
import logging

import pylogging

from pylogging import LogLevel

from pyformat import UFormat as U
from pyformat import Format as F


handler = pylogging.StdLogHandler()

logger = pylogging.Logger()

logger.add_handler(handler)


def runThread(i):
    fmt = U('thread ščřž %||: %||')
    fmt2 = F('thread ščřž xx %||: %||'.encode('utf-8'))

    def thread():
        for x in range(100):
            logger.info(fmt2 % i % x)
            logger.info(fmt % i % x)


    return thread


threads = []

for i in range(10):
    t = threading.Thread(target=runThread(i))
    t.start()

    threads.append(t)


for t in threads:
    t.join()
