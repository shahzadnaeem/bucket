# coding=utf-8

from sys import version_info

if version_info >= (3,):
    unichr = chr
    unicode = lambda s, e: s
    xrange = range


# Surrounding field for printing clarity
field = u'\u2591'
# List of all homoglyph strings
all_hgs = []
# Index dict of all homoglyphs
hg_index = {}


def fill_homoglyphs():
    """
    Use http://dev.networkerror.org/utf8/?start=0&end=255&cols=10&show_uni_hex=on
    with the stupid table width forced to auto.
    This dataset is for ASCII characters mapped to UTF-8 homoglyphs (some approximate).
    Some of the entries are also selected from the results of search(), below.
    """
    all_hgs.extend((
        u' \u00A0\u2000\u2001\u2002\u2003\u2004\u2005\u2006\u2007\u2008\u2009\u200A\u202F\u205F',
        u'!\uFF01\u01C3\u2D51\uFE15\uFE57',
        u'"\uFF02',
        u'#\uFF03\uFE5F',
        u'$\uFF04\uFE69',
        u'%\uFF05\u066A\u2052\uFE6A',
        u'&\uFF06\uFE60',
        u"'\uFF07\u02B9\u0374",
        u'(\uFF08\uFE59',
        u')\uFF09\uFE5A',
        u'*\uFF0A\u22C6\uFE61',
        u'+\uFF0B\u16ED\uFE62',
        u',\uFF0C\u02CF\u16E7\u201A',
        u'-\uFF0D\u02D7\u2212\u23BC\u2574\uFE63',
        u'.\uFF0E\u2024',
        u'/\uFF0F\u1735\u2044\u2215\u29F8',
        # u'0',
        # u'1',
        u'2\u14BF',
        u'3\u01B7\u2128',
        u'4\u13CE',
        # u'5',
        u'6\u13EE',
        # u'7',
        # u'8',
        u'9\u13ED',
        u':\uFF1A\u02D0\u02F8\u0589\u1361\u16EC\u205A\u2236\u2806\uFE13\uFE55',
        u';\uFF1B\u037E\uFE14\uFE54',
        u'<\uFF1C\u02C2\u2039\u227A\u276E\u2D66\uFE64',
        u'=\uFF1D\u2550\u268C\uFE66',
        u'>\uFF1E\u02C3\u203A\u227B\u276F\uFE65',
        u'?\uFF1F\uFE16\uFE56',
        u'@\uFF20\uFE6B',
        u'A\u0391\u0410\u13AA',
        u'B\u0392\u0412\u13F4\u15F7\u2C82',
        u'C\u03F9\u0421\u13DF\u216D\u2CA4',
        u'D\u13A0\u15EA\u216E',
        u'E\u0395\u0415\u13AC',
        u'F\u15B4',
        u'G\u050C\u13C0',
        u'H\u0397\u041D\u12D8\u13BB\u157C\u2C8E',
        u'I\u0399\u0406\u2160',
        u'J\u0408\u13AB\u148D',
        u'K\u039A\u13E6\u16D5\u212A\u2C94',
        u'L\u13DE\u14AA\u216C',
        u'M\u039C\u03FA\u041C\u13B7\u216F',
        u'N\u039D\u2C9A',
        u'O\u039F\u041E\u2C9E',
        u'P\u03A1\u0420\u13E2\u2CA2',
        u'Q\u051A\u2D55',
        u'R\u13A1\u13D2\u1587',
        u'S\u0405\u13DA',
        u'T\u03A4\u0422\u13A2',
        # u'U',
        u'V\u13D9\u2164',
        u'W\u13B3\u13D4',
        u'X\u03A7\u0425\u2169\u2CAC',
        u'Y\u03A5\u2CA8',
        u'Z\u0396\u13C3',
        u'[\uFF3B',
        u'\\\uFF3C\u2216\u29F5\u29F9\uFE68',
        u']\uFF3D',
        u'^\uFF3E\u02C4\u02C6\u1DBA\u2303',
        u'_\uFF3F\u02CD\u268A',
        u'`\uFF40\u02CB\u1FEF\u2035',
        u'a\u0251\u0430',
        # u'b',
        u'c\u03F2\u0441\u217D',
        u'd\u0501\u217E',
        u'e\u0435\u1971',
        # u'f',
        u'g\u0261',
        u'h\u04BB',
        u'i\u0456\u2170',
        u'j\u03F3\u0458',
        # u'k',
        u'l\u217C',
        u'm\u217F',
        u'n\u1952',
        u'o\u03BF\u043E\u0D20\u2C9F',
        u'p\u0440\u2CA3',
        # u'q',
        # u'r',
        u's\u0455',
        # u't',
        u'u\u1959\u222A',
        u'v\u1D20\u2174\u2228\u22C1',
        u'w\u1D21',
        u'x\u0445\u2179\u2CAD',
        u'y\u0443\u1EFF',
        u'z\u1D22',
        u'{\uFF5B\uFE5B',
        u'|\uFF5C\u01C0\u16C1\u239C\u239F\u23A2\u23A5\u23AA\u23AE\uFFE8',
        u'}\uFF5D\uFE5C',
        u'~\uFF5E\u02DC\u2053\u223C'
    ))
    hg_index.update({c: hgs for hgs in all_hgs for c in hgs})


