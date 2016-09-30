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
          std::regex("^\\]"),
          std::regex("^\\["),
          std::regex("^\\}"),
          std::regex("^\\{"),
          std::regex("^,"),
          std::regex("^(?:<%((?:(?!%>).)*)%>|<([^>]*)>)"),
          std::regex("^[\\S+]"),
          std::regex("^\\r|\\n|\\r\\n")
    };

    RTextNode::RTextNode(int const lineNumber, int const numberOfNodeLines, RTextNode * parent) :
        _lineNumber(lineNumber),
        _numberOfNodeLines(numberOfNodeLines),
        _parent(parent)
    {
    }

    int RTextNode::getLineNumber()const
    {
        return _lineNumber;
    }

    int RTextNode::getNumberOfNodeLines()const
    {
        return _numberOfNodeLines;
    }

    void RTextNode::setLineNumber(int const lineNumber)
    {
        _lineNumber = lineNumber;
    }

    void RTextNode::setNumberOfNodeLines(int const numberOfNodeLines)
    {
        _numberOfNodeLines = numberOfNodeLines;
    }

    Parser::Parser() :
        _currentLineNumber(0U),
        _currentPosition(0U)
    {
    }

    bool Parser::LookNextToken(TokenType const type, std::string const line)const
    {
        return std::regex_match(line, REGEX_MAP[type]);
    }

    Parser::InternalTokenType Parser::GetNextToken(TokenType const type, std::string const line)
    {
        std::smatch sm;
        std::regex_match(line.begin() + _currentPosition, line.end(), sm, REGEX_MAP[type]);
        
        auto t = InternalTokenType{ sm[0], _currentPosition, _currentLineNumber };

        _currentPosition += t._context.length();

        return t;
    }

    RTextNode * Parser::CreateRTextNodeTree(std::vector<char> & file)
    {
        std::string line;

        auto rootNode = new RTextNode(0, 0);
        auto currentTokenType = TokenType_Unknown;

        for (auto c : file)
        {

        }

        return rootNode;
    }
}
