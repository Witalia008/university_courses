using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace lab1
{
    public static class StringExt
    {
        public static string SafeSubstring(this string value, int startIndex, int length)
        {
            return new string((value ?? string.Empty).Skip(startIndex).Take(length).ToArray());
        }
    }
    struct Token
    {
        public enum TokenType
        {
            RESERVED, IDENTIFIER, OPERATOR, CONSTANT, COMMENT
        }
        public string lexem;
        public TokenType type;
    }
    class Program
    {
        static string[] operators = {
                "<<", ">>", "**", "<>", "><", "<=", ">=",
                ":=", "+=", "-=", "*=", "/=", "(*", "*)", "(.", ".)", "//",
                "+", "-", "*", "/", "=", "<", ">", "[", "]", ".", ",", "(", ")", ";",
                ":", "^", "@", "{", "}", "$", "#", "&", "%"};
        static string[] reserved = {
                "absolute", "and", "array", "asm", "begin", "case", "const", "constructor",
                "destructor", "div", "do", "downto", "else", "end", "file", "for", "function",
                "goto", "if", "implementation", "in", "inherited", "inline", "interface",
                "label", "mod", "nil", "not", "object", "of", "operator", "or", "packed",
                "procedure", "program", "record", "reintroduce", "repeat", "self", "set",
                "shl", "shr", "string", "then", "to", "type", "unit", "until", "uses",
                "var", "while", "with", "xor" };

        static List<Token> tokens = null;

        static void Main(string[] args)
        {
            string folder = "D:\\Cloud\\Google Drive\\My Computer\\Книги\\University" +
                                    "\\Books 3 course\\II\\OS\\compilers\\labs\\lab1\\lab1\\";
            string path = folder + "prog.pas";

            StreamReader rd = new StreamReader(path, Encoding.Default);
            string entireProgramText = rd.ReadToEnd();
            rd.Close();

            program(entireProgramText);

            using (StreamWriter wr = new StreamWriter(folder + "out.txt"))
            {
                foreach (Token token in tokens)
                {
                    wr.WriteLine(token.type + " " + token.lexem);
                }
            }
        }

        static int pos;
        static void program(string prog)
        {
            tokens = new List<Token>();
            pos = 0;
            while (pos < prog.Length)
            {
                while (pos < prog.Length && Char.IsWhiteSpace(prog[pos])) ++pos;
                if (pos >= prog.Length) break;
                char currentSymb = prog[pos];
                // Comments
                if (prog.SafeSubstring(pos, 2) == "(*" || prog.SafeSubstring(pos, 1) == "{"
                    || prog.SafeSubstring(pos, 2) == "//")
                {
                    tokens.Add(new Token() { lexem = readComment(prog), type = Token.TokenType.COMMENT });
                }
                else if (currentSymb == '_' || Char.IsLetter(currentSymb))
                {
                    string lexem = readIdentifier(prog);
                    foreach (string res in reserved)
                        if (res == lexem)
                        {
                            tokens.Add(new Token() { lexem = lexem, type = Token.TokenType.RESERVED });
                            lexem = "";
                        }
                    if (lexem != "")
                    {
                        tokens.Add(new Token() { lexem = lexem, type = Token.TokenType.IDENTIFIER });
                    }
                }
                else if (Char.IsDigit(currentSymb))
                {
                    tokens.Add(new Token() { lexem = readNumber(prog), type = Token.TokenType.CONSTANT });
                }
                else if (currentSymb == '\'')
                {
                    tokens.Add(new Token() { lexem = readString(prog), type = Token.TokenType.CONSTANT });
                }
                else
                {
                    // should be an operator
                    bool isOp = false;
                    foreach (string op in operators)
                        if (op == prog.SafeSubstring(pos, op.Length))
                        {
                            tokens.Add(new Token() { lexem = op, type = Token.TokenType.OPERATOR });
                            pos += op.Length;
                            isOp = true;
                        }
                    if (!isOp)
                    {
                        Console.WriteLine("Something bad encountered");
                    }
                }
            }
        }

        static string readComment(string prog)
        {
            StringBuilder res = new StringBuilder();

            if (prog.SafeSubstring(pos, 2) == "//")
            {
                while (pos < prog.Length && (prog[pos] != '\n' || (pos > 0 && prog[pos - 1] != '\\'))) res.Append(prog[pos++]);
            }
            else
            {
                int balance = 0;
                do
                {
                    if (prog.SafeSubstring(pos, 2) == "(*" || prog[pos] == '{')
                    {
                        res.Append(prog.SafeSubstring(pos, prog[pos] == '{' ? 1 : 2));
                        pos += prog[pos] == '{' ? 1 : 2;
                        ++balance;
                    }
                    else if (prog.SafeSubstring(pos, 2) == "*)" || prog[pos] == '}')
                    {
                        res.Append(prog.SafeSubstring(pos, prog[pos] == '}' ? 1 : 2));
                        pos += prog[pos] == '}' ? 1 : 2;
                        --balance;
                    }
                    else
                    {
                        res.Append(prog[pos++]);
                    }
                } while (pos < prog.Length && balance != 0);
                if (balance != 0)
                    Console.WriteLine("Comment has no end");
            }

            return res.ToString();
        }

        static string readIdentifier(string prog)
        {
            StringBuilder res = new StringBuilder();
            while (pos < prog.Length && (Char.IsDigit(prog[pos]) ||
                    Char.IsLetter(prog[pos]) || prog[pos] == '_'))
                res.Append(prog[pos++]);
            return res.ToString().ToLower();
        }

        static string readNumber(string prog)
        {
            StringBuilder res = new StringBuilder();
            while (pos < prog.Length && Char.IsDigit(prog[pos]))
                res.Append(prog[pos++]);
            if (pos < prog.Length && prog[pos] == '.')
            {
                do res.Append(prog[pos++]);
                while (pos < prog.Length && Char.IsDigit(prog[pos]));
                if (pos < prog.Length && prog[pos] == 'e')
                {
                    do res.Append(prog[pos++]);
                    while (pos < prog.Length && Char.IsDigit(prog[pos]));
                }
            }
            return res.ToString();
        }

        static string readString(string prog)
        {
            StringBuilder res = new StringBuilder();
            do
            {
                res.Append(prog[pos]);
                if (prog[pos] == '\\') res.Append(prog[pos++]);
                ++pos;
            } while (pos < prog.Length && prog[pos] != '\'');
            return res.ToString() + prog[pos++];
        }
    }
}
