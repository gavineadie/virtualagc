#!/usr/bin/env python

# CAVEAT UTILITOR
#
# This file was automatically generated by TatSu.
#
#    https://pypi.python.org/pypi/tatsu/
#
# Any changes you make to it will be overwritten the next time
# the file is generated.

from __future__ import annotations

import sys

from tatsu.buffering import Buffer
from tatsu.parsing import Parser
from tatsu.parsing import tatsumasu
from tatsu.parsing import leftrec, nomemo, isname # noqa
from tatsu.infos import ParserConfig
from tatsu.util import re, generic_main  # noqa


KEYWORDS = {}  # type: ignore


class operandInvocationBuffer(Buffer):
    def __init__(self, text, /, config: ParserConfig = None, **settings):
        config = ParserConfig.new(
            config,
            owner=self,
            whitespace=None,
            nameguard=None,
            comments_re=None,
            eol_comments_re=None,
            ignorecase=False,
            namechars='',
            parseinfo=False,
        )
        config = config.replace(**settings)
        super().__init__(text, config=config)


class operandInvocationParser(Parser):
    def __init__(self, /, config: ParserConfig = None, **settings):
        config = ParserConfig.new(
            config,
            owner=self,
            whitespace=None,
            nameguard=None,
            comments_re=None,
            eol_comments_re=None,
            ignorecase=False,
            namechars='',
            parseinfo=False,
            keywords=KEYWORDS,
            start='operand',
        )
        config = config.replace(**settings)
        super().__init__(config=config)

    @tatsumasu()
    def _operand_(self):  # noqa
        with self._optional():
            self._replacement_()

            def block0():
                self._token(',')
                self._replacement_()
            self._closure(block0)

    @tatsumasu()
    def _replacement_(self):  # noqa
        with self._choice():
            with self._option():
                self._identifier_()
                self._token('=')
                self._token("'")
                self._pattern("[^']*")

                def block1():
                    self._token("''")
                    self._pattern('[^;]*')
                self._closure(block1)
                self._token("'")
            with self._option():
                self._identifier_()
                self._token('=')
                self._token('(')
                self._list_()
                self._token(')')
            with self._option():
                self._identifier_()
                self._token('=')
                self._pattern('[^, ()]*')
            with self._option():
                self._token("'")
                self._pattern("[^']*")

                def block2():
                    self._token("''")
                    self._pattern('[^;]*')
                self._closure(block2)
                self._token("'")
            with self._option():
                self._token('(')
                self._list_()
                self._token(')')
            with self._option():
                self._pattern('[^, ()]*')
            self._error(
                'expecting one of: '
                '"\'" \'(\' <identifier>'
                '[@#$A-Z][@#$A-Z0-9]* [^, ()]*'
            )

    @tatsumasu()
    def _identifier_(self):  # noqa
        self._pattern('[@#$A-Z][@#$A-Z0-9]*')

    @tatsumasu()
    def _list_(self):  # noqa
        self._listItem_()

        def block0():
            self._token(',')
            self._listItem_()
        self._closure(block0)

    @tatsumasu()
    def _listItem_(self):  # noqa
        with self._choice():
            with self._option():
                self._token('(')
                self._list_()
                self._token(')')
            with self._option():
                self._pattern('[^ ,()]*')
            self._error(
                'expecting one of: '
                "'(' [^ ,()]*"
            )


class operandInvocationSemantics:
    def operand(self, ast):  # noqa
        return ast

    def replacement(self, ast):  # noqa
        return ast

    def identifier(self, ast):  # noqa
        return ast

    def list(self, ast):  # noqa
        return ast

    def listItem(self, ast):  # noqa
        return ast


def main(filename, **kwargs):
    if not filename or filename == '-':
        text = sys.stdin.read()
    else:
        with open(filename) as f:
            text = f.read()
    parser = operandInvocationParser()
    return parser.parse(
        text,
        filename=filename,
        **kwargs
    )


if __name__ == '__main__':
    import json
    from tatsu.util import asjson

    ast = generic_main(main, operandInvocationParser, name='operandInvocation')
    data = asjson(ast)
    print(json.dumps(data, indent=2))