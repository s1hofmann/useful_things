#!/usr/bin/env python2.7

import cv2
import numpy as np
import argparse
from sys import exit
from os.path import isdir, join
from os import listdir

"""
Just a small snippet I used to generate test and training sets
Previews images of a given input folder and after a visual check copies them
to a given output folder by pressing j or y
"""


def main():
    parser = argparse.ArgumentParser(description='Copy image after visually checking them.')
    parser.add_argument('input', nargs=1,
                        help='Input folder')
    parser.add_argument('output', nargs=1,
                        help='Output folder')

    args = parser.parse_args()

    in_folder = args.input[0]
    out_folder = args.output[0]

    if not isdir(in_folder) or not isdir(out_folder):
        print("Invalid path(s)")
        exit(-1)

    for file in listdir(in_folder):
        img = cv2.imread(file)

        if img is not None:
            # TODO Adjust to screen size
            preview = cv2.resize(img, (800, 600), interpolation=cv2.INTER_LINEAR)
            cv2.imshow('Preview', preview)
            key = cv2.waitKey(0)
            if key == ord('j') or key == ord('y'):
                cv2.imwrite(join(out_folder, file), img)

    cv2.destroyAllWindows()


if __name__ == "__main__":
    main()
