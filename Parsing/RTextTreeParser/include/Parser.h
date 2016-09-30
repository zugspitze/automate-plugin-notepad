#ifndef RTEXT_PARSER_H__
#define RTEXT_PARSER_H__

#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <ctype.h>

namespace RText
{
    class RTextNode
    {
    public:
        RTextNode(int const lineNumber, int const numberOfNodeLines, RTextNode * parent = nullptr);

        int getLineNumber()const;

        int getNumberOfNodeLines()const;

        void setLineNumber(int const lineNumber);

        void setNumberOfNodeLines(int const numberOfNodeLines);

    private:
        int         _lineNumber;
        int         _numberOfNodeLines;
        RTextNode * _parent;
        std::vector< RTextNode * > _children;
    };

    class Parser
    {
    public:
        Parser();

        enum TokenType
        {
            TokenType_Space,
            TokenType_Comment,
            TokenType_Notation,
            TokenType_Reference,
            TokenType_Float,
            TokenType_Integer,
            TokenType_QuotedString,
            TokenType_Boolean,
            TokenType_Label,
            TokenType_Identifier,
            TokenType_RightBracket,
            TokenType_LeftBracket,
            TokenType_RightAngleBracket,
            TokenType_LeftAngleBracket,
            TokenType_Comma,
            TokenType_Template,
            TokenType_Error,
            TokenType_NewLine,
            TokenType_Max_Number,
            TokenType_Unknown
        };

        RTextNode * CreateRTextNodeTree(std::vector<char> & file);
    private:
        struct InternalTokenType
        {
            std::string _context;
            unsigned    _position;
            unsigned    _line;
        };

        int _currentLineNumber;
        unsigned int _currentPosition;

        static const std::regex REGEX_MAP[];

        std::string Trim(const std::string &s)const;

        bool IsLineExtended(std::string const & line)const;

        bool LookNextToken(TokenType const type, std::string const line)const;

        InternalTokenType GetNextToken(TokenType const type, std::string const line);
    };

    inline std::string Parser::Trim(const std::string &s)const
    {
        auto  wsfront = std::find_if_not(s.begin(), s.end(), [](int c){return ::isspace(c); });
        return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return ::isspace(c); }).base());
    }

    inline bool Parser::IsLineExtended(std::string const & line)const
    {
        if (line.empty())
        {
            return false;
        }
        else
        {
            auto const aTrimmed = Trim(line);
            char const c        = aTrimmed.back();
            return (c == ',' || c == '[' || c == '\\');
        }
    }
}

#endif //#ifndef RTEXT_PARSER_H__
