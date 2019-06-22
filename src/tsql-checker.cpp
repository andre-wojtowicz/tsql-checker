#include "antlr4-runtime.h"

#include "TSqlLexer.h"
#include "TSqlParser.h"
#include "CaseChangingCharStream.h"

#include <iostream>

std::ofstream t_sw;
std::ofstream g_sw;
std::vector<std::string> rule_names;

void explore_tree(antlr4::tree::ParseTree *ctx);

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    std::ifstream stream(argv[1]);

    if (!stream.is_open())
        return 2;

    antlr4::ANTLRInputStream input(stream);
    CaseChangingCharStream upper(&input, true);
    TSqlLexer lexer((antlr4::CharStream*)(&upper));
    antlr4::CommonTokenStream tokens((antlr4::TokenSource*)(&lexer));
    TSqlParser parser((antlr4::TokenStream*)(&tokens));

    antlr4::tree::ParseTree *tree = parser.tsql_file();
    
    std::string fn(argv[1]);
    std::string fb = fn.substr(0, fn.find_last_of("."));

    std::string file_tokens_name  = fb + ".tokens",
                file_grammar_name = fb + ".grammar";

    t_sw = std::ofstream(file_tokens_name);
    g_sw = std::ofstream(file_grammar_name);
    
    rule_names = parser.getRuleNames();

    explore_tree(tree);
}

void explore_tree(antlr4::tree::ParseTree *ctx)
{
    if (antlr4::tree::TerminalNodeImpl *ptr = dynamic_cast<antlr4::tree::TerminalNodeImpl*>(ctx))
    {
        t_sw << ctx->getText() << std::endl;
    }

    if (antlr4::RuleContext *ptr = dynamic_cast<antlr4::RuleContext*>(ctx))
    {
        std::string rule_name = rule_names[ptr->getRuleIndex()];
    
        g_sw << rule_name << std::endl;
    }

    for (int i = 0; i < ctx->children.size(); i++)
    {
        antlr4::tree::ParseTree *child = ctx->children[i];

        explore_tree(child);
    }
}