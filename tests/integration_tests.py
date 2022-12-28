import unittest
from subprocess import Popen, PIPE


def run_program(query):
    p = Popen(["./../build/set_app"], stdout=PIPE, stdin=PIPE)
    for q in query:
        p.stdin.write(q)
    p.stdin.flush()
    result = p.stdout.readlines()
    p.kill()
    return result


class IntegrationTests(unittest.TestCase):
    def test_add(self):
        result = run_program([b"8\n", b"3\n", b"+ a b\n", b"+ b c\n", b"+ a c\n"])
        self.assertListEqual(result, [b"OK\n", b"OK\n", b"FAIL\n"])

    def test_basecase_integration(self):
        result = run_program([
            b"8\n",
            b"9\n",
            b"+ str1 a\n",
            b"+ str2 b\n",
            b"+ str3 c\n",
            b"+ str1 d\n",
            b"? str1\n",
            b"? somestr\n",
            b"- str1\n",
            b"- str1\n",
            b"? str1\n",
        ])
        self.assertListEqual(result, [
            b"OK\n",
            b"OK\n",
            b"OK\n",
            b"FAIL\n",
            b"a\n",
            b"\n",
            b"OK\n",
            b"FAIL\n",
            b"\n",
        ])

    def test_expand_integration(self):
        result = run_program([
            b"2\n",
            b"9\n",
            b"+ 1 a\n",
            b"+ 2 b\n",
            b"+ 3 c\n",
            b"+ 1 d\n",
            b"? 1\n",
            b"? 4\n",
            b"- str1\n",
            b"- str1\n",
            b"? str1\n",
        ])
        self.assertListEqual(result, [
            b"OK\n",
            b"OK\n",
            b"OK\n",
            b"FAIL\n",
            b"a\n",
            b"\n",
            b"OK\n",
            b"FAIL\n",
            b"\n",
        ])


if __name__ == '__main__':
    unittest.main()
