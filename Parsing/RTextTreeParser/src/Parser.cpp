#include "Parser.h"

namespace RText
{
    const std::regex Parser::REGEX_MAP[] = {
        std::regex("^[ \\t]+"),
        std::regex("^#.*"),
        std::regex("^@.*"),
        std::regex("^\\w*(?:[/]\\w*)+"),
        std::regex("^[-+]?\\d+\\.\\d+(?:e[+-]\\d+)?\\b"),
        std::regex("^(?:0x[0-9a-f]+|[-+]?\\\\d+)\\b"),
        std::regex("^(""|')(?:\\\1|.)*?\\\\1"),
        std::regex("^(?:true|false)\\b"),
        std::regex("^\\w+:"),
        std::regex("^[a-z_]\\w*(?=\\s*[^:]|)"),
        std::regex("^]"),
        std::regex("^\\["),
        std::regex("^}"),
        std::regex("^{"),
        std::regex("^,"),
        std::regex("^(?:<%((?:(?!%>).)*)%>|<([^>]*)>)"),
        std::regex("^[\\S+]"),
        std::regex("^\\r|\\n|\\r\\n")
    };

    Parser::RTextNode::RTextNode(int const lineNumber, int const numberOfNodeLines) : 
        _lineNumber(lineNumber),
        _numberOfNodeLines(numberOfNodeLines)
    {

    }

    int Parser::RTextNode::getLineNumber()const
    {
        return _lineNumber;
    }

    int Parser::RTextNode::getNumberOfNodeLines()const
    {
        return _numberOfNodeLines;
    }

    void Parser::RTextNode::setLineNumber(int const lineNumber)
    {
        _lineNumber = lineNumber;
    }

    void Parser::RTextNode::setNumberOfNodeLines(int const numberOfNodeLines)
    {
        _numberOfNodeLines = numberOfNodeLines;
    }

    Parser::Parser(std::vector< std::string> fileLines)
    {
        std::vector<std::string> aJoinedLines(fileLines.size());
        
        JoinLines(fileLines, aJoinedLines);
    }

    Parser::Parser(std::istringstream fileLines)
    {

    }

    std::vector< std::string > Parser::JoinLines(std::vector< std::string> const & fileLines, std::vector< std::string> & joinedLines)const
    {
        bool aIsBroken    = false;
        int aCurrentIndex = 0;
        int count         = fileLines.size();

        for (auto & line : fileLines)
        {
            --count;
            auto trimmed = Trim(line);
            bool aWasBroken = aIsBroken;

            if (!trimmed.empty())
            {
                if (trimmed[0] == '@' || trimmed[0] == '#')
                {
                    continue;
                }
                //need to check if "previous joined line" is also a label...just check last line - it's already joined
                bool isPreviousLineLabel = (aCurrentIndex >= 0) && (joinedLines[aCurrentIndex] != null) && COMMAND_LABEL_REGEX.Match((joinedLines[aCurrentIndex].ToString())).Success;
                aIsBroken = !isPreviousLineLabel && ((trimmed.Last() == '[' && !COMMAND_LABEL_REGEX.Match(trimmed).Success) || trimmed.Last() == ',' || trimmed.Last() == '\\');
                //handle closing bracket after last element
                if (trimmed.First() == ']' && aCurrentIndex > 0 && (aJoinedLines[aCurrentIndex] != null && aJoinedLines[aCurrentIndex].ToString().Contains('[')))
                {
                    aWasBroken = true;
                    --aCurrentIndex;
                }
            }
        }
    }
}
