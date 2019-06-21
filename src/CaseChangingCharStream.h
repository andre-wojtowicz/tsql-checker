/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */
#ifndef CASECHANGINGCHARSTREAM_H
#define CASECHANGINGCHARSTREAM_H

#include "antlr4-runtime.h"
    /// <summary>
    /// This class supports case-insensitive lexing by wrapping an existing
    /// <see cref="ICharStream"/> and forcing the lexer to see either upper or
    /// lowercase characters. Grammar literals should then be either upper or
    /// lower case such as 'BEGIN' or 'begin'. The text of the character
    /// stream is unaffected. Example: input 'BeGiN' would match lexer rule
    /// 'BEGIN' if constructor parameter upper=true but getText() would return
    /// 'BeGiN'.
    /// </summary>
class ANTLR4CPP_PUBLIC CaseChangingCharStream : antlr4::CharStream
{
    private:
        antlr4::CharStream *stream;
        bool upper;

    public:
        /// <summary>
        /// Constructs a new CaseChangingCharStream wrapping the given <paramref name="stream"/> forcing
        /// all characters to upper case or lower case.
        /// </summary>
        /// <param name="stream">The stream to wrap.</param>
        /// <param name="upper">If true force each symbol to upper case, otherwise force to lower.</param>
        CaseChangingCharStream(antlr4::CharStream *stream, bool upper);

        size_t index();

        size_t size();

        std::string getSourceName() const;

        void consume();

        std::string getText(const antlr4::misc::Interval &interval);

        std::string toString() const;

        size_t LA(ssize_t i);

        ssize_t mark();

        void release(ssize_t marker);

        void seek(size_t index);  
};

#endif
