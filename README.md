# QP/C and QP/C++ Q_ASSERT List and meta information

This repository includes a C module providing means to lookup a meta description of 
various internal QP Q_ASSERT ids encountered when developing an application for QP.

Use this module in your firmware to get a handy debug print output (when available)
indicating the reason for the assert and possible meta/higher level guidance
on how to resolve the assert.

Or, if the firmware has no means to print such information from within
an assert, just keep this repository handy and manually search the internal
tables.

Better yet, follow a TDD methodology using cpputest-for-qpc or qpcpp, which
will include this repo and automatically print the information to stderr
upon hitting such asserts while unit testing.

# Building

If using the provided cmake setup, then the libary will by default compile for QP/C.

If QP/C++ meta information is preferred, enable the `CMS_ENABLE_QASSERT_META_QPCPP` 
cmake flag. An example that could be used in a higher level cmake:

`option(CMS_ENABLE_QASSERT_META_QPCPP "Enable QP/C++ for qassert-meta library" ON)`

# Other

This repo is included and used by both cpputest-for-qpc and cpputest-for-qpcpp.
See those repositories for example usage of this repository.

And, if interested in learning more about cpputest-for-qpc or qpcpp, check out
this tutorial video on YouTube: https://youtu.be/hr1qkNH1wSA

