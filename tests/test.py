#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pylogging

from pylogging import LogLevel
from pyformat import Format as F


f = F('test log %||')



handler = pylogging.StdOutHandler()
handler2 = pylogging.StdOutHandler()
logger = pylogging.Logger()

logger.add_handler(handler)
logger.add_handler(handler2)

handler.set_level(LogLevel.INFO)

logger.debug(f % 'at debug')
logger.info(f % 'at info')
logger.remove_handler(handler2)
logger.warning(f % 'at warning')
logger.error(f % 'at error')
logger.critical(f % 'at critical')


print(vars(pylogging.StdOutHandler))
