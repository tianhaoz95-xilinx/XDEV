# XCLBIN Repository Utilities

## Objective

Automate operations to the xclbin repository for portability and stability.

## Why?

Compiling the xclbin repository takes a long time, so idealy many instances of XDEV, even with different version should be able to share the same xclbin repository as the xclbin depends on hardware instead of software.

## Design Overview

This utility should first take the root directory of the xclbin repository as the input and then construct a class of that represents the xclbin repository. Operations can then be performed on the class.