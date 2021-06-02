#!/usr/bin/env python3

import glob
import os

for file in glob.glob("**/*.cpp", recursive=True):
    if 'include/Common' in file:
        continue
    print(file)
    data = open(file).read().strip()
    if (data.split('\n')[0] == '/*'):
        data = '\n'.join(data.split('\n')[1:])
        while (data[0] == '*'):
            data = '\n'.join(data.split('\n')[1:])
        data = data.strip()
    basename = os.path.basename(file)
    data = '''/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ''' + basename + '''
*/

''' + data
    open(file, 'w').write(data)

for file in glob.glob("**/*.h", recursive=True):
    if 'include/Common' in file:
        continue
    print(file)
    data = open(file).read().strip()
    if (data.split('\n')[0] == '/*'):
        data = '\n'.join(data.split('\n')[1:])
        while (data[0] == '*'):
            data = '\n'.join(data.split('\n')[1:])
        data = data.strip()
    basename = os.path.basename(file)
    data = '''/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ''' + basename + ''' header
*/

''' + data
    open(file, 'w').write(data)

for file in glob.glob("**/*.hpp", recursive=True):
    if 'include/Common' in file:
        continue
    print(file)
    data = open(file).read().strip()
    if (data.split('\n')[0] == '/*'):
        data = '\n'.join(data.split('\n')[1:])
        while (data[0] == '*'):
            data = '\n'.join(data.split('\n')[1:])
        data = data.strip()
    basename = os.path.basename(file)
    data = '''/*
** EPITECH PROJECT, 2021
** Arcade
** File description:
** ''' + basename + ''' header
*/

''' + data
    open(file, 'w').write(data)