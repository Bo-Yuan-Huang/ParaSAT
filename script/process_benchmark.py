#!/usr/bin/env python3

# ==============================================================================
# MIT License
#
# Copyright (c) 2020 Princeton University
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# ==============================================================================

import argparse
import os
import json
import subprocess
import sys


def UnzipAllFiles(data_dir):

    file_list = []
    for root, _, files in os.walk(data_dir):
        file_list += [os.path.join(root, name) for name in files]

    for f in file_list:
        _, ext = os.path.splitext(f)
        if ext != '.bz2':
            continue

        try:
            print('Unzipping {}'.format(f))
            res = subprocess.run(['bzip2', '-d', f])
        except BaseException:
            print('Fail unzipping {}'.format(f))


def SolveAllFiles(data_dir, solver):

    answer = {}

    for root, _, files in os.walk(data_dir):
        for f in files:
            _, ext = os.path.splitext(f)
            if ext != '.cnf':
                continue

            full_path = os.path.join(root, f)

            try:
                print('Solving {}'.format(full_path))
                res = subprocess.run([solver, full_path])
                answer[f] = res.returncode
            except BaseException:
                print("Terminated")

    with open('answer.json', 'w') as fw:
        json.dump(answer, fw, indent=True, sort_keys=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Process SAT Competition benchmark')

    parser.add_argument('dir', type=str, help='benchmark directory')
    parser.add_argument('--unzip', action='store_true', help='Unzip all files')
    parser.add_argument(
        '--solve',
        type=str,
        default='',
        help='Solve all using solver')

    args = parser.parse_args()

    if args.unzip:
        UnzipAllFiles(args.dir)

    if args.solve:
        SolveAllFiles(args.dir, args.solve)
