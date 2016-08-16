#!/usr/bin/env python3
# -*- coding: utf-8 -*-

##
# @file unit_test.py
# @brief Unittest of PyLogging
#
# Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
#
#

import unittest
import pylogging


class PyLoggingTest(unittest.TestCase):
    def testAddRemoveHandler(self):
        handler  = pylogging.NullHandler()
        logger   = pylogging.Logger()

        logger.add_handler(handler)

        self.assertTrue( handler in logger )

        with self.assertRaises(ValueError):
            logger.add_handler(handler)

        logger.remove_handler(handler)

        self.assertFalse( handler in logger )

        with self.assertRaises(ValueError):
            logger.remove_handler(handler)


if __name__ == '__main__':
    unittest.main()


# EOF

