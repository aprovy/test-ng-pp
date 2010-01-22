#!/usr/bin/python

import sys
import re
import os
import codecs

from Phase1Result import *
from Phase2Result import *
from Phase3Result import *

from TestCaseParser import TestCaseParser

from Message import *

testcase_re = re.compile( r'^\s*TEST\s*\(\s*(?P<testcaseName>\w+)\s*\)\s*' , re.UNICODE)

##########################################################
def is_testcase_def(line):
   m = testcase_re.match(line.get_content())
   if m:
      return m.group("testcaseName")

   return None

##########################################################
class TestFixture(Fixture):
   #######################################################
   def __init__(self, name):
      Fixture.__init__(self, name)

   #######################################################
   def add_testcase(self, testcase):
      self.testcases.append(testcase)

##########################################################
class FixtureParser:
   #######################################################
   def __init__(self, name):
      self.scopes = []
      self.in_testcase = None
      self.numberOfUnclosedBraces = 0
      self.begin = True
      self.end = None
      self.done = None
      self.fixture = TestFixture(name)
      self.parser = None

   #######################################################
   def add_scope(self, scope):
      self.scopes.append(scope)

   #######################################################
   def add_testcase(self, testcase):
      self.fixture.add_testcase(testcase)

   #######################################################
   def handle_tag(self, tag):
      return None

   #######################################################
   def handle_space(self, line, c):
      if c.isspace():
         return True

      return None

   #######################################################
   def handle_done(self, line, c):
      if not self.done:
         return None

      fatal(line, "unexpected char '" + c + "'")

   #######################################################
   def handle_begin(self, line, c):
      if not self.begin:
         return None
      
      if c == '{':
         self.numberOfUnclosedBraces = 1
         self.begin = None
         return True

      fatal(line, "expected '{'")

   #######################################################
   def handle_end(self, line, c):
      if not self.end:
         return None

      if c == ';':
         self.done = True
         return True

      fatal(line, "expected ';'")

   #######################################################
   def handle_others(self, line, c):
      if c == '{':
         self.numberOfUnclosedBraces += 1
      elif c == '}':
         self.numberOfUnclosedBraces -= 1
         if self.numberOfUnclosedBraces == 0:
            self.end = True

   #######################################################
   def handle_char(self, line, c):
      self.handle_space(line, c) or \
      self.handle_done(line, c) or \
      self.handle_begin(line, c) or \
      self.handle_end(line, c)   or \
      self.handle_others(line, c)


   #######################################################
   def handle_line(self, line):
      if self.parser:
         testcase = self.parser.parse(line)
         if testcase:
            self.add_testcase(testcase) 
            self.parser = None

         return None
         
      return self.look_for_testcase(line)

   #######################################################
   def look_for_testcase(self, line):
      testcase_name = is_testcase_def(line)
      if testcase_name:
         self.parser = TestCaseParser(testcase_name)
         return None

      return self.handle_normal_line(line)
        
   #######################################################
   def handle_normal_line(self, line):
      for c in line.get_content():
         self.handle_char(line, c)

      if self.done:
         return self.fixture

      return None

   #######################################################
   def parse(self, line):
      if isinstance(line, Tag):
         return self.handle_tag(line)

      if isinstance(line, Scope):
         self.add_scope(line)
         return None
      
      return self.handle_line(line)
