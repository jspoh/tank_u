"""
checks for #pragma once in every header file in specified directory
excluding files in exclusion list. 
"""

import os
from typing import List
import re

class NoIncludeGuardError(Exception):
  def __init__(self, *args: object) -> None:
    super().__init__(*args)
    

regex: str = ""


def getFiles(absPath: str):
  files = os.listdir(absPath)
  uFiles = []

  for file in files:
    if re.search(regex, file):
      uFiles.append(absPath + file)
  return uFiles


def main():
  global regex
  regex = r"^[a-zA-Z-_]+\.h$"  # this matches all files ending in .h
  absPath = r"C:/Users/jings/Desktop/sit/acad/CSD1401 - Software Engineering 1/tank_u/"  # absolute path of file
  exclusions = ['cjson.h']  # lowercase only!

  files = getFiles(absPath)
  for filename in files:
    if filename.split('/')[-1].lower() in exclusions:
      continue

    with open(filename, 'r') as f:
      contents = f.readlines()
      
      if "#pragma once\n" not in contents:
        # print(f"File {filename} is missing include guards!")
        raise NoIncludeGuardError(f"File {filename} is missing include guards!")


if __name__ == '__main__':
  main()