def homoglyphs_for_char(char):
    """
    :param char: The char to look up
    :return: A string of homoglyphs for that char
    """
    return hg_index[char]


def has_homoglyphs(char):
    """
    :param char: A character to check
    :return: Whether we have homoglyphs for it
    """
    return char in hg_index


def is_ascii(char):
    return ord(' ') <= ord(char) <= ord('~')


def get_writer():
    """
    :return: A codec writer for stdout. Necessary for output piping to work.
    """
    from codecs import getwriter
    from sys import stdout

    if version_info >= (3,):
        return stdout
    return getwriter(stdout.encoding or 'utf-8')(stdout)


def read_line():
    from sys import stdin

    if version_info >= (3,):
        return input()
    return raw_input().decode(stdin.encoding or 'utf-8')


def listing():
    """
    Show a list of all known homoglyphs
    """
    out = get_writer()
    for hgs in all_hgs:
        for c in hgs:
            out.write(field + c)
        out.write(field + '\n')


def explain(char):
    """
    Show an explanation of all known homoglyphs for the given ASCII char
    :param char: An ASCII char to explain
    """
    if not has_homoglyphs(char):
        print('No homoglyphs.')
        return

    try:
        import unicodedata
    except ImportError:
        print('Install docutils.')
        return

    out = get_writer()

    out.write('Char\t%6s %20s Cat Name\n' % ('Point', 'Normal'))

    for hg in homoglyphs_for_char(char):
        norms = ''
        for form in ('NFC', 'NFKC', 'NFD', 'NFKD'):
            h = unicodedata.normalize(form, hg)
            if h == hg[0]:
                if norms:
                    norms += ' '
                norms += form
        out.write(' %(field)c%(hg)c%(field)c\t'
                  'U+%(point)04X %(norms)20s %(cat)3s %(name)s\n' % {
                      'field': field,
                      'hg': hg,
                      'point': ord(hg),
                      'norms': norms,
                      'cat': unicodedata.category(hg),
                      'name': unicodedata.name(hg, '<unnamed>')
                  })


def search():
    """
    (Not useful to the user) Troll the unicode DB for normalization matches, which are potentially homoglyphs.
    """
    try:
        import unicodedata
    except ImportError:
        print('Install docutils.')
        return

    out = get_writer()

    for point in xrange(ord('~') + 1, 0x10000):
        u = unichr(point)
        for form in ('NFC', 'NFKC', 'NFD', 'NFKD'):
            if u in hg_index:
                continue
            h = unicodedata.normalize(form, u)
            if len(h) == 1 and ord(h) != ord(u) and (
                        has_homoglyphs(h) or is_ascii(h)):
                out.write('%(ascii)c %(form)s->  %(hg)c\tU+%(point)04X %(cat)s/%(name)s\n' % {
                    'ascii': h,
                    'form': form,
                    'hg': u,
                    'point': ord(u),
                    'cat': unicodedata.category(u),
                    'name': unicodedata.name(u, '<unnamed>')
                })
                break


def pipe(replace):
    """
    Pipe from input to output
    End with ctrl+C or EOF
    :param replace: A function to replace each char
    """

    out = get_writer()

    # "for line in stdin" works for piped input but not keyboard input

    while True:
        try:
            line = read_line()
        except EOFError:
            return
        for c in line:
            out.write(replace(c))
        out.write('\n')


def pipe_mimic(hardness):
    """
    Pipe from input to output, replacing chars with homoglyphs
    :param hardness: Percent probability to replace a char
    """
    from random import random, randrange
    
    def replace(c):
        if random() > hardness / 100. or not has_homoglyphs(c):
            return c
        hms = homoglyphs_for_char(c)
        index = randrange(len(hms))
        return hms[index]

    pipe(replace)


def replace_reverse(c):
    """
    Undo the damage to c
    """
    return hg_index.get(c, c)[0]


def replace_check(c):
    """
    Replace non-ASCII chars with their code point
    """
    if ord(c) <= ord('~'):
        return c
    return '<%(orig)c:U+%(point)04X>' % {
        'orig': c,
        'point': ord(c)
    }


def parse():
    from optparse import OptionParser

    parser = OptionParser()
    parser.add_option('-m', '--me-harder', dest='chance', type='float', default=1,
                      help='replacement percent')
    parser.add_option('-e', '--explain', dest='char',
                      help="show a char's homoglyphs")
    parser.add_option('-l', '--list', action='store_true',
                      help='show all homoglyphs')
    parser.add_option('-c', '--check', action='store_true',
                      help='check input for suspicious chars')
    parser.add_option('-r', '--reverse', action='store_true',
                      help='reverse operation, clean a mimicked file')
    return parser.parse_args()


def main():
    try:
        (options, args) = parse()
        if options.list:
            listing()
        elif options.char:
            explain(unicode(options.char, 'utf-8'))
        elif options.check:
            pipe(replace_check)
        elif options.reverse:
            pipe(replace_reverse)
        else:
            pipe_mimic(options.chance)
    except KeyboardInterrupt:
        pass


fill_homoglyphs()

