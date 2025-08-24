"""This script sets source directories for the Unreal Engine project."""
import os
import re
from time import time

SOURCE_DIR_PUBLIC = r'E:/Unreal/Unreal projects/Projects/TheWalk/Source/TheWalk/Public'
SOURCE_DIR_PRIVATE = r'E:/Unreal/Unreal projects/Projects/TheWalk/Source/TheWalk/Private'
SEPARATOR = '---------------'

all_files_short = []


def prepare():
   global all_files_short
   for file in files:
      all_files_short.append(short(file))


def short(file):
   file = file.replace(SOURCE_DIR_PUBLIC + '/', '')
   file = file.replace(SOURCE_DIR_PRIVATE+ '/', '')
   return file


def get_all_files():
   files = []
   for r, d, f in os.walk(SOURCE_DIR_PUBLIC):
      for file in f:
         files.append(os.path.join(r, file).replace('\\', '/'))
   for r, d, f in os.walk(SOURCE_DIR_PRIVATE):
      for file in f:
         files.append(os.path.join(r, file).replace('\\', '/'))
   return files
      

def print_common_data():
   count_lines = 0
   count_characters = 0
   for file in files:
      f = open(file, 'r')
      content = f.read()
      count_lines += len(content.split('\n'))
      count_characters += len(content)
      f.close()
   print('total number of files: %s' % len(files))
   print('total number of lines: %s' % count_lines)
   print('total number of characters: %s' % count_characters)


def test_source_files(func):
   for file in files:
      f = open(file, 'r')
      content = f.read()
      func(file, content)
      f.close()


def check_valid_order_include(file, content):
   includes = get_includes(content)
   includes = [i for i in includes if not i.strip().endswith('CoreMinimal.h')]
   for i in range(len(includes) - 1):
      if not first_less(file, includes[i], includes[i + 1]):
         print(includes[i])
         print(includes[i + 1])
         print('Incorrect order of the include file: %s' % short(file))


def first_less(file, include_1, include_2):
   if file.endswith('.cpp'):
      if file.replace('.cpp', '.h').endswith(include_1):
         return True
      elif file.replace('.cpp', '.h').endswith(include_2):
         return False
   elif include_1.endswith('.generated.h'):
      return False
   elif include_2.endswith('.generated.h'):
      return True
   
   if include_1 in all_files_short and include_2 in all_files_short:
      return include_1 <= include_2
   elif include_1 not in all_files_short and include_2 not in all_files_short:
      return include_1 <= include_2 
   elif include_1 in all_files_short:
      return False
   else:
      return True


def get_includes(content):
   lines = content.split('\n')
   includes = []
   for line in lines:
      if '#include' in line:
         line = line.replace('#include ', '')
         line = line.replace('"', '')
         includes.append(line)
   return includes
                    

def check_todo_comments(file, content):
    todos = re.findall(r'//\s*TODO[:\s](.*)', content, re.IGNORECASE)
    if todos:
        print('Found TODOs in %s:' % short(file))
        for todo in todos:
            print(f'  - {todo.strip()}')


def check_ue_log_usage(file, content):
    if not file.endswith('.cpp'):
        return

    matches = re.findall(r'UE_LOG\s*\(([^)]+)\)', content)
    if matches:
        print('Found UE_LOG usage in %s:' % short(file))
        for m in matches:
            log_parts = [p.strip() for p in m.split(',')]
            if len(log_parts) >= 2:
                category = log_parts[0]
                verbosity = log_parts[1]
                message = ', '.join(log_parts[2:])
                print(f'  - Category: {category}, Verbosity: {verbosity}, Msg: {message}')
            else:
                print(f'  - Possibly malformed UE_LOG: {m}')


# def check_incorrect_types(file, content):
#    for line in content.split('\n'):
#       if re.search(r'\sint\s', line):
#          print(line)
#          print('fint a int type in file: %s' % short(file))


# def check_missing_pragma_once(file, content):
#     if file.endswith('.h') and '#pragma once' not in content:
#         print('Missing #pragma once in file: %s' % short(file))


if __name__ == "__main__":
   start = time()
   files = get_all_files()
   prepare()
   print('Starting Test')
   
   print(SEPARATOR)
   print_common_data()
   
   print(SEPARATOR)
   
   print('Starting to check the order of the include')
   test_source_files(check_valid_order_include)
   print('Finished checking the the order of the include')
   
   print(SEPARATOR)
   
   print('Checking UE_LOG usage')
   test_source_files(check_ue_log_usage)
   print('Finished checking UE_LOG usage')
   
   print(SEPARATOR)
   
   print('There is a TODO in your project, do not forget about it')
   test_source_files(check_todo_comments)
   print('There is no TODO in your project')
   
   print(SEPARATOR)
   
   # print('Checking for incorrect type')
   # test_source_files(check_incorrect_types)
   # print('Finished checking for incorrect type')
   
   # print(SEPARATOR)
   
   # print('Starting to check the missing pragma once')
   # test_source_files(check_missing_pragma_once)
   # print('Finished checking the missing pragma once')
   
   # print(SEPARATOR)
   
   print('End of Test')
   print('It took %.1f seconds for the Test' % (time() - start))