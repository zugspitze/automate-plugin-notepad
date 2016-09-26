#ifndef RTEXT_PARSER_H__
#define RTEXT_PARSER_H__

#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <ctype.h>

namespace RText
{
    class Parser
    {
    public:
        Parser(std::vector< std::string> fileLines);

        Parser(std::istringstream fileLines);

        class RTextNode
        {
        public:
            RTextNode(int const lineNumber, int const numberOfNodeLines);

            int getLineNumber()const;

            int getNumberOfNodeLines()const;

            void setLineNumber(int const lineNumber);

            void setNumberOfNodeLines(int const numberOfNodeLines);

        private:
            int _lineNumber;
            int _numberOfNodeLines;
        };
    private:
        enum Token
        {
            Token_Space,
            Token_Comment,
            Token_Notation,
            Token_Reference,
            Token_Float,
            Token_Integer,
            Token_QuotedString,
            Token_Boolean,
            Token_Label,
            Token_Identifier,
            Token_RightBracket,
            Token_LeftBracket,
            Token_RightAngleBracket,
            Token_LeftAngleBracket,
            Token_Comma,
            Token_Template,
            Token_Error,
            Token_NewLine,
            Token_Max_Number
        };

        static const std::regex REGEX_MAP[];

        std::vector< std::string > JoinLines(std::vector< std::string> const & fileLines, std::vector< std::string> & joinedLines)const;

        std::string Trim(const std::string &s)const;

        bool isLineExtended(std::string const & line)const;
    };

    inline std::string Parser::Trim(const std::string &s)const
    {
        auto  wsfront = std::find_if_not(s.begin(), s.end(), [](int c){return ::isspace(c); });
        return std::string(wsfront, std::find_if_not(s.rbegin(), std::string::const_reverse_iterator(wsfront), [](int c){return ::isspace(c); }).base());
    }

    inline bool Parser::isLineExtended(std::string const & line)const
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
